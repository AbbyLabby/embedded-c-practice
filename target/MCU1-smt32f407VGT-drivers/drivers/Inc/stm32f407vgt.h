/*
 * stm32f407vgt.h
 *
 *  Created on: 9 квіт. 2026 р.
 *      Author: Savhe
 *
 *  Peripheral base addresses and register definitions for STM32F407VGT6
 *  Reference: RM0090 Reference Manual (STM32F405/407/415/417)
 */

#ifndef INC_STM32F407VGT_H_
#define INC_STM32F407VGT_H_

#include <stdint.h>

/*
 * ============================================================
 *  MEMORY MAP — Base addresses of main memory regions
 *  (RM0090, Section 2.3 — Memory map)
 * ============================================================
 */

#define FLASH_BASE_ADDR         0x08000000U  /* Flash memory (up to 1 MB) — stores program code */
#define SRAM1_BASE_ADDR         0x20000000U  /* SRAM1 (112 KB) — main data RAM, DMA-accessible */
#define SRAM2_BASE_ADDR         0x2001C000U  /* SRAM2 (16 KB)  — additional data RAM */
#define SRAM3_BASE_ADDR         0x20020000U  /* SRAM3 (64 KB)  — available on F42x/43x only */
#define SRAM                    SRAM1_BASE_ADDR  /* Default SRAM alias → SRAM1 */
#define ROM_BASE_ADDR           0x1FFF0000U  /* System memory (ROM, 30 KB) — factory bootloader */
#define OTP_BASE_ADDR           0x1FFF7800U  /* OTP memory (512 B) — one-time programmable area */


/*
 * ============================================================
 *  BUS BASE ADDRESSES
 *  STM32F4 uses AHB and APB buses of different speeds:
 *    APB1 — up to 42 MHz  (low-speed peripherals: UART, SPI, I2C, Timers)
 *    APB2 — up to 84 MHz  (high-speed peripherals: ADC, SPI1, USART1/6)
 *    AHB1 — up to 168 MHz (GPIO, DMA, RCC, Flash interface)
 *    AHB2 — up to 168 MHz (USB OTG FS, camera, crypto)
 * ============================================================
 */

#define PERIPH_BASE_ADDR        0x40000000U          /* Start of peripheral address space */
#define APB1_PERIPH_BASE_ADDR   PERIPH_BASE_ADDR     /* APB1 bus base = 0x40000000 */
#define APB2_PERIPH_BASE_ADDR   0x40010000U          /* APB2 bus base = 0x40010000 */
#define AHB1_PERIPH_BASE_ADDR   0x40020000U          /* AHB1 bus base = 0x40020000 */
#define AHB2_PERIPH_BASE_ADDR   0x50000000U          /* AHB2 bus base = 0x50000000 */


/*
 * ============================================================
 *  APB1 PERIPHERAL BASE ADDRESSES
 *  Max clock: 42 MHz
 *  Includes: basic/general timers, WDG, SPI2/3, USART2-3,
 *            UART4/5/7/8, I2C1-3, CAN1/2, PWR, DAC
 * ============================================================
 */

