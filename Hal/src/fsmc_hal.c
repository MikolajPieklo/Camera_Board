/*
 * FSMC_hal.c
 *
 *  Created on: Mar 6, 2022
 *      Author: mkpk
 */

#include <string.h>

#include <fsmc_hal.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_fsmc.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_rcc.h>

#include <timestamp.h>

#define FSMC_D0_GPIO_PIN         LL_GPIO_PIN_14 //PD14
#define FSMC_D0_GPIO_PORT        GPIOD
#define FSMC_D1_GPIO_PIN         LL_GPIO_PIN_15 //PD11
#define FSMC_D1_GPIO_PORT        GPIOD
#define FSMC_D2_GPIO_PIN         LL_GPIO_PIN_0  //PD0
#define FSMC_D2_GPIO_PORT        GPIOD
#define FSMC_D3_GPIO_PIN         LL_GPIO_PIN_1  //PD1
#define FSMC_D3_GPIO_PORT        GPIOD
#define FSMC_D4_GPIO_PIN         LL_GPIO_PIN_7  //PE7
#define FSMC_D4_GPIO_PORT        GPIOE
#define FSMC_D5_GPIO_PIN         LL_GPIO_PIN_8  //PE8
#define FSMC_D5_GPIO_PORT        GPIOE
#define FSMC_D6_GPIO_PIN         LL_GPIO_PIN_9  //PE9
#define FSMC_D6_GPIO_PORT        GPIOE
#define FSMC_D7_GPIO_PIN         LL_GPIO_PIN_10 //PE10
#define FSMC_D7_GPIO_PORT        GPIOE
#define FSMC_D8_GPIO_PIN         LL_GPIO_PIN_11 //PE11
#define FSMC_D8_GPIO_PORT        GPIOE
#define FSMC_D9_GPIO_PIN         LL_GPIO_PIN_12 //PE12
#define FSMC_D9_GPIO_PORT        GPIOE
#define FSMC_D10_GPIO_PIN        LL_GPIO_PIN_13 //PE13
#define FSMC_D10_GPIO_PORT       GPIOE
#define FSMC_D11_GPIO_PIN        LL_GPIO_PIN_14 //PE14
#define FSMC_D11_GPIO_PORT       GPIOE
#define FSMC_D12_GPIO_PIN        LL_GPIO_PIN_15 //PE15
#define FSMC_D12_GPIO_PORT       GPIOE
#define FSMC_D13_GPIO_PIN        LL_GPIO_PIN_8  //PD8
#define FSMC_D13_GPIO_PORT       GPIOD
#define FSMC_D14_GPIO_PIN        LL_GPIO_PIN_9  //PD9
#define FSMC_D14_GPIO_PORT       GPIOD
#define FSMC_D15_GPIO_PIN        LL_GPIO_PIN_10 //PD10
#define FSMC_D15_GPIO_PORT       GPIOD

#define FSMC_A0_GPIO_PIN         LL_GPIO_PIN_0  //PF0
#define FSMC_A0_GPIO_PORT        GPIOF
#define FSMC_A1_GPIO_PIN         LL_GPIO_PIN_1  //PF1
#define FSMC_A1_GPIO_PORT        GPIOF
#define FSMC_A2_GPIO_PIN         LL_GPIO_PIN_2  //PF2
#define FSMC_A2_GPIO_PORT        GPIOF
#define FSMC_A3_GPIO_PIN         LL_GPIO_PIN_3  //PF3
#define FSMC_A3_GPIO_PORT        GPIOF
#define FSMC_A4_GPIO_PIN         LL_GPIO_PIN_4  //PF4
#define FSMC_A4_GPIO_PORT        GPIOF
#define FSMC_A5_GPIO_PIN         LL_GPIO_PIN_5  //PF5
#define FSMC_A5_GPIO_PORT        GPIOF
#define FSMC_A6_GPIO_PIN         LL_GPIO_PIN_12 //PF12
#define FSMC_A6_GPIO_PORT        GPIOF
#define FSMC_A7_GPIO_PIN         LL_GPIO_PIN_13 //PF13
#define FSMC_A7_GPIO_PORT        GPIOF
#define FSMC_A8_GPIO_PIN         LL_GPIO_PIN_14 //PF14
#define FSMC_A8_GPIO_PORT        GPIOF
#define FSMC_A9_GPIO_PIN         LL_GPIO_PIN_15 //PF15
#define FSMC_A9_GPIO_PORT        GPIOF
#define FSMC_A10_GPIO_PIN        LL_GPIO_PIN_0  //PG0
#define FSMC_A10_GPIO_PORT       GPIOG
#define FSMC_A11_GPIO_PIN        LL_GPIO_PIN_1  //PG1
#define FSMC_A11_GPIO_PORT       GPIOG
#define FSMC_A12_GPIO_PIN        LL_GPIO_PIN_2  //PG2
#define FSMC_A12_GPIO_PORT       GPIOG
#define FSMC_A13_GPIO_PIN        LL_GPIO_PIN_3  //PG3
#define FSMC_A13_GPIO_PORT       GPIOG
#define FSMC_A14_GPIO_PIN        LL_GPIO_PIN_4  //PG4
#define FSMC_A14_GPIO_PORT       GPIOG
#define FSMC_A15_GPIO_PIN        LL_GPIO_PIN_5  //PG5
#define FSMC_A15_GPIO_PORT       GPIOG
#define FSMC_A16_GPIO_PIN        LL_GPIO_PIN_11 //PD11
#define FSMC_A16_GPIO_PORT       GPIOD
#define FSMC_A17_GPIO_PIN        LL_GPIO_PIN_12 //PD12
#define FSMC_A17_GPIO_PORT       GPIOD
#define FSMC_A18_GPIO_PIN        LL_GPIO_PIN_13 //PD13
#define FSMC_A18_GPIO_PORT       GPIOD

