# struct_excercise_union

Extends the packet struct exercise by embedding the bitfield struct inside a `union` alongside a raw `uint32_t` value.

## What it does

Wraps the bitfield struct in a `union`:

```c
union {
    Packet_t fields;
    uint32_t raw;
} Packet_u;
```

This allows the same memory to be accessed either as individual fields (via `fields`) or as a single 32-bit integer (via `raw`) — a standard pattern for register access in embedded C.

## Key takeaway

The union technique lets you both set/read individual bits through a named struct and read/write the whole register as a single value, without casting.

## Concepts

- `union` declaration and memory sharing
- Combining bitfield structs with raw-word access
- Foundation of peripheral register definition headers (e.g., CMSIS)

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
