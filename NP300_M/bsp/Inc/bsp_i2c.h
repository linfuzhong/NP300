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
#ifndef __i2c_H
#define __i2c_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"

typedef enum{
//	e_i2c1_idx = 0,
	e_i2c2_idx,
	e_i2c_max,
}bsp_i2c_idx_e;


bool bsp_i2c_init(bsp_i2c_idx_e idx);
bool bsp_i2c_deinit(bsp_i2c_idx_e idx);
bool bsp_i2c_write_data(bsp_i2c_idx_e idx, uint8_t slave_addr, uint16_t reg_addr, bool reg_type, uint8_t *data, int16_t data_len);
bool bsp_i2c_read_data(bsp_i2c_idx_e idx, uint8_t slave_addr, uint16_t reg_addr, bool reg_type, uint8_t *data, int16_t data_len);

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
