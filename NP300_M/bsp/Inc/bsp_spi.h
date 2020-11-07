/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef enum{
	e_spi1_idx = 0,
	e_spi3_idx,
	e_spi_max,
}bsp_spi_port_e;

bool bsp_spi_init(bsp_spi_port_e port_e);
bool bsp_spi_deinit(bsp_spi_port_e port_e);

int16_t bsp_spi_read_data(bsp_spi_port_e port_e, uint8_t *rx_data, int16_t rx_len);
int16_t bsp_spi_write_data(bsp_spi_port_e port_e, uint8_t *tx_data, int16_t tx_len);


#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
