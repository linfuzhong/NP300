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
#include <rtthread.h>

#include "bsp_log.h"
#include "bsp_spi.h"
#include <app_drv_oled.h>
#include <app_srv_oled.h>
#include <app_srv_sample.h>

bool app_srv_dispaly_init(void)
{
  /* 初始化SPI */
	if ( !bsp_spi_init(e_spi3_idx)){
			return false;
	}
  /* 初始化OLED */
	if ( !app_drv_oled_Init()){
			return false;
	}
  /* 界面排版 */
  return true;
}

bool app_srv_display_state(app_display_message_e e_dispaly)
{
  app_srv_sample_data_t sample_data = {0};
  switch(e_dispaly){
    case e_display_bat:
    {
			app_drv_oled_show_bmp(e_bat_four, 111, 0, 127, 1);       
    }

      break;
    case e_display_sample:
    {
      app_srv_sample_data_get(&sample_data);
      app_drv_oled_show_char_string(e_char_1206, 10, 4, "%02d.%02d",sample_data.sample_temp / 100, sample_data.sample_temp % 100);
      app_drv_oled_show_chinese(e_hz_1206, 40, 4, 9);
      
      app_drv_oled_show_char_string(e_char_1206, 80, 4, "%02d.%02d",sample_data.sample_humi / 100, sample_data.sample_humi % 100);
      app_drv_oled_show_char(e_char_1206, 110, 4,'%');
    }
      break;
    case e_display_rtc:
    {
    
    
    } 
      break;
    case e_dispaly_wifi:
    {
    
    
    }  
      break;
    default:
      return false; 
  }
  return true;

}




















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
