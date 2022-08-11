/* System includes */
#include <stdio.h>
#include <string.h>

/* Project includes */
#include <main.h>
#include <spi.h>
#include <usart.h>
#include <gpio.h>

#include <camera.h>
#include <cm_backtrace.h>
#include <timestamp.h>
#include <fsmc_hal.h>
#include <lcd.h>
#include <platform.h>
#include <printf.h>
#include <st7789.h>
#include <self_test.h>

#define HARDWARE_VERSION               "v1.0.0"
#define SOFTWARE_VERSION               "v0.2.1"

extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);
extern uint16_t image[230*320*2];

void SystemClock_Config(void);

volatile bool CameraEndTransfer = false;
volatile uint32_t VSyncCnt = 0;
volatile uint32_t LineCnt = 0;
volatile uint32_t FrameCnt = 0;

int main(void)
{
   LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

   NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

   SystemClock_Config();

   MX_GPIO_Init();
   MX_USART1_UART_Init();
   MX_SPI1_Init();
   TS_Init_ms();
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

   Camera_Init();
   Camera_Start();

   TS_Delay_ms(100);
   ST7789_SetWindow(0, 0, DisplayWidth - 1, DisplayHeight - 1);

   while (1)
   {
      for(i = 0; i < 57600/2; i++)
      {
         uint32_t data = *((uint32_t*)image + i + offset);
         uint16_t data1 = (uint16_t)(data >> 16);
         uint16_t data2 = (uint16_t)data;
         ST7789_SetPixel((uint16_t)data1);
         ST7789_SetPixel((uint16_t)data2);
         j += 2;
         if (j == 240)
         {
            offset += 40;
            j = 0;
         }
      }
      j = 0;
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
