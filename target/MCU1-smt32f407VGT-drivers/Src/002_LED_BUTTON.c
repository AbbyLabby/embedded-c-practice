/*
 * 002_LED_BUTTON.c
 *
 *  Created on: 9 черв. 2026 р.
 *      Author: Savhe
 */


#include <stdint.h>
#include "stm32f407vgt.h"

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

  GpioLed.pGPIOBaseAddr = GPIOD;
  GpioButton.pGPIOBaseAddr = GPIOA;

  GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
  GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
  GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GpioButton.GPIO_PinConfig.GPIO_PinPuPdControll = GPIO_NO_PUPD;

  GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
  GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
  GpioLed.GPIO_PinConfig.GPIO_PinPuPdControll = GPIO_PU;

  GPIO_PeriClockControl(GPIOA, ENABLE);
  GPIO_PeriClockControl(GPIOD, ENABLE);

  GPIO_Init(&GpioButton);
  GPIO_Init(&GpioLed);

  while(1)
  {
    if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0))
    {
        delay();
        GPIO_ToggleOutptPin(GPIOD, GPIO_PIN_NO_12);
    }
    delay();
  }

  return 0;
}
