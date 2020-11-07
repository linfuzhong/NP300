/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#include <app_drv_power.h>
/* LDO电源使能脚 */
#define LDO_ON_PIN									LL_GPIO_PIN_3
#define LDO_ON_GPIO_PORT 						GPIOB

/* 电源输入检测脚 */
#define OFF_SIG_PIN 								LL_GPIO_PIN_4
#define OFF_SIG_GPIO_PORT 					GPIOB

/* LED指示灯 */
#define DEBUG_LED_PIN 							LL_GPIO_PIN_11
#define DEBUG_LED_GPIO_PORT 				GPIOA

static bool power_enable = false;
/**
 * @brief  power init function
 * @param  none
 * @return none
 **/
void app_drv_power_init(void)
{
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	/* LDO电源使能脚 */
	GPIO_InitStruct.Pin 				= LDO_ON_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
	LL_GPIO_Init(LDO_ON_GPIO_PORT, &GPIO_InitStruct);

	/* 电源输入检测脚  */
	GPIO_InitStruct.Pin 				= OFF_SIG_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(OFF_SIG_GPIO_PORT, &GPIO_InitStruct);

	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE4);

	/* 电源输入检测脚外部中断配置位上升沿触发  */
	EXTI_InitStruct.Line_0_31 	= LL_EXTI_LINE_4;
	EXTI_InitStruct.Line_32_63 	= LL_EXTI_LINE_NONE;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode 				= LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger 		= LL_EXTI_TRIGGER_RISING;
	LL_EXTI_Init(&EXTI_InitStruct);

	/* EXTI interrupt init*/
	NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(EXTI4_IRQn);
}

/**
 * @brief  This function handles EXTI line4 interrupt.
 * @param  none
 * @return none
 **/
void EXTI4_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_4)) {
			LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
      power_enable = !power_enable;
      app_drv_power_ldo_on_set(power_enable);	      
  }
}

/**
 * @brief  设置电源使能脚
 * @param  type:true/false
 * @return none
 **/
void app_drv_power_ldo_on_set(bool type)
{
	if (type){
			LL_GPIO_ResetOutputPin(LDO_ON_GPIO_PORT, LDO_ON_PIN);
	} else {
			LL_GPIO_SetOutputPin(LDO_ON_GPIO_PORT, LDO_ON_PIN);
	}
}

/**
 * @brief  power init led function
 * @param  none
 * @return none
 **/
void app_drv_power_led_init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

	/* LDO电源使能脚 */
	GPIO_InitStruct.Pin 				= DEBUG_LED_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
	LL_GPIO_Init(DEBUG_LED_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief  设置LED灯亮灭
 * @param  type:true/false
 * @return none
 **/
void app_drv_power_set_led(bool type)
{
	if (type){
			LL_GPIO_ResetOutputPin(DEBUG_LED_GPIO_PORT, DEBUG_LED_PIN);
	} else {
			LL_GPIO_SetOutputPin(DEBUG_LED_GPIO_PORT, DEBUG_LED_PIN);
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
