# struct_excercise_bitfield

Redefines the same data packet struct from `struct_excercise` using C bitfields to pack fields into a single `uint32_t`.

## What it does

Declares the packet struct with bitfield members:

```c
typedef struct {
    uint32_t crc     : 2;
    uint32_t status  : 1;
    uint32_t payload : 12;
    // ...
} Packet_t;
```

Prints `sizeof(Packet_t)` to compare with the plain struct version.

## Key takeaway

Bitfields pack multiple flags and small values into a single word, eliminating padding and reducing memory usage — critical for MCU register definitions.

## Concepts

- C bitfield syntax (`: N`)
- Bit packing vs. byte alignment
- Practical use case: peripheral register modeling in embedded C

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
