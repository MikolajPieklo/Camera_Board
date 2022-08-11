/*
 * gtest_timestamp.cpp
 *
 *  Created on: Dec 5, 2021
 *      Author: mkpk
 */

#include <gtest_timestamp_mock.hpp>

static Timestamp_Mock *s_timestamp_mock = nullptr;

void Timestamp_Mock_Setup(Timestamp_Mock &mock)
{
   s_timestamp_mock = &mock;
}

void Timestamp_Mock_Remove()
{
   s_timestamp_mock = nullptr;
}

int TS_Get_msec(void)
{
   int msec = 0;

   if (nullptr != s_timestamp_mock)
   {
      msec = s_timestamp_mock->TS_Get_msec();
   }

   return msec;
}
