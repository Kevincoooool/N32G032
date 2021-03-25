/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 17:08:55
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:12:45
 * @FilePath     : \N32G032_KEIL\BSP\bsp_uart2.c
 */

#include "bsp_uart1.h"

/****************************************************
*函 数 名: USART2_Init
*功能说明: 串口一初始化  JQ8400使用  开机需要等待8400回复是否存在SD卡 所以不能开接收中断  必须保持接收
*形    参: 无
*返 回 值: 无
*****************************************************/
void USART2_Init(u32 br_num)
{
	GPIO_InitType GPIO_InitStructure;
	USART_InitType USART_InitStructure;
	NVIC_InitType NVIC_InitStructure;
	/* Enable GPIO clock */
	GPIO_APB1ClkCmd(USART2_GPIO_CLK, ENABLE);
	/* Enable USARTy and USARTz Clock */
	USART_APB1ClkCmd(USART2_CLK, ENABLE);
	/* Initialize GPIO_InitStructure */
	GPIO_InitStruct(&GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USART2_TxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.GPIO_Alternate = USART2_Tx_GPIO_AF;
	GPIO_InitPeripheral(USART2_GPIO, &GPIO_InitStructure);

	/* Configure USARTz Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = USART2_RxPin;
	GPIO_InitStructure.GPIO_Alternate = USART2_Rx_GPIO_AF;
	GPIO_InitPeripheral(USART2_GPIO, &GPIO_InitStructure);

	USART_InitStructure.BaudRate = br_num;
	USART_InitStructure.WordLength = USART_WL_8B;
	USART_InitStructure.StopBits = USART_STPB_1;
	USART_InitStructure.Parity = USART_PE_NO;
	USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
	USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;

	/* Configure USARTy and USARTz */
	USART_Init(USART2, &USART_InitStructure);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ConfigInt(USART2, USART_INT_RXDNE, ENABLE);
	USART_ConfigInt(USART2, USART_INT_TXDE, ENABLE);

	/* Enable the USARTy and USARTz */
	USART_Enable(USART2, ENABLE);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
