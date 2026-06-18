/*
 * stm32f407vgt_spi_driver.h
 *
 *  Created on: 15 черв. 2026 р.
 *      Author: Savhe
 */

#ifndef INC_STM32F407VGT_SPI_DRIVER_H_
#define INC_STM32F407VGT_SPI_DRIVER_H_

#include "stm32f407vgt.h"

//Configuration structure for SPIx peripheral
typedef struct
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
} SPI_Config_t;

//Handle structure for SPIx peripheral
typedef struct
{
    SPI_RegDef_t *pSPIx;
    SPI_Config_t SPIConfig;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint8_t TxLen;
    uint8_t RxLen;
    uint8_t TxState;
    uint8_t RxState;
} SPI_Handle_t;

#define SPI_DEVICE_MODE_MASTER          1
#define SPI_DEVICE_MODE_SLAVE           0

#define SPI_BUS_CONFG_FD                1
#define SPI_BUS_CONFG_HD                2
#define SPI_BUS_CONFG_SIMPLEX_RXONLY    3

#define SPI_SCLK_SPEED_DIV2             0
#define SPI_SCLK_SPEED_DIV4             1
#define SPI_SCLK_SPEED_DIV8             2
#define SPI_SCLK_SPEED_DIV16            3
#define SPI_SCLK_SPEED_DIV32            4
#define SPI_SCLK_SPEED_DIV64            5
#define SPI_SCLK_SPEED_DIV128           6
#define SPI_SCLK_SPEED_DIV256           7

#define SPI_DFF_8BITS                   0
#define SPI_DFF_16BITS                  1

#define SPI_CPOL_HIGH                   1
#define SPI_CPOL_LOW                    0

#define SPI_CPHA_HIGH                   1
#define SPI_CPHA_LOW                    0

#define SPI_SSM_EN                      1
#define SPI_SSM_DI                      0

#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBFIRST    7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRCNEXT     12
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIOE      14
#define SPI_CR1_BIDIMODE    15

#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2
#define SPI_CR2_FRF         4
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7

#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8

void     SPI_Init(SPI_Handle_t *pSPIHandle);                          /* Initialize a GPIO pin using the settings in GPIO_Handle_t        */
void     SPI_DeInit(SPI_RegDef_t *pSPIx);                             /* Reset all registers of a GPIO port via RCC AHB1RSTR              */
void     SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t Status);  /* Enable or disable the peripheral clock for a GPIO port           */
void     SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t Status);
void     SPI_Enable(SPI_RegDef_t *pSPIx);
void     SPI_Disable(SPI_RegDef_t *pSPIx);
void     SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t Status);

uint8_t  SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagOffset);

void     SPI_ClearOVRFlag(SPI_Handle_t *pSPIHandle);
void     SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void     SPI_CloseReception(SPI_Handle_t *pSPIHandle);

void     SPI_Send(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void     SPI_Receive(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

uint8_t  SPI_SendIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t  SPI_ReceiveIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

void     SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Status);      /* Enable/disable an IRQ line in the NVIC (processor side)        */
void     SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);  /* Set IRQ priority in the NVIC IPR registers (0 = highest)       */
void     SPI_IRQHandling(SPI_Handle_t *pSPIHandle);                             /* Call from EXTIx_IRQHandler to clear the EXTI pending bit       */

void     SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t Event);

#define SPI_READY           0
#define SPI_BUSY_IN_RX      1
#define SPI_BUSY_IN_TX      2

//possible spi application events
#define SPI_EVENT_TX_CMPLT  1
#define SPI_EVENT_RX_CMPLT  2
#define SPI_EVENT_OVR_ERR   3


#endif /* INC_STM32F407VGT_SPI_DRIVER_H_ */
