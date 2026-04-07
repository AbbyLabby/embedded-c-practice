# Even_Or_Odd

Checks whether a given integer is even or odd using a bitwise operation.

## What it does

Reads a number from the user and uses the bitwise AND operator (`& 1`) to test the least significant bit — if it is set, the number is odd; otherwise it is even.

## Key concept

```c
if (val & 1)
    printf("number is odd\n");
else
    printf("number is even\n");
```

Using bitwise `& 1` is faster than the modulo approach `% 2` and is a common embedded-C idiom.

## Concepts

- Bitwise AND (`&`)
- Least significant bit (LSB) testing
- `uint32_t` and integer casting

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
