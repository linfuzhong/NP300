/**
  ******************************************************************************
  * File Name          : SPI.c
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

/* Includes ------------------------------------------------------------------*/
#include <bsp_spi.h>

/**SPI1 GPIO Configuration
PA5-> SPI1_SCK
PA6-> SPI1_MISO
PA7-> SPI1_MOSI
*/
#define FLASH_SPI_PORT						SPI1
#define FLASH_SPI_GPIO_PORT				GPIOA
#define FLASH_SPI_GPIO_AF					LL_GPIO_AF_5

#define FLASH_CS_Pin 							LL_GPIO_PIN_4

#define FLASH_SCK_PIN 						LL_GPIO_PIN_5
#define FLASH_MISO_PIN 						LL_GPIO_PIN_6
#define FLASH_MOSI_PIN 						LL_GPIO_PIN_7

/**SPI3 GPIO Configuration
PC10   ------> SPI3_SCK
PC12   ------> SPI3_MOSI
*/
#define LCD_SPI_PORT							SPI3
#define LCD_SPI_GPIO_PORT					GPIOC
#define LCD_SPI_GPIO_AF					  LL_GPIO_AF_6

#define LCD_SCK_PIN 							LL_GPIO_PIN_10
#define LCD_MOSI_PIN							LL_GPIO_PIN_12


typedef struct 
{
	SPI_TypeDef  *spi_port;
	GPIO_TypeDef *spi_gpio_x;
	uint32_t      spi_pin[3];
	uint32_t      spi_clock_periphs;
	uint32_t 			spi_port_af;
	uint32_t			dma_clock_periphs;
	IRQn_Type     dma_irqn_e;
	DMA_TypeDef   *dma_port;
	uint32_t      dma_channel;
	bool          spi_dma_enable;	
}bsp_spi_t;

static const bsp_spi_t spi_config_array [e_spi_max] = 
{
	{FLASH_SPI_PORT, 
	 FLASH_SPI_GPIO_PORT, 
	 FLASH_SCK_PIN,  
	 FLASH_MISO_PIN, 
	 FLASH_MOSI_PIN,
	 LL_AHB2_GRP1_PERIPH_GPIOA, 
	 FLASH_SPI_GPIO_AF, 
	 LL_AHB1_GRP1_PERIPH_DMA2,
	 DMA2_Channel2_IRQn,
	 DMA2,
	 LL_DMA_CHANNEL_2,
	 false},
	
	{LCD_SPI_PORT,   
	 LCD_SPI_GPIO_PORT, 
	 LCD_SCK_PIN, 
	 0, 
	 LCD_MOSI_PIN, 
	 LL_AHB2_GRP1_PERIPH_GPIOC, 
	 LCD_SPI_GPIO_AF, 
	 LL_AHB1_GRP1_PERIPH_DMA2,
	 DMA2_Channel2_IRQn,
	 DMA2,
	 LL_DMA_CHANNEL_2,
	 true},
};

/**
 * @brief  SPI init function
 * @param  port_e:bsp_spi1/bsp_spi3
 * @return none
 **/
