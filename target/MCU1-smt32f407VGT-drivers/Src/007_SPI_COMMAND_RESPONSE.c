/*
 * 007_SPI_COMMAND_RESPONSE.c
 *
 *  Created on: 17 черв. 2026 р.
 *      Author: Savhe
 */

#include <stdint.h>
#include "stm32f407vgt.h"
#include <string.h>

#define COMMAND_LED_CTRL        0x50
#define COMMAND_SENSOR_READ     0x51
#define COMMAND_LED_READ        0x52
#define COMMAND_PRINT           0x53
#define COMMAND_ID_READ         0x54

#define LED_ON                  1
#define LED_OFF                 0

#define ANALOG_PIN0             0
#define ANALOG_PIN1             1
#define ANALOG_PIN2             2
#define ANALOG_PIN3             3
#define ANALOG_PIN4             4

#define LED_PIN                 9

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
    GPIOPins->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(GPIOPins);

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
    pSpiHandle->SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32; // 2mhz
    pSpiHandle->SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    pSpiHandle->SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    pSpiHandle->SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    pSpiHandle->SPIConfig.SPI_SSM = SPI_SSM_DI;

    SPI_Init(pSpiHandle);

    SPI_SSOEConfig(SPI2, ENABLE);
}

uint8_t SPI_VeifyResponse(uint8_t ackByte)
{
    if(ackByte == (uint8_t)0xF5)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    uint8_t dummy_write = 0xff;
    uint8_t dummy_read;

    GPIO_Handle_t GPIOPins;

    GPIO_PreInit(&GPIOPins);

    SPI_Handle_t SPI2Handle;

    SPI_PreInit(&SPI2Handle);

    SPI_SSOEConfig(SPI2,ENABLE);

    while(1)
    {
        while ( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

        delay(); //debounce delay

        SPI_Enable(SPI2);

        //CMD 1

        uint8_t commandCode = COMMAND_LED_CTRL;
        uint8_t ackByte;
        uint8_t response;
        uint8_t args[2];

        //send command
        SPI_Send(SPI2, &commandCode, 1);

        //dummy read
        SPI_Receive(SPI2, &dummy_read, 1);

        //send some dummy bits to fetch response from the slave
        SPI_Send(SPI2, &dummy_write, 1);
        SPI_Receive(SPI2, &ackByte, 1);

        if( SPI_VeifyResponse(ackByte) )
        {
            args[0] = LED_PIN;
            args[1] = LED_ON;

            SPI_Send(SPI2, args, 2);
            SPI_Receive(SPI2, &dummy_read, 2);
        }

        while ( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

        delay(); //debounce delay

        //CMD 2
        commandCode = COMMAND_SENSOR_READ;

        SPI_Send(SPI2, &commandCode, 1);

        //dummy read
        SPI_Receive(SPI2, &dummy_read, 1);

        //send some dummy bits to fetch response from the slave
        SPI_Send(SPI2, &dummy_write, 1);
        SPI_Receive(SPI2, &ackByte, 1);

        if( SPI_VeifyResponse(ackByte) )
        {
            args[0] = ANALOG_PIN2;

            SPI_Send(SPI2, args, 1);

            //dummy read
            SPI_Receive(SPI2, &dummy_read, 1);

            delay();

            //send some dummy bits to fetch response from the slave
            SPI_Send(SPI2, &dummy_write, 1);
            SPI_Receive(SPI2, &response, 1);
        }

        while ( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

        delay(); //debounce delay

        //CMD 3
        commandCode = COMMAND_LED_READ;

        SPI_Send(SPI2, &commandCode, 1);

        //dummy read
        SPI_Receive(SPI2, &dummy_read, 1);

        //send some dummy bits to fetch response from the slave
        SPI_Send(SPI2, &dummy_write, 1);
        SPI_Receive(SPI2, &ackByte, 1);

        if( SPI_VeifyResponse(ackByte) )
        {
            args[0] = LED_PIN;

            SPI_Send(SPI2, args, 1);
            SPI_Receive(SPI2, &dummy_read, 1);

            delay();

            //send some dummy bits to fetch response from the slave
            SPI_Send(SPI2, &dummy_write, 1);
            SPI_Receive(SPI2, &response, 1);
        }

        while ( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

        delay(); //debounce delay

        //CMD 4
        commandCode = COMMAND_PRINT;

        SPI_Send(SPI2, &commandCode, 1);

        //dummy read
        SPI_Receive(SPI2, &dummy_read, 1);

        //send some dummy bits to fetch response from the slave
        SPI_Send(SPI2, &dummy_write, 1);
        SPI_Receive(SPI2, &ackByte, 1);

        if( SPI_VeifyResponse(ackByte) )
        {
            uint8_t message[] = "Hello, Arduino!";

            args[0] = strlen((char*)message);

            SPI_Send(SPI2, args, 1);
            SPI_Receive(SPI2, &dummy_read, 1);

            delay();

            for(int i = 0; i < args[0]; i++)
            {
                SPI_Send(SPI2, &message[i], 1);
                SPI_Receive(SPI2, &dummy_read, 1);
            }
        }

        while ( !GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

        delay(); //debounce delay

        //CMD 5
        commandCode = COMMAND_ID_READ;

        SPI_Send(SPI2, &commandCode, 1);

        //dummy read
        SPI_Receive(SPI2, &dummy_read, 1);

        //send some dummy bits to fetch response from the slave
        SPI_Send(SPI2, &dummy_write, 1);
        SPI_Receive(SPI2, &ackByte, 1);

        if( SPI_VeifyResponse(ackByte) )
        {
            delay();

            uint8_t message[11];

            for(int i = 0; i < 10; i++)
            {
                SPI_Send(SPI2, &dummy_write, 1);
                SPI_Receive(SPI2, &message[i], 1);
            }

            message[10] = '\0';
        }


        while(SPI_GetFlagStatus(SPI2, SPI_SR_BSY) == FLAG_SET); //wait until flag BSY is set

        SPI_Disable(SPI2);

        delay(); //debounce delay
    }

    return 0;
}
