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
#include "app_oled_sm.h"
#include "os_sm.h"
#include "bsp_log.h"
#include "os_mgq.h"
#include <app_oled_srv.h>
#include <app_sample_srv.h>
#include <app_oled_drv.h>
#include <bsp_rtc.h>

#define LOG_SM_DISPLAY(re, fmt, args...)			NP300_LOG(re, "oled sm:"fmt, ##args)

#define DISPLAY_SAMPLE_UPDATE_TIME						(5)
#define DISPLAY_RTC_UPDATE_TIME								(30)
typedef enum
{
	e_event_display_init,
	e_event_display_timeout,
	e_event_display_key,
	e_event_display_max,
}app_oled_sm_evt_e;

typedef enum
{
	e_state_display_sample_data,						/* 采集信息显示 */
	e_state_display_dev_param,							/* 设备信息*/
	e_state_display_sleep,									/* 睡眠模式 */
	e_state_display_max,
}app_oled_sm_sta_e;

/*LCD 状态机结构体 */
typedef uint8(*app_sm_sta_mach_proc_t)(app_oled_sm_evt_e sta, void* ptdata);
typedef struct 
{
	const char*              str_sta_name;
	app_sm_sta_mach_proc_t 	 proc;
}app_oled_sm_sta_mach_t;

typedef struct
{
	uint8  									 u8sm_sta;
	uint16 	      					 time_out;
}app_oled_sm_sta_info_t;

static app_oled_sm_sta_info_t   oled_sm_info;

static uint8 app_display_sensor_data(app_oled_sm_evt_e evt, void* ptdata);
static uint8 app_display_dev_param(app_oled_sm_evt_e evt, void* ptdata);
static uint8 app_dispaly_sleep(app_oled_sm_evt_e evt, void* ptdata);

static const app_oled_sm_sta_mach_t oeld_sm_sta_proc_array[e_state_display_max] = 
{
	{"data", 								app_display_sensor_data},
	{"param", 							app_display_dev_param},
	{"sleep", 							app_dispaly_sleep},
};

/* 更新显示温湿度 */
static bool app_display_updtate_sample(void)
{	  
	app_srv_sample_data_t sample_data = {0};
	if ( app_srv_sample_data_get(&sample_data)){
			 app_drv_oled_show_char_string(e_char_1206, 10, 3, "%02d.%02d",sample_data.sample_temp / 100, sample_data.sample_temp % 100);
			 app_drv_oled_show_chinese(e_hz_1206, 40, 3, 9);					//℃

			 app_drv_oled_show_char_string(e_char_1206, 80, 3, "%02d.%02d",sample_data.sample_humi / 100, sample_data.sample_humi % 100);
			 app_drv_oled_show_char(e_char_1206, 110, 3,'%');				  //%
			 return true;
	} else {
			 return false;
	}
}	

/* 更新显示RTC时间 */
static bool app_display_upddate_rtc(void)
{
	bsp_rtc_time_t rtc_time = {0};
	if ( bsp_rtc_get_time(e_rtc_format_bin, &rtc_time)){
		   app_drv_oled_show_char_string(e_char_1005, 35, 0, "%02d.%02d %02d:%02d",rtc_time.month, rtc_time.day,rtc_time.hour, rtc_time.minute);
		   return true;
	} else {
			 return false;
	}
}	


static uint8 app_display_sensor_data(app_oled_sm_evt_e evt, void* ptdata)
{
	app_oled_sm_sta_info_t *pt_sm = &oled_sm_info;
	static uint16 sample_cnt = DISPLAY_SAMPLE_UPDATE_TIME;
	static uint16 rtc_cnt    = DISPLAY_RTC_UPDATE_TIME;
	uint8 u8Ret = e_state_display_sample_data;
	uint8 key_type;
	app_mgq_pt pt_msg = (app_mgq_pt)ptdata;
	
	key_type = pt_msg->pt_mgdata[0];

	
	switch (evt){
	case e_event_display_init:
    pt_sm->time_out = 0;
  
		break;

	case e_event_display_timeout:
	  sample_cnt ++;
		rtc_cnt ++;
	  if (sample_cnt >= DISPLAY_SAMPLE_UPDATE_TIME){
				sample_cnt = 0;
				app_display_updtate_sample();
			  
		}
		if (rtc_cnt >= DISPLAY_RTC_UPDATE_TIME){
				rtc_cnt = 0;
				app_display_upddate_rtc();
		}

		break;
	case e_event_display_key:
		break;

    default:
        break;

	}
	return u8Ret;
}

static uint8 app_display_dev_param(app_oled_sm_evt_e evt, void* ptdata)
{
	uint8 u8Ret = e_state_display_dev_param;
	uint8 key_type;
	app_mgq_pt pt_msg = (app_mgq_pt)ptdata;
	
	key_type = pt_msg->pt_mgdata[0];

	switch (evt){
	case e_event_display_init:
		break;

	case e_event_display_timeout:

		break;
	case e_event_display_key:
		break;

    default:
        break;

	}
	return u8Ret;
}

static uint8 app_dispaly_sleep(app_oled_sm_evt_e evt, void* ptdata)
{
	uint8 u8Ret = e_state_display_sleep;
	uint8 key_type;
	app_mgq_pt pt_msg = (app_mgq_pt)ptdata;
	
	key_type = pt_msg->pt_mgdata[0];

	switch (evt){
	case e_event_display_init:
		break;

	case e_event_display_timeout:

		break;
	case e_event_display_key:
		break;

    default:
        break;

	}
	return u8Ret;
}

/******************************************************************************
**  状态机事件处理
******************************************************************************/
static void app_oled_sm_sta_proc(app_oled_sm_evt_e evt, app_mgq_pt ptdata)
{
    uint8 u8cur_sta   = 0;
    uint8 u8tran_sta = 0;
    const app_oled_sm_sta_mach_t * p_array = NULL;

    u8cur_sta  = oled_sm_info.u8sm_sta;
    u8tran_sta = u8cur_sta;

    if (( evt < e_event_display_max) && ( u8cur_sta < e_state_display_max)){
STA_INIT:
        p_array = &oeld_sm_sta_proc_array[u8cur_sta];
        if (NULL != p_array->proc){
            u8tran_sta = p_array->proc(evt, ptdata);	 //执行并获取下一个状态
        }
        if (u8tran_sta != u8cur_sta){
            /* 打印输出当前状态和下一个状态 */
            LOG_SM_DISPLAY(e_log_trace, "Now=%s,Next=%s", 
												   oeld_sm_sta_proc_array[(u8cur_sta)].str_sta_name, 
													 oeld_sm_sta_proc_array[(u8tran_sta)].str_sta_name);
            u8cur_sta = u8tran_sta;
            oled_sm_info.u8sm_sta = u8cur_sta;
            evt = e_event_display_init;
            goto STA_INIT;
        } else{
            // same mode
        }
    }
}

bool app_oled_sm_sta_init(void)
{
	memset(&oled_sm_info, 0, sizeof(oled_sm_info));
	oled_sm_info.u8sm_sta = e_state_display_sample_data;
	app_oled_sm_sta_proc(e_event_display_init, NULL);
	return true;
}

bool app_oled_sm_sta_deinit(void)
{
	app_oled_sm_sta_proc(e_event_display_init, NULL);
  return true;
}

void app_oled_sm_sta_timeout(void)
{
	app_oled_sm_sta_proc(e_event_display_timeout, NULL);
}

void app_oled_sm_sta_key(app_mgq_pt pt_msg)
{
	app_oled_sm_sta_proc(e_event_display_key, pt_msg);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
