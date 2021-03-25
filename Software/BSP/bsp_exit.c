/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 15:55:36
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 16:05:26
 * @FilePath     : \N32G032_KEIL\BSP\bsp_exit.c
 */

#include "bsp_led.h"
#include "bsp_motor.h"

void KeyInputExtiInit(GPIO_Module *GPIOx, uint16_t Pin);

void KEY_Init(void)
{
	KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);
}
void KeyInputExtiInit(GPIO_Module *GPIOx, uint16_t Pin)
{
	GPIO_InitType GPIO_InitStructure;
	EXTI_InitType EXTI_InitStructure;
	NVIC_InitType NVIC_InitStructure;

	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	/* Enable the GPIO Clock */
	if (GPIOx == GPIOA)
	{
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
	}
	else if (GPIOx == GPIOB)
	{
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
	}
	else if (GPIOx == GPIOC)
	{
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
	}
	else if (GPIOx == GPIOD)
	{
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
	}
	else if (GPIOx == GPIOF)
	{
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF | RCC_APB2_PERIPH_AFIO, ENABLE);
	}
	else
	{
		return;
	}

	/*Configure the GPIO pin as input floating*/
	if (Pin <= GPIO_PIN_ALL)
	{
		GPIO_InitStruct(&GPIO_InitStructure);
		GPIO_InitStructure.Pin = Pin;
		GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
		GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
	}

	/*Configure key EXTI Line to key input Pin*/
	GPIO_ConfigEXTILine(KEY_INPUT_PORT_SOURCE, KEY_INPUT_PIN_SOURCE);

	/*Configure key EXTI line*/
	EXTI_InitStructure.EXTI_Line = KEY_INPUT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitPeripheral(&EXTI_InitStructure);

	/*Set key input interrupt priority*/
	NVIC_InitStructure.NVIC_IRQChannel = KEY_INPUT_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
