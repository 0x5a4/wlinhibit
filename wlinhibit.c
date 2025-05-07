#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <idle-inhibit-unstable-v1-client-protocol.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

struct wl_compositor *compositor;
struct zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
struct wl_surface *surface;
struct zwp_idle_inhibitor_v1 *idle_inhibitor;

void registry_global_handler(void *data, struct wl_registry *registry,
                             uint32_t name, const char *interface,
                             uint32_t version) {
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor =
            wl_registry_bind(registry, name, &wl_compositor_interface, 3);
    } else if (strcmp(interface, "zwp_idle_inhibit_manager_v1") == 0) {
        idle_inhibit_manager = wl_registry_bind(
            registry, name, &zwp_idle_inhibit_manager_v1_interface, 1);
    }
}

void registry_global_remove_handler(void *data, struct wl_registry *registry,
                                    uint32_t name) {
    // maybe we should handle this, but does this piece of shit app have to
    // care?
}

void shutdown(int sig) {
    // destroy the inhibitor on process exit
    zwp_idle_inhibitor_v1_destroy(idle_inhibitor);
    wl_surface_destroy(surface);
    exit(EXIT_SUCCESS);
}

const struct wl_registry_listener registry_listener = {
    .global = registry_global_handler,
    .global_remove = registry_global_remove_handler};

int main(void) {
    struct wl_display *display = wl_display_connect(NULL);

    if (!display) {
        printf("unable to aquire wayland display\n");
        return 1;
    }

    struct wl_registry *registry = wl_display_get_registry(display);
    if (!registry) {
        printf("unable to aquire wayland registry\n");
        return 1;
    }

    wl_registry_add_listener(registry, &registry_listener, NULL);

    wl_display_roundtrip(display);

    if (!compositor) {
        printf("unable to aquire wl_compositor\n");
        return 1;
    }

    if (!idle_inhibit_manager) {
        printf("unable to aquire idle inhibit manager. does your compositor "
               "support idle-inhibit-unstable-v1?\n");
        return 1;
    }

    surface = wl_compositor_create_surface(compositor);

    if (!surface) {
        printf("unable to create surface");
        return 1;
    }

    idle_inhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(
        idle_inhibit_manager, surface);

    signal(SIGINT, shutdown);
    signal(SIGTERM, shutdown);

    while (1) {
        wl_display_dispatch(display);
    }

    shutdown(0);
}
