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
#include <app_sample_drv.h>
#include <app_sample_srv.h>
#include <app_oled_srv.h>

static app_srv_sample_data_t sample_data = {0};

/* 采集任务消息队列控制块 */
#define SAMPLE_MSG_POOL_SIZE							(256)
#define SAMPLE_MSG_SIZE										(4)
static struct rt_messagequeue sample_mq = {0};
/* 采集任务消息队列中用到的放置消息的内存池 */
static uint8 sample_msg_pool[SAMPLE_MSG_POOL_SIZE];
#define SAMPLE_TIMEOUT_MAX								(3)
static bool app_srv_sample_sm(app_srv_sample_msgq_e e_sm);

/*采集任务定时器 */
#define SAMPLE_TIME			 									(1000)
rt_timer_t time_1s    = RT_NULL;
/* 采集定时器超时回调函数 */
static void app_srv_sample_timeout(void *param)
{
	app_srv_sample_send_msg(e_sample_msg_timeout_1s);								/* 发送1s超时消息 */
	app_srv_display_send_msg_timeout();
}

/* 采集任务初始化 */
bool app_srv_sample_init(void)
{
	rt_err_t result;
	
  /* 初始化I2C2 */
	if (!bsp_i2c_init(e_i2c2_idx)){
			return false;	
	}
  
	/* 初始化采集消息队列 */
	result = rt_mq_init(&sample_mq,                        
						          "smp_mqt",                        
                      sample_msg_pool,               /* 消息内存池 */                        
						          SAMPLE_MSG_SIZE,               /* 每个消息的大小 */                        
	                    ARRAY_SIZE(sample_msg_pool),   /* 内存池的大小 */                        
						          RT_IPC_FLAG_FIFO);             /* 如果有多个线程等待，按照先来先得到的方法分配消息 */
	
	if (result != RT_EOK) {      
		  return false; 
	}		
  
  /* 初始化1s周期定时器 */
  time_1s = rt_timer_create ("1stime",
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

/* 采集任务函数 */
bool app_srv_sample_runing(void)
{
  uint8 evt;
	app_srv_sample_msgq_e e_sample_msg;
  evt = rt_mq_recv(&sample_mq, &e_sample_msg, sizeof(e_sample_msg), RT_WAITING_FOREVER);
	if ( evt == RT_EOK) {            
       evt = app_srv_sample_sm(e_sample_msg);    
	}
  return evt;
}

/* 采集任务执行函数 */
static bool app_srv_sample_sm(app_srv_sample_msgq_e e_sm)
{
	static uint32 sample_cnt = SAMPLE_TIMEOUT_MAX;
  switch(e_sm){
	case e_sample_msg_start:
	{
	
	}
		break;
	
	case e_sample_msg_timeout_1s:
	{
		sample_cnt++;
		if (sample_cnt >= SAMPLE_TIMEOUT_MAX){
				sample_cnt = 0; 			
		}
		if (sample_cnt == 0){		
				if (!app_drv_sample_shtc3(&(sample_data.sample_temp), &(sample_data.sample_humi)) ){
						return false;
				}
		}	
	}
		break;
	
	case e_sample_msg_end:
	{
	
	}
		break;
	
	default:
		return false;
	}
  return true;
}
 
/* 发送采集消息 */
bool app_srv_sample_send_msg(app_srv_sample_msgq_e e_sample_msg)
{ 
  rt_err_t result;	
	if (e_sample_msg > e_sample_msg_end){
			return false;
	}
	result = rt_mq_send(&sample_mq, &e_sample_msg, sizeof(e_sample_msg));	
	return (result != RT_EOK ? false : true);
}

/* 获取采集的传感器数据 */
bool app_srv_sample_data_get(app_srv_sample_data_t *pt_data)
{
  if (!pt_data){
      return false;
  }
  memcpy(pt_data, &sample_data, sizeof(sample_data));
  return true;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
