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
#include "app_oled_mgq.h"
#include "os_sm.h"
#include "app_oled_sm.h"


static void app_oled_srv_time_out(app_mgq_pt pt_msg);
static void app_oled_srv_key_msg(app_mgq_pt pt_msg);

static const os_msg_array_t oled_msg_proc_array[e_oled_mgq_max] = 
{
	{e_oled_mgq_start,  				NULL},
	{e_oled_mgq_timeout,				app_oled_srv_time_out},
	{e_oled_mgq_key,						app_oled_srv_key_msg},
	{e_oled_mgq_end,						NULL},
};

static void app_oled_srv_time_out(app_mgq_pt pt_msg)
{
	app_oled_sm_sta_timeout();
}

static void app_oled_srv_key_msg(app_mgq_pt pt_msg)
{
	app_oled_sm_sta_key(pt_msg);
}


static bool app_oled_srv_mp_chk_msg_tbl(void)
{
    return os_msg_sm_array_init(e_oled_mgq_start, e_oled_mgq_end, ARRAY_SIZE(oled_msg_proc_array),	oled_msg_proc_array);
}

/* 显示消息和状态机的初始化 */
bool app_oled_srv_init(void)
{
	if (!app_oled_srv_mp_chk_msg_tbl()){
		  return false;
	}
	if (!app_oled_sm_sta_init()){
	    return false;
	}

	return true;
}


/* 接收到消息后查询具体需要执行的函数  */
bool app_oled_srv_sm_msg_proc(app_mgq_pt ptmsg)
{
    return os_msg_sm_proc(e_oled_mgq_start, e_oled_mgq_end, oled_msg_proc_array, ptmsg);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
