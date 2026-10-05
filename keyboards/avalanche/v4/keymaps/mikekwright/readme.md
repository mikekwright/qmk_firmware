# mikekwright

Avalanche v4 (Pro Micro) keymap that follows the `mikekwright` Lily58 layers. The extra Avalanche keys are used
for `Caps`/`Del` on the outer edges of the home row, `Home`/`End` and `PgDn`/`PgUp` on the inner column, and
`Play`/`Mute` on the outer thumb positions. The rotary encoders keep the keyboard-level behaviour: volume on the
left, page up/down on the right.

`QK_BOOT` is on the ADJUST layer (hold LOWER and RAISE together, press the top-left key).

## Build

```sh
qmk compile -kb avalanche/v4 -km mikekwright
```

With the Nix workflow in this repository:

```sh
nix develop -c setup-keyboard avalanche
nix develop -c build-keyboard avalanche
nix develop -c flash-keyboard avalanche
```

The flash command targets the stock Pro Micro Caterina bootloader. Flash the same firmware to both halves and plug
the left half into the computer. For an Elite-C controller, add `-e BOOTLOADER=atmel-dfu` to the `qmk` commands.
