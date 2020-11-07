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
//OLED���Դ�
//��Ÿ�ʽ����.
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

	/* OLED ��Դʹ�ܽ� */
	GPIO_InitStruct.Pin 				= OLED_VDDB_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_UP;
	LL_GPIO_Init(OLED_VDDB_GPIO_PORT, &GPIO_InitStruct);

	/* OLED ����/���ݽ� */
	GPIO_InitStruct.Pin 				= OLED_DC_PIN;
	GPIO_InitStruct.Mode 				= LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed 			= LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType 	= LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull 				= LL_GPIO_PULL_NO;
	LL_GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStruct);

	/* OLED ��λ�� */
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
 * @brief  ����OLED��Դʹ�ܽ�
 * @param  type:true-ʹ��/false-ʧ��
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
 * @brief   ����oled ��д
 * @param   value :  CMD   д����
 * @param		DATA  д����
 * @return  none
 */
static bool app_drv_oled_dc_set(app_drv_oled_dc_config_e value)
{
	switch (value){
	case CMD:	  /* ����д���� */
		LL_GPIO_ResetOutputPin(OLED_DC_GPIO_PORT, OLED_DC_PIN);
		break;
	case DATA:	/* ����д���� */
		LL_GPIO_SetOutputPin(OLED_DC_GPIO_PORT, OLED_DC_PIN);
		break;
	default:
		return false;
	}
    return true;
}

/**
 * @brief   ����OLED ��λ
 * @param   enable  ��true   ��λ
 * @param		false  ����λ
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
 * @brief   ����OLED CS
 * @param   enable  ��true   ʹ��
 * @param		false  ʧ��
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
 * @brief   OLED д����/����(1�ֽ�)
 * @param   value    ��CMD ����/ DATA ����
 * @param   cmd_data ���������������
 * @return  none
 */
static bool app_drv_oled_write(app_drv_oled_dc_config_e value, uint8_t cmd_data)
{
	int16_t len;
	app_drv_oled_cs_set(true);							/* Ƭѡ */
	app_drv_oled_dc_set(value);							/* ����/���� */
	len = bsp_spi_write_data(e_spi3_idx, &cmd_data, 1);	/*д����*/
	app_drv_oled_cs_set(false);							/*ȡ��Ƭѡ */
	return ( len == 1 ? true : false);
}

/**
 * @brief   ����OLED�Ƿ�ɫ��ʾ
 * @param   color :true-��ɫ��ʾ/false-������ʾ
 * @return  none
 */
void app_drv_oled_color_turn(bool color)
{
	if (color){
			DRV_OLED_WRITE(CMD, 0xA7);					//��ɫ��ʾ
	} else {
			DRV_OLED_WRITE(CMD, 0xA6);					//������ʾ
	}
}

/**
 * @brief   ����OLED�Ƿ�ת��ʾ
 * @param   color :true-��ת��ʾ/false-������ʾ
 * @return  none
 */
void app_drv_oled_display_turn(bool display)
{
	if (display){
			DRV_OLED_WRITE(CMD, 0xC0);//��ת��ʾ
			DRV_OLED_WRITE(CMD, 0xA0);
	} else {
			DRV_OLED_WRITE(CMD, 0xC8);//������ʾ
			DRV_OLED_WRITE(CMD, 0xA1);
	}
}

/**
 * @brief   ����OLED�Ƿ���ʾ
 * @param   enable :true-��ʾ/false-�ر���ʾ
 * @return  none
 */
void app_drv_oled_display_on(bool enable)
{
	DRV_OLED_WRITE(CMD, 0x8D);		//��ɱ�ʹ��
	if (enable){
			DRV_OLED_WRITE(CMD, 0x14);	//������ɱ�
			DRV_OLED_WRITE(CMD, 0xAF);	//������Ļ
	} else {
			DRV_OLED_WRITE(CMD, 0x10);	//�رյ�ɱ�
			DRV_OLED_WRITE(CMD, 0xAE);	//�ر���Ļ
	}
}

/**
 * @brief  OLED fill�����������Ļ
 * @param  fill_Data:Ҫ��������
 * @return ��
 */
static void app_drv_oled_fill(uint8_t fill_data)
{
	uint8_t i,n;
	for (i = 0; i < 8; i++){
			DRV_OLED_WRITE (CMD, 0xB0 + i);  //����ҳ��ַ��0~7��
			DRV_OLED_WRITE (CMD, 0x00);      //������ʾλ�á��е͵�ַ
			DRV_OLED_WRITE (CMD, 0x10);      //������ʾλ�á��иߵ�ַ
			for (n = 0; n < 128; n++) {
					DRV_OLED_WRITE(DATA, fill_data);
			}
	}
}

