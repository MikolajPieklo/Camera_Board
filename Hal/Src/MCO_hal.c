/*
 * MCO_hal.c
 *
 *  Created on: Mar 29, 2022
 *      Author: mkpk
 */

#include <MCO_hal.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_rcc.h>

#define CAMERA_XCLK_PIN           LL_GPIO_PIN_8
#define CAMERA_XCLK_GPIO_Port     GPIOA

void MCO1_Init(void)
{
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

   LL_GPIO_SetPinSpeed       (CAMERA_XCLK_GPIO_Port, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (CAMERA_XCLK_GPIO_Port, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (CAMERA_XCLK_GPIO_Port, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetPinPull        (CAMERA_XCLK_GPIO_Port, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);
   LL_GPIO_SetAFPin_8_15     (CAMERA_XCLK_GPIO_Port, LL_GPIO_PIN_8, LL_GPIO_AF_0);

   /* Select MCO clock source and prescaler */
   /* 42 MHz */
   //LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_PLLCLK, LL_RCC_MCO1_DIV_4);

   /* HSI 16Mhz */
   //LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_HSI, LL_RCC_MCO1_DIV_1);

   /* HSE 8MHz */
   LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_HSE, LL_RCC_MCO1_DIV_1);

   LL_RCC_MCO1_Enable();
}

