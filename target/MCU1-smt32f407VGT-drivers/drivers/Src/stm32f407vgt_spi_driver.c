#include "stm32f407vgt_spi_driver.h"

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
            (uint16_t*)pTxBuffer++;
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

}

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Status)
{

}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{

}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{

}