bool bsp_spi_init(bsp_spi_port_e port_e)
{
  LL_SPI_InitTypeDef 	  SPI_InitStruct 		= {0};
  LL_GPIO_InitTypeDef 	GPIO_InitStruct 	= {0};
  if ( port_e >= e_spi_max ){
	  return false;
  }
  switch (port_e){
  case e_spi1_idx:
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
	  break;

  case e_spi3_idx:
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
	  break;

  default:
	  return false;
  }

	LL_AHB2_GRP1_EnableClock(spi_config_array[port_e].spi_clock_periphs);
	GPIO_InitStruct.Pin 				= spi_config_array[port_e].spi_pin[0]|spi_config_array[port_e].spi_pin[1]|spi_config_array[port_e].spi_pin[2];
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate 	= spi_config_array[port_e].spi_port_af;
	LL_GPIO_Init(spi_config_array[port_e].spi_gpio_x, &GPIO_InitStruct);
	
	if (spi_config_array[port_e].spi_dma_enable){
		  /* DMA controller clock enable */
			LL_AHB1_GRP1_EnableClock(spi_config_array[port_e].dma_clock_periphs);

			/* DMA2_Channel2_IRQn interrupt configuration */
			NVIC_SetPriority(spi_config_array[port_e].dma_irqn_e, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
			NVIC_EnableIRQ(spi_config_array[port_e].dma_irqn_e);

			/* SPI3 DMA Init SPI3_TX*/
			LL_DMA_SetPeriphRequest(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_REQUEST_3);
			LL_DMA_SetDataTransferDirection(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
			LL_DMA_SetChannelPriorityLevel(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_PRIORITY_MEDIUM);
			LL_DMA_SetMode(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_MODE_NORMAL);
			LL_DMA_SetPeriphIncMode(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_PERIPH_NOINCREMENT);
			LL_DMA_SetMemoryIncMode(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_MEMORY_INCREMENT);
			LL_DMA_SetPeriphSize(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_PDATAALIGN_BYTE);
			LL_DMA_SetMemorySize(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel, LL_DMA_MDATAALIGN_BYTE);	
	}
  SPI_InitStruct.TransferDirection 	= LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode 							= LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth 					= LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity 			= LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase 				= LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS 								= LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate 					= LL_SPI_BAUDRATEPRESCALER_DIV2;
  SPI_InitStruct.BitOrder 					= LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation 		= LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly 						= 7;
  LL_SPI_Init(spi_config_array[port_e].spi_port, &SPI_InitStruct);
  LL_SPI_SetStandard(spi_config_array[port_e].spi_port, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_DisableNSSPulseMgt(spi_config_array[port_e].spi_port);
  LL_SPI_SetRxFIFOThreshold(spi_config_array[port_e].spi_port, LL_SPI_RX_FIFO_TH_QUARTER);
  LL_SPI_Enable(spi_config_array[port_e].spi_port);
  return true;
}

/**
 * @brief  SPI deinit function
 * @param  port_e:bsp_spi1/bsp_spi3
 * @return none
 **/
bool bsp_spi_deinit(bsp_spi_port_e port_e)
{
  LL_GPIO_InitTypeDef 	GPIO_InitStruct 	= {0};
  if (port_e >= e_spi_max ){
	    return false;
  }
	LL_AHB2_GRP1_EnableClock(spi_config_array[port_e].spi_clock_periphs);
	
	GPIO_InitStruct.Pin 				= spi_config_array[port_e].spi_pin[0]|spi_config_array[port_e].spi_pin[1]|spi_config_array[port_e].spi_pin[2];
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate 	= LL_GPIO_AF_0;
	LL_GPIO_Init(spi_config_array[port_e].spi_gpio_x, &GPIO_InitStruct);
	
	if (spi_config_array[port_e].spi_dma_enable){
			LL_DMA_DeInit(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel);
	}
  LL_SPI_DeInit(spi_config_array[port_e].spi_port);
  return true;
}

/**
 * @brief  SPI read data function
 * @param  port_e:bsp_spi1/bsp_spi3
 * @param  *rx_data:read data
 * @param  rx_len:data len
 * @return rx_len
 **/
int16_t bsp_spi_read_data(bsp_spi_port_e port_e, uint8_t *rx_data, int16_t rx_len)
{
  if ( port_e >= e_spi_max  || rx_len < 0){
			return -1;
  }
	/* 目前只适配SPI1的读函数,因为LCD屏幕无读函数 */
	if (!spi_config_array[port_e].spi_dma_enable){
			int16_t i = 0;
			for	(i = 0; i < rx_len; i++) {
					while( LL_SPI_IsActiveFlag_BSY(spi_config_array[port_e].spi_port) );
					LL_SPI_TransmitData8(spi_config_array[port_e].spi_port, 0x00);

					while( LL_SPI_IsActiveFlag_BSY(spi_config_array[port_e].spi_port) );
					while( !LL_SPI_IsActiveFlag_RXNE(spi_config_array[port_e].spi_port));
					rx_data[i] = LL_SPI_ReceiveData8(spi_config_array[port_e].spi_port);
			}
	
	} else {
		  return -1;
	}
  return rx_len;
}

/**
 * @brief  SPI write data function
 * @param  port_e:bsp_spi1/bsp_spi3
 * @param  *tx_data:write data
 * @param  tx_len:data len
 * @return tx_len
 **/
int16_t bsp_spi_write_data(bsp_spi_port_e port_e, uint8_t *tx_data, int16_t tx_len)
{
  if ( port_e >= e_spi_max || tx_len < 0){
      return -1;
  }
	if (spi_config_array[port_e].spi_dma_enable){
			LL_DMA_DisableChannel(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel);																											/*失能DMA*/
			while(LL_DMA_IsEnabledChannel(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel) != RESET);																		/*等待关闭成功，可进行配置*/

			LL_DMA_SetMemoryAddress(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel,(uint32_t)tx_data);																	/*设置内存地址*/
			LL_DMA_SetPeriphAddress(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel,(uint32_t)&(spi_config_array[port_e].spi_port->DR));/*设置外设地址*/
			LL_DMA_SetDataLength(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel,(uint32_t)tx_len);																			/*设置传输字节数*/

			LL_DMA_EnableChannel(spi_config_array[port_e].dma_port, spi_config_array[port_e].dma_channel);						 																					/*使能DMA*/
			LL_SPI_EnableDMAReq_TX(spi_config_array[port_e].spi_port);

			/*目前只适配DMA2 LL_DMA_CHANNEL_2*/
			while(LL_DMA_IsActiveFlag_TC2(spi_config_array[port_e].dma_port) != SET);
			LL_DMA_ClearFlag_TC2(spi_config_array[port_e].dma_port);
	
	} else {
		int16_t i = 0;
		for(i = 0;  i < tx_len; i++) {
				while( !LL_SPI_IsActiveFlag_TXE(spi_config_array[port_e].spi_port) );
				LL_SPI_TransmitData8(spi_config_array[port_e].spi_port, tx_data[i]);

				while( LL_SPI_IsActiveFlag_BSY(spi_config_array[port_e].spi_port) );

				while( !LL_SPI_IsActiveFlag_RXNE(spi_config_array[port_e].spi_port));
				LL_SPI_ReceiveData8(spi_config_array[port_e].spi_port);
		}
	}

  return tx_len;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
