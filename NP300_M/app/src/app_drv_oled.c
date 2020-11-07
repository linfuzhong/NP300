/**
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
#include "app_drv_oled.h"
#include "app_drv_oled_font.h"
#include "bsp_spi.h"
#include "rtthread.h"
#include <stdio.h>
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127

#define OLED_VDDB_PIN 							LL_GPIO_PIN_12
#define OLED_VDDB_GPIO_PORT 				GPIOA

#define OLED_DC_PIN 								LL_GPIO_PIN_11
#define OLED_DC_GPIO_PORT 					GPIOC

#define OLED_RST_PIN 								LL_GPIO_PIN_2
#define OLED_RST_GPIO_PORT 					GPIOD

#define OLED_CS_PIN									LL_GPIO_PIN_15
#define OLED_CS_GPIO_PORT 					GPIOA

#define OLED_MAX_COLUMN							(128)

#define OLED_STRING_BUF_LEN 			  (128)

typedef enum{
 	CMD     =    0,
 	DATA    =    1,
}app_drv_oled_dc_config_e;

static bool app_drv_oled_write(app_drv_oled_dc_config_e value, uint8_t cmd_data);

#define DRV_OLED_WRITE(value, cmd_data)         (bool)(app_drv_oled_write((app_drv_oled_dc_config_e)value, (uint8_t)cmd_data))
/**
 * @brief  oled port init function
 * @param  none
 * @return none
 **/
static void app_drv_oled_port_init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);

	/* OLED 电源使能脚 */
	GPIO_InitStruct.Pin 				= OLED_VDDB_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
	LL_GPIO_Init(OLED_VDDB_GPIO_PORT, &GPIO_InitStruct);

	/* OLED 命令/数据脚 */
	GPIO_InitStruct.Pin 				= OLED_DC_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
	LL_GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStruct);

	/* OLED 复位脚 */
	GPIO_InitStruct.Pin 				= OLED_RST_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
	LL_GPIO_Init(OLED_RST_GPIO_PORT, &GPIO_InitStruct);

	/* OLED CS */
	GPIO_InitStruct.Pin 				= OLED_CS_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
	LL_GPIO_Init(OLED_CS_GPIO_PORT, &GPIO_InitStruct);

}

/**
 * @brief  设置OLED电源使能脚
 * @param  type:true-使能/false-失能
 * @return none
 **/
static void app_drv_oled_power_set(bool type)
{
	if (type){
			LL_GPIO_ResetOutputPin(OLED_VDDB_GPIO_PORT, OLED_VDDB_PIN);
	} else {
			LL_GPIO_SetOutputPin(OLED_VDDB_GPIO_PORT, OLED_VDDB_PIN);
	}
}

/**
 * @brief   设置oled 读写
 * @param   value :  CMD   写命令
 * @param		DATA  写数据
 * @return  none
 */
static bool app_drv_oled_dc_set(app_drv_oled_dc_config_e value)
{
	switch (value){
	case CMD:	  /* 拉低写命令 */
		LL_GPIO_ResetOutputPin(OLED_DC_GPIO_PORT, OLED_DC_PIN);
		break;
	case DATA:	/* 拉高写数据 */
		LL_GPIO_SetOutputPin(OLED_DC_GPIO_PORT, OLED_DC_PIN);
		break;
	default:
		return false;
	}
    return true;
}

/**
 * @brief   设置OLED 复位
 * @param   enable  ：true   复位
 * @param		false  不复位
 * @return  none
 */
static void app_drv_oled_rest_set(bool enable)
{
	if (enable){
			LL_GPIO_ResetOutputPin(OLED_RST_GPIO_PORT, OLED_RST_PIN);
	} else{
			LL_GPIO_SetOutputPin(OLED_RST_GPIO_PORT, OLED_RST_PIN);
	}
}

/**
 * @brief   设置OLED CS
 * @param   enable  ：true   使能
 * @param		false  失能
 * @return  none
 */
