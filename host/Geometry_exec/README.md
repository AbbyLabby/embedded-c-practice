# Geometry_exec

An interactive geometry area calculator supporting five shapes.

## What it does

Displays a menu where the user enters a letter code to select a shape, then inputs the required dimensions. The program calculates and prints the area.

| Code | Shape | Formula |
|---|---|---|
| `t` | Triangle | `(base × height) / 2` |
| `z` | Trapezoid | `((a + b) / 2) × height` |
| `c` | Circle | `π × radius` |
| `s` | Square | `side²` |
| `r` | Rectangle | `length × width` |

## Concepts

- `switch / case` statement
- Functions with `float` return types
- Input validation with `scanf` return value check
- Multi-branch program flow

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
