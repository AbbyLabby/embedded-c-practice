# MCU1-SortingsDebug (STM32)

Bubble sort and insertion sort running on the STM32 target — used to practice embedded debugging techniques.

## What it does

1. Fills an integer array with random values using `rand()`.
2. Displays the unsorted array via semihosting.
3. Runs **bubble sort** and **insertion sort** on separate arrays.
4. Displays sorted results.

The project is designed for debugging: set breakpoints in `swap_numbers()` or inside the sort loops to inspect array state step-by-step in STM32CubeIDE.

## Concepts

- Running algorithmically complex code on a bare-metal target
- Embedded debugging: breakpoints, step-in/step-over, watch expressions
- Memory view inspection of arrays on the target
- `rand()` + `stdlib.h` on ARM Cortex-M4
- `volatile` keyword in swap to prevent compiler optimization of debug code

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD with semihosting (semihosting for `printf`)
