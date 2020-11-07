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

/* Includes ------------------------------------------------------------------*/

#include <rtthread.h>

#include "bsp_log.h"
#include "app_drv_power.h"
#include "app_srv_power.h"

bool app_srv_power_init(void)
{
	app_drv_power_init();                    /* 初始化电源检测和配置脚 */    
	app_drv_power_led_init();
  return true;
}

void app_srv_state(void)
{ 		
  rt_thread_mdelay(500);
  app_drv_power_set_led(true);
  rt_thread_mdelay(500);
  app_drv_power_set_led(false);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
