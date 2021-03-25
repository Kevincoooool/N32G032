/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2021-03-25 17:15:11
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-03-25 17:17:41
 * @FilePath     : \N32G032_KEIL\USER\touch.c
 */
#include "bsp_button.h"
#include "touch.h"
/*******************************************************************
 *                          变量声明                               
 *******************************************************************/

Button_t Button1;
Button_t Button2;

//按键一单击
void Btn1_Down_CallBack(void *btn)
{
	
	LedBlink(LED1_PORT, LED1_PIN);
}
//按键一双击
void Btn1_Double_CallBack(void *btn)
{
}

void Btn1_Long_CallBack(void *btn)
{
}
void Btn1_Long_Free_CallBack(void *btn)
{
}
void Btn1_Continuos_CallBack(void *btn)
{
	//   printf("Button1 连按!");
}

void Btn1_ContinuosFree_CallBack(void *btn)
{
	//   printf("Button1 连按释放!");
}

void Btn2_Down_CallBack(void *btn)
{
	LedBlink(LED3_PORT, LED3_PIN);
}

void Btn2_Double_CallBack(void *btn)
{
}

void Btn2_Long_CallBack(void *btn)
{
}
void Btn2_Long_Free_CallBack(void *btn)
{
}
void Btn2_Continuos_CallBack(void *btn)
{
	//   printf("Button2 连按!");
}
void Btn2_ContinuosFree_CallBack(void *btn)
{
	//   printf("Button2 连按释放!");
}

uint8_t Read_KEY1_Level(void)
{
	return GPIO_ReadInputDataBit(TOUCH_GPIO, TOUCH_PIN1);
}

uint8_t Read_KEY2_Level(void)
{
	return GPIO_ReadInputDataBit(TOUCH_GPIO, TOUCH_PIN2);
}

void Button_Init(void)
{

	Button_Create("Button1",
				  &Button1,
				  Read_KEY1_Level,
				  KEY_ON);
	Button_Attach(&Button1, BUTTON_DOWN, Btn1_Down_CallBack);			//单击
	Button_Attach(&Button1, BUTTON_DOUBLE, Btn1_Double_CallBack);		//双击
	Button_Attach(&Button1, BUTTON_LONG, Btn1_Long_CallBack);			//长按按下
	Button_Attach(&Button1, BUTTON_LONG_FREE, Btn1_Long_Free_CallBack); //长按松开

	Button_Create("Button2",
				  &Button2,
				  Read_KEY2_Level,
				  KEY_ON);
	Button_Attach(&Button2, BUTTON_DOWN, Btn2_Down_CallBack);			//单击
	Button_Attach(&Button2, BUTTON_DOUBLE, Btn2_Double_CallBack);		//双击
	Button_Attach(&Button2, BUTTON_LONG, Btn2_Long_CallBack);			//长按
	Button_Attach(&Button2, BUTTON_LONG_FREE, Btn2_Long_Free_CallBack); //长按

	Get_Button_Event(&Button1);
	Get_Button_Event(&Button2);
}