#define FSMC_NOE_GPIO_PIN        LL_GPIO_PIN_4  //PD4
#define FSMC_NOE_GPIO_PORT       GPIOD
#define FSMC_NWE_GPIO_PIN        LL_GPIO_PIN_5  //PD5
#define FSMC_NWE_GPIO_PORT       GPIOD
#define FSMC_NBL0_GPIO_PIN       LL_GPIO_PIN_0  //PE0
#define FSMC_NBL0_GPIO_PORT      GPIOE
#define FSMC_NBL1_GPIO_PIN       LL_GPIO_PIN_1  //PE1
#define FSMC_NBL1_GPIO_PORT      GPIOE
#define FSMC_NE3_GPIO_PIN        LL_GPIO_PIN_10 //PG10 -> SRAM
#define FSMC_NE3_GPIO_PORT       GPIOG
#define FSMC_NE4_GPIO_PIN        LL_GPIO_PIN_12 //PG12 -> LCD
#define FSMC_NE4_GPIO_PORT       GPIOG

void FSMC_Init(void)
{
   LL_GPIO_InitTypeDef GPIO_InitStruct;
   FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
   FSMC_NORSRAMTimingInitTypeDef readWriteTiming;

   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);

   LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_FSMC);

   memset(&GPIO_InitStruct, 0x00, sizeof(LL_GPIO_InitTypeDef));
   GPIO_InitStruct.Pin        =
            FSMC_D2_GPIO_PIN |
            FSMC_D3_GPIO_PIN |
            FSMC_NOE_GPIO_PIN |
            FSMC_NWE_GPIO_PIN |
            FSMC_D13_GPIO_PIN |
            FSMC_D14_GPIO_PIN |
            FSMC_D15_GPIO_PIN |
            FSMC_A16_GPIO_PIN |
            FSMC_A17_GPIO_PIN |
            FSMC_A18_GPIO_PIN |
            FSMC_D0_GPIO_PIN |
            FSMC_D1_GPIO_PIN;
   GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
   GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   GPIO_InitStruct.Pull       = LL_GPIO_PULL_UP;
   GPIO_InitStruct.Alternate  = LL_GPIO_AF_12;
   LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   memset(&GPIO_InitStruct, 0x00, sizeof(LL_GPIO_InitTypeDef));
   GPIO_InitStruct.Pin        =
            FSMC_NBL0_GPIO_PIN |
            FSMC_NBL1_GPIO_PIN |
            FSMC_D4_GPIO_PIN |
            FSMC_D5_GPIO_PIN |
            FSMC_D6_GPIO_PIN |
            FSMC_D7_GPIO_PIN |
            FSMC_D8_GPIO_PIN |
            FSMC_D9_GPIO_PIN |
            FSMC_D10_GPIO_PIN |
            FSMC_D11_GPIO_PIN |
            FSMC_D12_GPIO_PIN;
   GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
   GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   GPIO_InitStruct.Pull       = LL_GPIO_PULL_UP;
   GPIO_InitStruct.Alternate  = LL_GPIO_AF_12;
   LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

   memset(&GPIO_InitStruct, 0x00, sizeof(LL_GPIO_InitTypeDef));
   GPIO_InitStruct.Pin        =
            FSMC_A0_GPIO_PIN |
            FSMC_A1_GPIO_PIN |
            FSMC_A2_GPIO_PIN |
            FSMC_A3_GPIO_PIN |
            FSMC_A4_GPIO_PIN |
            FSMC_A5_GPIO_PIN |
            FSMC_A6_GPIO_PIN |
            FSMC_A7_GPIO_PIN |
            FSMC_A8_GPIO_PIN |
            FSMC_A9_GPIO_PIN ;
   GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
   GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   GPIO_InitStruct.Pull       = LL_GPIO_PULL_UP;
   GPIO_InitStruct.Alternate  = LL_GPIO_AF_12;
   LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

   memset(&GPIO_InitStruct, 0x00, sizeof(LL_GPIO_InitTypeDef));
   GPIO_InitStruct.Pin        =
            FSMC_A10_GPIO_PIN |
            FSMC_A11_GPIO_PIN |
            FSMC_A12_GPIO_PIN |
            FSMC_A13_GPIO_PIN |
            FSMC_A14_GPIO_PIN |
            FSMC_A15_GPIO_PIN |
            FSMC_NE3_GPIO_PIN |
            FSMC_NE4_GPIO_PIN;
   GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
   GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
   GPIO_InitStruct.Pull       = LL_GPIO_PULL_UP;
   GPIO_InitStruct.Alternate  = LL_GPIO_AF_12;
   LL_GPIO_Init(GPIOG, &GPIO_InitStruct);

   readWriteTiming.FSMC_AddressSetupTime = 0x00;
   readWriteTiming.FSMC_AddressHoldTime = 0x00;
   readWriteTiming.FSMC_DataSetupTime = 0x08;
   readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
   readWriteTiming.FSMC_CLKDivision = 0x00;
   readWriteTiming.FSMC_DataLatency = 0x00;
   readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

   FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
   FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
   FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;
   FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
   FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
   FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
   FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
   FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
   FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
   FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming;

   FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
   FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);

   //LCD
   readWriteTiming.FSMC_AddressSetupTime = 4;
   readWriteTiming.FSMC_AddressHoldTime = 15;
   readWriteTiming.FSMC_DataSetupTime = 8;
   readWriteTiming.FSMC_BusTurnAroundDuration = 4;
   readWriteTiming.FSMC_CLKDivision = 16;
   readWriteTiming.FSMC_DataLatency = 17;
   readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

