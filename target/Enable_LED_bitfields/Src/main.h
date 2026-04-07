/*
 * main.h
 *
 *  Created on: 15 лют. 2026 р.
 *      Author: Savhe
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define RCC_AHB1ENR_REG ((RCC_AHB1ENR_t*)0x40023830)
#define GPIOD_MODE_REG ((GPIOx_MODE_t*)0x40020C00)
#define GPIOD_ODR_REG (GPIOx_ODR_t*)0x40020C14

#define CLOCK_ENABLE 1
#define MODE_CONF_OUTPUT 1
#define PIN_STATE_HIGH 1
#define PIN_STATE_LOW 0

#define DELAY_COUNT 1000000ul

typedef struct
{
	uint32_t gpioA_en:1;
	uint32_t gpioB_en:1;
	uint32_t gpioC_en:1;
	uint32_t gpioD_en:1;
	uint32_t gpioE_en:1;
	uint32_t gpioF_en:1;
	uint32_t gpioG_en:1;
	uint32_t gpioH_en:1;
	uint32_t gpioI_en:1;
	uint32_t gpioJ_en:1;
	uint32_t gpioK_en:1;
	uint32_t reserved_0:1;
	uint32_t crc_en:1;
	uint32_t reserved_1:5;
	uint32_t bkpsram_en:1;
	uint32_t ccmdataram_en:1;
	uint32_t dma1_en:1;
	uint32_t dma2_en:1;
	uint32_t dma2D_en:1;
	uint32_t reserved_2:1;
	uint32_t ethmac_en:1;
	uint32_t ethmactx_en:1;
	uint32_t ethmacrx_en:1;
	uint32_t ethmacptp_en:1;
	uint32_t otghs_en:1;
	uint32_t otghsulpi_en:1;
	uint32_t reserved_3:1;
} RCC_AHB1ENR_t;

typedef struct
{
	uint32_t moder_0:2;
	uint32_t moder_1:2;
	uint32_t moder_2:2;
	uint32_t moder_3:2;
	uint32_t moder_4:2;
	uint32_t moder_5:2;
	uint32_t moder_6:2;
	uint32_t moder_7:2;
	uint32_t moder_8:2;
	uint32_t moder_9:2;
	uint32_t moder_10:2;
	uint32_t moder_11:2;
	uint32_t moder_12:2;
	uint32_t moder_13:2;
	uint32_t moder_14:2;
	uint32_t moder_15:2;
} GPIOx_MODE_t;

typedef struct
{
	uint32_t odr_0:1;
	uint32_t odr_1:1;
	uint32_t odr_2:1;
	uint32_t odr_3:1;
	uint32_t odr_4:1;
	uint32_t odr_5:1;
	uint32_t odr_6:1;
	uint32_t odr_7:1;
	uint32_t odr_8:1;
	uint32_t odr_9:1;
	uint32_t odr_10:1;
	uint32_t odr_11:1;
	uint32_t odr_12:1;
	uint32_t odr_13:1;
	uint32_t odr_14:1;
	uint32_t odr_15:1;
	uint32_t reserved:16;
} GPIOx_ODR_t;

#endif /* MAIN_H_ */
