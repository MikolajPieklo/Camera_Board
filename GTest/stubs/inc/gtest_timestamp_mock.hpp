/*
 * gtest_timestamp.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: mkpk
 */

#ifndef STUBS_INC_GTEST_TIMESTAMP_MOCK_HPP_
#define STUBS_INC_GTEST_TIMESTAMP_MOCK_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//#include <timestamp.h>
int TS_Get_msec(void);

struct Timestamp_Mock
{
   MOCK_METHOD0(TS_Get_msec, int());
};

void Timestamp_Mock_Setup(Timestamp_Mock &mock);
void Timestamp_Mock_Remove();







#endif /* STUBS_INC_GTEST_TIMESTAMP_MOCK_HPP_ */