static void app_drv_oled_cs_set(bool enable)
{
	if (enable){
			LL_GPIO_ResetOutputPin(OLED_CS_GPIO_PORT, OLED_CS_PIN);
	} else{
			LL_GPIO_SetOutputPin(OLED_CS_GPIO_PORT, OLED_CS_PIN);
	}
}

/**
 * @brief   OLED 写命令/数据(1字节)
 * @param   value    ：CMD 命令/ DATA 数据
 * @param   cmd_data ：具体命令和数据
 * @return  none
 */
static bool app_drv_oled_write(app_drv_oled_dc_config_e value, uint8_t cmd_data)
{
	int16_t len;
	app_drv_oled_cs_set(true);							/* 片选 */
	app_drv_oled_dc_set(value);							/* 命令/数据 */
	len = bsp_spi_write_data(e_spi3_idx, &cmd_data, 1);	/*写函数*/
	app_drv_oled_cs_set(false);							/*取消片选 */
	return ( len == 1 ? true : false);
}

/**
 * @brief   设置OLED是否反色显示
 * @param   color :true-反色显示/false-正常显示
 * @return  none
 */
void app_drv_oled_color_turn(bool color)
{
	if (color){
			DRV_OLED_WRITE(CMD, 0xA7);					//反色显示
	} else {
			DRV_OLED_WRITE(CMD, 0xA6);					//正常显示
	}
}

/**
 * @brief   设置OLED是否反转显示
 * @param   color :true-反转显示/false-正常显示
 * @return  none
 */
void app_drv_oled_display_turn(bool display)
{
	if (display){
			DRV_OLED_WRITE(CMD, 0xC0);//反转显示
			DRV_OLED_WRITE(CMD, 0xA0);
	} else {
			DRV_OLED_WRITE(CMD, 0xC8);//正常显示
			DRV_OLED_WRITE(CMD, 0xA1);
	}
}

/**
 * @brief   设置OLED是否显示
 * @param   enable :true-显示/false-关闭显示
 * @return  none
 */
void app_drv_oled_display_on(bool enable)
{
	DRV_OLED_WRITE(CMD, 0x8D);		//电荷泵使能
	if (enable){
			DRV_OLED_WRITE(CMD, 0x14);	//开启电荷泵
			DRV_OLED_WRITE(CMD, 0xAF);	//点亮屏幕
	} else {
			DRV_OLED_WRITE(CMD, 0x10);	//关闭电荷泵
			DRV_OLED_WRITE(CMD, 0xAE);	//关闭屏幕
	}
}

/**
 * @brief  OLED fill，填充整个屏幕
 * @param  fill_Data:要填充的数据
 * @return 无
 */
static void app_drv_oled_fill(uint8_t fill_data)
{
	uint8_t i,n;
	for (i = 0; i < 8; i++){
			DRV_OLED_WRITE (CMD, 0xB0 + i);  //设置页地址（0~7）
			DRV_OLED_WRITE (CMD, 0x00);      //设置显示位置—列低地址
			DRV_OLED_WRITE (CMD, 0x10);      //设置显示位置—列高地址
			for (n = 0; n < 128; n++) {
					DRV_OLED_WRITE(DATA, fill_data);
			}
	}
}

/**
 * @brief  OLED 清屏
 * @param  无
 * @return 无
 */
void app_drv_oled_clear(void)
{
	app_drv_oled_fill(0x00);//清屏
}

/**
 * @brief  m ^ n函数
 * @param  m,n
 * @return result
 */
//static uint32_t app_drv_oled_pow(uint8_t m, uint8_t n)
//{
//	uint32_t result = 1;
//	while (n--) {
//	   result *= m;
//	}
//	return result;
//}

/**
 * @brief  OLED 设置光标位置
 * @param  x,y
 * @return none
 */
static void app_drv_oled_set_address(uint8_t x, uint8_t y)
{
	DRV_OLED_WRITE(CMD, 0xB0 + y);
	DRV_OLED_WRITE(CMD, ( (x & 0xF0) >> 4 ) | 0x10);
	DRV_OLED_WRITE(CMD,   (x & 0x0F) | 0x01 );
}

