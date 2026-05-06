{
  description = "QMK firmware development shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };

        build-keyboard = pkgs.writeShellApplication {
          name = "build-keyboard";
          runtimeInputs = [ pkgs.qmk ];
          text = ''
            set -euo pipefail

            keyboard="''${1:-}"

            case "$keyboard" in
              corne)
                exec qmk compile -kb crkbd/rev1 -km mikekwright_crkbd -e BOOTLOADER=atmel-dfu
                ;;
              "")
                echo "Usage: build-keyboard <keyboard>" >&2
                echo "Available keyboards: corne" >&2
                exit 1
                ;;
              *)
                echo "Unknown keyboard: $keyboard" >&2
                echo "Available keyboards: corne" >&2
                exit 1
                ;;
            esac
          '';
        };

        flash-keyboard = pkgs.writeShellApplication {
          name = "flash-keyboard";
          runtimeInputs = [ pkgs.qmk ];
          text = ''
            set -euo pipefail

            keyboard="''${1:-}"

            case "$keyboard" in
              corne)
                # Corne using the sea micro so uses dfu to flash
                exec qmk flash -kb crkbd/rev1 -km mikekwright_crkbd -e BOOTLOADER=atmel-dfu -bl dfu
                ;;
              "")
                echo "Usage: build-keyboard <keyboard>" >&2
                echo "Available keyboards: corne" >&2
                exit 1
                ;;
              *)
                echo "Unknown keyboard: $keyboard" >&2
                echo "Available keyboards: corne" >&2
                exit 1
                ;;
            esac
          '';
        };

      in {
        packages.build-keyboard = build-keyboard;

        apps = {
          build-keyboard = {
            type = "app";
            program = "${build-keyboard}/bin/build-keyboard";
          };

          flash-keyboard = {
            type = "app";
            program = "${flash-keyboard}/bin/flash-keyboard";
          };
        };

        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.qmk
            pkgs.git
            pkgs.gnumake
            pkgs.diffutils
            pkgs.dos2unix
            pkgs.avrdude
            pkgs.dfu-programmer
            pkgs.dfu-util
            pkgs.pkgsCross.avr.buildPackages.gcc
            pkgs.pkgsCross.arm-embedded.buildPackages.gcc
            build-keyboard
          ];

          MAKE = "make";
        };
      });
}
