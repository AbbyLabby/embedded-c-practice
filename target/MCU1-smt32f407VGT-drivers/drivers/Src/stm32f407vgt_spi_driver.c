#include "stm32f407vgt_spi_driver.h"

static void spi_txe_interrupt_handler(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handler(SPI_Handle_t *pSPIHandle);
static void spi_ovr_interrupt_handler(SPI_Handle_t *pSPIHandle);

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    uint32_t tempReg = 0;

    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    //set corresponding device mode
    tempReg |= ( pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR);

    //set bus configuration
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFG_FD)
    {
        tempReg &= ~( 1 << SPI_CR1_BIDIMODE);
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFG_HD)
    {
        tempReg |= ( 1 << SPI_CR1_BIDIMODE);
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFG_SIMPLEX_RXONLY)
    {
        tempReg &= ~( 1 << SPI_CR1_BIDIMODE);
        tempReg |= ( 1 << SPI_CR1_RXONLY);
    }

    //set sclk speed
    tempReg |= ( pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR);

    //set DFF
    tempReg |= ( pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF);

    //set CPOL and CPHA
    tempReg |= ( pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL);
    tempReg |= ( pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA);

    //set SSM
    tempReg |= ( pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM);

    pSPIHandle->pSPIx->CR1 = tempReg;
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t Status)
{
    if(Status == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t Status)
{
    if(Status == ENABLE)
    {
        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }
    else
    {
        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    if(pSPIx == SPI1)
    {
        SPI1_REG_RESET();
    }
    else if(pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if(pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }
}

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t Status)
{
    if(Status == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
    }
    else
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_DI();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_DI();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_DI();
        }
    }
}

void SPI_Enable(SPI_RegDef_t *pSPIx)
{
    pSPIx->CR1 |= (1 << SPI_CR1_SPE);
}

void SPI_Disable(SPI_RegDef_t *pSPIx)
{
    pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagOffset)
{
    if(pSPIx->SR & ( 1 << FlagOffset ))
    {
        return FLAG_SET;
    }

    return FLAG_RESET;
}

void SPI_Send(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        while (SPI_GetFlagStatus(pSPIx, SPI_SR_TXE) == FLAG_RESET); //wait for TXE flag set

        if(pSPIx->CR1 & ( 1 << SPI_CR1_DFF)) //16it DFF
        {
            pSPIx->DR = *((uint16_t*)pTxBuffer);
            Len--;
            Len--;
            pTxBuffer++;
            pTxBuffer++;
        }
        else //8bit DFF
        {
            pSPIx->DR = *(pTxBuffer);
            Len--;
            pTxBuffer++;
        }
    }
}

void SPI_Receive(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        while (SPI_GetFlagStatus(pSPIx, SPI_SR_RXNE) == FLAG_RESET); //wait for RXNE flag set

        if(pSPIx->CR1 & ( 1 << SPI_CR1_DFF)) //16it DFF
        {
            *((uint16_t*)pRxBuffer) = pSPIx->DR;
            Len--;
            Len--;
            pRxBuffer++;
            pRxBuffer++;
        }
        else //8bit DFF
        {
            *(pRxBuffer) = pSPIx->DR;
            Len--;
            pRxBuffer++;
        }
    }
}

uint8_t SPI_SendIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->TxState;

    if(state != SPI_BUSY_IN_TX)
    {
        //save values to handle
        pSPIHandle->pTxBuffer = pTxBuffer;
        pSPIHandle->TxLen = Len;

        //set SPI state to busy in TX
        pSPIHandle->TxState = SPI_BUSY_IN_TX;

        //set TXEIE to 1 in CR2 register
        pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_TXEIE );
    }

    return state;
}

