# keypad (STM32)

4×4 matrix keypad scanner using bitfield struct register abstractions on GPIOD.

## What it does

Drives a 4×4 matrix keypad connected to GPIOD:

- **Rows (output):** PD0–PD3 — driven LOW one at a time
- **Columns (input):** PD4–PD7 — read to detect which key is pressed

The `CheckRow(row)` function scans each column while the corresponding row is driven LOW. When a key press is detected, it prints the key identifier via semihosting.

Peripheral registers (RCC, GPIO MODER, ODR, IDR, PUPDR) are accessed through typed bitfield structs defined in `main.h`.

## Concepts

- Matrix keypad scanning algorithm (row-by-row)
- GPIO output + input + pull-up/pull-down configuration
- Bitfield struct register abstraction (same pattern as `Enable_LED_bitfields`)
- `volatile` struct pointers for hardware registers

## Hardware

- **Board:** STM32F4 Discovery
- **Keypad:** 4×4 matrix connected to **GPIOD PD0–PD7**
- **Debug:** ST-Link / SWD with semihosting
