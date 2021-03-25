/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:55:36
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:39:42
 * @FilePath     : \N32G032_KEIL\BSP\bsp_spi.h
 */
#ifndef __bsp_led_H__
#define __bsp_led_H__

#include "include.h"


#define sFLASH_SPI                SPI1
#define sFLASH_SPI_CLK            RCC_APB2_PERIPH_SPI1

#define sFLASH_SPI_SCK_PIN        GPIO_PIN_5 /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT  GPIOA      /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK   RCC_APB2_PERIPH_GPIOA

#define sFLASH_SPI_MISO_PIN       GPIO_PIN_6 /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT GPIOA      /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK  RCC_APB2_PERIPH_GPIOA

#define sFLASH_SPI_MOSI_PIN       GPIO_PIN_7 /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT GPIOA      /* GPIOA */
#define sFLASH_SPI_MOSI_GPIO_CLK  RCC_APB2_PERIPH_GPIOA

#define sFLASH_CS_PIN             GPIO_PIN_4 /* PA.04 */
#define sFLASH_CS_GPIO_PORT       GPIOA      /* GPIOA */
#define sFLASH_CS_GPIO_CLK        RCC_APB2_PERIPH_GPIOA


/**
 * @brief  Select sFLASH: Chip Select pin low
 */
#define sFLASH_CS_LOW() GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
/**
 * @brief  Deselect sFLASH: Chip Select pin high
 */
#define sFLASH_CS_HIGH() GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)

void  SPI_1_Init(void);
uint8_t SPI_Send_Receive_Byte(uint8_t byte);

#endif