/**
 * @brief  OLED 显示字符
 * @param  x,y
 * @return none
 */
bool app_drv_oled_show_char(app_drv_oled_char_size_e size, uint8_t x, uint8_t y, uint8_t c_data)
{
	uint8_t c;
	uint8_t i, n;
	uint8_t x_rows, y_rows;
	const uint8_t *asc_p = NULL;
	if ( x > OLED_MAX_COLUMN - 1){
			 x = 0;
			 y += 2;
	}
	c = c_data - ' ';						//得到的行的偏移值
	switch (size){
	case e_char_1206:
	{
		x_rows = 12;
		y_rows = 6;
		asc_p = asc_1206;
	}
		break;

	case e_char_1608:
	{
		x_rows = 16;
		y_rows = 8;
		asc_p = asc_1608;
	}
		break;

	default:
		return false;
	}
	for (n = 0; n < 2; n++){
			app_drv_oled_set_address(x, y + n);
			for (i = 0; i < y_rows; i++){
					DRV_OLED_WRITE(DATA, asc_p[c * x_rows + i + y_rows * n]);
			}
	}
	return true;
}
/**
 * @brief   display the string on the OLED.
 * @param   x       x position
 * @param   y       y position
 * @param   size    size of font
 * @return  true : display success
 *          false: size of font is not support
 */
bool app_drv_oled_show_char_string(app_drv_oled_char_size_e size, uint8_t x, uint8_t y, const char *fmt, ...)
{
    va_list args;
    uint8_t string_buf[OLED_STRING_BUF_LEN] = {0};
    uint8_t *p = NULL;
    uint8_t x_offset;
    switch (size){
    case e_char_1206:
    	x_offset = 6;
    	break;
    case e_char_1608:
    	x_offset = 8;
    	break;
    default:
    	return false;
    }
    va_start(args, fmt);
    vsnprintf((char *)string_buf, OLED_STRING_BUF_LEN, (const char *)fmt, args);
    va_end(args);
    p = string_buf;
    while (*p != '\0'){
				app_drv_oled_show_char(size, x, y, *p);
        x += x_offset;
        p++;
    }
    return true;
}

/**
 * @brief   OLED显示单个汉字
 * @param   x       x position
 * @param   y       y position
 * @param   hz_data chinese
 * @return  none
 */
bool app_drv_oled_show_chinese(app_drv_oled_hz_size_e size, uint8_t x, uint8_t y, uint8_t no)
{      			    
	uint8_t i, n;
	uint8_t x_rows, y_rows;
	const uint8_t *hz_p = NULL;
  switch (size){
  case e_hz_1206:
	{		
		x_rows = 24;
	  y_rows = 12;
	  hz_p   = hz_1206;
	}
  break;
  
  case e_hz_1608:
	{		
		x_rows = 32;
	  y_rows = 16;
		hz_p	 = hz_1608;	
	}		
  break;
  
  default:
  return false;  
  }
	for	(n = 0; n < 2; n++){
			app_drv_oled_set_address(x, y + n);
			for	(i = 0; i < y_rows; i++){
					DRV_OLED_WRITE(DATA, hz_p[no * x_rows + i + y_rows * n]);
			}
	}
  return true;  
}


/**
  * @brief  OLED_DrawBMP，显示BMP位图
  * @param  x0,y0 : 起始点坐标(x0:0~127, y0:0~7);
  *	@param	x1,y1 : 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
  * @return  none
  */
