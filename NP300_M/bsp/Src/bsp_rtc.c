/**
  ******************************************************************************
  * File Name          : RTC.c
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <bsp_rtc.h>

/* bin格式转换为bcd */
#define BIN2BCD(value) 				(uint8_t)((((value) / 10) << 4) | ((value) % 10))
/* bcd格式转换为bin */
#define BCD2BIN(value) 				(uint8_t)((((uint8_t)((value) & (uint8_t)0xF0) >> (uint8_t)0x04) * 10 ) + ((value) & (uint8_t)0x0F))

/* RTC init function */
void bsp_rtc_init(void)
{
  LL_RTC_InitTypeDef RTC_InitStruct = {0};
  LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
  LL_RTC_DateTypeDef RTC_DateStruct = {0};
	LL_PWR_EnableBkUpAccess();
  /* Peripheral clock enable */
  LL_RCC_EnableRTC();										
  /** Initialize RTC and set the Time and Date */
  RTC_InitStruct.HourFormat 			= LL_RTC_HOURFORMAT_24HOUR;
	extern bool  lsi_enable;
	if (lsi_enable){
			/* 内部LSI  0x7C (AsynchPrescaler(124) + 1) + (SynchPrescaler(255) + 1) = LSI */
			RTC_InitStruct.AsynchPrescaler = 0x7C;
	} else {
			/* 外部LSE  0x7F (AsynchPrescaler(127) + 1) + (SynchPrescaler(255) + 1) = LSE */
			RTC_InitStruct.AsynchPrescaler = 0x7F;
	}
  RTC_InitStruct.SynchPrescaler 	 	 = 0xFF;
  LL_RTC_Init(RTC, &RTC_InitStruct);
	
	/* 2020-01-01 00:00:00 周三 */
  RTC_TimeStruct.TimeFormat  = LL_RTC_TIME_FORMAT_AM_OR_24;
  RTC_TimeStruct.Hours   		 = 0x15;
  RTC_TimeStruct.Minutes 		 = 0x19;
  RTC_TimeStruct.Seconds 		 = 0x20;
  LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);

  RTC_DateStruct.WeekDay 		 = LL_RTC_WEEKDAY_FRIDAY;
  RTC_DateStruct.Day     		 = 0x13;
  RTC_DateStruct.Month   		 = LL_RTC_MONTH_NOVEMBER;
  RTC_DateStruct.Year    		 = 0x20;
  LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
	
	LL_PWR_DisableBkUpAccess();
}

/**
 ******************************************************************************
 ** @brief  更新RTC时间
 ** @param  time_type 时间格式BCD/BIN
 ** @param	pt_time 需要更新的RTC时间
 ** @return TRUE/FALSE
 ******************************************************************************/
bool bsp_rtc_set_time(bsp_rtc_format_e time_type, const bsp_rtc_time_t *pt_time) 
{
	bool u8et = true;
	if (!pt_time){
			return false;
	}
	LL_PWR_EnableBkUpAccess();
	/* Disable the write protection for RTC registers */
	LL_RTC_DisableWriteProtection(RTC);

	/* Set Initialization mode */
	if ( !LL_RTC_EnterInitMode(RTC)){
			switch (time_type){
			case e_rtc_format_bcd:
			{
				LL_RTC_TIME_Config(RTC, LL_RTC_HOURFORMAT_24HOUR,
																(uint32_t)pt_time->hour,
																(uint32_t)pt_time->minute,
																(uint32_t)pt_time->second);
				LL_RTC_DATE_Config(RTC, (uint32_t)(pt_time->week),
																(uint32_t)(pt_time->day),
																(uint32_t)(pt_time->month),
																(uint32_t)(pt_time->year));

			}
			break;

			case e_rtc_format_bin:
			{
				LL_RTC_TIME_Config(RTC, LL_RTC_HOURFORMAT_24HOUR,
																(uint32_t)BIN2BCD(pt_time->hour),
																(uint32_t)BIN2BCD(pt_time->minute),
																(uint32_t)BIN2BCD(pt_time->second));
				LL_RTC_DATE_Config(RTC, (uint32_t)BIN2BCD(pt_time->week),
																(uint32_t)BIN2BCD(pt_time->day),
																(uint32_t)BIN2BCD(pt_time->month),
																(uint32_t)BIN2BCD(pt_time->year));
			}
			break;

			default:
				u8et = false;
			break;
			}
	    /* Exit Initialization mode */
	    LL_RTC_DisableInitMode(RTC);
	} else {
    	u8et = false;
	}
	/* Enable the write protection for RTC registers */
	LL_RTC_EnableWriteProtection(RTC);
	LL_PWR_DisableBkUpAccess();
	return u8et;
}

/**
 ******************************************************************************
 ** @brief  获取RTC时间
 ** @param  time_type 时间格式BCD/BIN
 ** @param  pt_time 获取的RTC时间
 ** @return TRUE/FALSE
 **
 ******************************************************************************/
bool bsp_rtc_get_time(bsp_rtc_format_e time_type, bsp_rtc_time_t *pt_time) 
{
	if (!pt_time){
	    return false;
	}
	uint32_t time,date;
	switch(time_type){
	case e_rtc_format_bcd:
	{		
		time = LL_RTC_TIME_Get(RTC);
		pt_time->hour  		  = (time >> 16) & 0xFF;
		pt_time->minute  		= (time >> 8)  & 0xFF;
		pt_time->second    	=  time & 0xFF;
		
		date = LL_RTC_DATE_Get(RTC);
		pt_time->week			 	= (date >> 24) & 0xFF;
		pt_time->day     		= (date >> 16) & 0xFF;	
		pt_time->month      = (date >> 8)  & 0xFF;
		pt_time->year       =  date & 0xFF;
	}
	break;
	
	case e_rtc_format_bin:
	{
		time = LL_RTC_TIME_Get(RTC);
		pt_time->hour  		  = BCD2BIN( (time >> 16) & 0xFF );
		pt_time->minute  		= BCD2BIN( (time >> 8)  & 0xFF );
		pt_time->second    	= BCD2BIN(  time & 0xFF );
		
		date = LL_RTC_DATE_Get(RTC);
		pt_time->week			 	= BCD2BIN( (date >> 24) & 0xFF );
		pt_time->day     		= BCD2BIN( (date >> 16) & 0xFF );	
		pt_time->month      = BCD2BIN( (date >> 8)  & 0xFF );
		pt_time->year       = BCD2BIN(  date & 0xFF );
	
	}
	break;
	
	default:
	return false;	
	}

	return true;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
