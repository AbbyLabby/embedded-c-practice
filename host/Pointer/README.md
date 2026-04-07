# Pointer

Introduction to C pointers — reading and writing a variable through its memory address.

## What it does

1. Declares a `char` variable and prints its address and value.
2. Stores the address in a pointer (`char *var_address`).
3. Reads the value via pointer dereference (`*var_address`).
4. Writes a new value (`65` = `'A'`) through the pointer.
5. Prints the updated variable to confirm the change.

## Concepts

- Address-of operator (`&`)
- Pointer declaration and initialization
- Pointer dereference (`*`)
- Read and write through a pointer

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
