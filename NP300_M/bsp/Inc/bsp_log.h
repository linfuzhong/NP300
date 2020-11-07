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
#ifndef _BSP_LOG_H
#define _BSP_LOG_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define NP300_LOG_ENABLE      (1)

typedef enum
{
	e_log_begin = 0,  /* 0 */
	e_log_critical,   /* 1 */
	e_log_error,      /* 2 */
	e_log_waring,    /* 3 */
	e_log_entry,      /* 4 */
	e_log_exit,       /* 5 */
	e_log_trace,      /* 6 */
	e_log_debug,      /* 7 */
	e_log_end,        /* 8 */
	e_log_max
}bsp_log_reson_e;

void bsp_log_init(bsp_log_reson_e ereason);
void bsp_log_output(const bsp_log_reson_e ereason, const char *fmt, ...);

uint32_t bsp_tick_get(void);
bool bsp_tick_expire(uint32_t ustarttick, uint32_t utmot);

#if NP300_LOG_ENABLE
#define NP300_LOG(re,fmt,args...)         bsp_log_output((bsp_log_reson_e)(re), fmt, ##args)
#else
#define NP300_LOG(re,fmt,args...)
#endif

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
