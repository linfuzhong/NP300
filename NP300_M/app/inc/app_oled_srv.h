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
#ifndef _APP_OLED_SRV_H
#define _APP_OLED_SRV_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"
typedef enum
{ 
  e_display_bat = 0,
  e_display_sample,
  e_display_rtc,
  e_dispaly_wifi,
  e_display_mgs_end   = 32,
}app_display_e;

bool app_srv_dispaly_init(void);
void app_srv_display_runing(void);

bool app_srv_display_send_msg_timeout(void);
bool app_srv_display_send_msg_key(uint8 key_value);

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