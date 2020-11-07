/**
  ******************************************************************************
  * File Name          : bsp_ulog.c
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
#include "bsp_log.h"
#include <rtthread.h>
#include <stdio.h>

#define LOG_SIZE									(128)
static int8_t log_buf[LOG_SIZE] = {0};

static bsp_log_reson_e ge_uart_log_lv = e_log_end;

static const char* const gt_reson_tab[e_log_end] = 
{
	"FTL",  /* fatal    */
	"CRT",  /* critical */
	"ERR",  /* error    */
	"WRN",  /* warning  */
	"ENT",  /* entry    */
	"EXT",  /* exit     */
	"TRC",  /* trace    */
	"DBG",  /* debug    */
};

void bsp_log_init(bsp_log_reson_e ereason)
{
	if ( ereason >= e_log_end){
			ereason = e_log_end;
	} 
	ge_uart_log_lv = ereason;
}

void bsp_log_output(const bsp_log_reson_e ereason, const char *fmt, ...)
{
	uint32_t tick = 0;
	va_list args;  
	if (ereason > ge_uart_log_lv){
			return;
	}
	tick = bsp_tick_get();
	va_start(args, fmt);
	vsnprintf((char *)log_buf, LOG_SIZE, (const char *)fmt, args);	
	va_end(args);	
	rt_kprintf("%08d[%s]%s\n", tick, gt_reson_tab[ereason], log_buf);	
}


uint32_t bsp_tick_get(void) 
{
	return (uint32_t)rt_tick_get();
}

bool bsp_tick_expire(uint32_t ustarttick, uint32_t utmot) 
{
	uint32_t tick = rt_tick_get();
	return ( (tick - ustarttick) > utmot);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
