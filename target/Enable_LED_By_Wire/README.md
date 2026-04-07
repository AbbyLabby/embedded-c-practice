# Enable_LED_By_Wire (STM32)

Controls the LED on PD12 with a physical button (wire) connected to PA0 — direct register access.

## What it does

1. Enables RCC clocks for GPIOD (LED) and GPIOA (button input).
2. Configures PD12 as output and PA0 as input.
3. In the main loop, reads PA0 input state:
   - If PA0 is HIGH → turns LED (PD12) ON.
   - If PA0 is LOW → turns LED (PD12) OFF.

```c
inputData = *pPortAInpReg & 0x01;
if (inputData == 1)
    *pPortDOutReg |= (1 << 12);
else
    *pPortDOutReg &= ~(1 << 12);
```

## Concepts

- Reading GPIO input via IDR register
- GPIO input mode configuration (MODER = 00)
- Using `volatile const *const` pointers for register access
- Polling-based input reading

## Hardware

- **Board:** STM32F4 Discovery
- **LED:** PD12 | **Button/wire:** PA0
- **Debug:** ST-Link / SWD
