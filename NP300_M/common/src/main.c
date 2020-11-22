/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
#include "main.h"

/*外设驱动头文件*/
#include "bsp_log.h"
#include "bsp_rtc.h"

/*任务初始化头文件*/
#include "app_oled_task.h"
#include "app_power_task.h"
#include "app_sample_task.h"

/* 外设驱动接口 */
static void app_hw_boad_init(void)
{
	bsp_log_init(e_log_debug);
	bsp_rtc_init();
	bsp_log_output(e_log_begin, "app bsp start init ok");
}

/* 任务初始化 */
static void app_thread_init(void)
{	
	app_srv_power_led_tread();
	app_srv_sample_tread();
	app_srv_oled_tread();
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	app_hw_boad_init();
	app_thread_init();
	return 0;
}


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
