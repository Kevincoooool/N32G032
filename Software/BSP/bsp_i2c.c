/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:55:36
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:40:44
 * @FilePath     : \N32G032_KEIL\BSP\bsp_i2c.c
 */

#include "bsp_i2c.h"

//#define I2C_MASTER_LOW_LEVEL

#define TEST_BUFFER_SIZE 100
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(20 * I2C_FLAG_TIMOUT))
#define I2C_MASTER_ADDR 0x30
#define I2C_SLAVE_ADDR 0xA0

uint8_t tx_buf[TEST_BUFFER_SIZE] = {0};
uint8_t rx_buf[TEST_BUFFER_SIZE] = {0};
volatile Status test_status = FAILED;
uint32_t stsbuf[4];
Status Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);

static __IO uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;
void delay(uint32_t count)
{
	uint32_t i;
	for (i = 0; i < count; i++)
	{
	}
}
int i2c_master_init(void)
{
	I2C_InitType i2c1_master;
	GPIO_InitType i2c1_gpio;
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

	GPIO_InitStruct(&i2c1_gpio);
	/*PB6 -- SCL; PB7 -- SDA*/
	i2c1_gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	i2c1_gpio.GPIO_Speed = GPIO_SPEED_HIGH;
	i2c1_gpio.GPIO_Mode = GPIO_MODE_AF_OD;
	i2c1_gpio.GPIO_Alternate = GPIO_AF6_I2C1;
	i2c1_gpio.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitPeripheral(GPIOB, &i2c1_gpio);

	I2C_DeInit(I2C1);
	i2c1_master.BusMode = I2C_BUSMODE_I2C;
	i2c1_master.FmDutyCycle = I2C_FMDUTYCYCLE_2; //if the spped greater than 400KHz, the FmDutyCycle mast be configured to I2C_FMDUTYCYCLE_2
	i2c1_master.OwnAddr1 = I2C_MASTER_ADDR;
	i2c1_master.AckEnable = I2C_ACKEN;
	i2c1_master.AddrMode = I2C_ADDR_MODE_7BIT;
	i2c1_master.ClkSpeed = 100000;

	I2C_Init(I2C1, &i2c1_master);
#ifdef I2C_MASTER_LOW_LEVEL //I2C work in low level(for example:1.8V)
	AFIO_EnableI2CLV(AFIO_I2C1_LV, ENABLE);
#endif
	I2C_Enable(I2C1, ENABLE);
	return 0;
}

int i2c_master_send(uint8_t *data, int len)
{
	uint8_t *sendBufferPtr = data;
	I2CTimeout = I2CT_LONG_TIMEOUT;
	while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
	{
		if ((I2CTimeout--) == 0)
			return 4;
	};

	I2C_ConfigAck(I2C1, ENABLE);

	I2C_GenerateStart(I2C1, ENABLE);
	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_MODE_FLAG)) // EV5
	{
		if ((I2CTimeout--) == 0)
			return 5;
	};

	I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_SEND);
	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_TXMODE_FLAG)) // EV6
	{
		if ((I2CTimeout--) == 0)
			return 6;
	};

	// send data
	while (len-- > 0)
	{
		I2C_SendData(I2C1, *sendBufferPtr++);
		I2CTimeout = I2C_FLAG_TIMOUT;
		while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDING)) // EV8
		{
			if ((I2CTimeout--) == 0)
				return 7;
		};
	};

	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDED)) // EV8-2
	{
		if ((I2CTimeout--) == 0)
			return 8;
	};
	// Delay_us(8);
	I2C_GenerateStop(I2C1, ENABLE);
	return 0;
}

int i2c_master_recv(uint8_t *data, int len)
{
	uint8_t *recvBufferPtr = data;
	I2CTimeout = I2CT_LONG_TIMEOUT;
	while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
	{
		if ((I2CTimeout--) == 0)
			return 9;
	};

	I2C_ConfigAck(I2C1, ENABLE);

	// send start
	I2C_GenerateStart(I2C1, ENABLE);
	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_MODE_FLAG)) // EV5
	{
		if ((I2CTimeout--) == 0)
			return 10;
	};

	// send addr
	I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_RECV);
	I2CTimeout = I2C_FLAG_TIMOUT;
	while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_RXMODE_FLAG)) // EV6
	{
		if ((I2CTimeout--) == 0)
			return 6;
	};

	// recv data
	while (len-- > 0)
	{
		I2CTimeout = I2CT_LONG_TIMEOUT;
		while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_RECVD_FLAG)) // EV7
		{
			if ((I2CTimeout--) == 0)
				return 14;
		};
		if (len == 1)
		{
			I2C_ConfigAck(I2C1, DISABLE);
		}
		if (len == 0)
		{
			I2C_GenerateStop(I2C1, ENABLE);
		}
		*recvBufferPtr++ = I2C_RecvData(I2C1);
	};
	return 0;
}
