/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <bsp_adc.h>

/**ADC1 GPIO Configuration
PC3   ------> ADC1_IN4
PA1   ------> ADC1_IN6
PA3   ------> ADC1_IN8
*/	
#define LIGHT_ADC_PIN 									LL_GPIO_PIN_3
#define LIGHT_ADC_GPIO_PORT 						GPIOC

#define BAT_INP_PIN 										LL_GPIO_PIN_1
#define BAT_INP_GPIO_PORT 							GPIOA

#define NTC_INP_PIN 										LL_GPIO_PIN_3
#define NTC_INP_GPIO_PORT 							GPIOA

typedef struct{
	uint32_t 			adc_periphs;
	uint32_t 			adc_pin;
	uint32_t      adc_channel;
	GPIO_TypeDef *adc_gpiox;
}bsp_adc_config_t;

static const bsp_adc_config_t adc_config_array[e_adc_max] = 
{
	{LL_AHB2_GRP1_PERIPH_GPIOC, LIGHT_ADC_PIN, LL_ADC_CHANNEL_4,   LIGHT_ADC_GPIO_PORT},
	{LL_AHB2_GRP1_PERIPH_GPIOA, BAT_INP_PIN,   LL_ADC_CHANNEL_6,   BAT_INP_GPIO_PORT},
	{LL_AHB2_GRP1_PERIPH_GPIOA, NTC_INP_PIN,   LL_ADC_CHANNEL_8,   NTC_INP_GPIO_PORT},
};

/* ADC1 init function */
bool bsp_adc_init(bsp_adc_idx_e idx)
{
  LL_ADC_InitTypeDef       ADC_InitStruct       = {0};
  LL_ADC_REG_InitTypeDef   ADC_REG_InitStruct   = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
  LL_GPIO_InitTypeDef      GPIO_InitStruct      = {0};	

	if (idx >= e_adc_max){
			return false;
	}
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC);
	
	LL_AHB2_GRP1_EnableClock(adc_config_array[idx].adc_periphs);
	GPIO_InitStruct.Pin 								= adc_config_array[idx].adc_pin;
	GPIO_InitStruct.Mode 								= LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull 								= LL_GPIO_PULL_NO;
	LL_GPIO_Init(adc_config_array[idx].adc_gpiox, &GPIO_InitStruct);

  /** Common config
  */
  ADC_InitStruct.Resolution 					= LL_ADC_RESOLUTION_12B;
  ADC_InitStruct.DataAlignment 				= LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.LowPowerMode 				= LL_ADC_LP_AUTOWAIT;									//LL_ADC_LP_MODE_NONE
  LL_ADC_Init(ADC1, &ADC_InitStruct);
	
  ADC_REG_InitStruct.TriggerSource 		= LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength 	= LL_ADC_REG_SEQ_SCAN_DISABLE;
  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct.ContinuousMode 	= LL_ADC_REG_CONV_SINGLE;
  ADC_REG_InitStruct.DMATransfer 			= LL_ADC_REG_DMA_TRANSFER_NONE;
  ADC_REG_InitStruct.Overrun 					= LL_ADC_REG_OVR_DATA_PRESERVED;
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);

	/* Disable ADC deep power down (enabled by default after reset state) */
	LL_ADC_DisableDeepPowerDown(ADC1);
	/* Enable ADC internal voltage regulator */
	LL_ADC_EnableInternalRegulator(ADC1);
	/* Delay for ADC internal voltage regulator stabilization. */
	/* Compute number of CPU cycles to wait for, from delay in us. */
	/* Note: Variable divided by 2 to compensate partially */
	/* CPU processing cycles (depends on compilation optimization). */
	/* Note: If system core clock frequency is below 200kHz, wait time */
	/* is only a few CPU processing cycles. */
	uint32_t wait_loop_index;
	wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
	while(wait_loop_index != 0){
				wait_loop_index--;
	}
  ADC_CommonInitStruct.CommonClock 		= LL_ADC_CLOCK_ASYNC_DIV1;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
  /** Configure Regular Channel
  */

	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, adc_config_array[idx].adc_channel);
	LL_ADC_SetChannelSamplingTime(ADC1, adc_config_array[idx].adc_channel, LL_ADC_SAMPLINGTIME_2CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, adc_config_array[idx].adc_channel, LL_ADC_SINGLE_ENDED);
	return true;
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
