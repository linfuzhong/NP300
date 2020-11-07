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

/* Includes ------------------------------------------------------------------*/
#include <bsp_i2c.h>
#include "bsp_log.h"

#define BSP_I2C_MAX_TRANS_LEN						(256)
#define BSP_I2C_DEFALUT_TMOUT						(200)

/**I2C2 GPIO Configuration
PB10-> I2C2_SCL
PB11-> I2C2_SDA
*/
#define SHTX_I2C_GPIO_PORT 					GPIOB
#define SHTX_SCL_PIN 								LL_GPIO_PIN_10
#define SHTX_SDA_PIN 								LL_GPIO_PIN_11
#define SHTX_I2C_GPIO_AF						LL_GPIO_AF_4
#define SHTX_I2C_PORT								I2C2

typedef struct
{
	uint32_t 			 i2c_gpio_periphs;
	uint32_t 			 i2c_gpio_pin[2];
	uint32_t 			 i2c_gpio_af;
	uint32_t 			 i2c_clock_periphs;
	GPIO_TypeDef 	*i2c_gpio_port;
	I2C_TypeDef 	*i2c_port;
}bsp_i2c_config_t;

static const bsp_i2c_config_t i2c_config_array[e_i2c_max] = 
{
	{
	 LL_AHB2_GRP1_PERIPH_GPIOB,
	 SHTX_SCL_PIN,
	 SHTX_SDA_PIN,
	 SHTX_I2C_GPIO_AF,
	 LL_APB1_GRP1_PERIPH_I2C2,
   SHTX_I2C_GPIO_PORT,
	 SHTX_I2C_PORT
	}
};

/**
 * @brief  I2C2 init function
 * @param  none
 * @return none
 **/
bool bsp_i2c_init(bsp_i2c_idx_e idx)
{
  LL_I2C_InitTypeDef   I2C_InitStruct 	= {0};
  LL_GPIO_InitTypeDef  GPIO_InitStruct 	= {0};

	if (idx >= e_i2c_max){
			return false;
	}
  LL_AHB2_GRP1_EnableClock(i2c_config_array[idx].i2c_gpio_periphs);

  GPIO_InitStruct.Pin 						= i2c_config_array[idx].i2c_gpio_pin[0]|i2c_config_array[idx].i2c_gpio_pin[1];
  GPIO_InitStruct.Mode 						= LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed 					= LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType 			= LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull 						= LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate 			= i2c_config_array[idx].i2c_gpio_af;
  LL_GPIO_Init(i2c_config_array[idx].i2c_gpio_port, &GPIO_InitStruct);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(i2c_config_array[idx].i2c_clock_periphs);

  I2C_InitStruct.PeripheralMode 	= LL_I2C_MODE_I2C;
  I2C_InitStruct.Timing 					= 0x10909CEC;
  I2C_InitStruct.AnalogFilter 		= LL_I2C_ANALOGFILTER_ENABLE;
  I2C_InitStruct.DigitalFilter 		= 0;
  I2C_InitStruct.OwnAddress1 			= 0;
  I2C_InitStruct.TypeAcknowledge 	= LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize 			= LL_I2C_OWNADDRESS1_7BIT;
  LL_I2C_Init(i2c_config_array[idx].i2c_port, &I2C_InitStruct);
	
	LL_I2C_EnableAutoEndMode(i2c_config_array[idx].i2c_port);
	LL_I2C_SetOwnAddress2(i2c_config_array[idx].i2c_port, 0, LL_I2C_OWNADDRESS2_NOMASK);
  LL_I2C_DisableOwnAddress2(i2c_config_array[idx].i2c_port);
  LL_I2C_DisableGeneralCall(i2c_config_array[idx].i2c_port);
  LL_I2C_EnableClockStretching(i2c_config_array[idx].i2c_port);
	
	return true;
}

/**
 * @brief  I2C2 deinit function
 * @param  none
 * @return none
 **/
