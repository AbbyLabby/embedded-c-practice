# Embedded C / STM32 Practice Projects

A collection of C programming exercises completed as part of an Embedded Systems course focused on STM32 microcontrollers. The workspace is split into two environments: **host** (PC-based C programs) and **target** (bare-metal STM32 firmware).

## Repository Structure

```
.
├── host/       # C programs compiled and run on a PC (x86/x64)
└── target/     # Bare-metal C firmware for STM32F4xx (ARM Cortex-M4)
```

---

## Host Projects (PC / x86)

These programs are standard C applications developed in STM32CubeIDE's host toolchain. They cover fundamental C concepts and are run directly on the development machine.

| Project | Description |
|---|---|
| [TestProject](host/TestProject/) | Hello World — first C program |
| [IF_test](host/IF_test/) | If/else: voter eligibility checker |
| [While_exc](host/While_exc/) | While loop: print numbers up to N |
| [Even_Or_Odd](host/Even_Or_Odd/) | Bitwise check: even or odd number |
| [Grater_test](host/Grater_test/) | Comparison of two integers |
| [Function_Test](host/Function_Test/) | Functions: average of 3 numbers |
| [Math](host/Math/) | Custom math library (add, sub, mul, div) |
| [Geometry_exec](host/Geometry_exec/) | Geometry area calculator (5 shapes) |
| [Tax_payable](host/Tax_payable/) | US income tax bracket calculator |
| [array](host/array/) | Arrays: store and print byte values in hex |
| [Pointer](host/Pointer/) | Pointers: basic read/write via pointer |
| [Pointers_1](host/Pointers_1/) | Pointer types: reading a 64-bit variable with different widths |
| [Pointers_2](host/Pointers_2/) | Pointer arithmetic on a 64-bit variable |
| [swapping_arrays](host/swapping_arrays/) | Swap two user-defined arrays |
| [bitwise](host/bitwise/) | Bitwise operators: AND, OR, XOR, NOT |
| [Clear_bits](host/Clear_bits/) | Clear specific bits using AND mask |
| [Setting_of_Bits](host/Setting_of_Bits/) | Set specific bits using OR mask |
| [Asceii_print](host/Asceii_print/) | Read 6 characters, print their ASCII values |
| [string_exec](host/string_exec/) | Student record management system (strings & structs) |
| [struct_excercise](host/struct_excercise/) | Struct memory layout (CRC/status/payload packet) |
| [struct_excercise_bitfield](host/struct_excercise_bitfield/) | Same packet struct using bitfields |
| [struct_excercise_union](host/struct_excercise_union/) | Same packet struct using union |
| [MCU1-Debugging](host/MCU1-Debugging/) | Bubble sort & insertion sort (debuggable host version) |

---

## Target Projects (STM32F4xx — Bare-Metal)

These projects are compiled for ARM Cortex-M4 and flashed to an STM32F4 Discovery board (or equivalent). All hardware interaction is done via direct register manipulation — no HAL or CMSIS abstraction layer.

| Project | Description |
|---|---|
| [Hello_World](target/Hello_World/) | First STM32 program — printf data type sizes via semihosting |
| [Add](target/Add/) | Add two global integers, print result via semihosting |
| [structs](target/structs/) | Struct memory layout on ARM Cortex-M4 |
| [struct_pointers](target/struct_pointers/) | Accessing and modifying struct members via pointer |
| [structs_exervise](target/structs_exervise/) | Parse a 32-bit raw packet into a struct |
| [Enable_LED](target/Enable_LED/) | Blink LED on PD12 via direct GPIO register access |
| [Enable_LED_By_Wire](target/Enable_LED_By_Wire/) | LED on PD12 controlled by button input on PA0 |
| [Enable_LED_bitfields](target/Enable_LED_bitfields/) | Same LED blink but using bitfield struct register abstractions |
| [Clock](target/Clock/) | Direct register access: set ADC SCAN bit via CR1 |
| [MCU1-Clock-Measurment](target/MCU1-Clock-Measurment/) | Output HSI clock on MCO1 (PA8) for oscilloscope measurement |
| [MCU1-Clock-Measurment-HSE](target/MCU1-Clock-Measurment-HSE/) | Output HSE clock on MCO1 (PA8) |
| [keypad](target/keypad/) | 4×4 matrix keypad scanner using bitfield register structs |
| [keypad_bitwise](target/keypad_bitwise/) | Same keypad scanner using raw bitwise operations |
| [Button_ISR](target/Button_ISR/) | External interrupt (EXTI0) on PA0: count button presses |
| [MCU1-SortingsDebug](target/MCU1-SortingsDebug/) | Bubble sort & insertion sort running on STM32 with debug |

---

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx) or compatible STM32F4xx board
- **IDE:** STM32CubeIDE
- **Debug:** ST-Link / SWD, semihosting via ITM/OpenOCD

## Topics Covered

- C fundamentals: control flow, functions, arrays, strings
- Pointers and pointer arithmetic
- Structs, bitfields, unions
- Bitwise operations and bit manipulation
- Bare-metal GPIO programming (no HAL)
- Clock configuration (RCC, HSI, HSE, MCO1)
- Interrupts (EXTI, NVIC)
- Sorting algorithms (bubble sort, insertion sort)
- Debugging on embedded targets

---

*Practice projects from an Embedded C / STM32 course.*
