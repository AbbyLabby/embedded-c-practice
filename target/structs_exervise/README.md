# structs_exervise (STM32)

Parses a 32-bit raw packet value into individual fields using a struct.

## What it does

Reads a 32-bit hex value from the user, then extracts and stores each field (CRC, status, payload, battery, sensor, address, etc.) into a `Packet_t` struct using bitmasking inside `CollectPacketData()`. Prints all parsed fields via `PrintPacketData()`.

## Concepts

- Manual bit extraction from a raw `uint32_t` using `&` and `>>` operations
- Populating a struct from a raw data word
- Struct design for protocol/packet representation
- Practical exercise for UART/SPI frame parsing in embedded systems

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD with semihosting