#define TIM2_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x0000U)  /* TIM2  — 32-bit general purpose timer */
#define TIM3_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x0400U)  /* TIM3  — 16-bit general purpose timer */
#define TIM4_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x0800U)  /* TIM4  — 16-bit general purpose timer */
#define TIM5_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x0C00U)  /* TIM5  — 32-bit general purpose timer */
#define TIM6_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x1000U)  /* TIM6  — basic timer (used with DAC) */
#define TIM7_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x1400U)  /* TIM7  — basic timer */
#define TIM12_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x1800U)  /* TIM12 — 16-bit general purpose timer */
#define TIM13_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x1C00U)  /* TIM13 — 16-bit general purpose timer */
#define TIM14_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x2000U)  /* TIM14 — 16-bit general purpose timer */
#define RTC_BKP_REG_BASE_ADDR   (APB1_PERIPH_BASE_ADDR + 0x2800U)  /* RTC & backup registers — real-time clock */
#define WWDG_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x2C00U)  /* WWDG — window watchdog timer */
#define IWDG_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x3000U)  /* IWDG — independent watchdog (LSI-clocked) */
#define I2S2EXT_BASE_ADDR       (APB1_PERIPH_BASE_ADDR + 0x3400U)  /* I2S2ext — extended I2S2 (full duplex) */
#define SPI2_I2S2_BASE_ADDR     (APB1_PERIPH_BASE_ADDR + 0x3800U)  /* SPI2 / I2S2 — shared peripheral block */
#define SPI3_I2S3_BASE_ADDR     (APB1_PERIPH_BASE_ADDR + 0x3C00U)  /* SPI3 / I2S3 — shared peripheral block */
#define I2S3EXT_BASE_ADDR       (APB1_PERIPH_BASE_ADDR + 0x4000U)  /* I2S3ext — extended I2S3 (full duplex) */
#define USART2_BASE_ADDR        (APB1_PERIPH_BASE_ADDR + 0x4400U)  /* USART2 — universal sync/async receiver/transmitter */
#define USART3_BASE_ADDR        (APB1_PERIPH_BASE_ADDR + 0x4800U)  /* USART3 */
#define UART4_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x4C00U)  /* UART4  — async only (no sync/hardware flow) */
#define UART5_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x5000U)  /* UART5  — async only */
#define I2C1_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x5400U)  /* I2C1 — inter-integrated circuit bus */
#define I2C2_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x5800U)  /* I2C2 */
#define I2C3_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x5C00U)  /* I2C3 */
#define CAN1_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x6400U)  /* CAN1 — controller area network */
#define CAN2_BASE_ADDR          (APB1_PERIPH_BASE_ADDR + 0x6800U)  /* CAN2 — slave CAN (depends on CAN1) */
#define PWR_BASE_ADDR           (APB1_PERIPH_BASE_ADDR + 0x7000U)  /* PWR  — power control (sleep, standby, voltage) */
#define DAC_BASE_ADDR           (APB1_PERIPH_BASE_ADDR + 0x7400U)  /* DAC  — dual 12-bit digital-to-analog converter */
#define UART7_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x7800U)  /* UART7 — available on F405/407/415/417 */
#define UART8_BASE_ADDR         (APB1_PERIPH_BASE_ADDR + 0x7C00U)  /* UART8 */


/*
 * ============================================================
 *  APB2 PERIPHERAL BASE ADDRESSES
 *  Max clock: 84 MHz
 *  Includes: advanced timers, USART1/6, ADC, SDIO, SPI1/4-6,
 *            SYSCFG, EXTI, SAI, LCD-TFT
 * ============================================================
 */

#define TIM1_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x0000U)  /* TIM1 — 16-bit advanced timer (complementary PWM) */
#define TIM8_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x0400U)  /* TIM8 — 16-bit advanced timer */
#define USART1_BASE_ADDR        (APB2_PERIPH_BASE_ADDR + 0x1000U)  /* USART1 — high-speed USART (up to 10.5 Mbit/s) */
#define USART6_BASE_ADDR        (APB2_PERIPH_BASE_ADDR + 0x1400U)  /* USART6 */
#define ADC1_ADC2_ADC3_BASE_ADDR (APB2_PERIPH_BASE_ADDR + 0x2000U) /* ADC1/2/3 — shared common register block */
#define SDIO_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x2C00U)  /* SDIO — SD/MMC card interface */
#define SPI1_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x3000U)  /* SPI1 — high-speed SPI (up to 42 Mbit/s) */
#define SPI4_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x3400U)  /* SPI4 */
#define SYSCFG_BASE_ADDR        (APB2_PERIPH_BASE_ADDR + 0x3800U)  /* SYSCFG — system config (EXTI mux, memory remap) */
#define EXTI_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x3C00U)  /* EXTI — external interrupt/event controller */
#define TIM9_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x4000U)  /* TIM9  — 16-bit general purpose timer */
#define TIM10_BASE_ADDR         (APB2_PERIPH_BASE_ADDR + 0x4400U)  /* TIM10 — 16-bit general purpose timer */
#define TIM11_BASE_ADDR         (APB2_PERIPH_BASE_ADDR + 0x4800U)  /* TIM11 — 16-bit general purpose timer */
#define SPI5_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x5000U)  /* SPI5 */
#define SPI6_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x5400U)  /* SPI6 */
#define SAI1_BASE_ADDR          (APB2_PERIPH_BASE_ADDR + 0x5800U)  /* SAI1 — serial audio interface */
#define LCD_TFT_BASE_ADDR       (APB2_PERIPH_BASE_ADDR + 0x6800U)  /* LCD-TFT — display controller (LTDC) */


