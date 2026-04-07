# Pointers_1

Demonstrates how different pointer types read the same memory location with different widths.

## What it does

A `long long int` global variable `g_data` is accessed using four different pointer types — `char*`, `int*`, `long long int*`, and `short*` — and the value at each address is printed in hex. This illustrates how the CPU reads 1, 2, 4, or 8 bytes starting from the same base address.

## Concepts

- Casting a variable address to different pointer types
- How pointer width affects the number of bytes read
- Little-endian memory layout (visible from the output)
- `printf` format specifiers for various integer widths

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
