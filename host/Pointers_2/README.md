# Pointers_2

Demonstrates pointer arithmetic — how incrementing a pointer advances the address by the size of the pointed-to type.

## What it does

An `int*` pointer is initialized to the address of a `long long int` global variable (`0xFFFEABCD11112345`). The pointer is then incremented by 1 (`pAddress += 1`), which advances the address by `sizeof(int)` = 4 bytes, and the value at the new address is printed.

This shows the upper 32 bits of the 64-bit variable on a little-endian system.

## Concepts

- Pointer arithmetic: `p + 1` moves by `sizeof(*p)` bytes
- Difference between byte offset and type-based offset
- Practical view into memory layout (little-endian)

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
