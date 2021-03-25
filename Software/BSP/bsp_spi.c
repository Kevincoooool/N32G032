/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:55:36
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:39:07
 * @FilePath     : \N32G032_KEIL\BSP\bsp_spi.c
 */

#include "bsp_spi.h"

/*******************************
*函 数 名: SPI_1_Init
*功能说明: 
*形    参: 无
*返 回 值: 无
********************************/
void SPI_1_Init(void)
{
	SPI_InitType SPI_InitStructure;

	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);

	/*!< sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO
         and sFLASH_SPI_SCK_GPIO Periph clock enable */
	RCC_EnableAPB2PeriphClk(
		sFLASH_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | sFLASH_SPI_SCK_GPIO_CLK, ENABLE);

	/*!< sFLASH_SPI Periph clock enable */
	RCC_EnableAPB2PeriphClk(sFLASH_SPI_CLK | RCC_APB2_PERIPH_AFIO, ENABLE);

	/*!< Configure sFLASH_SPI pins: SCK */
	GPIO_InitStructure.Pin = sFLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
	GPIO_InitPeripheral(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_SPI pins: MOSI */
	GPIO_InitStructure.Pin = sFLASH_SPI_MOSI_PIN;
	GPIO_InitPeripheral(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_SPI pins: MISO */
	GPIO_InitStructure.Pin = sFLASH_SPI_MISO_PIN;
	//   GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitPeripheral(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
	GPIO_InitStructure.Pin = sFLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitPeripheral(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< SPI configuration */
	SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
	SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
	SPI_InitStructure.DataLen = SPI_DATA_SIZE_8BITS;
	SPI_InitStructure.CLKPOL = SPI_CLKPOL_HIGH;
	SPI_InitStructure.CLKPHA = SPI_CLKPHA_SECOND_EDGE;
	SPI_InitStructure.NSS = SPI_NSS_SOFT;

	SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_4;

	SPI_InitStructure.FirstBit = SPI_FB_MSB;
	SPI_InitStructure.CRCPoly = 7;
	SPI_Init(sFLASH_SPI, &SPI_InitStructure);

	/*!< Enable the sFLASH_SPI  */
	SPI_Enable(sFLASH_SPI, ENABLE);
}
uint8_t SPI_Send_Receive_Byte(uint8_t byte)
{
    /*!< Loop while DAT register in not emplty */
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_TransmitData(sFLASH_SPI, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_RNE_FLAG) == RESET)
        ;

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(sFLASH_SPI);
}