/*
 * ============================================================
 *  AHB1 PERIPHERAL BASE ADDRESSES
 *  Max clock: 168 MHz
 *  Includes: GPIO A–K, CRC, RCC, Flash interface,
 *            backup SRAM, DMA1/2, Ethernet, DMA2D, USB OTG HS
 * ============================================================
 */

#define GPIOA_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x0000U)  /* GPIOA — port A (PA0..PA15) */
#define GPIOB_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x0400U)  /* GPIOB — port B */
#define GPIOC_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x0800U)  /* GPIOC — port C */
#define GPIOD_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x0C00U)  /* GPIOD — port D */
#define GPIOE_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x1000U)  /* GPIOE — port E */
#define GPIOF_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x1400U)  /* GPIOF — port F */
#define GPIOG_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x1800U)  /* GPIOG — port G */
#define GPIOH_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x1C00U)  /* GPIOH — port H */
#define GPIOI_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0x2000U)  /* GPIOI — port I */
#define CRC_BASE_ADDR           (AHB1_PERIPH_BASE_ADDR + 0x3000U)  /* CRC   — hardware CRC-32 calculation unit */
#define RCC_BASE_ADDR           (AHB1_PERIPH_BASE_ADDR + 0x3800U)  /* RCC   — reset & clock control */
#define FLASH_INT_REG_BASE_ADDR (AHB1_PERIPH_BASE_ADDR + 0x3C00U)  /* Flash interface registers (ACR, KEYR, etc.) */
#define BKPSRAM_BASE_ADDR       (AHB1_PERIPH_BASE_ADDR + 0x4000U)  /* Backup SRAM (4 KB) — retained in VBAT mode */
#define DMA1_BASE_ADDR          (AHB1_PERIPH_BASE_ADDR + 0x6000U)  /* DMA1 — 8 streams, used by APB1 peripherals */
#define DMA2_BASE_ADDR          (AHB1_PERIPH_BASE_ADDR + 0x6400U)  /* DMA2 — 8 streams, used by APB2 + memory */
#define ETHERNET_MAC_BASE_ADDR  (AHB1_PERIPH_BASE_ADDR + 0x8000U)  /* Ethernet MAC — 10/100 Mbit/s MAC controller */
#define DMA2D_BASE_ADDR         (AHB1_PERIPH_BASE_ADDR + 0xB000U)  /* DMA2D — Chrom-ART accelerator (graphic DMA) */
#define USB_OTG_HS_BASE_ADDR    (AHB1_PERIPH_BASE_ADDR + 0x20000U) /* USB OTG HS — high-speed USB (with PHY) */


/*
 * ============================================================
 *  AHB2 PERIPHERAL BASE ADDRESSES
 *  Max clock: 168 MHz
 *  Includes: USB OTG FS, camera (DCMI), crypto (CRYP/HASH/RNG)
 * ============================================================
 */

#define USB_OTG_FS_BASE_ADDR    (AHB2_PERIPH_BASE_ADDR + 0x0000U)  /* USB OTG FS — full-speed USB (12 Mbit/s) */
#define DCMI_BASE_ADDR          (AHB2_PERIPH_BASE_ADDR + 0x50000U) /* DCMI — digital camera interface */
#define CRYP_BASE_ADDR          (AHB2_PERIPH_BASE_ADDR + 0x10000U) /* CRYP — AES/DES/TDES hardware accelerator */
#define HASH_BASE_ADDR          (AHB2_PERIPH_BASE_ADDR + 0x10400U) /* HASH — SHA-1/MD5 hardware hash processor */
#define RNG_BASE_ADDR           (AHB2_PERIPH_BASE_ADDR + 0x10800U) /* RNG  — hardware random number generator */


