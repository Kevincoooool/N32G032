/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-06-01 14:24:59
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 15:37:21
 * @FilePath     : \N32G032_KEIL\USER\my_gpio.h
 */
#ifndef _GPIO_H
#define _GPIO_H

#include "n32g032.h"

#define BUSY_FL GPIO_PIN_15
#define Music_Busy GPIO_ReadInputDataBit(GPIOC, GPIO_PIN_13)
#define BUSY_TF GPIO_PIN_13

#define CHARGE_GPIO GPIOC
#define CHARGE_PIN GPIO_PIN_13

#define POWER_GPIO GPIOC
#define POWER_PIN GPIO_PIN_14

#define MOTOR_POWER_ON GPIO_SetBits(POWER_GPIO, POWER_PIN)
#define MOTOR_POWER_OFF GPIO_ResetBits(POWER_GPIO, POWER_PIN)

#define TOUCH_GPIO   GPIOA
#define TOUCH_PIN1   GPIO_PIN_4
#define TOUCH_PIN2   GPIO_PIN_6



void MY_GPIO_Init(void);

#endif
