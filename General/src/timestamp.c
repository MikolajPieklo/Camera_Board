/*
 * timestamp.c
 *
 *  Created on: Aug 17, 2021
 *      Author: mkpk
 */

#include <timestamp.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_tim.h>

static volatile uint64_t timestamp_tick = 0;

void TIM2_IRQHandler(void)
{
   if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == 1)    /* Check whether update interrupt is pending */
   {
     timestamp_tick++;
     LL_TIM_ClearFlag_UPDATE(TIM2);             /* Clear the update interrupt flag*/
   }
}

void TS_Init_ms(void)
{
   // 1KHz
   // APB1 -> PCLK1 -> 42MHz
   // tim uptade frequency = TIM_CLK/(TIM_PSC+1)/(TIM_ARR + 1)

   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);     /* Enable the timer peripheral clock */
   LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);     /* Set counter mode */
   LL_TIM_SetPrescaler(TIM2, 4199);
   LL_TIM_SetAutoReload(TIM2, 9);

   LL_TIM_EnableIT_UPDATE(TIM2);         /* Enable the update interrupt */

   NVIC_SetPriority(TIM2_IRQn, 0);       /* Configure the NVIC to handle TIM2 update interrupt */
   NVIC_EnableIRQ(TIM2_IRQn);

   LL_TIM_EnableCounter(TIM2);           /* Enable counter */
   LL_TIM_GenerateEvent_UPDATE(TIM2);    /* Force update generation */
}

void TS_Delay_ms(uint32_t delay_ms)
{
   uint32_t tickstart = timestamp_tick;
   while ((timestamp_tick - tickstart) < delay_ms)
   {
   }
}

uint32_t TS_Get_ms(void)
{
   return timestamp_tick;
}
