/**
  ******************************************************************************
  * File Name          : I2C.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _APP_OLED_MGQ_H
#define _APP_OLED_MGQ_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "os_types.h"
#include "os_mgq.h"

typedef enum
{
  e_oled_mgq_start = 0,
	e_oled_mgq_timeout,
	e_oled_mgq_key,
	e_oled_mgq_end,
	e_oled_mgq_max
} app_oled_mgq_e;

bool app_oled_srv_init(void);

bool app_oled_srv_sm_msg_proc(app_mgq_pt ptmsg);


#ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
