# mikekwright_crkbd

This keymap uses split pointing-device support on a Corne with Cirque trackpads.

## Pointing Device Setup

The keymap enables the QMK pointing-device stack and uses the Cirque Pinnacle I2C driver from `rules.mk`:

```make
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
```

The split behavior is configured in `config.h`:

```c
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED
#define POINTING_DEVICE_ROTATION_90

#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
```

This setup treats the left pad as scroll input and the right pad as cursor input. The right-side report is rotated before the two reports are combined.

## Mouse Drag Support

Mouse drag support is implemented in `keymap.c` by keeping button state in `held_mouse_buttons` and merging that state back into each combined pointing-device report.

This is important for `POINTING_DEVICE_COMBINED` because the pointing-device task rebuilds the mouse report every scan. Without reapplying the held buttons, a mouse button press can look like a click instead of a hold, which breaks click-and-drag.

The following keycodes are handled through the pointing-device report path so the button stays held until key release:

- `MY_BTN1`, `MY_BTN2`, `MY_BTN3`
- `MS_BTN1`, `MS_BTN2`, `MS_BTN3`

## Build

Examples for this keymap:

```sh
qmk compile -kb crkbd/rev1 -km mikekwright_crkbd -e BOOTLOADER=atmel-dfu
```

If you are using the local Nix workflow in this repository:

```sh
nix develop -c build-keyboard corne
```