//   readWriteTiming.FSMC_AddressSetupTime = 0x00;
//   readWriteTiming.FSMC_AddressHoldTime = 0x00;
//   readWriteTiming.FSMC_DataSetupTime = 0x08;
//   readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//   readWriteTiming.FSMC_CLKDivision = 0x00;
//   readWriteTiming.FSMC_DataLatency = 0x00;
//   readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

   FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
   FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
   FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;
   FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
   FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
   FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
   FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
   FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
   FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
   FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming;

   FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
   FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);

   TS_Delay_ms(10);
}

void FSMC_Write_u8 (uint32_t bank, uint8_t data, uint32_t writeAddr)
{
   *(volatile uint8_t*) (bank + writeAddr) = data;
}
void FSMC_Read_u8 (uint32_t bank, uint8_t* data, uint32_t readAddr)
{
   *data = *(volatile uint8_t*) (bank + readAddr);
}
void FSMC_Write_u16 (uint32_t bank, uint16_t data, uint32_t writeAddr)
{
   *(volatile uint16_t*) (bank + (2 * writeAddr)) = data;
}
void FSMC_Read_u16 (uint32_t bank, uint16_t* data, uint32_t readAddr)
{
   *data  = *(volatile uint16_t*) (bank + (2 * readAddr));
}

void FSMC_Write_Buffer_u8(uint32_t bank, uint8_t* pBuffer, uint32_t writeAddr, uint32_t n)
{
   for (; n != 0; n--)
   {
      *(volatile uint8_t*) (bank + writeAddr) = *pBuffer;
      writeAddr++;
      pBuffer++;
   }
}

void FSMC_Read_Buffer_u8(uint32_t bank, uint8_t* pBuffer, uint32_t readAddr, uint32_t n)
{
   for (; n != 0; n--)
   {
      *pBuffer++ = *(volatile uint8_t*) (bank + readAddr);
      readAddr++;
   }
}

void FSMC_Write_Buffer_u16(uint32_t bank, uint16_t* pBuffer, uint32_t writeAddr, uint32_t n)
{
   for (; n != 0; n--)
   {
      *(volatile uint16_t*) (bank + (2 * writeAddr)) = *pBuffer;
      writeAddr++;
      pBuffer++;
   }
}

void FSMC_Read_Buffer_u16(uint32_t bank, uint16_t* pBuffer, uint32_t readAddr, uint32_t n)
{
   for (; n != 0; n--)
   {
      *pBuffer++  = *(volatile uint16_t*) (bank + (2 * readAddr));
      readAddr++;
   }
}

