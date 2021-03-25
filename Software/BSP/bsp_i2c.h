/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:55:36
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:31:45
 * @FilePath     : \N32G032_KEIL\BSP\bsp_i2c.h
 */
#ifndef __bsp_led_H__
#define __bsp_led_H__

#include "include.h"


int i2c_master_init(void);
int i2c_master_send(uint8_t* data, int len);
int i2c_master_recv(uint8_t* data, int len);

#endif

