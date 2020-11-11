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
#include "bsp_spi.h"
#include <app_oled_drv.h>
#include "app_oled_mgq.h"

/* 采集任务消息队列控制块 */
static struct rt_messagequeue display_mq = {0};

/*显示初始化函数*/
bool app_srv_dispaly_init(void)
{
  /* 初始化SPI */
	if ( !bsp_spi_init(e_spi3_idx)){
			return false;
	}
	
  /* 初始化OLED */
	if ( !app_drv_oled_init()){
			return false;
	}
	
	/* 初始化采集消息队列 */
	if ( !os_mq_init(&display_mq, "oled_mqt", e_mgs_pool_display)) {      
		  return false; 
	}	
	
	/* 初始化消息队列处理状态机 */
	if ( !app_oled_srv_init()){
			return false; 
	}
	
  return true;
}

/*显示任务函数*/
void app_srv_display_runing(void)
{
	rt_mq_t  mq = &display_mq;
	app_message_t  oled_mgq = {0};	
	if ( os_mq_recv(mq, &oled_mgq, RT_WAITING_FOREVER) ) {            
       if ( app_oled_srv_sm_msg_proc(&oled_mgq) ){
						
			 } else {
				 
			 }    
		   os_mq_free_mem(&oled_mgq);
	}
}

/*****************************************************************************************************/

/* 发送更新显示的超时消息 */
bool app_srv_display_send_msg_timeout(void)
{ 
	rt_mq_t  mq = &display_mq;
	uint8 mgq_type = e_oled_mgq_timeout;
	return ( os_mq_send_no_data(mq, mgq_type, false) );
}

/* 发送显示按键操作的消息*/
bool app_srv_display_send_msg_key(uint8 key_value)
{ 
	rt_mq_t  mq = &display_mq;
	app_message_t oled_mgq = {0};
	if ( os_mq_get_mem(&oled_mgq, e_oled_mgq_key, 1) ){
		  oled_mgq.pt_mgdata[0] =  key_value;
			return ( os_mq_send_with_data(mq, &oled_mgq, false) );
	} else {
			return false;
	}	
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
