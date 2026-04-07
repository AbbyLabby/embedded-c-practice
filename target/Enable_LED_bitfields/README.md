# Enable_LED_bitfields (STM32)

Same LED blink as `Enable_LED`, but implemented using bitfield structs to abstract register access.

## What it does

Instead of raw bit shifting, peripheral registers are represented as typed bitfield structs defined in `main.h`. The LED blink on PD12 is controlled through struct member assignments:

```c
pRccRegister->gpioD_en = CLOCK_ENABLE;
pPortDModeRegister->moder_12 = MODE_CONF_OUTPUT;
pPortDOutRegister->odr_12 = PIN_STATE_HIGH;
```

## Key takeaway

Bitfield structs make register access more readable and less error-prone compared to raw bit shifting. This is the foundation of how CMSIS device headers define peripheral registers.

## Concepts

- Bitfield struct-based register abstraction
- `typedef struct` with bitfield members for hardware registers
- `volatile` qualifier for hardware-mapped pointers
- Comparing raw-register vs. struct approaches to the same operation

## Hardware

- **Board:** STM32F4 Discovery
- **LED:** Green LED on **PD12**
- **Debug:** ST-Link / SWD
