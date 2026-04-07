# Hello_World (STM32)

The first bare-metal STM32 program — prints "Hello World" and C data type sizes via semihosting.

## What it does

Prints the following to the debug console via semihosting (OpenOCD / ST-Link):

```
Hello World!
Size of Char: 1
Size of Int: 4
Size of Long: 4
Size of Long Long: 8
Size of Double: 8
```

Then loops forever.

## Concepts

- Minimal STM32 bare-metal project structure
- `printf` output via semihosting on ARM Cortex-M4
- `sizeof` operator — comparing type sizes on ARM vs. x86
- Startup code and linker script basics

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD with semihosting enabled
