# Clock (STM32)

Direct register access exercise: enables the SCAN mode bit in the ADC CR1 register.

## What it does

Sets bit 8 (SCAN bit) of the ADC1 CR1 register via a raw pointer:

```c
#define ADC_BASE_ADDR       0x40012000UL
#define ADC_CR1_REG_OFFSET  0x04UL

uint32_t *pAdcCr1Reg = (uint32_t*)(ADC_BASE_ADDR + ADC_CR1_REG_OFFSET);
*pAdcCr1Reg |= (1 << 8);
```

Then loops forever. The result can be verified in the STM32CubeIDE live watch or memory view.

## Concepts

- Peripheral base address + register offset addressing pattern
- `#define` macros for register addresses
- Bitwise OR to set a single bit without disturbing others
- Verifying register changes via debugger memory/peripheral view

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD
