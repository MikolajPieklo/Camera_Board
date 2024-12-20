/*
 * DCMI_hal.c
 *
 *  Created on: Mar 30, 2022
 *      Author: mkpk
 */
#include <stdbool.h>

#include <dcmi_hal.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_rcc.h>
#include <stm32f4xx_dcmi.h>

#define DCMI_D0_GPIO_PIN       LL_GPIO_PIN_6
#define DCMI_D0_GPIO_PORT      GPIOC
#define DCMI_D1_GPIO_PIN       LL_GPIO_PIN_7
#define DCMI_D1_GPIO_PORT      GPIOC
#define DCMI_D2_GPIO_PIN       LL_GPIO_PIN_8
#define DCMI_D2_GPIO_PORT      GPIOC
#define DCMI_D3_GPIO_PIN       LL_GPIO_PIN_9
#define DCMI_D3_GPIO_PORT      GPIOC
#define DCMI_D4_GPIO_PIN       LL_GPIO_PIN_11
#define DCMI_D4_GPIO_PORT      GPIOC
#define DCMI_D5_GPIO_PIN       LL_GPIO_PIN_6
#define DCMI_D5_GPIO_PORT      GPIOB
#define DCMI_D6_GPIO_PIN       LL_GPIO_PIN_5
#define DCMI_D6_GPIO_PORT      GPIOE
#define DCMI_D7_GPIO_PIN       LL_GPIO_PIN_6
#define DCMI_D7_GPIO_PORT      GPIOE
#define DCMI_D8_GPIO_PIN       LL_GPIO_PIN_10
#define DCMI_D8_GPIO_PORT      GPIOC
#define DCMI_D9_GPIO_PIN       LL_GPIO_PIN_12
#define DCMI_D9_GPIO_PORT      GPIOC
#define DCMI_HSYNC_GPIO_PIN    LL_GPIO_PIN_4
#define DCMI_HSYNC_GPIO_PORT   GPIOA
#define DCMI_VSYNC_GPIO_PIN    LL_GPIO_PIN_7
#define DCMI_VSYNC_GPIO_PORT   GPIOB
#define DCMI_PIXCLK_GPIO_PIN   LL_GPIO_PIN_6
#define DCMI_PIXCLK_GPIO_PORT  GPIOA

#ifdef DEBUG
volatile bool CameraEndTransfer;
volatile uint32_t VSyncCnt;
volatile uint32_t LineCnt;
volatile uint32_t FrameCnt;
#endif

void DCMI_IRQHandler(void)
{
   if(SET == DCMI_GetITStatus(DCMI_IT_FRAME))
   {
      DCMI_ClearITPendingBit(DCMI_IT_FRAME);
      DCMI_Start();
#ifdef DEBUG
      CameraEndTransfer = true;
      FrameCnt++;
      VSyncCnt = 0;
      LineCnt = 0;
#endif
   }

   if(SET == DCMI_GetITStatus(DCMI_IT_OVF))
   {
      DCMI_ClearITPendingBit(DCMI_IT_OVF);
   }

   if(SET == DCMI_GetITStatus(DCMI_IT_ERR))
   {
      DCMI_ClearITPendingBit(DCMI_IT_ERR);
   }

   if(SET == DCMI_GetITStatus(DCMI_IT_VSYNC))
   {
      DCMI_ClearITPendingBit(DCMI_IT_VSYNC);
#ifdef DEBUG
      VSyncCnt++;
#endif
   }
   if(SET == DCMI_GetITStatus(DCMI_IT_LINE))
   {
      DCMI_ClearITPendingBit(DCMI_IT_LINE);
#ifdef DEBUG
      LineCnt++;
#endif
   }
}

