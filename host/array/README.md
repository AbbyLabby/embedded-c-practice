# array

Introduction to C arrays — stores byte values and prints them in hexadecimal.

## What it does

Declares a `uint8_t` array of 3 bytes initialized to `0xFF`, calculates its size at runtime using `sizeof`, and prints each element in hex format using a helper function `print_array`.

## Key concept

```c
uint32_t arraySize = sizeof(someData) / sizeof(someData[0]);
```

This idiom calculates the number of elements without hard-coding the size.

## Concepts

- Fixed-size arrays with `uint8_t`
- `sizeof` operator for array length
- Passing arrays to functions via pointer
- Hex output with `printf("%x", ...)`

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
