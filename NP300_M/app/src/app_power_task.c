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
#include <rtthread.h>

#include "bsp_log.h"
#include "app_srv_power.h"
#include "app_power_task.h"

#define APP_POWER_DEBUG                     (1)
#if  APP_POWER_DEBUG
#define LOG_APP_POWER(re, fmt, args...)			NP300_LOG(re, "power:"fmt, ##args)
#else
#define LOG_APP_POWER(re, fmt, args...)
#endif

#define LED_STACK_SIZE		     		          (256)
#define LED_PRIORITY		     			          (30)
#define LED_TIMESLICE            	          (50)

static void app_srv_power_led_entry(void *param)
{ 
  if (!app_srv_power_init()){
      LOG_APP_POWER(e_log_error, "init error");	
      return; 
  }
	
	while(1){
      app_srv_state();
	}
}


bool app_srv_power_led_tread(void)
{
	rt_thread_t power_led = RT_NULL;
	power_led = rt_thread_create("power",
																app_srv_power_led_entry,
																RT_NULL,
																LED_STACK_SIZE,
																LED_PRIORITY,
																LED_TIMESLICE);
	if (power_led != RT_NULL){
      LOG_APP_POWER(e_log_entry, "init ok");	
			rt_thread_startup(power_led);
	}
	return true;
}



















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
