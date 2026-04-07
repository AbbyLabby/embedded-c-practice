# Setting_of_Bits

Sets specific bits of a number using a bitwise OR mask.

## What it does

Reads an integer from the user and applies the mask `144` (`0x90` = `1001 0000b`) using bitwise OR, which sets bits 4 and 7 while leaving all other bits unchanged.

```c
uint32_t result = val1 | 144;  // mask: 0b10010000
```

## Concepts

- Bit setting with `| mask`
- Complementary to `Clear_bits` — together they cover the core bit manipulation idioms
- Directly applicable to MCU peripheral register configuration

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
