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
#include <app_drv_sample.h>
#include <app_srv_sample.h>

static app_srv_sample_data_t sample_data = {0};

rt_sem_t sample_sm    = RT_NULL;
rt_timer_t time_1s    = RT_NULL;
#define SAMP_SM          "samp_sm"
#define SAMPLE_TIME			 (1000)

static void app_srv_sample_timeout(void *param)
{


}

bool app_srv_sample_init(void)
{
  /* 初始化I2C2 */
	if (!bsp_i2c_init(e_i2c2_idx)){
			return false;	
	}
  
  /* 初始化采集信号量 */
  sample_sm = rt_sem_create(SAMP_SM, 0 ,RT_IPC_FLAG_FIFO);
  if (!sample_sm){
      return false;
  }
  
  /* 初始化1s周期定时器 */
  time_1s   = rt_timer_create ("1stime",
                                app_srv_sample_timeout, 
                                RT_NULL,
                                SAMPLE_TIME,
                                RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_PERIODIC);
  if ( time_1s !=  RT_NULL){
       rt_timer_start (time_1s);
  } else {
       return false;
  }
  
  return true;
}

bool app_srv_sample_state(void)
{
  bool evt = false;
  evt = app_drv_sample_shtc3(&(sample_data.sample_temp), &(sample_data.sample_humi));  
  if (evt){
      rt_sem_release(sample_sm);
  }
  rt_thread_mdelay(5000);
  return evt;
}

bool app_srv_sample_data_get(app_srv_sample_data_t *pt_data)
{
  if (!pt_data){
      return false;
  }
  memcpy(pt_data, &sample_data, sizeof(sample_data));
  return true;
}















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
