/*
 * stm32f407vgt_gpio_driver.c
 *
 *  Created on: 10 квіт. 2026 р.
 *      Author: Savhe
 */

#include "stm32f407vgt_gpio_driver.h"

/*********************************************************************************
 * @fn              - GPIO_Init
 *
 * @brief           - Initializes a GPIO pin according to the configuration
 *                    stored in the GPIO_Handle_t structure. Handles both normal
 *                    modes (input/output/analog/AF) and interrupt modes
 *                    (falling/rising/both edge) by configuring EXTI and SYSCFG
 *
 * @param[in]       - pGPIOHandle : pointer to the GPIO handle structure
 *                    containing port base address and pin configuration
 *
 * @return          - none
 *
 * @Note            - Must enable peripheral clock (GPIO_PeriClockControl)
 *                    before calling this function
 *
 *********************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;  // short alias for readability

	// 1. Configure pin mode
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// Non-interrupt mode: 2 bits per pin in MODER -> shift by (2 * pin)
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pin));
		pGPIOHandle->pGPIOBaseAddr->MODER &= ~(0x3 << (2 * pin));  // clear the 2-bit field
		pGPIOHandle->pGPIOBaseAddr->MODER |= temp;                 // set the new value
	}
	else
	{
		// Interrupt mode: select trigger edge in EXTI, then route the pin via SYSCFG
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// Falling edge: enable FTSR, make sure RTSR is cleared for this line
			EXTI->FTSR |= (1 << pin);
			EXTI->RTSR &= ~(1 << pin);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// Rising edge: enable RTSR, make sure FTSR is cleared for this line
			EXTI->RTSR |= (1 << pin);
			EXTI->FTSR &= ~(1 << pin);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// Both edges: enable BOTH RTSR and FTSR for this line
			EXTI->RTSR |= (1 << pin);
			EXTI->FTSR |= (1 << pin);
		}

		// Route the chosen GPIO port to the EXTI line via SYSCFG_EXTICR.
		// 4 lines per EXTICR register, 4 bits per line.
		uint8_t temp1 = pin / 4;            // which EXTICR register (0..3)
		uint8_t temp2 = (pin % 4) * 4;      // bit offset inside that register
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOBaseAddr);

		SYSCFG_PCLK_EN();                   // SYSCFG clock must be on before writing EXTICR
		SYSCFG->EXTICR[temp1] = portcode << temp2;

		// Unmask the EXTI line so the interrupt is delivered to the NVIC
		EXTI->IMR |= (1 << pin);
	}

	temp = 0;

	// 2. Configure output speed (2 bits per pin -> shift by 2 * pin)
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pin));
	pGPIOHandle->pGPIOBaseAddr->OSPEEDR &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOBaseAddr->OSPEEDR |= temp;

	temp = 0;

	// 3. Configure pull-up / pull-down (2 bits per pin -> shift by 2 * pin)
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControll << (2 * pin));
	pGPIOHandle->pGPIOBaseAddr->PUPDR &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOBaseAddr->PUPDR |= temp;

	temp = 0;

	// 4. Configure output type (1 bit per pin -> shift by pin, NOT 2 * pin)
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pin);
	pGPIOHandle->pGPIOBaseAddr->OTYPER &= ~(0x1 << pin);
	pGPIOHandle->pGPIOBaseAddr->OTYPER |= temp;

	temp = 0;

	// 5. Configure alternate function (only relevant in AF mode)
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALFTN)
	{
		// 4 bits per pin; AFR[0] handles pins 0-7, AFR[1] handles pins 8-15
		uint8_t temp1, temp2;

		temp1 = pin / 8;   // AFR low (0) or AFR high (1)
		temp2 = pin % 8;   // pin position within the chosen register

		pGPIOHandle->pGPIOBaseAddr->AFR[temp1] &= ~(0xF << (4 * temp2));  // clear the 4-bit field
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

	// Shift the wanted bit down to position 0, then mask everything else off
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1);

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

	value = (uint16_t)pGPIOx->IDR;  // only the low 16 bits of IDR are valid

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
		pGPIOx->ODR |= (1 << PinNumber);   // set the bit -> drive pin high
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);  // clear the bit -> drive pin low
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
 * @fn              - GPIO_ToggleOutptPin
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
	pGPIOx->ODR ^= (1 << PinNumber);  // XOR flips just this bit
}

/*********************************************************************************
 * @fn              - GPIO_IRQInterruptConfig
 *
 * @brief           - Enables or disables a given IRQ line in the NVIC
 *                    (processor side of the interrupt path)
 *
 * @param[in]       - IRQNumber : IRQ number from the vector table (e.g. 6 for EXTI0)
 * @param[in]       - Status    : ENABLE or DISABLE
 *
 * @return          - none
 *
 * @Note            - Each ISER/ICER register covers 32 IRQs:
 *                      reg index = IRQNumber / 32, bit = IRQNumber % 32.
 *                    To DISABLE an IRQ you write 1 to the matching ICER bit,
 *                    not 0 to ISER.
 *
 *********************************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Status)
{
	if(Status == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// IRQ 0..31 -> ISER0
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}
		else if(IRQNumber > 31 && IRQNumber < 64) // 32 to 63
		{
			// IRQ 32..63 -> ISER1, bit = IRQNumber % 32
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96) // 64 to 95
		{
			// IRQ 64..95 -> ISER2. NOTE: bit should be IRQNumber % 32;
			// % 64 happens to give the same result for the IRQs that exist
			// on this MCU, which is why the course leaves it as-is.
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			// IRQ 0..31 -> ICER0
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}
		else if(IRQNumber > 31 && IRQNumber < 64) // 32 to 63
		{
			// IRQ 32..63 -> ICER1, bit = IRQNumber % 32
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96) // 64 to 95
		{
			// IRQ 64..95 -> ICER2 (same % 64 note as ISER2 above)
			*NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
}

/*********************************************************************************
 * @fn              - GPIO_IRQPriorityConfig
 *
 * @brief           - Sets the priority of a given IRQ line in the NVIC IPR
 *                    registers
 *
 * @param[in]       - IRQNumber   : IRQ number from the vector table
 * @param[in]       - IRQPriority : priority value (0 = highest)
 *
 * @return          - none
 *
 * @Note            - Each IPR register holds 4 IRQs (1 byte each), but only the
 *                    upper NO_PR_BITS_IMPLEMENTED bits of each byte are used,
 *                    hence the extra (8 - NO_PR_BITS_IMPLEMENTED) shift.
 *
 *********************************************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	// Find the IPR register and the byte section within it
	uint8_t iprx = IRQNumber / 4;             // which IPR register
	uint8_t iprx_section = IRQNumber % 4;      // which byte (0..3) inside it

	// Lower bits of each byte are not implemented, so shift the priority up
	uint8_t shift_amount = ( (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED) );

	*(NVIC_PR_BASE_ADDR + iprx) |= ( IRQPriority << shift_amount );
}

/*********************************************************************************
 * @fn              - GPIO_IRQHandling
 *
 * @brief           - Clears the EXTI pending bit for the given pin number.
 *                    Must be called inside the EXTIx_IRQHandler to acknowledge
 *                    the interrupt
 *
 * @param[in]       - PinNumber : EXTI line number corresponding to the pin (0..15)
 *
 * @return          - none
 *
 * @Note            - The pending bit is cleared by writing 1 to it. Failing to
 *                    clear it will cause the ISR to fire repeatedly.
 *
 *********************************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
	// If the pending bit for this line is set, clear it by writing 1 to it
	if(EXTI->PR & ( 1 << PinNumber ))
	{
		EXTI->PR |= ( 1 << PinNumber );
	}
}
