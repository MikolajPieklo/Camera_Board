/*
 * FSMC_hal.h
 *
 *  Created on: Mar 6, 2022
 *      Author: mkpk
 */

#ifndef INC_FSMC_HAL_H_
#define INC_FSMC_HAL_H_

#include <stdint.h>

//FSMC_Bank1_NORSRAM4
#define Bank1_SRAM1_ADDR    ((uint32_t)(0x60000000))
#define Bank1_SRAM2_ADDR    ((uint32_t)(0x64000000))
#define Bank1_SRAM3_ADDR    ((uint32_t)(0x68000000)) //SRAM
#define Bank1_SRAM4_ADDR    ((uint32_t)(0x6C000000)) //LCD

#define Bank3_SRAM1_ADDR    ((uint32_t)(0x80000000))
#define Bank3_SRAM2_ADDR    ((uint32_t)(0x84000000))
#define Bank3_SRAM3_ADDR    ((uint32_t)(0x88000000))
#define Bank3_SRAM4_ADDR    ((uint32_t)(0x8C000000))

void FSMC_Init(void);

void FSMC_Write_u8 (uint32_t bank, uint8_t data, uint32_t writeAddr);
void FSMC_Read_u8 (uint32_t bank, uint8_t* data, uint32_t readAddr);
void FSMC_Write_u16 (uint32_t bank, uint16_t data, uint32_t writeAddr);
void FSMC_Read_u16 (uint32_t bank, uint16_t* data, uint32_t ReadAddr);

void FSMC_Write_Buffer_u8 (uint32_t bank, uint8_t* pBuffer, uint32_t WriteAddr, uint32_t n);
void FSMC_Read_Buffer_u8 (uint32_t bank, uint8_t* pBuffer, uint32_t ReadAddr, uint32_t n);
void FSMC_Write_Buffer_u16 (uint32_t bank, uint16_t* pBuffer, uint32_t WriteAddr, uint32_t n);
void FSMC_Read_Buffer_u16 (uint32_t bank, uint16_t* pBuffer, uint32_t ReadAddr, uint32_t n);

#endif /* INC_FSMC_HAL_H_ */
