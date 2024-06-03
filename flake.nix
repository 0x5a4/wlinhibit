{
  description = "simple, stupid idle inhibitor for wayland";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
      in rec {
        devShell = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            clang
            meson
            pkg-config
            ninja
            wayland
            wayland-protocols
          ];
        };

        defaultPackage = pkgs.stdenv.mkDerivation {
          name = "wlinhibit";
          src = self;

          nativeBuildInputs = with pkgs; [
            clang
            meson
            pkg-config
            ninja
            wayland
            wayland-protocols
          ];
        };

        defaultApp = flake-utils.lib.mkApp {
          drv = defaultPackage;
          exePath = "/bin/wlinhibit";
        };
      }
    );
}
