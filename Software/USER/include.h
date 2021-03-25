/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:40:02
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 16:26:26
 * @FilePath     : \N32G032_KEIL\USER\include.h
 */
#ifndef _include_H_
#define _include_H_

#include "n32g032.h"

#define SYSTEM_SUPPORT_OS 1 //定义系统文件夹是否支持OS

/* c 标准库 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "stdbool.h"
#include <math.h>
#include "stdio.h"
#include "ctype.h"
#include "main.h"
/* 驱动 */

#include "touch.h"
#include "mymath.h"
#include "my_gpio.h"
#include "bsp_adc.h"
#include "bsp_exit.h"

#include "bsp_led.h"
#include "bsp_adc.h"

#include "bsp_motor.h"

#include "bsp_button.h"
#include "bsp_uart1.h"
#include "bsp_uart2.h"
/* 应用库 */

/*********FreeRTOS********/

extern uint8_t sys_init_ok;



#endif
