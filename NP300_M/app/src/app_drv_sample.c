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
#include "app_drv_sample.h"
#include "bsp_i2c.h"
#include <rtthread.h>

#define SHTC3_I2C_ADDR										(0x70)
#define SHTC3_CMD_READ_ID									(0xEFC8)
#define SHTC3_CMD_WAKE_UP   							(0x3517)
#define SHTC3_CMD_SLEEP     							(0xB098)
#define SHTC3_CMD_CS_MEASURI_T_FIRST     	(0x7CA2)
#define SHTC3_CMD_CS_MEASURI_LP_T_FIRST  	(0x6458)
#define SHTC3_CMD_MEASURI_T_FIRST        	(0x7866)
#define SHTC3_CMD_MEASURI_LP_T_FIRST     	(0x6096)
#define SHTC3_CMD_MEASURI_LP_T_FIRST     	(0x6096)

#define CRC_POLYNOMIAL      							(0x131)

/* 温度转化 */
#define BTC2UTC(temp)											(int16_t)(((17500 * (uint32_t) temp) >> 16) - 4500)	
/* 湿度转化 */
#define BRH2URH(humi)											(int16_t)((10000 * (uint32_t) humi) >> 16)

/* SHTC3 传输数据 CRC校验 */
static bool shtx_check_crc(uint8_t data[], uint8_t nbrofbytes, uint8_t checksum)
{
  uint8_t bit;        // bit mask
  uint8_t crc = 0xFF; // calculated checksum
  uint8_t byteCtr;    // byte counter
  // calculates 8-Bit checksum with given polynomial
  for (byteCtr = 0; byteCtr < nbrofbytes; byteCtr++) {
       crc ^= (data[byteCtr]);
       for (bit = 8; bit > 0; --bit) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ CRC_POLYNOMIAL;
            } else {
                crc = (crc << 1);
            }
       }
  }
	return (crc != checksum ? false : true);
}

static bool app_drv_sample_write(uint16_t reg_addr, uint8_t *data, int16_t data_len)
{
	return bsp_i2c_write_data(e_i2c2_idx, SHTC3_I2C_ADDR, reg_addr, true, data, data_len);
}

//static bool app_drv_sample_read_cmd(uint16_t reg_addr, uint8_t *data, int16_t data_len)
//{
//	return bsp_i2c_read_data(e_i2c2_idx, SHTC3_I2C_ADDR, reg_addr, true, data, data_len);
//}

static bool app_drv_sample_read(uint8_t *data, int16_t data_len)
{
	return bsp_i2c_read_data(e_i2c2_idx, SHTC3_I2C_ADDR, 0, false, data, data_len);
}

/* SHTC3温湿度数据的获取 */
bool app_drv_sample_shtc3(int16_t *pt_temp, int16_t *pt_humi)
{
    uint8_t utemp[8] 	     = {0};
    uint8_t retry_count    = 1;				//加上第一次进来的一次，总共重试次数为2次
    uint8_t sample_machine = 0;
    uint8_t ret            = false;
    uint16_t temp, humi;
    if (pt_temp == NULL || pt_humi == NULL){
				return false;
    }
next:
    switch (sample_machine) {
    case 0 :
    	ret = app_drv_sample_write(SHTC3_CMD_WAKE_UP, utemp, 0);
        break;
    case 1 :
    	ret = app_drv_sample_write(SHTC3_CMD_MEASURI_T_FIRST, utemp, 0);
        break;
    case 2 :
    	ret = app_drv_sample_read(utemp, 6);
			if (shtx_check_crc(utemp, 2, utemp[2]) && shtx_check_crc(utemp + 3, 2, utemp[5])) {
					temp = (utemp[0] << 8) | utemp[1];
					*pt_temp = BTC2UTC(temp);

					humi = (utemp[3] << 8) | utemp[4];
					*pt_humi = BRH2URH(humi);
			}
        break;
    case 3 :
    	ret = app_drv_sample_write(SHTC3_CMD_SLEEP, utemp, 0);
        break;
    default :
        return true;
    }
    if (ret){
        sample_machine ++;
    } else {
        if (retry_count > 0) {
						retry_count--;
						bsp_i2c_init(e_i2c2_idx);
						sample_machine = 0;
        } else {
            return false;
        }
    }
    rt_thread_mdelay(20);
    goto next;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
