/*
 * IIC_HAL.c
 *
 *  Created on: Dec 3, 2021
 *      Author: mkpk
 */

#include <iic_hal.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_i2c.h>
#include <stm32f4xx_ll_rcc.h>

/* I2C SPEEDCLOCK define to max value: Fast Mode @400kHz */
#define I2C_SPEEDCLOCK            100000

void I2C_Init(void)
{
   LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
   LL_I2C_InitTypeDef I2C_InitStruct;
   LL_GPIO_InitTypeDef GPIO_InitStruct;

   /**I2C2 GPIO Configuration
   PB8   ------> I2C2_SCL
   PB9   ------> I2C2_SDA
   */
   GPIO_InitStruct.Pin        = LL_GPIO_PIN_8;
   GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
   GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
   GPIO_InitStruct.Pull       = LL_GPIO_PULL_UP;
   GPIO_InitStruct.Alternate  = LL_GPIO_AF_4;
   LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   GPIO_InitStruct.Pin        = LL_GPIO_PIN_9;
   GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
   GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
   GPIO_InitStruct.Pull       = LL_GPIO_PULL_UP;
   GPIO_InitStruct.Alternate  = LL_GPIO_AF_4;
   LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   /* Peripheral clock enable */
   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

   /**I2C Initialization */
   LL_I2C_DisableOwnAddress2(I2C1);

   LL_I2C_DisableGeneralCall(I2C1);

   LL_I2C_EnableClockStretching(I2C1);

   I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
   I2C_InitStruct.ClockSpeed = I2C_SPEEDCLOCK;
   I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
   I2C_InitStruct.OwnAddress1 = 0;
   I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
   I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
   LL_I2C_Init(I2C1, &I2C_InitStruct);

   LL_I2C_SetOwnAddress2(I2C1, 0);
}

uint8_t I2C_Master_Transmit_Byte(uint8_t Address, uint16_t Mem, uint8_t TxData)
{
   //Start
   LL_I2C_GenerateStartCondition(I2C1);
   while(!LL_I2C_IsActiveFlag_SB(I2C1));

   //Address
   LL_I2C_TransmitData8(I2C1, Address | 0);
   while(!LL_I2C_IsActiveFlag_ADDR(I2C1));
   LL_I2C_ClearFlag_ADDR(I2C1);

   LL_I2C_TransmitData8(I2C1, Mem);
   while (!LL_I2C_IsActiveFlag_TXE(I2C1));

   LL_I2C_TransmitData8(I2C1, TxData);
   while (!LL_I2C_IsActiveFlag_TXE(I2C1));

   LL_I2C_GenerateStopCondition(I2C1);
   while(LL_I2C_IsActiveFlag_STOP(I2C1));

   return 0;
}

uint8_t I2C_Master_Transmit(uint8_t Address, uint16_t Mem, bool memExtended, uint8_t* TxData, uint8_t TxDataLen)
{
   uint8_t txIndex =0;

   //Start
   LL_I2C_GenerateStartCondition(I2C1);
   while(!LL_I2C_IsActiveFlag_SB(I2C1));

   //Address
   LL_I2C_TransmitData8(I2C1, Address | 0);
   while(!LL_I2C_IsActiveFlag_ADDR(I2C1));
   LL_I2C_ClearFlag_ADDR(I2C1);

   //Mem
   if(memExtended == false)
   {
      LL_I2C_TransmitData8(I2C1, Mem);
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
   }
   else
   {
      LL_I2C_TransmitData8(I2C1, (uint8_t)(Mem>>8));
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
      LL_I2C_TransmitData8(I2C1, (uint8_t)(Mem&0xFF));
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
   }

   //Data
   while ( txIndex < TxDataLen)
   {
      LL_I2C_TransmitData8(I2C1, *(TxData + txIndex));
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
      txIndex++;
   }

   //Stop
   LL_I2C_GenerateStopCondition(I2C1);
   while(LL_I2C_IsActiveFlag_STOP(I2C1));

   return 0;

}
uint8_t I2C_Master_Recesive(uint8_t Address, uint16_t Mem, bool memExtended, uint8_t* RxData, uint8_t RxDataLen)
{
   uint8_t rxIndex = 0;

    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

   //Start
   LL_I2C_GenerateStartCondition(I2C1);
   while (!LL_I2C_IsActiveFlag_SB(I2C1));

   //Address
   LL_I2C_TransmitData8(I2C1, Address | 0);
   while (!LL_I2C_IsActiveFlag_ADDR(I2C1));
   LL_I2C_ClearFlag_ADDR(I2C1);

   //Mem
   if(memExtended == false)
   {
      LL_I2C_TransmitData8(I2C1, Mem);
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
   }
   else
   {
      LL_I2C_TransmitData8(I2C1, (uint8_t)(Mem>>8));
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
      LL_I2C_TransmitData8(I2C1, (uint8_t)(Mem&0xFF));
      while (!LL_I2C_IsActiveFlag_TXE(I2C1));
   }

   //Stop
   LL_I2C_GenerateStopCondition(I2C1);
   while (LL_I2C_IsActiveFlag_STOP(I2C1));

   //Second start
   LL_I2C_GenerateStartCondition(I2C1);
   while (!LL_I2C_IsActiveFlag_SB(I2C1));

   //Address
   LL_I2C_TransmitData8(I2C1, Address | 1); //Read
   while (!LL_I2C_IsActiveFlag_ADDR(I2C1));
   LL_I2C_ClearFlag_ADDR(I2C1);

   //LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

   //RxData
   while(rxIndex < RxDataLen)
   {
      if(rxIndex == RxDataLen -1)
      {
         LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
      }
      else
      {
         LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
      }

      while (!LL_I2C_IsActiveFlag_RXNE(I2C1));
      *(RxData + rxIndex) = LL_I2C_ReceiveData8(I2C1);
      rxIndex++;
   }

   //Stop
   LL_I2C_GenerateStopCondition(I2C1);
   while (LL_I2C_IsActiveFlag_STOP(I2C1));

   return 0;
}
