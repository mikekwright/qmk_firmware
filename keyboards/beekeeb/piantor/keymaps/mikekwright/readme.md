# mikekwright

Piantor (Raspberry Pi Pico, RP2040) keymap that mirrors the `mikekwright_crkbd` Corne layers without the
Cirque trackpad code. The mouse buttons on layer 1 and the cursor keys on layer 3 use QMK mouse keys instead.

`QK_BOOT` lives on layer 3 (hold `MO(1)` then `MO(3)`, press the top-left key) so the board can be put into the
UF2 bootloader without reaching for the `BOOTSEL` button.

## Handedness

`EE_HANDS` is enabled, so each half is flashed with a side-specific UF2 and remembers which side it is. Either half
can then be plugged into the computer.

## Build

```sh
qmk compile -kb beekeeb/piantor -km mikekwright
```

With the Nix workflow in this repository:

```sh
nix develop -c setup-keyboard piantor
nix develop -c build-keyboard piantor
nix develop -c flash-keyboard piantor left
nix develop -c flash-keyboard piantor right
```

Flashing waits for the `RPI-RP2` drive. Hold `BOOTSEL` while plugging in the half you want to flash, or double tap
the reset button.
