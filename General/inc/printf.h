/*
 * printf.h
 *
 *  Created on: Aug 17, 2021
 *      Author: mkpk
 */

#ifndef GENERAL_INC_PRINTF_H_
#define GENERAL_INC_PRINTF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

void Project_Info_Print(void);

void USART_Printf(USART_TypeDef *USARTx,const uint8_t* text, bool newline);

#endif /* GENERAL_INC_PRINTF_H_ */
