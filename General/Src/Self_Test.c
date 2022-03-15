/*
 * Self_Test.c
 *
 *  Created on: Mar 15, 2022
 *      Author: mkpk
 */

#include <stdio.h>
#include <Self_Test.h>
#include <FSMC_hal.h>

SelfTest_t Self_Test_Run()
{
   SelfTest_t result = SelfTestSuccesed;

   uint8_t u8txdata[] = { 'T', 'E', 'S'};
   uint8_t u8rxdata[3];

   uint16_t u16txdata[] = { 0xC123, 0x11A1, 0x9CD1 };
   uint16_t u16rxdata[3];

   do
   {
      SRAM_Write_Buffer_u8(u8txdata, 0x00, 0x03);
      SRAM_Read_Buffer_u8 (u8rxdata, 0x00, 0x03);
      if ((u8txdata[0] != u8rxdata[0]) || (u8txdata[1] != u8rxdata[1]) || ((u8txdata[2] != u8rxdata[2])))
      {
         printf("\nSelfTest: Problem with SRAM U8\n");
         result = SelfTestErrorSRAMU8;
         break;
      }

      SRAM_Write_Buffer_u16(u16txdata, 0x163, 0x03);
      SRAM_Read_Buffer_u16 (u16rxdata, 0x163, 0x03);
      if ((u16txdata[0] != u16rxdata[0]) || (u16txdata[1] != u16rxdata[1]) || ((u16txdata[2] != u16rxdata[2])))
      {
         printf("\nSelfTest: Problem with SRAM U16\n");
         result = SelfTestErrorSRAMU16;
         break;
      }


   }while(false);

   return result;
}
