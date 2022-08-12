/*
 * platform.c
 *
 *  Created on: Mar 30, 2022
 *      Author: mkpk
 */

#include <platform.h>

#include <stdint.h>

#include <g_common_macros.h>

void Platform_Read_Device_ID(void)
{
   uint32_t *p = (uint32_t*)0x1FFF7A10;
   UNUSED(p);
}

void Platform_Read_Flash_Size(void)
{
   uint16_t *p = (uint16_t*)0x1FFF7A22;
   UNUSED(p);
}
