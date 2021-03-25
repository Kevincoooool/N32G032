
/**
 * @file main.c
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include <stdio.h>
#include "cmsis_os.h"
#include "include.h"

/**
 *  FreeRTOS ThreadCreation
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SYSTICK_1MS ((uint32_t)1000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Tick_num = 0;
osThreadId LEDThread1Handle, LEDThread2Handle;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 */
int main(void)
{
	/*Configure the SysTick IRQ priority */
	N32_NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY, 0);
	/* Get SystemCoreClock */
	SystemCoreClockUpdate();

	/* Config 1s SysTick 1ms  */
	SysTick_Config(SystemCoreClock / SYSTICK_1MS);

	/* Initialize Led1~Led2 as output pushpull mode*/
	MY_GPIO_Init();
	LED_Init();
	KEY_Init();
	ADC1_Init();
	Button_Init();
	USART1_Init(115200);
	USART2_Init(115200);
	USART1_Put_Buf("ALL ok!!\r\n",20);
	/* Thread 1 definition */
	osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

	/*  Thread 2 definition */
	osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

	/* Start thread 1 */
	LEDThread1Handle = osThreadCreate(osThread(LED1), NULL);
	/* Start thread 2 */
	LEDThread2Handle = osThreadCreate(osThread(LED2), NULL);
	
	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */
	while (1)
    {
		
    }
}

/**
  * @brief  Toggle LED1 thread
  * @param  thread not used
  * @retval None
  */
uint8_t key_level = 0;
static void LED_Thread1(void const *argument)
{
	uint32_t count = 0;
	(void)argument;

	for (;;)
	{
		Button_Process();
		key_level = GPIO_ReadInputDataBit(TOUCH_GPIO, TOUCH_PIN1);
		osDelay(20);
		
		//    /* Suspend Thread 1 */
		//    osThreadSuspend(NULL);

		//    count = osKernelSysTick() + 5000;

		//    /* Resume Thread 2*/
		//    osThreadResume(LEDThread2Handle);
	}
}

/**
  * @brief  Toggle LED2 thread
  * @param  argument not used
  * @retval None
  */
static void LED_Thread2(void const *argument)
{
	uint32_t count;
	(void)argument;

	for (;;)
	{

		USART1_Put_Buf("LED_Thread2 ok!!\r\n",20);
		//	  LedOff(LED2_PORT,LED2_PIN);
		osDelay(1000);

	}
}

/**
  * @brief  Sets the priority of an interrupt.
  * @param  IRQn External interrupt number .
  *         This parameter can be an enumerator of  IRQn_Type enumeration
  * @param  PreemptPriority The pre-emption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 3.
  *         A lower priority value indicates a higher priority 
  * @param  SubPriority the subpriority level for the IRQ channel.
  *         this parameter is a dummy value and it is ignored, because 
  *         no subpriority supported in Cortex M0 based products.   
  * @retval None
  */
void N32_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
	/* Check the parameters */
	assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
	NVIC_SetPriority(IRQn, PreemptPriority);
}

/**
 * @}
 */

/**
 * @}
 */