void DCMI_Initialize(void)
{
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
   //PC6  - DCMI_D0
   //PC7  - DCMI_D1
   //PC8  - DCMI_D2
   //PC9  - DCMI_D3
   //PC11 - DCMI_D4
   //PB6  - DCMI_D5
   //PE5  - DCMI_D6
   //PE6  - DCMI_D7
   //PC10 - DCMI_D8
   //PC12 - DCMI_D9
   LL_GPIO_SetPinSpeed       (DCMI_D0_GPIO_PORT, DCMI_D0_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D0_GPIO_PORT, DCMI_D0_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D0_GPIO_PORT, DCMI_D0_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D0_GPIO_PORT, DCMI_D0_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D1_GPIO_PORT, DCMI_D1_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D1_GPIO_PORT, DCMI_D1_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D1_GPIO_PORT, DCMI_D1_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D1_GPIO_PORT, DCMI_D1_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D2_GPIO_PORT, DCMI_D2_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D2_GPIO_PORT, DCMI_D2_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D2_GPIO_PORT, DCMI_D2_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_8_15     (DCMI_D2_GPIO_PORT, DCMI_D2_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D3_GPIO_PORT, DCMI_D3_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D3_GPIO_PORT, DCMI_D3_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D3_GPIO_PORT, DCMI_D3_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_8_15     (DCMI_D3_GPIO_PORT, DCMI_D3_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D4_GPIO_PORT, DCMI_D4_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D4_GPIO_PORT, DCMI_D4_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D4_GPIO_PORT, DCMI_D4_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_8_15     (DCMI_D4_GPIO_PORT, DCMI_D4_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D5_GPIO_PORT, DCMI_D5_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D5_GPIO_PORT, DCMI_D5_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D5_GPIO_PORT, DCMI_D5_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D5_GPIO_PORT, DCMI_D5_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D6_GPIO_PORT, DCMI_D6_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D6_GPIO_PORT, DCMI_D6_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D6_GPIO_PORT, DCMI_D6_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D6_GPIO_PORT, DCMI_D6_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D7_GPIO_PORT, DCMI_D7_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D7_GPIO_PORT, DCMI_D7_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D7_GPIO_PORT, DCMI_D7_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D7_GPIO_PORT, DCMI_D7_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D8_GPIO_PORT, DCMI_D8_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D8_GPIO_PORT, DCMI_D8_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D8_GPIO_PORT, DCMI_D8_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D8_GPIO_PORT, DCMI_D8_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_D9_GPIO_PORT, DCMI_D9_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_D9_GPIO_PORT, DCMI_D9_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_D9_GPIO_PORT, DCMI_D9_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_D9_GPIO_PORT, DCMI_D9_GPIO_PIN, LL_GPIO_AF_13);
   //PA4  - DCMI_HSYNC
   //PB7  - DCMI_VSYNC
   //PA6  - DCMI_PIXCLK
   LL_GPIO_SetPinSpeed       (DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_HSYNC_GPIO_PORT, DCMI_HSYNC_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_VSYNC_GPIO_PORT, DCMI_VSYNC_GPIO_PIN, LL_GPIO_AF_13);

   LL_GPIO_SetPinSpeed       (DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_GPIO_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
   LL_GPIO_SetPinMode        (DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
   LL_GPIO_SetPinOutputType  (DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
   LL_GPIO_SetAFPin_0_7      (DCMI_PIXCLK_GPIO_PORT, DCMI_PIXCLK_GPIO_PIN, LL_GPIO_AF_13);

   LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DCMI);
   DCMI_InitTypeDef  DCMI_InitStructure;

   DCMI_DeInit();

   DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
   DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
   DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
   DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;         //PCLK
   DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;       //HSYNC,VSYNC
   DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;             //VSYNC
   DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;              //HSYNC

   DCMI_Init (&DCMI_InitStructure);

   __NVIC_EnableIRQ (DCMI_IRQn);
   DCMI_ITConfig (DCMI_IT_FRAME, ENABLE);
   DCMI_ITConfig (DCMI_IT_OVF,   ENABLE);
   DCMI_ITConfig (DCMI_IT_ERR,   ENABLE);
   DCMI_ITConfig (DCMI_IT_VSYNC, ENABLE);
   DCMI_ITConfig (DCMI_IT_LINE,  ENABLE);
}

void DCMI_Enable(void)
{
   DCMI_Cmd(ENABLE);
}

void DCMI_Start(void)
{
   DCMI_CaptureCmd(ENABLE);
}

void DCMI_Stop(void)
{
   DCMI_CaptureCmd(DISABLE);
   while(DCMI->CR&0X01);
}
