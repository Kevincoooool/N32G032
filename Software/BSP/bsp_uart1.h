#ifndef __bsp_uart1_H__
#define __bsp_uart1_H__

#include "include.h"


void  USART1_Init(u32 br_num);
void  USART1_DeInit(void);
void  USART1_IRQ(void);
void  USART1_Put_Char(unsigned char DataToSend);
void  USART1_Put_String(unsigned char *Str);
void  USART1_Put_Buf(unsigned char *DataToSend , uint8_t data_num);



#endif
