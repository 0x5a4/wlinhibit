{
  description = "simple, stupid idle inhibitor for wayland";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
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
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            clang
            wayland
            wayland-protocols
            meson
            ninja
            pkg-config
            wayland-scanner
          ];
        };

        packages.default = pkgs.stdenv.mkDerivation {
          pname = "wlinhibit";
          version = "0.1.2";
          src = self;
          
          buildInputs = with pkgs; [
            wayland
            wayland-protocols
          ];

          strictDeps = true;

          nativeBuildInputs = with pkgs; [
            meson
            ninja
            pkg-config
            wayland-scanner
          ];
        };

        checks.build = packages.default;

        apps.default = flake-utils.lib.mkApp {
          drv = packages.default;
        };
      }
    );
}
