/*
 * DMA_hal.c
 *
 *  Created on: Mar 30, 2022
 *      Author: mkpk
 */

#include <dma_hal.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_dma.h>

void DMA_Init(void)
{
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
   LL_DMA_InitTypeDef DMA_InitStructure;

   LL_DMA_DeInit(DMA2, LL_DMA_STREAM_1);

   while (LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_1) != DISABLE){}

   uint32_t *p = (uint32_t*)0x68000000;
   //DMA Stream
   DMA_InitStructure.Channel = LL_DMA_CHANNEL_1;
   DMA_InitStructure.PeriphOrM2MSrcAddress = (uint32_t)&DCMI->DR;
   DMA_InitStructure.MemoryOrM2MDstAddress = (uint32_t)p;
   DMA_InitStructure.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
   DMA_InitStructure.NbData = 38400; //320 * 240 * 2 = 153600 bytes / 4 = 38400
   DMA_InitStructure.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
   DMA_InitStructure.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
   DMA_InitStructure.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;
   DMA_InitStructure.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;
   DMA_InitStructure.Mode = LL_DMA_MODE_CIRCULAR;
   DMA_InitStructure.Priority = LL_DMA_PRIORITY_HIGH;
   DMA_InitStructure.FIFOMode = LL_DMA_FIFOMODE_ENABLE;
   DMA_InitStructure.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_FULL;
   DMA_InitStructure.MemBurst = LL_DMA_MBURST_INC4;
   DMA_InitStructure.PeriphBurst = LL_DMA_PBURST_SINGLE;

   __NVIC_EnableIRQ (DMA2_Stream1_IRQn);
   LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_1);

   LL_DMA_Init(DMA2, LL_DMA_STREAM_1, &DMA_InitStructure);
}

void DMA_EnableStream(void)
{
   LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_1);
}

void DMA_DisableStream(void)
{
   LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);
}