/*
 * ============================================================
 *  GPIO REGISTER DEFINITION STRUCTURE
 *  (RM0090, Section 8.4 — GPIO registers)
 *
 *  Each GPIO port has 10 registers mapped sequentially.
 *  Base address example: GPIOA = 0x40020000
 *
 *  Usage:
 *    GPIO_RegDef_t *pGPIOA = (GPIO_RegDef_t *) GPIOA_BASE_ADDR;
 *    pGPIOA->MODER |= (1 << 10);  // set PA5 as output
 * ============================================================
 */

typedef struct
{
    volatile uint32_t MODER;    /* MODER — GPIO port mode register              Offset: 0x00 */
    volatile uint32_t OTYPER;   /* OTYPER — GPIO port output type register      Offset: 0x04 */
    volatile uint32_t OSPEEDR;  /* OSPEEDR — GPIO port output speed register    Offset: 0x08 */
    volatile uint32_t PUPDR;    /* PUPDR — GPIO port pull-up/pull-down register Offset: 0x0C */
    volatile uint32_t IDR;      /* IDR — GPIO port input data register          Offset: 0x10 */
    volatile uint32_t ODR;      /* ODR — GPIO port output data register         Offset: 0x14 */
    volatile uint32_t BSRR;     /* BSRR — GPIO port bit set/reset register      Offset: 0x18 */
    volatile uint32_t LCKR;     /* LCKR — GPIO port configuration lock register Offset: 0x1C */
    volatile uint32_t AFR[2];   /* AFR — GPIO alternate function registers      Offset: 0x20-0x24 */

} GPIO_RegDef_t;

typedef struct
{
    volatile uint32_t CR;           /* CR       — clock control register                    Offset: 0x00 */
    volatile uint32_t PLLCFGR;     /* PLLCFGR  — PLL configuration register                Offset: 0x04 */
    volatile uint32_t CFGR;        /* CFGR     — clock configuration register               Offset: 0x08 */
    volatile uint32_t CIR;         /* CIR      — clock interrupt register                   Offset: 0x0C */
    volatile uint32_t AHB1RSTR;    /* AHB1RSTR — AHB1 peripheral reset register             Offset: 0x10 */
    volatile uint32_t AHB2RSTR;    /* AHB2RSTR — AHB2 peripheral reset register             Offset: 0x14 */
    volatile uint32_t AHB3RSTR;    /* AHB3RSTR — AHB3 peripheral reset register             Offset: 0x18 */
    uint32_t          RESERVED0;   /* Reserved                                              Offset: 0x1C */
    volatile uint32_t APB1RSTR;    /* APB1RSTR — APB1 peripheral reset register             Offset: 0x20 */
    volatile uint32_t APB2RSTR;    /* APB2RSTR — APB2 peripheral reset register             Offset: 0x24 */
    uint32_t          RESERVED1;   /* Reserved                                              Offset: 0x28 */
    uint32_t          RESERVED2;   /* Reserved                                              Offset: 0x2C */
    volatile uint32_t AHB1ENR;     /* AHB1ENR  — AHB1 peripheral clock enable register      Offset: 0x30 */
    volatile uint32_t AHB2ENR;     /* AHB2ENR  — AHB2 peripheral clock enable register      Offset: 0x34 */
    volatile uint32_t AHB3ENR;     /* AHB3ENR  — AHB3 peripheral clock enable register      Offset: 0x38 */
    uint32_t          RESERVED3;   /* Reserved                                              Offset: 0x3C */
    volatile uint32_t APB1ENR;     /* APB1ENR  — APB1 peripheral clock enable register      Offset: 0x40 */
    volatile uint32_t APB2ENR;     /* APB2ENR  — APB2 peripheral clock enable register      Offset: 0x44 */
    uint32_t          RESERVED4;   /* Reserved                                              Offset: 0x48 */
    uint32_t          RESERVED5;   /* Reserved                                              Offset: 0x4C */
    volatile uint32_t AHB1LPENR;   /* AHB1LPENR — AHB1 clock enable in low-power mode       Offset: 0x50 */
    volatile uint32_t AHB2LPENR;   /* AHB2LPENR — AHB2 clock enable in low-power mode       Offset: 0x54 */
    volatile uint32_t AHB3LPENR;   /* AHB3LPENR — AHB3 clock enable in low-power mode       Offset: 0x58 */
    uint32_t          RESERVED6;   /* Reserved                                              Offset: 0x5C */
    volatile uint32_t APB1LPENR;   /* APB1LPENR — APB1 clock enable in low-power mode       Offset: 0x60 */
    volatile uint32_t APB2LPENR;   /* APB2LPENR — APB2 clock enable in low-power mode       Offset: 0x64 */
    uint32_t          RESERVED7;   /* Reserved                                              Offset: 0x68 */
    uint32_t          RESERVED8;   /* Reserved                                              Offset: 0x6C */
    volatile uint32_t BDCR;        /* BDCR     — backup domain control register             Offset: 0x70 */
    volatile uint32_t CSR;         /* CSR      — clock control & status register            Offset: 0x74 */
    uint32_t          RESERVED9;   /* Reserved                                              Offset: 0x78 */
    uint32_t          RESERVED10;  /* Reserved                                              Offset: 0x7C */
    volatile uint32_t SSCGR;       /* SSCGR    — spread spectrum clock generation register  Offset: 0x80 */
    volatile uint32_t PLLI2SCFGR;  /* PLLI2SCFGR — PLLI2S configuration register           Offset: 0x84 */
} RCC_RegDef_t;

