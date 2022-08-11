/*
 * FSMC_hal.h
 *
 *  Created on: Mar 6, 2022
 *      Author: mkpk
 */

#ifndef INC_FSMC_HAL_H_
#define INC_FSMC_HAL_H_

#include <stdint.h>

void SRAM_FSMC_Init(void);

void SRAM_Write_Buffer_u8  (uint8_t* pBuffer, uint32_t WriteAddr, uint32_t n);
void SRAM_Read_Buffer_u8   (uint8_t* pBuffer, uint32_t ReadAddr, uint32_t n);
void SRAM_Write_Buffer_u16 (uint16_t* pBuffer, uint32_t WriteAddr, uint32_t n);
void SRAM_Read_Buffer_u16  (uint16_t* pBuffer, uint32_t ReadAddr, uint32_t n);

#endif /* INC_FSMC_HAL_H_ */
