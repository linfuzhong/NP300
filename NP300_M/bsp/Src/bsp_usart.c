/**
  ******************************************************************************
  * File Name          : USART.c
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <bsp_usart.h>

#define USART_ENABLE_IRQ                            (1)

/*Finsh USART1 */
#define USB_TX_RX_GPIO_PORT 		                		GPIOA
#define USB_TX_PIN 				                    			LL_GPIO_PIN_9
#define USB_RX_PIN 				                    			LL_GPIO_PIN_10
#define USB_TX_RX_AF                                LL_GPIO_AF_7

/*WIFI USART3*/
#define WIFI_TX_RX_GPIO_PORT                        GPIOC
#define WIFI_TX_PIN                                 LL_GPIO_PIN_4
#define WIFI_RX_PIN                                 LL_GPIO_PIN_5
#define WIFI_TX_RX_AF                               LL_GPIO_AF_7

/**LPUART1 GPIO Configuration
PC0   ------> LPUART1_RX
PC1   ------> LPUART1_TX
*/
#define MODE_TX_RX_GPIO_PORT                        GPIOC
#define MODE_RX_PIN                                 LL_GPIO_PIN_0
#define MODE_TX_PIN                                 LL_GPIO_PIN_1

typedef struct 
{   
	uint32_t            bsp_uart_periphs;
	uint32_t            bsp_uart_pin[2];
	uint32_t            bsp_uart_af;
	IRQn_Type           bsp_uart_irq_e;
	GPIO_TypeDef        *bsp_uart_port;
	USART_TypeDef       *bsp_uart_idx;    
}bsp_uart_config_t;

static const uint32_t uart_baud_rate[e_uart_rate_max] = 
{
	9600, 38400,115200,
};
static const bsp_uart_config_t uart_config_array[e_uart_max_idx] = 
{  
	{LL_AHB2_GRP1_PERIPH_GPIOA,
	 USB_TX_PIN,                USB_RX_PIN,                   /*Finsh USART1 */
	 USB_TX_RX_AF,              USART1_IRQn,
	 USB_TX_RX_GPIO_PORT,       USART1},

	{LL_AHB2_GRP1_PERIPH_GPIOC,                               /*WIFI USART3*/
	 WIFI_TX_PIN,               WIFI_RX_PIN,
	 WIFI_TX_RX_AF,             USART3_IRQn, 
	 WIFI_TX_RX_GPIO_PORT,      USART3},
};

/*USART 中断回调函数*/
static func_cb_void  uart_callback_arry[e_uart_max_idx] = {NULL};

/* USART init function */
bool bsp_uart_init(bsp_uart_idx_e idx, bsp_uart_baud_rate_e rate, func_cb_void cb)
{ 
  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct   = {0};

  if (rate >= e_uart_rate_max || idx  >= e_uart_max_idx){  
      return false;
  } 
  LL_AHB2_GRP1_EnableClock(uart_config_array[idx].bsp_uart_periphs);        /* GPIO时钟初始化 */
  
  switch (idx){
  case e_uart1_idx:
      LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);                 /* UART1时钟初始化*/
  break;
      
  case e_uart3_idx:
      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);                 /* UART3时钟初始化*/
  break;
  
  default:
  break;  
  }
  /* GPIO初始化*/ 
  GPIO_InitStruct.Pin 						= uart_config_array[idx].bsp_uart_pin[0] | uart_config_array[idx].bsp_uart_pin[1];
  GPIO_InitStruct.Mode 						= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 					= LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType 			= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 						= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate 			= uart_config_array[idx].bsp_uart_af;
  LL_GPIO_Init(uart_config_array[idx].bsp_uart_port, &GPIO_InitStruct);

#if USART_ENABLE_IRQ
  /* USART interrupt Init */
  NVIC_SetPriority(uart_config_array[idx].bsp_uart_irq_e, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(uart_config_array[idx].bsp_uart_irq_e);
  uart_callback_arry[idx] = cb;
#endif
  
  USART_InitStruct.BaudRate 						= uart_baud_rate[rate];
  USART_InitStruct.DataWidth 						= LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits 						= LL_USART_STOPBITS_1;
  USART_InitStruct.Parity 							= LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection 		= LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl 	= LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling 				= LL_USART_OVERSAMPLING_16;  
  LL_USART_Init(uart_config_array[idx].bsp_uart_idx, &USART_InitStruct);
  
  LL_USART_DisableOverrunDetect(uart_config_array[idx].bsp_uart_idx);
  LL_USART_DisableDMADeactOnRxErr(uart_config_array[idx].bsp_uart_idx);
  LL_USART_ConfigAsyncMode(uart_config_array[idx].bsp_uart_idx);
  LL_USART_Enable(uart_config_array[idx].bsp_uart_idx);
  
#if USART_ENABLE_IRQ
  LL_USART_EnableIT_RXNE(uart_config_array[idx].bsp_uart_idx); /* 使能接收中断 */
#endif
  return true;
}
	
/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
	if (uart_callback_arry[e_uart1_idx] != NULL){
			uart_callback_arry[e_uart1_idx]();
	}
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
	if (uart_callback_arry[e_uart3_idx] != NULL){
			uart_callback_arry[e_uart3_idx]();
	}
}

/* USART deinit function */
bool bsp_uart_deinit(bsp_uart_idx_e idx)
{  
	LL_GPIO_InitTypeDef GPIO_InitStruct   = {0};
  if (idx >= e_uart_max_idx){  
      return false;
  }
	LL_AHB2_GRP1_EnableClock(uart_config_array[idx].bsp_uart_periphs);        /* GPIO时钟初始化 */

  GPIO_InitStruct.Pin 						= uart_config_array[idx].bsp_uart_pin[0] | uart_config_array[idx].bsp_uart_pin[1];
	GPIO_InitStruct.Mode 						= LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Speed 					= LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType 			= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 						= LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate 			= LL_GPIO_AF_0;
  LL_GPIO_Init(uart_config_array[idx].bsp_uart_port, &GPIO_InitStruct);
	
	uart_callback_arry[idx] = NULL;
	LL_USART_DeInit(uart_config_array[idx].bsp_uart_idx);
	return true;
}	
/* LPUART1 init function */

void MX_LPUART1_UART_Init(void)
{
  LL_LPUART_InitTypeDef LPUART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPUART1);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

  GPIO_InitStruct.Pin 									= MODE_RX_PIN|MODE_TX_PIN;
  GPIO_InitStruct.Mode 									= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 								= LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType 						= LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull 									= LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate 						= LL_GPIO_AF_8;
  LL_GPIO_Init(MODE_TX_RX_GPIO_PORT, &GPIO_InitStruct);

  LPUART_InitStruct.BaudRate 						= 209700;
  LPUART_InitStruct.DataWidth 					= LL_LPUART_DATAWIDTH_8B;
  LPUART_InitStruct.StopBits 						= LL_LPUART_STOPBITS_1;
  LPUART_InitStruct.Parity 							= LL_LPUART_PARITY_NONE;
  LPUART_InitStruct.TransferDirection 	= LL_LPUART_DIRECTION_TX_RX;
  LPUART_InitStruct.HardwareFlowControl = LL_LPUART_HWCONTROL_NONE;
  LL_LPUART_Init(LPUART1, &LPUART_InitStruct);
  LL_LPUART_Enable(LPUART1);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