bool bsp_i2c_deinit(bsp_i2c_idx_e idx)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct   = {0};
  if (idx >= e_i2c_max){  
      return false;
  }
	LL_AHB2_GRP1_EnableClock(i2c_config_array[idx].i2c_gpio_periphs);        /* GPIO时钟初始化 */

  GPIO_InitStruct.Pin 						= i2c_config_array[idx].i2c_gpio_pin[0] | i2c_config_array[idx].i2c_gpio_pin[1];
	GPIO_InitStruct.Mode 						= LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Speed 					= LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType 			= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 						= LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate 			= LL_GPIO_AF_0;
  LL_GPIO_Init(i2c_config_array[idx].i2c_gpio_port, &GPIO_InitStruct);
	
	LL_I2C_Disable(i2c_config_array[idx].i2c_port);
	LL_I2C_DeInit(i2c_config_array[idx].i2c_port);
	
	return true;
}

/**
 * @brief  I2C2 write data
 * @param  idx					:I2C端口号
 * @param  slave_addr		:从机地址
 * @param  reg_addr			:寄存器地址
 * @param  reg_type			:true: 16bit reg_addr / false:8bit reg_addr
 * @param  data					:数据
 * @param  data_len			:数据长度
 * @return false/true
 **/
bool bsp_i2c_write_data(bsp_i2c_idx_e idx, uint8_t slave_addr, uint16_t reg_addr, bool reg_type, uint8_t *data, int16_t data_len)
{
	uint8_t  reg_cmd[2] = {0};	
	uint8_t  ui, uy, reg_addr_size;
	uint8_t  sla_add = 0;
	uint32_t utick;
	if (idx >= e_i2c_max){
			return false;
	}
	sla_add = slave_addr << 1;			//从机地址需要左移一位	
	/* 区分从机寄存器地址的位数 */
	if (reg_type){
			reg_addr_size = 2;
			reg_cmd[0]    = reg_addr >> 8;
			reg_cmd[1]    = reg_addr & 0xFF;	  
	} else {
		  reg_addr_size = 1;
			reg_cmd[0]    = reg_addr & 0xFF;
	}

	utick = bsp_tick_get();
	while ( LL_I2C_IsActiveFlag_BUSY(i2c_config_array[idx].i2c_port)) {
		    if (bsp_tick_expire(utick, BSP_I2C_DEFALUT_TMOUT)){
			     return false;
		    }
	}
	/* 起始信号 + 寄存器配置  + 自动停止信号 */
	LL_I2C_HandleTransfer(i2c_config_array[idx].i2c_port, sla_add, LL_I2C_ADDRSLAVE_7BIT, reg_addr_size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
	/* 写寄存器地址 */
	utick = bsp_tick_get();
	for (uy = 0; uy < reg_addr_size; uy ++) {
			 while ( !LL_I2C_IsActiveFlag_TXE(i2c_config_array[idx].i2c_port)) {
			        if (bsp_tick_expire(utick,BSP_I2C_DEFALUT_TMOUT)){
							    return false;
			        }
		   }
			 /*只有当TXE为1时才能写 */
			 LL_I2C_TransmitData8(i2c_config_array[idx].i2c_port, reg_cmd[uy]);
			 if ( LL_I2C_IsActiveFlag_NACK(i2c_config_array[idx].i2c_port) ){
					  return false;
			 }
	}

	/* 写对应寄存器的数据  */
	if (data_len > 0) {
			if (data_len >= BSP_I2C_MAX_TRANS_LEN ) {
					return false;
			}
			/* 起始信号  + 自动停止信号 */
			LL_I2C_HandleTransfer(i2c_config_array[idx].i2c_port, sla_add, LL_I2C_ADDRSLAVE_7BIT, data_len, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
			utick = bsp_tick_get();
			for (ui = 0;  ui < data_len; ui++) {
					 while ( !LL_I2C_IsActiveFlag_TXE(i2c_config_array[idx].i2c_port) ) {
								if (bsp_tick_expire(utick,BSP_I2C_DEFALUT_TMOUT)){
										return false;
								}
					 }
					 /*只有当TXE为1时才能写 */
					 LL_I2C_TransmitData8(i2c_config_array[idx].i2c_port, data[ui]);
					 if ( LL_I2C_IsActiveFlag_NACK(i2c_config_array[idx].i2c_port)){
								return false;
					 }
			}
			if (ui == data_len){
					return true;
			}
	}
	return true;
}

/**
 * @brief  I2C2 read data
 * @param  idx					:I2C端口号
 * @param  slave_addr		:从机地址
 * @param  reg_addr			:寄存器地址
 * @param  reg_type			:true: 16bit reg_addr / false:8bit reg_addr
 * @param  data					:数据
 * @param  data_len			:数据长度
 * @return false/true
 **/
bool bsp_i2c_read_data(bsp_i2c_idx_e idx, uint8_t slave_addr, uint16_t reg_addr, bool reg_type, uint8_t *data, int16_t data_len)
{
	uint8_t  reg_cmd[2] = {0};	
	uint8_t  ui, uy, reg_addr_size;
	uint8_t  sla_add = 0;
	uint32_t utick;
	if (idx >= e_i2c_max){
			return false;
	}
	sla_add = slave_addr << 1;			//从机地址需要左移一位									
	/* 区分从机寄存器地址的位数 */
	if (reg_type){
			reg_addr_size = 2;
			reg_cmd[0]    = reg_addr >> 8;
			reg_cmd[1]    = reg_addr & 0xFF;	  
	} else {
		  reg_addr_size = 1;
			reg_cmd[0]    = reg_addr & 0xFF;
	}

	utick = bsp_tick_get();
	while ( LL_I2C_IsActiveFlag_BUSY(i2c_config_array[idx].i2c_port)) {
				if (bsp_tick_expire(utick, BSP_I2C_DEFALUT_TMOUT)){
			      return false;
		    }
	}
	
	if (reg_addr) {
			LL_I2C_HandleTransfer(i2c_config_array[idx].i2c_port, sla_add, LL_I2C_ADDRSLAVE_7BIT, reg_addr_size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
		
			utick = bsp_tick_get();	
			for (uy = 0; uy < reg_addr_size; uy ++) {
					 while ( !LL_I2C_IsActiveFlag_TXE(i2c_config_array[idx].i2c_port) ) {
								 if (bsp_tick_expire(utick, BSP_I2C_DEFALUT_TMOUT)){
										 return false;
						     }
			     }
					 /*只有当TXE为1时才能写 */
					 LL_I2C_TransmitData8(i2c_config_array[idx].i2c_port, reg_cmd[uy]);
					 if ( LL_I2C_IsActiveFlag_NACK(i2c_config_array[idx].i2c_port) ){
							 return false;
					 }
					 if (uy == reg_addr_size) {
							 while ( !LL_I2C_IsActiveFlag_TXE(i2c_config_array[idx].i2c_port) ) {
										if (bsp_tick_expire(utick, BSP_I2C_DEFALUT_TMOUT)){
												return false;
										}
							}
					 }
			}
	}

	if (data_len > 0) {
			if( data_len > BSP_I2C_MAX_TRANS_LEN ) {
					return false;
			}
			LL_I2C_HandleTransfer(i2c_config_array[idx].i2c_port, sla_add, LL_I2C_ADDRSLAVE_7BIT, data_len, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

			utick = bsp_tick_get();
			for (ui = 0;  ui < data_len; ui++) {
					 while ( !LL_I2C_IsActiveFlag_RXNE(i2c_config_array[idx].i2c_port)) {
								if (bsp_tick_expire(utick, BSP_I2C_DEFALUT_TMOUT)){
									return false;
							 }
					}
					 /* 只有当RXNE为1时才能读 */
					data[ui] = LL_I2C_ReceiveData8(i2c_config_array[idx].i2c_port);
			}
	}
	return true;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
