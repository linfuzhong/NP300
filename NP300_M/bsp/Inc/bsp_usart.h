/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef enum
{
	e_uart1_idx = 0,
	e_uart3_idx,
	e_uart_max_idx,
}bsp_uart_idx_e;

typedef enum
{
	e_luart1_idx = 0,
	e_luart_max_idx,
}bsp_luart_idx_e;

typedef enum
{
	e_uart_rate_9600 = 0,
	e_uart_rate_38400,
	e_uart_rate_115200,
	e_uart_rate_max,
}bsp_uart_baud_rate_e;

bool bsp_uart_init(bsp_uart_idx_e idx, bsp_uart_baud_rate_e rate, func_cb_void back);
bool bsp_uart_deinit(bsp_uart_idx_e idx);


void MX_LPUART1_UART_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
