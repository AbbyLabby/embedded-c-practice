# structs (STM32)

Explores struct memory layout and alignment on ARM Cortex-M4.

## What it does

Declares a `DataSet_t` struct with mixed types and prints each field's value:

```c
typedef struct {
    char  data1;   // 0xAA
    int   data2;   // 0xFFFFEEEE
    char  data3;   // 0x55
    short data4;   // 0xA5A5
} DataSet_t;
```

Useful for observing how the ARM compiler pads the struct to meet alignment requirements.

## Concepts

- Struct memory layout and padding on ARM
- Mixed-type structs (`char`, `int`, `short`)
- Semihosting output for verification
- Using the memory view in STM32CubeIDE to inspect struct layout

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD with semihosting
