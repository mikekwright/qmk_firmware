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
                firmware_base="crkbd_rev1_mikekwright_crkbd"
                qmk compile -kb crkbd/rev1 -km mikekwright_crkbd -e BOOTLOADER=atmel-dfu
                cp "$firmware_base.hex" "$firmware_base-left.hex"
                cp "quantum/split_common/eeprom-lefthand.eep" "$firmware_base-left.eep"
                cp "$firmware_base.hex" "$firmware_base-right.hex"
                cp "quantum/split_common/eeprom-righthand.eep" "$firmware_base-right.eep"
                ;;
              piantor)
                qmk compile -kb beekeeb/piantor -km mikekwright
                ;;
              avalanche)
                qmk compile -kb avalanche/v4 -km mikekwright
                ;;
              lily58)
                qmk compile -kb lily58/rev1 -km mikekwright
                ;;
              "")
                echo "Usage: build-keyboard <keyboard>" >&2
                echo "Available keyboards: corne, piantor, avalanche, lily58" >&2
                exit 1
                ;;
              *)
                echo "Unknown keyboard: $keyboard" >&2
                echo "Available keyboards: corne, piantor, avalanche, lily58" >&2
                exit 1
                ;;
            esac
          '';
        };

        setup-keyboard = pkgs.writeShellApplication {
          name = "setup-keyboard";
          runtimeInputs = [ pkgs.git ];
          text = ''
            set -euo pipefail

            keyboard="''${1:-}"

            case "$keyboard" in
              corne|avalanche|lily58)
                exec git submodule update --init --recursive -- lib/lufa
                ;;
              piantor)
                exec git submodule update --init --recursive -- lib/chibios lib/chibios-contrib lib/pico-sdk
                ;;
              "")
                echo "Usage: setup-keyboard <keyboard>" >&2
                echo "Available keyboards: corne, piantor, avalanche, lily58" >&2
                exit 1
                ;;
              *)
                echo "Unknown keyboard: $keyboard" >&2
                echo "Available keyboards: corne, piantor, avalanche, lily58" >&2
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
            side="''${2:-}"

            case "$keyboard" in
              corne)
                case "$side" in
                  left)
                    exec qmk flash -kb crkbd/rev1 -km mikekwright_crkbd -e BOOTLOADER=atmel-dfu -bl dfu-split-left
                    ;;
                  right)
                    exec qmk flash -kb crkbd/rev1 -km mikekwright_crkbd -e BOOTLOADER=atmel-dfu -bl dfu-split-right
                    ;;
                  "")
                    echo "Usage: flash-keyboard corne <left|right>" >&2
                    exit 1
                    ;;
                  *)
                    echo "Unknown corne side: $side" >&2
                    echo "Usage: flash-keyboard corne <left|right>" >&2
                    exit 1
                    ;;
                esac
                ;;
              piantor)
                case "$side" in
                  left)
                    exec qmk flash -kb beekeeb/piantor -km mikekwright -bl uf2-split-left
                    ;;
                  right)
                    exec qmk flash -kb beekeeb/piantor -km mikekwright -bl uf2-split-right
                    ;;
                  "")
                    echo "Usage: flash-keyboard piantor <left|right>" >&2
                    exit 1
                    ;;
                  *)
                    echo "Unknown piantor side: $side" >&2
                    echo "Usage: flash-keyboard piantor <left|right>" >&2
                    exit 1
                    ;;
                esac
                ;;
              avalanche)
                if [ -n "$side" ]; then
                  echo "Usage: flash-keyboard avalanche" >&2
                  exit 1
                fi
                exec qmk flash -kb avalanche/v4 -km mikekwright
                ;;
              lily58)
                if [ -n "$side" ]; then
                  echo "Usage: flash-keyboard lily58" >&2
                  exit 1
                fi
                exec qmk flash -kb lily58/rev1 -km mikekwright
                ;;
              "")
                echo "Usage: flash-keyboard <keyboard> [side]" >&2
                echo "Available keyboards: corne, piantor, avalanche, lily58" >&2
                exit 1
                ;;
              *)
                echo "Unknown keyboard: $keyboard" >&2
                echo "Available keyboards: corne, piantor, avalanche, lily58" >&2
                exit 1
                ;;
            esac
          '';
        };

      in {
        packages.build-keyboard = build-keyboard;
        packages.setup-keyboard = setup-keyboard;
        packages.flash-keyboard = flash-keyboard;

        apps = {
          build-keyboard = {
            type = "app";
            program = "${build-keyboard}/bin/build-keyboard";
          };

          setup-keyboard = {
            type = "app";
            program = "${setup-keyboard}/bin/setup-keyboard";
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
            setup-keyboard
            build-keyboard
            flash-keyboard
          ];

          MAKE = "make";
        };
      });
}
