/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

#include <FSMC_hal.h>

#include "delay.h"
#include "printf.h"
#include <cm_backtrace.h>

#include <Camera.h>
#include <Lcd.h>
#include <ST7789.h>

#include <platform.h>
#include <self_test.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.2.0"
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile bool CameraEndTransfer = false;
volatile uint32_t VSyncCnt = 0;
volatile uint32_t LineCnt = 0;
volatile uint32_t FrameCnt = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* MCU Configuration--------------------------------------------------------*/

/* Reset of all peripherals, Initializes the Flash interface and the Systick. */

   LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

   NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

/* System interrupt init*/

/* USER CODE BEGIN Init */

/* USER CODE END Init */

/* Configure the system clock */
   SystemClock_Config();

/* USER CODE BEGIN SysInit */

/* USER CODE END SysInit */

/* Initialize all configured peripherals */
   MX_GPIO_Init();
   MX_USART1_UART_Init();
   MX_SPI1_Init();
   LL_SYSTICK_EnableIT();
   SRAM_FSMC_Init();

   cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);
   /*fault_test_by_div0();*/

   Project_Info_Print();

   ST7789_GPIO_Init();
   Lcd_Start ();
   Platform_Read_Flash_Size();
   Self_Test_Run();

   uint32_t i = 0;
   uint32_t j = 0;
   uint32_t offset = 0;
   uint32_t *p = (uint32_t*)0x68000000;
   for (i=0;i<230*320;i++)
   {
      *(p+i) = 0xF800F800;
   }

   Camera_Init();
   Camera_Start();

   TS_Delay_ms(100);
   ST7789_SetWindow(0, 0, DisplayWidth - 1, DisplayHeight - 1);

   while (1)
   {
//      TS_Delay_ms(100);
//      LL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
      for(i = 0; i < 57600/2; i++)
      {
         uint32_t data = *(p+i+offset);
         uint16_t data1 = (uint16_t)(data >> 16);
         uint16_t data2 = (uint16_t)data;
         ST7789_SetPixel((uint16_t)data1);
         ST7789_SetPixel((uint16_t)data2);
         j+=2;
         if (j == 240)
         {
            offset += 40;
            j=0;
         }
      }
      j=0;
      offset = 0;
   }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
   LL_FLASH_SetLatency (LL_FLASH_LATENCY_5);
   while (LL_FLASH_GetLatency () != LL_FLASH_LATENCY_5)
   {
   }
   LL_PWR_SetRegulVoltageScaling (LL_PWR_REGU_VOLTAGE_SCALE1);
   LL_RCC_HSE_Enable ();

/* Wait till HSE is ready */
   while (LL_RCC_HSE_IsReady () != 1)
   {

   }
   LL_RCC_HSE_EnableCSS ();
   LL_RCC_PLL_ConfigDomain_SYS (LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
   LL_RCC_PLL_Enable ();

/* Wait till PLL is ready */
   while (LL_RCC_PLL_IsReady () != 1)
   {

   }
   LL_RCC_SetAHBPrescaler (LL_RCC_SYSCLK_DIV_1);
   LL_RCC_SetAPB1Prescaler (LL_RCC_APB1_DIV_4);
   LL_RCC_SetAPB2Prescaler (LL_RCC_APB2_DIV_2);
   LL_RCC_SetSysClkSource (LL_RCC_SYS_CLKSOURCE_PLL);

/* Wait till System clock is ready */
   while (LL_RCC_GetSysClkSource () != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
   {

   }
   LL_Init1msTick (168000000);
   LL_SetSystemCoreClock (168000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
/* USER CODE BEGIN Error_Handler_Debug */
/* User can add his own implementation to report the HAL error return state */
   __disable_irq ();
   while (1)
   {
   }
/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
/* USER CODE BEGIN 6 */
   printf ("Wrong parameters value: file %s on line %lu\r\n", file, line);
/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
