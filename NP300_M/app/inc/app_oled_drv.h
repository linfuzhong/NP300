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
#ifndef _APP_DRV_OLED_H
#define _APP_DRV_OLED_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"
typedef enum{
	e_char_1005  = 0,
	e_char_1206,
	e_char_1608,
}app_drv_oled_char_size_e;

typedef enum{
	e_hz_1206   = 0,
	e_hz_1608,
}app_drv_oled_hz_size_e;

typedef enum{
  e_bat_four  = 0,
  e_bat_three,
  e_bat_two,
  e_bat_one,
  e_bat_zero,
  e_bat_none,
}app_drv_oled_bmp_e;

bool app_drv_oled_init(void);
void app_drv_oled_color_turn(bool color);
void app_drv_oled_display_turn(bool display);
void app_drv_oled_display_on(bool enable);
void app_drv_oled_clear(void);

bool app_drv_oled_show_char(app_drv_oled_char_size_e size, uint8_t x, uint8_t y, uint8_t c_data);
bool app_drv_oled_show_char_string(app_drv_oled_char_size_e size, uint8_t x, uint8_t y, const char *fmt, ...);

bool app_drv_oled_show_chinese(app_drv_oled_hz_size_e size, uint8_t x, uint8_t y, uint8_t no);

bool app_drv_oled_show_bmp(app_drv_oled_bmp_e bmp, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

#ifdef __cplusplus
}
#endif
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
