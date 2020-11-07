/**
  ******************************************************************************
  * File Name          : RTC.h
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __rtc_H
#define __rtc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef struct
{
	uint8_t  second;      ///<��
	uint8_t  minute;      ///<��
	uint8_t  hour;        ///<ʱ
	uint8_t  week;   			///<��
	uint8_t  day;         ///<��
	uint8_t  month;       ///<��
	uint8_t  year;        ///<��
}bsp_rtc_time_t;

typedef enum 
{
	e_rtc_format_bcd = 0,
	e_rtc_format_bin,
	e_rtc_format_max,
}bsp_rtc_format_e;


void bsp_rtc_init(void);
bool bsp_rtc_set_time(bsp_rtc_format_e time_type, const bsp_rtc_time_t *pt_time);
bool bsp_rtc_get_time(bsp_rtc_format_e time_type, bsp_rtc_time_t *pt_time);

#ifdef __cplusplus
}
#endif
#endif /*__ rtc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