bool app_drv_oled_show_bmp(app_drv_oled_bmp_e bmp, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{ 	
	uint32_t j = 0;
	uint8_t x;
	uint8_t y;
  const uint8_t *bmp_p = NULL;
	if (y1 % 8 == 0){
			y = y1 / 8; 
	} else {
		  y = y1 / 8 + 1;
	}
  switch (bmp){
  case e_bat_four:
    bmp_p = BMP_four;
    break;
  
  case e_bat_three:
    bmp_p = BMP_three;
    break;
  
  case e_bat_two:
    bmp_p = BMP_two;
    break;
  
  case e_bat_one:
    bmp_p = BMP_one;
    break;
  
  case e_bat_zero:
    bmp_p = BMP_zero;
    break;
  
  case e_bat_none:
    bmp_p = BMP_none;
    break;
  
  default:
    return false;
  }
	for (y = y0; y < y1; y++){
			app_drv_oled_set_address(x0, y);
			for (x = x0; x < x1; x++) {      
					DRV_OLED_WRITE(DATA, bmp_p[j++]);    	
			}
	}
  return true;
}

/**
 * @brief   OLED的初始化
 * @param   none
 * @return  none
 */
bool app_drv_oled_Init(void)
{
	/* 初始化OLED端口 */
	app_drv_oled_port_init();
	/* 开启OLED电源 */
	app_drv_oled_power_set(true);
	/* 复位OLED模块 */
	app_drv_oled_rest_set(true);
	rt_thread_mdelay(200);
	app_drv_oled_rest_set(false);
	rt_thread_mdelay(200);
	/* 配置OLED模块 */
	DRV_OLED_WRITE(CMD, 0xAE);//关闭显示
	DRV_OLED_WRITE(CMD, 0x00);//设置列低位地址
	DRV_OLED_WRITE(CMD, 0x10);//设置列高位地址
	DRV_OLED_WRITE(CMD, 0x40);//设置起始行地址及映射RAM显示起始行(0x00~0x3F)
	DRV_OLED_WRITE(CMD, 0x81);//设置对比度
	DRV_OLED_WRITE(CMD, 0x80);//1~255;默认0X7F (亮度设置,越大越亮)
	DRV_OLED_WRITE(CMD, 0xA1);//段重定义设置,bit0:0,0->0;1,0->127;  0xa0左右反置 0xA1正常
	DRV_OLED_WRITE(CMD, 0xC8);//设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数  0xC0上下反置 0xC8正常
	DRV_OLED_WRITE(CMD, 0xA6);//设置显示方式; bit0: 1,反向显示; 0,正常显示
	DRV_OLED_WRITE(CMD, 0xA8);//设置驱动路数(1 to 64)
	DRV_OLED_WRITE(CMD, 0x3F);//默认0X3F(1/64)
	DRV_OLED_WRITE(CMD, 0xD3);//设置显示偏移(0x00~0x3F)
	DRV_OLED_WRITE(CMD, 0x00);//不偏移
	DRV_OLED_WRITE(CMD, 0xD5);//设置时钟分频因子,震荡频率
	DRV_OLED_WRITE(CMD, 0x80);//[3:0],分频因子;[7:4],震荡频率
	DRV_OLED_WRITE(CMD, 0xD9);//设置预充电周期
	DRV_OLED_WRITE(CMD, 0xF1);//[3:0],PHASE 1;[7:4],PHASE 2;
	DRV_OLED_WRITE(CMD, 0xDA);//设置COM硬件引脚配置
	DRV_OLED_WRITE(CMD, 0x12);//[5:4]配置
	DRV_OLED_WRITE(CMD, 0xDB);//设置VCOMH 电压倍率
	DRV_OLED_WRITE(CMD, 0x40);//取消倍率等级
	DRV_OLED_WRITE(CMD, 0x20);//设置页地址模式(0x00/0x01/0x02)
	DRV_OLED_WRITE(CMD, 0x02);//[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	DRV_OLED_WRITE(CMD, 0x8D);//电荷泵设置 enable/disable
	DRV_OLED_WRITE(CMD, 0x14);//bit2，开启(0x14) /关闭(0x10)
	DRV_OLED_WRITE(CMD, 0xA4);//禁用显示开启 bit0: 1,开启; 0,关闭 (白屏/黑屏)(0xA4/0xA5)
	DRV_OLED_WRITE(CMD, 0xA6);//不使用反向显示 (0xA6/A7)
	DRV_OLED_WRITE(CMD, 0xAF);//开启显示
	app_drv_oled_clear();		  		//清屏
	return true;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