typedef struct
{
    volatile uint32_t IMR;    /* IMR   — interrupt mask register              Offset: 0x00 */
    volatile uint32_t EMR;    /* EMR   — event mask register                  Offset: 0x04 */
    volatile uint32_t RTSR;   /* RTSR  — rising trigger selection register    Offset: 0x08 */
    volatile uint32_t FTSR;   /* FTSR  — falling trigger selection register   Offset: 0x0C */
    volatile uint32_t SWIER;  /* SWIER — software interrupt event register    Offset: 0x10 */
    volatile uint32_t PR;     /* PR    — pending register                     Offset: 0x14 */
} EXTI_RegDef_t;

typedef struct
{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CMPCR;
} SYSCFG_RegDef_t;


/*
 * Convenience macros — cast base address to register struct pointer
 * Example usage:
 *   GPIOA->MODER |= (1U << 10);   // set PA5 as general-purpose output
 *   GPIOA->BSRR   = (1U << 5);    // atomically set PA5 high
 *   GPIOA->BSRR   = (1U << 21);   // atomically set PA5 low (bit 16+5)
 */
#define GPIOA   ((GPIO_RegDef_t *) GPIOA_BASE_ADDR)
#define GPIOB   ((GPIO_RegDef_t *) GPIOB_BASE_ADDR)
#define GPIOC   ((GPIO_RegDef_t *) GPIOC_BASE_ADDR)
#define GPIOD   ((GPIO_RegDef_t *) GPIOD_BASE_ADDR)
#define GPIOE   ((GPIO_RegDef_t *) GPIOE_BASE_ADDR)
#define GPIOF   ((GPIO_RegDef_t *) GPIOF_BASE_ADDR)
#define GPIOG   ((GPIO_RegDef_t *) GPIOG_BASE_ADDR)
#define GPIOH   ((GPIO_RegDef_t *) GPIOH_BASE_ADDR)
#define GPIOI   ((GPIO_RegDef_t *) GPIOI_BASE_ADDR)


/* ============================================================
 *  RCC peripheral struct pointer
 * ============================================================ */
#define RCC     ((RCC_RegDef_t *) RCC_BASE_ADDR)

#define EXTI    ((EXTI_RegDef_t *) EXTI_BASE_ADDR)

#define SYSCFG ((SYSCFG_RegDef_t *) SYSCFG_BASE_ADDR)

/* ============================================================
 *  GPIO peripheral clock enable macros (AHB1ENR)
 * ============================================================ */
