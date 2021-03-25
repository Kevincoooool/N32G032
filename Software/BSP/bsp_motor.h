/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:38:31
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 15:41:11
 * @FilePath     : \N32G032_KEIL\BSP\bsp_motor.h
 */
#ifndef _bsp_motor_H
#define	_bsp_motor_H

#include "n32g032.h"
#include "Config.h"

void pwm_out_init(void);
void leg_pwm_out(s16 PWM_A,s16 PWM_B,s16 PWM_C,s16 PWM_D);

#endif



