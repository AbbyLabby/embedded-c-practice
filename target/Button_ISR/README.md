# Button_ISR (STM32)

Counts button presses using an external interrupt (EXTI0) on PA0 — no polling.

## What it does

1. Configures PA0 as input and enables EXTI0 (rising-edge trigger) via the SYSCFG/EXTI registers.
2. Enables EXTI0 interrupt in the NVIC.
3. In the `EXTI0_IRQHandler` ISR, sets a `volatile` flag `g_button_pressed = 1` and clears the pending bit.
4. The main loop checks the flag (with the interrupt temporarily masked for atomicity), increments a counter, and prints the count via semihosting.

## Concepts

- External interrupt configuration: EXTI mask, edge control, NVIC enable
- ISR (Interrupt Service Routine) definition on Cortex-M4
- `volatile` flag for shared variable between ISR and main code
- Interrupt masking for safe flag read in main loop
- Button debounce via software delay

## Hardware

- **Board:** STM32F4 Discovery
- **Button:** User button on **PA0**
- **Debug:** ST-Link / SWD with semihosting
