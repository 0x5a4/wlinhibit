project('wlinhibit', 'c')

wl_dep = dependency('wayland-client')
wl_mod = import('unstable-wayland')

xml = wl_mod.find_protocol('idle-inhibit', state: 'unstable', version: 1)
idle_inhibit = wl_mod.scan_xml(xml)

executable('wlinhibit', 'wlinhibit.c', idle_inhibit, dependencies : wl_dep, install: true)
