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
#include "bsp_i2c.h"
#include <app_srv_sample.h>
#include "app_sample_task.h"

#define APP_SAMPLE_DEBUG                     (1)
#if  APP_SAMPLE_DEBUG
#define LOG_APP_SAMPLE(re, fmt, args...)			NP300_LOG(re, "sample:"fmt, ##args)
#else
#define LOG_APP_SAMPLE(re, fmt, args...)
#endif

#define SAMPLE_STACK_SIZE		     		(1024)
#define SAMPLE_PRIORITY		     			(7)
#define SAMPLE_TIMESLICE           	(50)

static void app_srv_sample_entry(void *param)
{ 
  if (!app_srv_sample_init()){
      LOG_APP_SAMPLE(e_log_error, "sample init error");
      return;
  }
	while(1){
      app_srv_sample_state();
	}
}

bool app_srv_sample_tread(void)
{
    rt_thread_t pt_sample = RT_NULL;	   
    pt_sample = rt_thread_create("sample",
																	app_srv_sample_entry,
																	RT_NULL,
																	SAMPLE_STACK_SIZE,
																	SAMPLE_PRIORITY,
																	SAMPLE_TIMESLICE);
    if ( pt_sample !=  RT_NULL){
         LOG_APP_SAMPLE(e_log_entry, "init ok");	
         rt_thread_startup(pt_sample);
    }

    return true;
}





















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