#define GPIOA_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 0 ) )    /* Enable GPIOA clock */
#define GPIOB_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 1 ) )    /* Enable GPIOB clock */
#define GPIOC_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 2 ) )    /* Enable GPIOC clock */
#define GPIOD_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 3 ) )    /* Enable GPIOD clock */
#define GPIOE_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 4 ) )    /* Enable GPIOE clock */
#define GPIOF_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 5 ) )    /* Enable GPIOF clock */
#define GPIOG_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 6 ) )    /* Enable GPIOG clock */
#define GPIOH_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 7 ) )    /* Enable GPIOH clock */
#define GPIOI_PCLK_EN()     ( RCC->AHB1ENR |= ( 1 << 8 ) )    /* Enable GPIOI clock */

/* ============================================================
 *  GPIO peripheral clock disable macros (AHB1ENR)
 * ============================================================ */
#define GPIOA_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 0 ) )   /* Disable GPIOA clock */
#define GPIOB_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 1 ) )   /* Disable GPIOB clock */
#define GPIOC_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 2 ) )   /* Disable GPIOC clock */
#define GPIOD_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 3 ) )   /* Disable GPIOD clock */
#define GPIOE_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 4 ) )   /* Disable GPIOE clock */
#define GPIOF_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 5 ) )   /* Disable GPIOF clock */
#define GPIOG_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 6 ) )   /* Disable GPIOG clock */
#define GPIOH_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 7 ) )   /* Disable GPIOH clock */
#define GPIOI_PCLK_DI()     ( RCC->AHB1ENR &= ~( 1 << 8 ) )   /* Disable GPIOI clock */

/* ============================================================
 *  I2C peripheral clock enable macros (APB1ENR)
 * ============================================================ */
#define I2C1_PCLK_EN()      ( RCC->APB1ENR |= ( 1 << 21 ) )   /* Enable I2C1 clock */
#define I2C2_PCLK_EN()      ( RCC->APB1ENR |= ( 1 << 22 ) )   /* Enable I2C2 clock */
#define I2C3_PCLK_EN()      ( RCC->APB1ENR |= ( 1 << 23 ) )   /* Enable I2C3 clock */

/* ============================================================
 *  I2C peripheral clock disable macros (APB1ENR)
 * ============================================================ */
#define I2C1_PCLK_DI()      ( RCC->APB1ENR &= ~( 1 << 21 ) )  /* Disable I2C1 clock */
#define I2C2_PCLK_DI()      ( RCC->APB1ENR &= ~( 1 << 22 ) )  /* Disable I2C2 clock */
#define I2C3_PCLK_DI()      ( RCC->APB1ENR &= ~( 1 << 23 ) )  /* Disable I2C3 clock */

/* ============================================================
 *  SPI peripheral clock enable macros (APB1ENR / APB2ENR)
 * ============================================================ */
#define SPI1_PCLK_EN()      ( RCC->APB2ENR |= ( 1 << 12 ) )   /* Enable SPI1 clock (APB2) */
#define SPI2_PCLK_EN()      ( RCC->APB1ENR |= ( 1 << 14 ) )   /* Enable SPI2 clock (APB1) */
#define SPI3_PCLK_EN()      ( RCC->APB1ENR |= ( 1 << 15 ) )   /* Enable SPI3 clock (APB1) */

/* ============================================================
 *  SPI peripheral clock disable macros (APB1ENR / APB2ENR)
 * ============================================================ */
#define SPI1_PCLK_DI()      ( RCC->APB2ENR &= ~( 1 << 12 ) )  /* Disable SPI1 clock (APB2) */
#define SPI2_PCLK_DI()      ( RCC->APB1ENR &= ~( 1 << 14 ) )  /* Disable SPI2 clock (APB1) */
#define SPI3_PCLK_DI()      ( RCC->APB1ENR &= ~( 1 << 15 ) )  /* Disable SPI3 clock (APB1) */

/* ============================================================
 *  USART/UART peripheral clock enable macros (APB1ENR / APB2ENR)
 * ============================================================ */
