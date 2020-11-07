/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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
#include <bsp_gpio.h>
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

//  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  /* GPIO Ports Clock Enable */
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
//
//  /**/
//  LL_GPIO_ResetOutputPin(GPIOA, FLASH_CS_Pin|DEBUG_LED_Pin|OLED_VDDB_Pin|LCD_CS_Pin);
//
//  /**/
//  LL_GPIO_ResetOutputPin(GPIOB, DCDC_EN_Pin|LDO_ON_Pin);
//
//  /**/
//  LL_GPIO_ResetOutputPin(LCD_DC_GPIO_Port, LCD_DC_Pin);
//
//  /**/
//  LL_GPIO_ResetOutputPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
//
//  /**/
//  GPIO_InitStruct.Pin = FLASH_CS_Pin|DEBUG_LED_Pin|OLED_VDDB_Pin|LCD_CS_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
//  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//  /**/
//  GPIO_InitStruct.Pin = DCDC_EN_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  LL_GPIO_Init(DCDC_EN_GPIO_Port, &GPIO_InitStruct);
//
//  /**/
//  GPIO_InitStruct.Pin = CHG_FUL_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  LL_GPIO_Init(CHG_FUL_GPIO_Port, &GPIO_InitStruct);
//
//  /**/
//  GPIO_InitStruct.Pin = LCD_DC_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  LL_GPIO_Init(LCD_DC_GPIO_Port, &GPIO_InitStruct);
//
//  /**/
//  GPIO_InitStruct.Pin = OLED_RST_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  LL_GPIO_Init(OLED_RST_GPIO_Port, &GPIO_InitStruct);
//
//  /**/
//  GPIO_InitStruct.Pin = LDO_ON_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
//  LL_GPIO_Init(LDO_ON_GPIO_Port, &GPIO_InitStruct);
//
//  /**/
//  GPIO_InitStruct.Pin = OFF_SIG_Pin|KEY_MENU_Pin|KEY_UP_Pin|KEY_DOWN_Pin;
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
