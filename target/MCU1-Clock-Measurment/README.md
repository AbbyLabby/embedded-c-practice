# MCU1-Clock-Measurment (STM32)

Outputs the internal HSI clock signal on the MCO1 pin (PA8) for measurement with an oscilloscope or logic analyzer.

## What it does

1. Configures the MCO1 output (bits 21–22 of RCC CFGR) to select **HSI** (internal 16 MHz RC oscillator) — clears those bits.
2. Applies an MCO1 prescaler of `/4` (bits 24–26 of RCC CFGR).
3. Enables RCC clock for GPIOA.
4. Configures PA8 in **Alternate Function** mode (`MODER = 10`).
5. Sets PA8 to **AF0** (MCO1) in the alternate function high register.

## Concepts

- RCC clock output configuration (MCO1)
- GPIO alternate function mode configuration
- Reading the clock signal with an oscilloscope: expected ~4 MHz on PA8 (HSI 16 MHz ÷ 4)
- `#define` macros for RCC and GPIO base addresses

## Hardware

- **Board:** STM32F4 Discovery
- **Measurement pin:** **PA8** (MCO1)
- **Debug:** ST-Link / SWD
