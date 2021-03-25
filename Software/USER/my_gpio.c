/*
 * @Descripttion: 其余IO控制
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-06-01 14:24:59
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 15:37:48
 * @FilePath     : \N32G032_KEIL\USER\my_gpio.c
 */
#include "my_gpio.h"
#include "bsp_adc.h"
#include "touch.h"
/****************************************************
*函 数 名: Other_GPIO_Init
*功能说明: 其他IO口初始化 用于检测音乐播放状态和控制功放开关
*形    参: 无
*返 回 值: 无
*****************************************************/
void MY_GPIO_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
	
	GPIO_InitStruct(&GPIO_InitStructure);
	GPIO_InitStructure.Pin = POWER_PIN;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitPeripheral(POWER_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = CHARGE_PIN;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_DOWN;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
	GPIO_InitPeripheral(CHARGE_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = TOUCH_PIN1 | TOUCH_PIN2;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
	GPIO_InitPeripheral(TOUCH_GPIO, &GPIO_InitStructure);
	
}
