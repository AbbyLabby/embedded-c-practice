# Clear_bits

Clears specific bits of a number using a bitwise AND mask.

## What it does

Reads an integer from the user and applies the mask `143` (`0x8F` = `1000 1111b`) using bitwise AND, which clears bits 4, 5, and 6 while keeping all other bits unchanged.

```c
uint32_t result = val1 & 143;  // mask: 0b10001111
```

## Concepts

- Bit clearing with `& mask`
- Choosing a mask to target specific bit positions
- `uint32_t` for 32-bit unsigned arithmetic
- A fundamental register manipulation technique used in embedded C

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
