# Enable_LED (STM32)

Blinks the onboard LED (PD12) using direct GPIO register access — no HAL, no CMSIS.

## What it does

1. Enables the RCC clock for GPIOD (`AHB1ENR`, bit 3).
2. Configures PD12 as a push-pull output (`GPIOD MODER`).
3. Toggles PD12 HIGH/LOW in an infinite loop with a software delay.

```c
*pPortDOutReg |= (1 << 12);   // LED ON
for(int i = 0; i <= 1000000; i++);
*pPortDOutReg &= ~(1 << 12);  // LED OFF
```

## Concepts

- RCC peripheral clock enable via direct register write
- GPIO mode configuration (MODER register)
- GPIO output via ODR register
- Software delay loop
- Memory-mapped I/O: accessing hardware registers as `uint32_t*`

## Hardware

- **Board:** STM32F4 Discovery
- **LED:** Green LED on **PD12**
- **Debug:** ST-Link / SWD
