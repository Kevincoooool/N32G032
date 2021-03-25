/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-06-01 14:24:56
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 15:27:12
 * @FilePath     : \N32G032_KEIL\BSP\bsp_adc.h
 */
#ifndef __bsp_adc_H
#define	__bsp_adc_H

#include "n32g032.h"

#define M 9

void ADC1_Init(void);
extern float ad_value[9];
extern __IO uint16_t ADC_ConvertedValue[];
void AD_convert(void);

#endif /* __ADC_H */


