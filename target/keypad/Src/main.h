/*
 * main.h
 *
 *  Created on: 15 лют. 2026 р.
 *      Author: Savhe
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

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

typedef struct
{
	uint32_t const odr_0:1;
	uint32_t const odr_1:1;
	uint32_t const odr_2:1;
	uint32_t const odr_3:1;
	uint32_t const odr_4:1;
	uint32_t const odr_5:1;
	uint32_t const odr_6:1;
	uint32_t const odr_7:1;
	uint32_t const odr_8:1;
	uint32_t const odr_9:1;
	uint32_t const odr_10:1;
	uint32_t const odr_11:1;
	uint32_t const odr_12:1;
	uint32_t const odr_13:1;
	uint32_t const odr_14:1;
	uint32_t const odr_15:1;
	uint32_t const reserved:16;
} GPIOx_IDR_t;

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
} GPIOx_PUPDR_t;

#endif /* MAIN_H_ */
