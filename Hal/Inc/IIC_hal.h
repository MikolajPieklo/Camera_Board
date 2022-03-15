/*
 * IIC_HAL.h
 *
 *  Created on: Dec 3, 2021
 *      Author: mkpk
 */

#ifndef HAL_INC_IIC_HAL_H_
#define HAL_INC_IIC_HAL_H_

#include <stdint.h>
#include <stdbool.h>

void    I2C_Init(void);

uint8_t I2C_Master_Transmit_Byte(uint8_t Address, uint16_t Mem, uint8_t TxData);
uint8_t I2C_Master_Transmit(uint8_t Address, uint16_t Mem, bool memExtended, uint8_t* TxData, uint8_t TxDataLen);
uint8_t I2C_Master_Recesive(uint8_t Address, uint16_t Mem, bool memExtended, uint8_t* RxData, uint8_t RxDataLen);



#endif /* HAL_INC_IIC_HAL_H_ */
