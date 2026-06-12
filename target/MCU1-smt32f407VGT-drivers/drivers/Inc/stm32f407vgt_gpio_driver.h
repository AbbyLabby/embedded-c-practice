/*
 * stm32f407vgt_gpio_driver.h
 *
 *  Created on: 10 квіт. 2026 р.
 *      Author: Savhe
 */

#ifndef INC_STM32F407VGT_GPIO_DRIVER_H_
#define INC_STM32F407VGT_GPIO_DRIVER_H_

#include "stm32f407vgt.h"

/* ============================================================
 *  GPIO pin configuration structure
 *  Filled by the user before calling GPIO_Init()
 * ============================================================ */
typedef struct
{
    uint8_t GPIO_PinNumber;       /* Pin number: 0..15                                         */
    uint8_t GPIO_PinMode;         /* Pin mode: see @GPIO pin possible modes below               */
    uint8_t GPIO_PinSpeed;        /* Output speed: see @GPIO pin possible output speed modes    */
    uint8_t GPIO_PinPuPdControll; /* Pull-up / pull-down: see @GPIO pin pull up pull down macros*/
    uint8_t GPIO_PinOPType;       /* Output type: see @GPIO pin possible output types           */
    uint8_t GPIO_PinAltFunMode;   /* Alternate function number: AF0..AF15 (mode = GPIO_MODE_ALFTN) */
} GPIO_PinConfig_t;

/* ============================================================
 *  GPIO handle structure
 *  Ties together the port base address and the pin configuration.
 *  Create one handle per pin, then pass it to GPIO_Init().
 * ============================================================ */
typedef struct
{
    GPIO_RegDef_t    *pGPIOBaseAddr;  /* Pointer to the GPIO port base address (e.g. GPIOA) */
    GPIO_PinConfig_t  GPIO_PinConfig; /* Pin configuration settings chosen by the user       */
} GPIO_Handle_t;

/* ============================================================
 *  @GPIO pin possible modes
 *  Used in GPIO_PinConfig_t.GPIO_PinMode
 * ============================================================ */
#define GPIO_MODE_IN        0   /* Input mode                                                */
#define GPIO_MODE_OUT       1   /* General purpose output mode                               */
#define GPIO_MODE_ALFTN     2   /* Alternate function mode (UART, SPI, I2C, etc.)            */
#define GPIO_MODE_ANALOG    3   /* Analog mode (ADC / DAC)                                   */
#define GPIO_MODE_IT_FT     4   /* Interrupt mode — falling edge trigger                     */
#define GPIO_MODE_IT_RT     5   /* Interrupt mode — rising edge trigger                      */
#define GPIO_MODE_IT_RFT    6   /* Interrupt mode — rising and falling edge trigger           */

/* ============================================================
 *  @GPIO pin possible output types
 *  Used in GPIO_PinConfig_t.GPIO_PinOPType
 * ============================================================ */
#define GPIO_OP_TYPE_PP     0   /* Push-pull output (default, drives high and low)           */
#define GPIO_OP_TYPE_OD     1   /* Open-drain output (requires external pull-up for high)    */

/* ============================================================
 *  @GPIO pin possible output speed modes
 *  Used in GPIO_PinConfig_t.GPIO_PinSpeed
 *  Higher speed = higher slew rate = more EMI, use only what is needed
 * ============================================================ */
#define GPIO_SPEED_LOW      0   /* Low speed      (~2  MHz)                                  */
#define GPIO_SPEED_MEDIUM   1   /* Medium speed   (~25 MHz)                                  */
#define GPIO_SPEED_FAST     2   /* Fast speed     (~50 MHz)                                  */
#define GPIO_SPEED_HIGH     3   /* Very high speed (~100 MHz)                                */

/* ============================================================
 *  @GPIO pin pull up pull down macros
 *  Used in GPIO_PinConfig_t.GPIO_PinPuPdControll
 * ============================================================ */
#define GPIO_NO_PUPD        0   /* No internal pull-up or pull-down resistor                 */
#define GPIO_PU             1   /* Internal pull-up resistor enabled (~40 kΩ)               */
#define GPIO_PD             2   /* Internal pull-down resistor enabled (~40 kΩ)             */

/* ============================================================
 *  @GPIO possible pin numbers
 *  Used in GPIO_PinConfig_t.GPIO_PinNumber
 *  and as PinNumber argument in driver API functions
 * ============================================================ */
#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15

/* ============================================================
 *  GPIO driver API prototypes
 * ============================================================ */

void     GPIO_Init(GPIO_Handle_t *pGPIOHandle);                          /* Initialize a GPIO pin using the settings in GPIO_Handle_t        */
void     GPIO_DeInit(GPIO_RegDef_t *pGPIOx);                             /* Reset all registers of a GPIO port via RCC AHB1RSTR              */
void     GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t Status);  /* Enable or disable the peripheral clock for a GPIO port           */

uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);   /* Read the logic level of a single input pin (returns 0 or 1)  */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);                      /* Read all 16 pins of a port at once (returns uint16_t)        */
void     GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, int8_t Value);  /* Write 0 or 1 to a single output pin             */
void     GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, int16_t Value);      /* Write a 16-bit value to all pins of a port at once           */
void     GPIO_ToggleOutptPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);     /* Toggle the current output state of a single pin              */

void     GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Status);      /* Enable/disable an IRQ line in the NVIC (processor side)        */
void     GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);  /* Set IRQ priority in the NVIC IPR registers (0 = highest)       */
void     GPIO_IRQHandling(uint8_t PinNumber);                             /* Call from EXTIx_IRQHandler to clear the EXTI pending bit       */
#endif /* INC_STM32F407VGT_GPIO_DRIVER_H_ */
