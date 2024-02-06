# wlinhibit

`wlinhibit` is an extremely simple program to prevent your wayland compositor from going idle.  
if it runs idle inhibit is active, if not not. its that simple.

_(Your compositor needs to support idle-inhibit-unstable-v1.xml, most of them do)_

## Usage
You will propable want to setup a keybind that runs something like
```
killall wlinhibit || wlinhibit
```

## Building
```
meson setup build
cd build
meson install
```
