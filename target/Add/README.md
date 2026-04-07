# Add (STM32)

Adds two global integers on the STM32 and prints the result via semihosting. Used to verify that the build and debug environment is working correctly.

## What it does

```c
int g_data1 = -4000;
int g_data2 = 200;
result = g_data1 + g_data2;  // result = -3800
printf("Result = %d\n", result);
```

Then loops forever with `for(;;)`.

## Concepts

- Global variable placement in `.data` / `.bss` sections
- Signed integer arithmetic on ARM Cortex-M4
- Observing variables in the Memory/Expressions view in STM32CubeIDE

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD with semihosting
