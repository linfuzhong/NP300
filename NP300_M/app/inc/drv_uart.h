/*
 * drv_uart.h
 *
 *  Created on: 2020年2月14日
 *      Author: LZ-LOVE
 */
#ifndef __DRV_UART_H__
#define __DRV_UART_H__
#include "bsp_usart.h"
#include "ringbuffer.h"
#include <rtthread.h>
#include <rthw.h>
#ifdef __cplusplus
extern "C" {
#endif


bool finsh_uart_init(void);

#ifdef __cplusplus
}
#endif
#endif /* _DRV_UART_H_ */
