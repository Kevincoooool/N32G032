#ifndef _config_H
#define _config_H

#include "n32g032.h"
/* 群控 发送还是接收*/
#define GROUP_CONTROL_T 	0
#define GROUP_CONTROL_R		0

/*是否是编程版本*/
#define ESP32_115200		0

/*主板硬件版本  6.6不能检测SD卡  7.0可以*/
#define Board_7_0			1
#define Board_6_6			0
/*是否使用AOA跟随*/
#define FLOW_AOA 			0

/*版本切换  */
#define HUAFUU_H3   		1
//北京幼儿园改的版本
#define HUAFUU_H3_BEIJING   0
//新版H3
#define HUAFUU_H3_NEW   	0

#define HUAFUU_H2   		0
//新版H2
#define HUAFUU_H2_NEW   	0

#define HUAFUU_H1   		0

#define HUAFUU_H0   		0
/*软硬件版本*/
#define HW_TYPE     		1
/*硬件PCB版本*/
#define HW_VER				280
/*BootLoder版本*/
#define BT_VER				100
/*主板软件版本*/
#define SF_VER				301 
/*避障板版本*/
#define QB_VER				1
/*语音识别版本*/
#define CI_VER				897
/*ESP32版本*/
#define ESP_VER				100

/*JQ8400可以设置最高30  最低0*/
#define MAX_VOL_JQ 			30
#define MIN_VOL_JQ 			10

/*1006最高设置7  最低0 */
#define MAX_VOL_CI 			7
#define MIN_VOL_CI 			2


/*是否使用Bootloader */
#define BOOTLOADER_ON_OFF   0
#if BOOTLOADER_ON_OFF
#define APP_BASE            0X3000
#endif
//位带操作
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
 
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808  
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 

#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
                                                   
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n) 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)


/* 腿部腰部ADC  PC0 PC1 PC2 PC3 PC4 PC5  */
#define AD_F_LEG_R  0
#define AD_F_LEG_L  1
#define AD_B_LEG_R  2
#define AD_B_LEG_L  3
#define AD_WAIST_X  4
#define AD_WAIST_Y  5
#define AD_POWER    7

/* 腿部电机12K HZ  PA8  PA9  PA10  PA11 */

#define Moto_F_LEG_R  		TIM3->CCDAT1
#define Moto_F_LEG_L  		TIM3->CCDAT2


/* 前后左右腿部电机正反转方向控制IO   */
#define  RCC_GPIO_F_LEG_R	RCC_APB2Periph_GPIOA
#define  GPIO_F_LEG			GPIOA
#define  PIN_F_LEG_L		GPIO_PIN_12
#define  PIN_F_LEG_R		GPIO_PIN_4

#define  RCC_GPIO_B_LEG_R	RCC_APB2Periph_GPIOA
#define  GPIO_B_LEG			GPIOA
#define  PIN_B_LEG_L		GPIO_PIN_5
#define  PIN_B_LEG_R		GPIO_PIN_6
/*电机转向控制*/

#define  A_R   				PAout(12)
#define  A_L   				PAout(4)
#define  B_R   				PAout(5)
#define  B_L   				PAout(6)

/* 腰部电机控制   */
#define  RCC_GPIO_WAIST		RCC_APB2Periph_GPIOB
#define  GPIO_WAIST_P		GPIOB
#define  GPIO_WAIST_N		GPIOB
#define  PIN_WAIST_P		GPIO_PIN_0
#define  PIN_WAIST_N		GPIO_PIN_1

#define  WAIST_P			PBout(0)
#define  WAIST_N			PBout(1)

#define  Tail_R				PBout(3)
#define  Tail_G				PBout(4)
#define  Tail_B				PBout(5)




#define USART1_CLK          RCC_APB2_PERIPH_USART1
#define USART1_GPIO         GPIOA
#define USART1_GPIO_CLK     RCC_APB2_PERIPH_GPIOA
#define USART1_RxPin        GPIO_PIN_10
#define USART1_TxPin        GPIO_PIN_9
#define USART1_Rx_GPIO_AF   GPIO_AF4_USART1
#define USART1_Tx_GPIO_AF   GPIO_AF4_USART1
#define GPIO_APB1ClkCmd     RCC_EnableAPB2PeriphClk
#define USART_APB1ClkCmd    RCC_EnableAPB2PeriphClk
#define USART1_IRQn       	USART1_2_IRQn
#define USART1_IRQHandler 	USART1_2_IRQHandler

#define USART2_CLK          RCC_APB1_PERIPH_USART2
#define USART2_GPIO         GPIOA
#define USART2_GPIO_CLK     RCC_APB2_PERIPH_GPIOA
#define USART2_RxPin        GPIO_PIN_3
#define USART2_TxPin        GPIO_PIN_2
#define USART2_Rx_GPIO_AF   GPIO_AF4_USART2
#define USART2_Tx_GPIO_AF   GPIO_AF4_USART2
#define GPIO_APB2ClkCmd     RCC_EnableAPB2PeriphClk
#define USART_APB2ClkCmd    RCC_EnableAPB1PeriphClk

#define USART2_IRQn       	USART1_2_IRQn
#define USART2_IRQHandler 	USART1_2_IRQHandler

#endif
