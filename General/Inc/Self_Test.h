/*
 * Self_Test.h
 *
 *  Created on: Mar 15, 2022
 *      Author: mkpk
 */

#ifndef INC_SELF_TEST_H_
#define INC_SELF_TEST_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum SelfTest
{
   SelfTestSuccesed,
   SelfTestErrorSRAMU8,
   SelfTestErrorSRAMU16,
   SelfTestErrorCameraId
} SelfTest_t;

SelfTest_t Self_Test_Run();

#endif /* INC_SELF_TEST_H_ */
