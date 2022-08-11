/*
 * timestamp.h
 *
 *  Created on: Aug 17, 2021
 *      Author: mkpk
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include "stdint.h"

void TS_Init_ms(void);

void TS_Delay_ms(uint32_t delay_ms);

uint32_t TS_Get_ms(void);

#endif /* TIMESTAMP_H_ */
