
#include "bsp_uart1.h"

/****************************************************
*函 数 名: USART1_Init
*功能说明: 串口一初始化  JQ8400使用  开机需要等待8400回复是否存在SD卡 所以不能开接收中断  必须保持接收
*形    参: 无
*返 回 值: 无
*****************************************************/
void USART1_Init(u32 br_num)
{
	GPIO_InitType GPIO_InitStructure;
	USART_InitType USART_InitStructure;
	NVIC_InitType NVIC_InitStructure;
	/* Enable GPIO clock */
	GPIO_APB1ClkCmd(USART1_GPIO_CLK, ENABLE);
	/* Enable USARTy and USARTz Clock */
	USART_APB1ClkCmd(USART1_CLK, ENABLE);
	/* Initialize GPIO_InitStructure */
	GPIO_InitStruct(&GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USART1_TxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.GPIO_Alternate = USART1_Tx_GPIO_AF;
	GPIO_InitPeripheral(USART1_GPIO, &GPIO_InitStructure);

	/* Configure USARTz Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USART1_RxPin;
	GPIO_InitStructure.GPIO_Alternate = USART1_Rx_GPIO_AF;
	GPIO_InitPeripheral(USART1_GPIO, &GPIO_InitStructure);

	USART_InitStructure.BaudRate = br_num;
	USART_InitStructure.WordLength = USART_WL_8B;
	USART_InitStructure.StopBits = USART_STPB_1;
	USART_InitStructure.Parity = USART_PE_NO;
	USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
	USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;

	/* Configure USARTy and USARTz */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ConfigInt(USART1, USART_INT_RXDNE, ENABLE);
	USART_ConfigInt(USART1, USART_INT_TXDE, ENABLE);

	/* Enable the USARTy and USARTz */
	USART_Enable(USART1, ENABLE);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

uint8_t TxBuffer1[256];
uint8_t TxCounter1 = 0;
uint8_t count1 = 0;

uint8_t TxBuffer2[256];
uint8_t TxCounter2 = 0;

uint8_t count2 = 0;

uint8_t com_data;
void USART1_IRQHandler(void)
{
	if (USART_GetIntStatus(USART1, USART_INT_RXDNE) != RESET)
	{
		USART_ClrIntPendingBit(USART1, USART_INT_RXDNE);
		com_data = USART_ReceiveData(USART1);
		//		JQ8400_Get(com_data);
		
	}
	
	/*发送中断*/
	if (USART_GetIntStatus(USART1, USART_INT_TXDE) != RESET)
	{
		/* Write one byte to the transmit data register */
		USART_SendData(USART1, TxBuffer1[TxCounter1++]);

		if (TxCounter1 == count1)
		{
			/* Disable the USARTy Transmit interrupt */
			USART_ConfigInt(USART1, USART_INT_TXDE, DISABLE);
		}
	}
	if (USART_GetIntStatus(USART2, USART_INT_RXDNE) != RESET)
	{
		USART_ClrIntPendingBit(USART2, USART_INT_RXDNE);
		com_data = USART_ReceiveData(USART2);
		//		JQ8400_Get(com_data);
		
	}
	
	/*发送中断*/
	if (USART_GetIntStatus(USART2, USART_INT_TXDE) != RESET)
	{
		/* Write one byte to the transmit data register */
		USART_SendData(USART2, TxBuffer2[TxCounter2++]);

		if (TxCounter2 == count2)
		{
			/* Disable the USARTy Transmit interrupt */
			USART_ConfigInt(USART2, USART_INT_TXDE, DISABLE);
		}
	}
}

void USART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer1[count1++] = DataToSend;
	USART_ConfigInt(USART1, USART_INT_TXDE, ENABLE);
}
void USART1_Put_String(unsigned char *Str)
{
	//判断Str指向的数据是否有效.
	while (*Str)
	{
		//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
		if (*Str == '\r')
			USART1_Put_Char(0x0d);
		else if (*Str == '\n')
			USART1_Put_Char(0x0a);
		else
			USART1_Put_Char(*Str);
		//指针++ 指向下一个字节.
		Str++;
	}
}
void USART1_Put_Buf(unsigned char *DataToSend, uint8_t data_num)
{
	for (uint8_t i = 0; i < data_num; i++)
		TxBuffer1[count1++] = *(DataToSend + i);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
	{
	}
	USART_ConfigInt(USART1, USART_INT_TXDE, ENABLE);
}


void USART2_Put_Char(unsigned char DataToSend)
{
	TxBuffer2[count2++] = DataToSend;
	USART_ConfigInt(USART2, USART_INT_TXDE, ENABLE);
}
void USART2_Put_String(unsigned char *Str)
{
	//判断Str指向的数据是否有效.
	while (*Str)
	{
		//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
		if (*Str == '\r')
			USART2_Put_Char(0x0d);
		else if (*Str == '\n')
			USART2_Put_Char(0x0a);
		else
			USART2_Put_Char(*Str);
		//指针++ 指向下一个字节.
		Str++;
	}
}
void USART2_Put_Buf(unsigned char *DataToSend, uint8_t data_num)
{
	for (uint8_t i = 0; i < data_num; i++)
		TxBuffer2[count2++] = *(DataToSend + i);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXDE) == RESET)
	{
	}
	USART_ConfigInt(USART2, USART_INT_TXDE, ENABLE);
}
