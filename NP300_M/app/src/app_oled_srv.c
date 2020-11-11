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

/* �ɼ�������Ϣ���п��ƿ� */
static struct rt_messagequeue display_mq = {0};

/*��ʾ��ʼ������*/
bool app_srv_dispaly_init(void)
{
  /* ��ʼ��SPI */
	if ( !bsp_spi_init(e_spi3_idx)){
			return false;
	}
	
  /* ��ʼ��OLED */
	if ( !app_drv_oled_init()){
			return false;
	}
	
	/* ��ʼ���ɼ���Ϣ���� */
	if ( !os_mq_init(&display_mq, "oled_mqt", e_mgs_pool_display)) {      
		  return false; 
	}	
	
	/* ��ʼ����Ϣ���д���״̬�� */
	if ( !app_oled_srv_init()){
			return false; 
	}
	
  return true;
}

/*��ʾ������*/
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

/* ���͸�����ʾ�ĳ�ʱ��Ϣ */
bool app_srv_display_send_msg_timeout(void)
{ 
	rt_mq_t  mq = &display_mq;
	uint8 mgq_type = e_oled_mgq_timeout;
	return ( os_mq_send_no_data(mq, mgq_type, false) );
}

/* ������ʾ������������Ϣ*/
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
