/*
 * drv_uart.c
 *
 *  Created on: 2020年2月14日
 *      Author: LZ-LOVE
 */
#include "drv_uart.h"

#define UART_RX_BUF_LEN 				(128)

uint8_t   uart_rx_buf[UART_RX_BUF_LEN]  = {0};
static struct rt_semaphore shell_rx_sem; /*定义一个静态信号量*/
rt_ringbuffer_t  uart_rxcb = {0};         /*定义一个 ringbuffer cb */

/***************************************************
 * FinSH uart outtput
 ***************************************************/
void rt_hw_console_output(const char *str)
{
	rt_size_t i = 0, size = 0;
	uint8_t cag_re = '\r';
	size = rt_strlen(str);
	for (i = 0; i < size; i++){
			if (*(str + i) == '\n'){
					LL_USART_TransmitData8(USART1, (uint8_t)cag_re);
					while(!LL_USART_IsActiveFlag_TXE(USART1));
			}
			LL_USART_TransmitData8(USART1, (uint8_t)*(str + i));
			while(!LL_USART_IsActiveFlag_TXE(USART1));
	}
}

/***************************************************
 * FinSH uart inttput
 ***************************************************/
char rt_hw_console_getchar(void)
{
	char ch = 0;
	/* 从 ringbuffer 中拿出数据 */
	while (rt_ringbuffer_getchar(&uart_rxcb, (uint8_t *)&ch) != 1){
				 rt_sem_take(&shell_rx_sem, RT_WAITING_FOREVER);  //接收信号量
	}
	return ((char)ch);
}

/***************************************************
 * @brief This function handles USART1 global interrupt
 **************************************************/
static void finsh_uart_callback(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	if (LL_USART_IsActiveFlag_RXNE(USART1)){
			/* 放入数据到ringbuffer */
			rt_ringbuffer_putchar(&uart_rxcb, (uint8_t)LL_USART_ReceiveData8(USART1));
			rt_sem_release(&shell_rx_sem); 		      	 	//释放信号量
	}

	/* leave interrupt */
	rt_interrupt_leave();
}

/* 串口初始化函数 */
bool finsh_uart_init(void)
{
	bool evt = false;
	/* 初始化串口接收 ringbuffer  */
	rt_ringbuffer_init(&uart_rxcb, uart_rx_buf, UART_RX_BUF_LEN);

	/* 初始化串口接收数据的信号量:设置为二值信号:信号量名字、初始值、信号量模式 FIFO(0x00) */
	rt_sem_init(&(shell_rx_sem), "shell_rx", 0, RT_IPC_FLAG_FIFO);

	/* 初始化Debug串口1 */
	evt = bsp_uart_init(e_uart1_idx, e_uart_rate_115200, finsh_uart_callback);
	return evt;
}
