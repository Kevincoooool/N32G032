
#include "bsp_adc.h"


__IO uint16_t ADC_ConvertedValue[M];
/*
 * 函数名：ADC1_GPIO_Config
 * 描述  ：使能ADC1和DMA1的时钟，初始化PC.01
 * 输入  : 无
 * 输出  ：无
 * 调用  ：内部调用
 */

static void ADC1_GPIO_Config(void)
{
	GPIO_InitType GPIO_InitStructure;
	/* Enable peripheral clocks ------------------------------------------------*/
	/* Enable DMA clocks */
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
	/* Enable GPIOC clocks */
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	/* Enable ADC clocks */
	RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);
	/* enable ADC 1M clock */
	RCC_EnableHsi(ENABLE);
	RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV1);
	/* RCC_ADCHCLK_DIV16*/
	RCC_ConfigAdcHclk(RCC_ADCHCLK_DIV16);
	GPIO_InitStruct(&GPIO_InitStructure);
	/* Configure PA.01 as analog input -------------------------*/
	GPIO_InitStructure.Pin = GPIO_PIN_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/* 函数名：ADC1_Mode_Config
 * 描述  ：配置ADC1的工作模式为MDA模式
 * 输入  : 无
 * 输出  ：无
 * 调用  ：内部调用
 */
ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
__IO uint16_t ADCConvertedValue;
static void ADC1_Mode_Config(void)
{

	/* DMA channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA_CH1);
	DMA_InitStructure.PeriphAddr = (uint32_t)&ADC->DAT;
	DMA_InitStructure.MemAddr = (uint32_t)&ADCConvertedValue;
	DMA_InitStructure.Direction = DMA_DIR_PERIPH_SRC;
	DMA_InitStructure.BufSize = 1;
	DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc = DMA_MEM_INC_DISABLE;
	DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
	DMA_InitStructure.MemDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.CircularMode = DMA_MODE_CIRCULAR;
	DMA_InitStructure.Priority = DMA_PRIORITY_HIGH;
	DMA_InitStructure.Mem2Mem = DMA_M2M_DISABLE;
	DMA_Init(DMA_CH1, &DMA_InitStructure);
	DMA_RequestRemap(DMA_REMAP_ADC, DMA, DMA_CH1, ENABLE);

	/* Enable DMA channel1 */
	DMA_EnableChannel(DMA_CH1, ENABLE);

	/* ADC configuration ------------------------------------------------------*/
	ADC_InitStructure.MultiChEn = ENABLE;
	ADC_InitStructure.ContinueConvEn = ENABLE;
	ADC_InitStructure.ExtTrigSelect = ADC_EXT_TRIGCONV_NONE;
	ADC_InitStructure.DatAlign = ADC_DAT_ALIGN_R;
	ADC_InitStructure.ChsNumber = 1;
	ADC_Init(ADC, &ADC_InitStructure);
	/* ADC regular channel1 configuration */
	ADC_ConfigRegularChannel(ADC, ADC_CH_1_PA1, 1, ADC_SAMP_TIME_56CYCLES5);
	/* Enable ADC DMA */
	ADC_EnableDMA(ADC, ENABLE);

	/* Enable ADC */
	ADC_Enable(ADC, ENABLE);

	/*wait ADC is ready to use*/
	while (!ADC_GetFlagStatusNew(ADC, ADC_FLAG_RDY))
		;
	/*wait ADC is powered on*/
	while (ADC_GetFlagStatusNew(ADC, ADC_FLAG_PD_RDY))
		;
	/* Start ADC Software Conversion */
	ADC_EnableSoftwareStartConv(ADC, ENABLE);

	/*test ADC converse finish flag*/
	while (!ADC_GetFlagStatus(ADC, ADC_FLAG_ENDC))
		;
	ADC_ClearFlag(ADC, ADC_FLAG_ENDC);

	/* DMA Channel1 transfer complete test */
	while (!DMA_GetFlagStatus(DMA_FLAG_TC1 | DMA_FLAG_GL1, DMA))
		;
	DMA_ClearFlag(DMA_FLAG_TC1 | DMA_FLAG_GL1, DMA);
}

/*
 * 函数名：ADC1_Init
 * 描述  ：无
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}
float ad_value[9] = {0};
void AD_convert(void)
{

		ad_value[0] = (float)ADCConvertedValue;
}
