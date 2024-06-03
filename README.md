# wlinhibit

**Notice:** As of hyprland 0.40, [this](https://github.com/hyprwm/Hyprland/issues/5878) issue breaks this app.

`wlinhibit` is an extremely simple program to prevent your wayland compositor from going idle.  
if it runs idle inhibit is active, if not not. its that simple.

_(Your compositor needs to support idle-inhibit-unstable-v1.xml, most of them do)_

## Installation
Available in nixpkgs unstable!

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
