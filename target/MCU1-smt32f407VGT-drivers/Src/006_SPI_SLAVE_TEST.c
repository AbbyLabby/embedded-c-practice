/*
 * 006_SPI_SLAVE_TEST.c
 *
 *  Created on: 16 черв. 2026 р.
 *      Author: Savhe
 */

#include <stdint.h>
#include "stm32f407vgt.h"
#include <string.h>

void GPIO_PreInit(GPIO_Handle_t *GPIOPins)
{
    GPIOPins->pGPIOBaseAddr = GPIOB;
    GPIOPins->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALFTN;
    GPIOPins->GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    GPIOPins->GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GPIOPins->GPIO_PinConfig.GPIO_PinPuPdControll = GPIO_NO_PUPD;
    GPIOPins->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //sysclk
    GPIOPins->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    GPIO_Init(GPIOPins);

    //mosi
    GPIOPins->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(GPIOPins);

    //miso
    //GPIOPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    //GPIO_Init(&GPIOPins);

    //nss
    GPIOPins->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GPIO_Init(GPIOPins);

    // init gpio for internal user button on the board
    GPIOPins->pGPIOBaseAddr = GPIOA;
    GPIOPins->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOPins->GPIO_PinConfig.GPIO_PinPuPdControll = GPIO_NO_PUPD;
    GPIOPins->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOPins->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;

    GPIO_Init(GPIOPins);
}

void delay(void)
{
  for(uint32_t i = 0; i < 500000 / 2; i++);
}

void SPI_PreInit(SPI_Handle_t *pSpiHandle)
{
    pSpiHandle->pSPIx = SPI2;
    pSpiHandle->SPIConfig.SPI_BusConfig = SPI_BUS_CONFG_FD;
    pSpiHandle->SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    pSpiHandle->SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; // 2mhz
    pSpiHandle->SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    pSpiHandle->SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    pSpiHandle->SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    pSpiHandle->SPIConfig.SPI_SSM = SPI_SSM_DI;

    SPI_Init(pSpiHandle);

    SPI_SSOEConfig(SPI2, ENABLE);
}

int main(void)
{
    GPIO_Handle_t GPIOPins;

    GPIO_PreInit(&GPIOPins);

    SPI_Handle_t SPI2Handle;

    SPI_PreInit(&SPI2Handle);

    while(1)
    {
        while ( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

        delay(); //debounce delay

        SPI_Enable(SPI2);

        char user_data[] = "hello my name is Roman and i m try to send long string via SPI to arduino";
        uint8_t bytes_count = strlen(user_data);

        SPI_Send(SPI2, &bytes_count, 1); // first send how many bytes will be send

        SPI_Send(SPI2, (uint8_t*)user_data, bytes_count); // send message

        while(SPI_GetFlagStatus(SPI2, SPI_SR_BSY) == FLAG_SET); //wait until flag BSY is set

        SPI_Disable(SPI2);

        delay(); //debounce delay
    }

    return 0;
}
