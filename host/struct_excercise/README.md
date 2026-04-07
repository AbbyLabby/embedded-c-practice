# struct_excercise

Explores struct memory layout and padding by modeling a communication packet.

## What it does

Defines a `struct` representing a data packet with the following fields:

| Field | Type | Size |
|---|---|---|
| `crc` | `uint8_t` | 1 byte |
| `status` | `uint8_t` | 1 byte |
| `payload` | `uint16_t` | 2 bytes |
| ... | ... | ... |

Prints the size of the struct using `sizeof` to observe compiler padding and alignment behavior.

## Concepts

- Struct declaration and member access
- Memory alignment and padding in C structs
- `sizeof` on struct types
- Difference between struct layout vs. bitfield layout (compare with `struct_excercise_bitfield`)

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
