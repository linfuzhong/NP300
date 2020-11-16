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
#include "os_mgq.h"

static app_srv_sample_data_t sample_data = {0};

/* �ɼ�������Ϣ���п��ƿ� */
static struct rt_messagequeue sample_mq = {0};

#define SAMPLE_TIMEOUT_MAX								(3)
static bool app_srv_sample_sm(app_srv_sample_msgq_e e_sm);

/*�ɼ�����ʱ�� */
#define SAMPLE_TIME			 									(1000)
rt_timer_t time_1s    = RT_NULL;
/* �ɼ���ʱ����ʱ�ص����� */
static void app_srv_sample_timeout(void *param)
{
	app_srv_sample_send_msg_timeout();	/* ���Ͳɼ�1s��ʱ��Ϣ */
	app_srv_display_send_msg_timeout();	/* ������ʾ1s��ʱ��Ϣ */
}

/* �ɼ������ʼ�� */
bool app_srv_sample_init(void)
{	
  /* ��ʼ��I2C2 */
	if (!bsp_i2c_init(e_i2c2_idx)){
			return false;	
	}
  
	/* ��ʼ���ɼ���Ϣ���� */
	if (!os_mq_init(&sample_mq, "smp_mqt", e_mgs_pool_sample)){
			return false;	
	}
		 
  /* ��ʼ��1s���ڶ�ʱ�� */
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

/* �ɼ������� */
bool app_srv_sample_runing(void)
{
	rt_mq_t  mq = &sample_mq;	
	app_message_t sample_mgq = {0}; 
  uint8 e_sm;
	if ( os_mq_recv(mq, &sample_mgq, RT_WAITING_FOREVER) ) {            
			 e_sm = sample_mgq.u8mg_type;
			 if (app_srv_sample_sm((app_srv_sample_msgq_e)e_sm)){
			 		 
			 } else {
			 
			 }
		   os_mq_free_mem(&sample_mgq);
	}
	return true;	
}

/* �ɼ�����ִ�к��� */
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
 
/* ���Ͳɼ���ʱ��Ϣ */
bool app_srv_sample_send_msg_timeout(void)
{ 	
	rt_mq_t  mq = &sample_mq;
	uint8 mgq_type = e_sample_msg_timeout_1s;
	return ( os_mq_send_no_data(mq, mgq_type, false) );
}


/* ��ȡ�ɼ��Ĵ��������� */
bool app_srv_sample_data_get(app_srv_sample_data_t *pt_data)
{
  if (!pt_data){
      return false;
  }
  memcpy(pt_data, &sample_data, sizeof(sample_data));
  return true;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
