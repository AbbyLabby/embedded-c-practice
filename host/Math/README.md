# Math

A custom math library with a separate header file demonstrating multi-file C projects.

## What it does

Implements and calls four math operations via a dedicated `math.h` / `math.c` library:

| Function | Operation |
|---|---|
| `math_sum(a, b)` | Addition |
| `math_sub(a, b)` | Subtraction |
| `math_mul(a, b)` | Multiplication (returns `long long`) |
| `math_div(a, b)` | Division (returns `float`) |

## Concepts

- Separate header (`.h`) and implementation (`.c`) files
- Function declarations and definitions
- Mixed return types (`int`, `long long`, `float`)

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
