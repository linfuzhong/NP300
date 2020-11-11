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
#ifndef _APP_SRV_SAMPLE_H
#define _APP_SRV_SAMPLE_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"

typedef struct 
{
	uint32_t sample_utime;
	int16_t  sample_temp;
	int16_t  sample_humi;
}app_srv_sample_data_t;

typedef enum{
 e_sample_msg_start = 0,
 e_sample_msg_timeout_1s,
 e_sample_msg_end,
}app_srv_sample_msgq_e;

bool app_srv_sample_init(void);
bool app_srv_sample_runing(void);

bool app_srv_sample_send_msg(app_srv_sample_msgq_e e_sample_msg);

bool app_srv_sample_data_get(app_srv_sample_data_t *pt_data);
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