/**
 * @brief  OLED ����
 * @param  ��
 * @return ��
 */
void app_drv_oled_clear(void)
{
	app_drv_oled_fill(0x00);//����
}

/**
 * @brief  m ^ n����
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
 * @brief  OLED ���ù��λ��
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
 * @brief  OLED ��ʾ�ַ�
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
	c = c_data - ' ';						//�õ����е�ƫ��ֵ
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
 * @brief   OLED��ʾ��������
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
  * @brief  OLED_DrawBMP����ʾBMPλͼ
  * @param  x0,y0 : ��ʼ������(x0:0~127, y0:0~7);
  *	@param	x1,y1 : ���Խ���(������)������(x1:1~128,y1:1~8)
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
 * @brief   OLED�ĳ�ʼ��
 * @param   none
 * @return  none
 */
bool app_drv_oled_Init(void)
{
	/* ��ʼ��OLED�˿� */
	app_drv_oled_port_init();
	/* ����OLED��Դ */
	app_drv_oled_power_set(true);
	/* ��λOLEDģ�� */
	app_drv_oled_rest_set(true);
	rt_thread_mdelay(200);
	app_drv_oled_rest_set(false);
	rt_thread_mdelay(200);
	/* ����OLEDģ�� */
	DRV_OLED_WRITE(CMD, 0xAE);//�ر���ʾ
	DRV_OLED_WRITE(CMD, 0x00);//�����е�λ��ַ
	DRV_OLED_WRITE(CMD, 0x10);//�����и�λ��ַ
	DRV_OLED_WRITE(CMD, 0x40);//������ʼ�е�ַ��ӳ��RAM��ʾ��ʼ��(0x00~0x3F)
	DRV_OLED_WRITE(CMD, 0x81);//���öԱȶ�
	DRV_OLED_WRITE(CMD, 0x80);//1~255;Ĭ��0X7F (��������,Խ��Խ��)
	DRV_OLED_WRITE(CMD, 0xA1);//���ض�������,bit0:0,0->0;1,0->127;  0xa0���ҷ��� 0xA1����
	DRV_OLED_WRITE(CMD, 0xC8);//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��  0xC0���·��� 0xC8����
	DRV_OLED_WRITE(CMD, 0xA6);//������ʾ��ʽ; bit0: 1,������ʾ; 0,������ʾ
	DRV_OLED_WRITE(CMD, 0xA8);//��������·��(1 to 64)
	DRV_OLED_WRITE(CMD, 0x3F);//Ĭ��0X3F(1/64)
	DRV_OLED_WRITE(CMD, 0xD3);//������ʾƫ��(0x00~0x3F)
	DRV_OLED_WRITE(CMD, 0x00);//��ƫ��
	DRV_OLED_WRITE(CMD, 0xD5);//����ʱ�ӷ�Ƶ����,��Ƶ��
	DRV_OLED_WRITE(CMD, 0x80);//[3:0],��Ƶ����;[7:4],��Ƶ��
	DRV_OLED_WRITE(CMD, 0xD9);//����Ԥ�������
	DRV_OLED_WRITE(CMD, 0xF1);//[3:0],PHASE 1;[7:4],PHASE 2;
	DRV_OLED_WRITE(CMD, 0xDA);//����COMӲ����������
	DRV_OLED_WRITE(CMD, 0x12);//[5:4]����
	DRV_OLED_WRITE(CMD, 0xDB);//����VCOMH ��ѹ����
	DRV_OLED_WRITE(CMD, 0x40);//ȡ�����ʵȼ�
	DRV_OLED_WRITE(CMD, 0x20);//����ҳ��ַģʽ(0x00/0x01/0x02)
	DRV_OLED_WRITE(CMD, 0x02);//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	DRV_OLED_WRITE(CMD, 0x8D);//��ɱ����� enable/disable
	DRV_OLED_WRITE(CMD, 0x14);//bit2������(0x14) /�ر�(0x10)
	DRV_OLED_WRITE(CMD, 0xA4);//������ʾ���� bit0: 1,����; 0,�ر� (����/����)(0xA4/0xA5)
	DRV_OLED_WRITE(CMD, 0xA6);//��ʹ�÷�����ʾ (0xA6/A7)
	DRV_OLED_WRITE(CMD, 0xAF);//������ʾ
	app_drv_oled_clear();		  		//����
	return true;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