uint8_t SPI_ReceiveIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->RxState;

    if(state != SPI_BUSY_IN_RX)
    {
        //save values to handle
        pSPIHandle->pRxBuffer = pRxBuffer;
        pSPIHandle->RxLen = Len;

        //set SPI state to busy in RX
        pSPIHandle->RxState = SPI_BUSY_IN_TX;

        //set RXNEIE to 1 in CR2 register
        pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_RXNEIE );
    }

    return state;
}

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Status)
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

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    // Find the IPR register and the byte section within it
	uint8_t iprx = IRQNumber / 4;             // which IPR register
	uint8_t iprx_section = IRQNumber % 4;      // which byte (0..3) inside it

	// Lower bits of each byte are not implemented, so shift the priority up
	uint8_t shift_amount = ( (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED) );

	*(NVIC_PR_BASE_ADDR + iprx) |= ( IRQPriority << shift_amount );
}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
    uint8_t temp1, temp2;

    //check for TXE
    temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_TXE );
    temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIE );

    if( temp1 && temp2)
    {
        //handle TXE
        spi_txe_interrupt_handler(pSPIHandle);
    }

    //check for RXNE
    temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE );
    temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIE );

    if( temp1 && temp2)
    {
        //handle RXNE
        spi_rxne_interrupt_handler(pSPIHandle);
    }

    //check for OVR error
    temp1 = pSPIHandle->pSPIx->SR & ( 1 << SPI_SR_OVR );
    temp2 = pSPIHandle->pSPIx->CR2 & ( 1 << SPI_CR2_ERRIE );

    if( temp1 && temp2)
    {
        //handle OVR
        spi_ovr_interrupt_handler(pSPIHandle);
    }
}

void SPI_ClearOVRFlag(SPI_Handle_t *pSPIHandle)
{
    uint8_t temp;

    temp = pSPIHandle->pSPIx->DR;
    temp = pSPIHandle->pSPIx->SR;

    (void)temp;
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_TXEIE );
    pSPIHandle->pTxBuffer = NULL;
    pSPIHandle->TxLen = 0;
    pSPIHandle->TxState = SPI_READY;
}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_RXNEIE );
    pSPIHandle->pRxBuffer = NULL;
    pSPIHandle->RxLen = 0;
    pSPIHandle->RxState = SPI_READY;
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t Event)
{

}

//some helpers

static void spi_txe_interrupt_handler(SPI_Handle_t *pSPIHandle)
{
    if(pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF)) //16it DFF
    {
        *((uint16_t*)pSPIHandle->pTxBuffer) = pSPIHandle->pSPIx->DR;
        pSPIHandle->TxLen--;
        pSPIHandle->TxLen--;
        pSPIHandle->pTxBuffer++;
        pSPIHandle->pTxBuffer++;
    }
    else //8bit DFF
    {
        *(pSPIHandle->pTxBuffer) = pSPIHandle->pSPIx->DR;
        pSPIHandle->TxLen--;
        pSPIHandle->pTxBuffer++;
    }

    if(pSPIHandle->TxLen == 0)
    {
        SPI_CloseTransmission(pSPIHandle);

        SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
    }
}

static void spi_rxne_interrupt_handler(SPI_Handle_t *pSPIHandle)
{
    if(pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF)) //16it DFF
    {
        *((uint16_t*)pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
        pSPIHandle->RxLen--;
        pSPIHandle->RxLen--;
        pSPIHandle->pRxBuffer++;
        pSPIHandle->pRxBuffer++;
    }
    else //8bit DFF
    {
        *(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
        pSPIHandle->RxLen--;
        pSPIHandle->pRxBuffer++;
    }

    if(pSPIHandle->RxLen == 0)
    {
        SPI_CloseReception(pSPIHandle);

        SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
    }
}

static void spi_ovr_interrupt_handler(SPI_Handle_t *pSPIHandle)
{
    uint8_t temp;

    if(pSPIHandle->TxLen != SPI_BUSY_IN_TX)
    {
        temp = pSPIHandle->pSPIx->DR;
        temp = pSPIHandle->pSPIx->SR;
    }

    (void)temp;

    SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
}