#define USART1_PCLK_EN()    ( RCC->APB2ENR |= ( 1 << 4 ) )    /* Enable USART1 clock (APB2) */
#define USART2_PCLK_EN()    ( RCC->APB1ENR |= ( 1 << 17 ) )   /* Enable USART2 clock (APB1) */
#define USART3_PCLK_EN()    ( RCC->APB1ENR |= ( 1 << 18 ) )   /* Enable USART3 clock (APB1) */
#define UART4_PCLK_EN()     ( RCC->APB1ENR |= ( 1 << 19 ) )   /* Enable UART4  clock (APB1) */
#define UART5_PCLK_EN()     ( RCC->APB1ENR |= ( 1 << 20 ) )   /* Enable UART5  clock (APB1) */
#define USART6_PCLK_EN()    ( RCC->APB2ENR |= ( 1 << 5 ) )    /* Enable USART6 clock (APB2) */

/* ============================================================
 *  USART/UART peripheral clock disable macros (APB1ENR / APB2ENR)
 * ============================================================ */
#define USART1_PCLK_DI()    ( RCC->APB2ENR &= ~( 1 << 4 ) )   /* Disable USART1 clock (APB2) */
#define USART2_PCLK_DI()    ( RCC->APB1ENR &= ~( 1 << 17 ) )  /* Disable USART2 clock (APB1) */
#define USART3_PCLK_DI()    ( RCC->APB1ENR &= ~( 1 << 18 ) )  /* Disable USART3 clock (APB1) */
#define UART4_PCLK_DI()     ( RCC->APB1ENR &= ~( 1 << 19 ) )  /* Disable UART4  clock (APB1) */
#define UART5_PCLK_DI()     ( RCC->APB1ENR &= ~( 1 << 20 ) )  /* Disable UART5  clock (APB1) */
#define USART6_PCLK_DI()    ( RCC->APB2ENR &= ~( 1 << 5 ) )   /* Disable USART6 clock (APB2) */

/* ============================================================
 *  SYSCFG peripheral clock enable / disable macros (APB2ENR)
 *  Must be enabled before configuring EXTI line multiplexer
 * ============================================================ */
#define SYSCFG_PCLK_EN()    ( RCC->APB2ENR |= ( 1 << 14 ) )   /* Enable  SYSCFG clock */
#define SYSCFG_PCLK_DI()    ( RCC->APB2ENR &= ~( 1 << 14 ) )  /* Disable SYSCFG clock */

//Macros to reset GPIOx peripherals
#define GPIOA_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 0 ) ); ( RCC->AHB1RSTR &= ~( 1 << 0 ) ); } while(0)
#define GPIOB_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 1 ) ); ( RCC->AHB1RSTR &= ~( 1 << 1 ) ); } while(0)
#define GPIOC_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 2 ) ); ( RCC->AHB1RSTR &= ~( 1 << 2 ) ); } while(0)
#define GPIOD_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 3 ) ); ( RCC->AHB1RSTR &= ~( 1 << 3 ) ); } while(0)
#define GPIOE_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 4 ) ); ( RCC->AHB1RSTR &= ~( 1 << 4 ) ); } while(0)
#define GPIOF_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 5 ) ); ( RCC->AHB1RSTR &= ~( 1 << 5 ) ); } while(0)
#define GPIOG_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 6 ) ); ( RCC->AHB1RSTR &= ~( 1 << 6 ) ); } while(0)
#define GPIOH_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 7 ) ); ( RCC->AHB1RSTR &= ~( 1 << 7 ) ); } while(0)
#define GPIOI_REG_RESET()    do{ ( RCC->AHB1RSTR |= ( 1 << 8 ) ); ( RCC->AHB1RSTR &= ~( 1 << 8 ) ); } while(0)

#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA) ? 0 :\
                                        (x == GPIOB) ? 1 :\
                                        (x == GPIOC) ? 2 :\
                                        (x == GPIOD) ? 3 :\
                                        (x == GPIOE) ? 4 :\
                                        (x == GPIOF) ? 5 :\
                                        (x == GPIOG) ? 6 :\
                                        (x == GPIOH) ? 7 :\
                                        (x == GPIOI) ? 8 : 0)

#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40


/* ============================================================
 *  Generic macros
 * ============================================================ */

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET 	RESET

#include "stm32f407vgt_gpio_driver.h"

#endif /* INC_STM32F407VGT_H_ */
