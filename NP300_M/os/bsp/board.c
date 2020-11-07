/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "drv_uart.h"
#include "main.h"

#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
extern uint32_t SystemCoreClock;
bool  lsi_enable = false;
static bool  hsi_enable = false;
#define WAIT_LSE_READ_TIMEOUT		(1000)   /* 1s when tick set to 1ms */
#define WAIT_HSE_READ_TIMEOUT		(1000)   /* 1s when tick set to 1ms */

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
	volatile uint32_t lse_timeout = WAIT_LSE_READ_TIMEOUT;
	volatile uint32_t hse_timeout = WAIT_HSE_READ_TIMEOUT;
	uint32_t hs_source			  		= LL_RCC_PLLSOURCE_HSE;
	uint32_t rcc_pllm			  			= LL_RCC_PLLM_DIV_1;

	LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
	while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_4);

	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	/* 配置高速时钟 */
	LL_RCC_HSE_Enable();
	/* Wait till HSE is ready */
	while( (hse_timeout != 0) && (LL_RCC_HSE_IsReady() != 1) ){
			if ( LL_SYSTICK_IsActiveCounterFlag() ){
					hse_timeout --;
			}
			if (hse_timeout == 0){
					hsi_enable = true;
					LL_RCC_HSE_Disable();
					break;
			}
	}
	if (hsi_enable){
			hs_source = LL_RCC_PLLSOURCE_HSI;
			rcc_pllm  = LL_RCC_PLLM_DIV_2;
			LL_RCC_HSI_Enable();
			while(LL_RCC_HSI_IsReady() != 1);		/* Wait till HSI is ready */
	}

	/* 配置低速时钟源 */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	LL_PWR_EnableBkUpAccess();
	if (LL_RCC_LSE_IsReady() == 0){
			LL_RCC_ForceBackupDomainReset();
			LL_RCC_ReleaseBackupDomainReset();

			LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
			LL_RCC_LSE_Enable();
		/* Wait till LSE is ready */
			while( (lse_timeout != 0) && (LL_RCC_LSE_IsReady() != 1) ){
					if ( LL_SYSTICK_IsActiveCounterFlag() ){
						lse_timeout --;
					}
					if (lse_timeout == 0){
						lsi_enable = true;
						LL_RCC_LSE_Disable();
						break;
					}
			}
			if (!lsi_enable){
					LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
			}
	} else {
			lsi_enable = false;
	}
	if (lsi_enable) {
			if (LL_RCC_LSI_IsReady() == 0){
					LL_RCC_ForceBackupDomainReset();
					LL_RCC_ReleaseBackupDomainReset();
					LL_RCC_LSI_Enable();
					while(LL_RCC_LSI_IsReady() != 1);
					LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
			}
	}

  /* 配置锁相环 */
	LL_RCC_PLL_ConfigDomain_SYS(hs_source, rcc_pllm, 16, LL_RCC_PLLR_DIV_2);
	LL_RCC_PLL_EnableDomain_SYS();
	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1);		/* Wait till PLL is ready */

	LL_RCC_PLLSAI1_ConfigDomain_ADC(hs_source, rcc_pllm, 8, LL_RCC_PLLSAI1R_DIV_2);
	LL_RCC_PLLSAI1_EnableDomain_ADC();
	LL_RCC_PLLSAI1_Enable();
	while(LL_RCC_PLLSAI1_IsReady() != 1);	 /* Wait till PLLSAI1 is ready */

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);/* Wait till System clock is ready */

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_SetSystemCoreClock(64000000);

	/* Update the time base */
	if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK){
			Error_Handler();
	}
	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);
	LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_PCLK1);
	LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);
	LL_RCC_SetI2CClockSource(LL_RCC_I2C2_CLKSOURCE_PCLK1);
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PLLSAI1);
}

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
	if ((ticks - 1) > 0xFFFFFF)
	{
			return 1;
	}
	
	_SYSTICK_LOAD = ticks - 1; 
	_SYSTICK_PRI  = 0xFF;
	_SYSTICK_VAL  = 0;
	_SYSTICK_CTRL = 0x07;  
	
	return 0;
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define STM32L431RC_SRAM_SIZE               (64)
#define STM32L431RC_SRAM_START              (0x20000000)
#define STM32L431RC_SRAM_END                (STM32L431RC_SRAM_START + STM32L431RC_SRAM_SIZE * 1024 - 1)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN                          ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
extern int __bss_end__;
#define HEAP_BEGIN      			   						((void *)&__bss_end__)
#endif

#define HEAP_END                       			STM32L431RC_SRAM_END

#endif

static void bsp_system_init(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

    /* System Clock Update */
	SystemClock_Config();

	/* System Tick Configuration */
	_SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
	bsp_system_init();

#ifdef RT_USING_FINSH
	finsh_uart_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
	rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
#endif

	/* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
	rt_components_board_init();
#endif
}

void SysTick_Handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}
