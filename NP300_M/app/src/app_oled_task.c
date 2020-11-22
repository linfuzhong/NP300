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
#include "app_oled_srv.h"
#include "app_oled_task.h"

#define APP_DISPALY_DEBUG                     (1)
#if  APP_DISPALY_DEBUG
#define LOG_APP_DISPLAY(re, fmt, args...)			NP300_LOG(re, "display:"fmt, ##args)
#else
#define LOG_APP_DISPLAY(re, fmt, args...)
#endif

#define OLED_STACK_SIZE		     		           (768)
#define OLED_PRIORITY		     			           (8)
#define OLED_TIMESLICE           	           (50)

extern rt_sem_t sample_sm;


static void app_srv_oled_entry(void *param)
{
  if (!app_srv_dispaly_init()){
      LOG_APP_DISPLAY(e_log_error, "init error");	
      return;
  }		
	while(1){
			app_srv_display_runing();    
  }
}

bool app_srv_oled_tread(void)
{
    rt_thread_t pt_display = RT_NULL;
    pt_display = rt_thread_create("oled",
																	app_srv_oled_entry,
																	RT_NULL,
																	OLED_STACK_SIZE,
																	OLED_PRIORITY,
																	OLED_TIMESLICE);
    if (pt_display != RT_NULL){
        LOG_APP_DISPLAY(e_log_entry, "init ok");
        rt_thread_startup(pt_display);
    }
    return true;
}



















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
