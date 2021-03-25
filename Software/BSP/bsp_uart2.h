/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 17:08:55
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:09:09
 * @FilePath     : \N32G032_KEIL\BSP\bsp_uart2.h
 */
#ifndef __bsp_uart2_H__
#define __bsp_uart2_H__

#include "include.h"


void  USART2_Init(u32 br_num);
void  USART2_DeInit(void);
void  USART2_IRQ(void);
void  USART2_Put_Char(unsigned char DataToSend);
void  USART2_Put_String(unsigned char *Str);
void  USART2_Put_Buf(unsigned char *DataToSend , uint8_t data_num);


#endif
