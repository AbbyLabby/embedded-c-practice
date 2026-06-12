/*
 * stm32f407vgt_gpio_driver.c
 *
 *  Created on: 10 квіт. 2026 р.
 *      Author: Savhe
 */

#include "stm32f407vgt_gpio_driver.h"

/*********************************************************************************
 * @fn              - GPIO_Init
 *
 * @brief           - Initializes a GPIO pin according to the configuration
 *                    stored in the GPIO_Handle_t structure
 *
 * @param[in]       - pGPIOHandle : pointer to the GPIO handle structure
 *                    containing port base address and pin configuration
 *
 * @return          - none
 *
 * @Note            - Must enable peripheral clock before calling this function
 *
 *********************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    // Configure mode
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOBaseAddr->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIOHandle->pGPIOBaseAddr->MODER |= temp;
    }
    else
    {
        //interrupt mode (will do later)

		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//Configure FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		} else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//Configure RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		} else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//Configure FTSR and RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//Clear FTSR bit
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4) * 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOBaseAddr);

		SYSCFG_PCLK_EN();

		SYSCFG->EXTICR[temp1] = portcode << temp2;

		//Enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;

    // Configure speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOBaseAddr->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOBaseAddr->OSPEEDR |= temp;

    temp = 0;

    // Configure pu\pd settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControll << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOBaseAddr->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOBaseAddr->PUPDR |= temp;

    temp = 0;

    // Configure output type
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOBaseAddr->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOBaseAddr->OTYPER |= temp;

    temp = 0;

    // Configure alternative functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALFTN)
    {
        uint8_t temp1, temp2;

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

        pGPIOHandle->pGPIOBaseAddr->AFR[temp1] &= ~(0xF << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIOHandle->pGPIOBaseAddr->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
    }
}

/*********************************************************************************
 * @fn              - GPIO_DeInit
 *
 * @brief           - Resets all registers of a given GPIO port to their
 *                    default values using RCC AHB1RSTR
 *
 * @param[in]       - pGPIOx : base address of the GPIO port (e.g. GPIOA)
 *
 * @return          - none
 *
 * @Note            - Resets the entire port, not a single pin
 *
 *********************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
	else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

/*********************************************************************************
 * @fn              - GPIO_PeriClockControl
 *
 * @brief           - Enables or disables the peripheral clock for a given
 *                    GPIO port via RCC AHB1ENR
 *
 * @param[in]       - pGPIOx  : base address of the GPIO port (e.g. GPIOA)
 * @param[in]       - Status  : ENABLE or DISABLE
 *
 * @return          - none
 *
 * @Note            - Always call this before GPIO_Init()
 *
 *********************************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t Status)
{
	if(Status == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
		else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}
}

/*********************************************************************************
 * @fn              - GPIO_ReadFromInputPin
 *
 * @brief           - Reads the current logic level of a single GPIO input pin
 *
 * @param[in]       - pGPIOx    : base address of the GPIO port (e.g. GPIOA)
 * @param[in]       - PinNumber : pin number to read (0..15)
 *
 * @return          - uint8_t   : 0 or 1
 *
 * @Note            - Pin must be configured as input mode
 *
 *********************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;

	value = (uint8_t)(pGPIOx->IDR >> PinNumber) & 0x1;

	return value;
}

/*********************************************************************************
 * @fn              - GPIO_ReadFromInputPort
 *
 * @brief           - Reads the current logic level of all 16 pins of a GPIO port
 *
 * @param[in]       - pGPIOx  : base address of the GPIO port (e.g. GPIOA)
 *
 * @return          - uint16_t : value of the entire input data register (IDR)
 *
 * @Note            - none
 *
 *********************************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;

	value = (int16_t)pGPIOx->IDR;

	return value;
}

/*********************************************************************************
 * @fn              - GPIO_WriteToOutputPin
 *
 * @brief           - Writes a logic 0 or 1 to a single GPIO output pin
 *
 * @param[in]       - pGPIOx    : base address of the GPIO port (e.g. GPIOA)
 * @param[in]       - PinNumber : pin number to write (0..15)
 * @param[in]       - Value     : GPIO_PIN_SET (1) or GPIO_PIN_RESET (0)
 *
 * @return          - none
 *
 * @Note            - Pin must be configured as output mode
 *
 *********************************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, int8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

/*********************************************************************************
 * @fn              - GPIO_WriteToOutputPort
 *
 * @brief           - Writes a 16-bit value to all pins of a GPIO output port
 *
 * @param[in]       - pGPIOx : base address of the GPIO port (e.g. GPIOA)
 * @param[in]       - Value  : 16-bit value to write to the output data register (ODR)
 *
 * @return          - none
 *
 * @Note            - Affects all 16 pins of the port simultaneously
 *
 *********************************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, int16_t Value)
{
	pGPIOx->ODR = Value;
}

/*********************************************************************************
 * @fn              - GPIO_ToggleOutputPin
 *
 * @brief           - Toggles the current output state of a single GPIO pin
 *
 * @param[in]       - pGPIOx    : base address of the GPIO port (e.g. GPIOA)
 * @param[in]       - PinNumber : pin number to toggle (0..15)
 *
 * @return          - none
 *
 * @Note            - Pin must be configured as output mode
 *
 *********************************************************************************/
void GPIO_ToggleOutptPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}

/*********************************************************************************
 * @fn              - GPIO_IRQConfig
 *
 * @brief           - Configures the IRQ number and priority in the NVIC,
 *                    and enables or disables the interrupt
 *
 * @param[in]       - IRQNumber   : IRQ number from the vector table (e.g. 6 for EXTI0)
 * @param[in]       - IRQPriority : priority level (0 = highest)
 * @param[in]       - Status      : ENABLE or DISABLE
 *
 * @return          - none
 *
 * @Note            - Call once during initialisation, before enabling interrupts
 *
 *********************************************************************************/
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Status)
{

}

/*********************************************************************************
 * @fn              - GPIO_IRQHandling
 *
 * @brief           - Clears the EXTI pending register for the given pin number.
 *                    Must be called inside the EXTIx_IRQHandler to acknowledge
 *                    the interrupt
 *
 * @param[in]       - PinNumber : EXTI line number corresponding to the pin (0..15)
 *
 * @return          - none
 *
 * @Note            - Failing to clear the pending bit will cause the ISR to
 *                    fire repeatedly
 *
 *********************************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
