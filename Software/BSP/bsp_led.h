/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:55:36
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 15:58:44
 * @FilePath     : \N32G032_KEIL\BSP\bsp_led.h
 */
#ifndef __bsp_led_H__
#define __bsp_led_H__

#include "include.h"
/*Led1-PB1,Led2-PB6,Led3-PB7*/
#define PORT_GROUP  GPIOB
#define LED1_PORT   PORT_GROUP
#define LED2_PORT   PORT_GROUP
#define LED3_PORT   PORT_GROUP
#define LED1_PIN    GPIO_PIN_1
#define LED2_PIN    GPIO_PIN_6
#define LED3_PIN    GPIO_PIN_7

void  LED_Init(void);


#endif

