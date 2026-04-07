# MCU1-Clock-Measurment-HSE (STM32)

Outputs the external HSE clock signal on the MCO1 pin (PA8) — same measurement setup as `MCU1-Clock-Measurment` but using the HSE oscillator.

## What it does

1. Enables the **HSE** oscillator (bit 16 of RCC CR) and waits until it is ready (HSERDY, bit 17).
2. Switches the system clock source to HSE (bit 0 of RCC CFGR).
3. Configures MCO1 to output **HSE** (bits 21–22 of RCC CFGR set to `10`).
4. Applies MCO1 prescaler of `/4`.
5. Configures PA8 as alternate function (AF0 = MCO1).

## Concepts

- HSE startup and ready-flag polling
- Switching system clock source from HSI to HSE
- MCO1 source selection and prescaler
- External crystal / clock input on STM32F4 Discovery (8 MHz HSE)

## Hardware

- **Board:** STM32F4 Discovery (8 MHz HSE crystal)
- **Measurement pin:** **PA8** (MCO1)
- **Debug:** ST-Link / SWD
