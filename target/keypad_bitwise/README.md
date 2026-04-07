# keypad_bitwise (STM32)

Same 4×4 matrix keypad scanner as `keypad`, reimplemented using raw bitwise operations instead of bitfield structs.

## What it does

Identical keypad scanning logic (GPIOD PD0–PD7), but all register access is done via raw `uint32_t*` pointers and bitwise operators:

```c
*pGpioDOutputRegister &= ~(1 << 0);  // drive row 0 LOW
// read columns...
*pGpioDOutputRegister |= (1 << 0);   // restore row 0 HIGH
```

## Key takeaway

Comparing this project with `keypad` shows the trade-off between raw bitwise manipulation (explicit, lower-level) and struct bitfield abstraction (more readable, self-documenting). Both compile to nearly identical machine code.

## Concepts

- Raw bitwise register manipulation
- Row-by-row keypad scanning
- GPIO pull-up configuration via PUPDR register
- Side-by-side comparison with struct-based approach

## Hardware

- **Board:** STM32F4 Discovery
- **Keypad:** 4×4 matrix connected to **GPIOD PD0–PD7**
- **Debug:** ST-Link / SWD with semihosting
