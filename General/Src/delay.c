/*
 * delay.c
 *
 *  Created on: Aug 17, 2021
 *      Author: mkpk
 */

#include "delay.h"

volatile uint32_t SysTickValue;

void TS_Delay_ms(uint32_t delay_ms)
{
   uint32_t tickstart = SysTickValue;
   while ((SysTickValue - tickstart) < delay_ms)
   {
   }
}

uint32_t TS_Get_ms(void)
{
   return SysTickValue;
}
