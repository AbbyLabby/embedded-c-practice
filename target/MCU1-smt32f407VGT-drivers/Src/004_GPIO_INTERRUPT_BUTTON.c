/*
 * 004_GPIO_INTERRUPT_BUTTON.c
 *
 *  Created on: 12 черв. 2026 р.
 *      Author: Savhe
 */

#include <stdint.h>
#include "stm32f407vgt.h"
#include <string.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay(void)
{
  for(uint32_t i = 0; i < 500000 / 2; i++);
}

int main(void)
{
  GPIO_Handle_t GpioLed;
  GPIO_Handle_t GpioButton;

  memset(&GpioLed, 0, sizeof(GpioLed));
  memset(&GpioButton, 0, sizeof(GpioButton));

  GpioLed.pGPIOBaseAddr = GPIOA;
  GpioButton.pGPIOBaseAddr = GPIOB;

  GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
  GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
  GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GpioButton.GPIO_PinConfig.GPIO_PinPuPdControll = GPIO_PU;

  GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
  GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_NO_PUPD;

  GPIO_PeriClockControl(GPIOA, ENABLE);
  GPIO_PeriClockControl(GPIOB, ENABLE);

  GPIO_Init(&GpioButton);
  GPIO_Init(&GpioLed);

  //IRQ configurations
  GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_PRIO_12);
  GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

  return 0;
}

void EXTI15_10_IRQHandler(void)
{
	delay();

	GPIO_IRQHandling(GPIO_PIN_NO_12);

	GPIO_ToggleOutptPin(GPIOA, GPIO_PIN_NO_4);
}
