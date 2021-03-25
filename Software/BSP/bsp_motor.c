#include "bsp_motor.h"
#include "mymath.h"

static inline void Direction_init(void) //腿部电机
{
	GPIO_InitType GPIO_InitStructure;
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);

	GPIO_InitStruct(&GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_F_LEG_L | PIN_F_LEG_R;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitPeripheral(GPIO_F_LEG, &GPIO_InitStructure);
}
static inline void Waist_init(void) //腰部电机
{
	GPIO_InitType GPIO_InitStructure;
	GPIO_InitStruct(&GPIO_InitStructure);
	GPIO_InitStructure.Pin = PIN_WAIST_P | PIN_WAIST_N;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitPeripheral(GPIO_WAIST_P, &GPIO_InitStructure); //根据设定参数初始化

	WAIST_P = 0;
	WAIST_N = 0;
}
#define TIM1_PWM_MAX 999  //计数上限
#define TIM1_PWM_HZ 20000 //PWM频率
TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t CCR1_Val = 333;
uint16_t CCR2_Val = 249;
uint16_t CCR3_Val = 166;
uint16_t CCR4_Val = 83;
uint16_t PrescalerValue = 0;
static inline void Tim3_pwm_init(void) //腿部电机
{
	GPIO_InitType GPIO_InitStructure;
/* TIM3 clock enable */
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);

	/* GPIOA and GPIOB clock enable */
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);

	GPIO_InitStruct(&GPIO_InitStructure);
	/* GPIOA Configuration:TIM3 Channel1, 2, 3 and 4 as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.GPIO_Current = GPIO_DC_LOW;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = GPIO_PIN_7;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

	/* GPIOB Configuration:TIM3 Channel3 and 4 as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.GPIO_Current = GPIO_DC_LOW;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
	GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = GPIO_PIN_1;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
	GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

	/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    The TIM3CLK frequency is set to SystemCoreClock (Hz), to get TIM3 counter
    clock at 24 MHz the Prescaler is computed as following:
     - Prescaler = (TIM3CLK / TIM3 counter clock) - 1
    SystemCoreClock is set to 48 MHz for N32G032 device

    The TIM3 is running at 36 KHz: TIM3 Frequency = TIM3 counter clock/(AR + 1)
                                                  = 24 MHz / 666 = 36 KHz
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
    ----------------------------------------------------------------------- */
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t)(SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.Period = 665;
	TIM_TimeBaseStructure.Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.OcMode = TIM_OCMODE_PWM1;
	TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
	TIM_OCInitStructure.Pulse = CCR1_Val;
	TIM_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH;

	TIM_InitOc1(TIM3, &TIM_OCInitStructure);

	TIM_EnableOc1Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
	TIM_OCInitStructure.Pulse = CCR2_Val;

	TIM_InitOc2(TIM3, &TIM_OCInitStructure);

	TIM_ConfigOc2Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
	TIM_OCInitStructure.Pulse = CCR3_Val;

	TIM_InitOc3(TIM3, &TIM_OCInitStructure);

	TIM_ConfigOc3Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
	TIM_OCInitStructure.Pulse = CCR4_Val;

	TIM_InitOc4(TIM3, &TIM_OCInitStructure);

	TIM_ConfigOc4Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

	TIM_ConfigArPreload(TIM3, ENABLE);

	/* TIM3 enable counter */
	TIM_Enable(TIM3, ENABLE);
	
	leg_pwm_out(0, 0, 0, 0);
}

void pwm_out_init(void)
{
	/*电机转向*/
	Direction_init();
	/*腰部电机*/
	Waist_init();
	/*腿部电机*/
	Tim3_pwm_init(); //腿部电机
}

/*
电机顺序
PA9    PA8
  1    2
   *  *
    **
   *  *
  3    4
PA11   PA10
*/

/*******************************
*函 数 名: leg_pwm_out
*功能说明: 电机PWM输出+
*形    参: 无
*返 回 值: 无
********************************/
void leg_pwm_out(s16 PWM_A, s16 PWM_B, s16 PWM_C, s16 PWM_D)
{


	//前左电机
	if (PWM_A < 0)
	{
		A_L = 1;	   //方向
		PWM_A += 1000; //满值是1000  相对电平
	}
	else
	{
		A_L = 0;
	}
	Moto_F_LEG_L = ABS(PWM_A);

	//前右电机
	if (PWM_B < 0)
	{
		A_R = 1;
		PWM_B += 1000;
	}
	else
	{
		A_R = 0;
	}
	Moto_F_LEG_R = ABS(PWM_B);


}
