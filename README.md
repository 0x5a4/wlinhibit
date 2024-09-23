# wlinhibit

**Notice:** In hyprland 0.40, [this](https://github.com/hyprwm/Hyprland/issues/5878) issue breaks this app.
Fixed in later versions.

`wlinhibit` is an extremely simple program to prevent your wayland compositor from going idle. if it runs idle inhibit is active, if not not. its that simple.

_(Your compositor needs to support idle-inhibit-unstable-v1.xml, most of them do. See [here](https://wayland.app/protocols/idle-inhibit-unstable-v1#compositor-support))_

## Installation

Get it from:
- [Nixpkgs Unstable](https://search.nixos.org/packages?channel=unstable&show=wlinhibit)
- [My Gentoo Overlay](https://github.com/0x5a4/ruhtra/tree/main/app-misc/wlinhibit)
- [The AUR](https://aur.archlinux.org/packages/wlinhibit)

## Usage

You will probably want to setup a keybind that runs something like

```
killall wlinhibit || wlinhibit
```

## Building

```
nix build
```

or the old fashioned way

```
meson setup build
cd build
meson install
```
