/* System includes */
#include <stdio.h>
#include <string.h>

/* Project includes */
#include <main.h>
#include <gpio.h>
#include <spi.h>
#include <usart.h>

#include <FreeRTOS.h>
#include <cmsis_os.h>
#include <task.h>

#include <cm_backtrace.h>
#include <fsmc_hal.h>
#include <platform.h>
#include <printf.h>
#include <timestamp.h>
#include <self_test.h>

#define HARDWARE_VERSION               "v1.0.0"
#define SOFTWARE_VERSION               "v0.2.1"

extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);

extern void StartIdleTask(void *argument);
extern void StartCameraTask(void *argument);
osThreadId_t idleTaskHandle;
osThreadId_t cameraTaskHandle;
extern const osThreadAttr_t idleTask_attributes;
extern const osThreadAttr_t cameraTask_attributes;

volatile bool CameraEndTransfer = false;
volatile uint32_t VSyncCnt = 0;
volatile uint32_t LineCnt = 0;
volatile uint32_t FrameCnt = 0;

void SystemClock_Config(void);

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
   Platform_Read_Flash_Size();
   Self_Test_Run();

   osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */

   idleTaskHandle = osThreadNew(StartIdleTask, NULL, &idleTask_attributes);
   cameraTaskHandle  = osThreadNew(StartCameraTask, NULL, &cameraTask_attributes);

   osKernelStart();    /* Start scheduler */

   while (1)
   {
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

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
/* User can add his own implementation to report the HAL error return state */
   __disable_irq ();
   while (1)
   {
   }
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
   printf ("Wrong parameters value: file %s on line %lu\r\n", file, line);
}
#endif /* USE_FULL_ASSERT */
