#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest_timestamp_mock.hpp>

using namespace testing;

struct SerializerTest: public Test
{
   void SetUp() override
   {
      Timestamp_Mock_Setup(mTimestamp_Mock);
   }

   void TearDown() override
   {
      Timestamp_Mock_Remove();
   }

   StrictMock<Timestamp_Mock> mTimestamp_Mock;
};


TEST_F(SerializerTest, GPIOFaultCheckWithSucceededStatus)
{
   InSequence seq;

}

TEST_F(SerializerTest, test)
{
   InSequence seq;
   EXPECT_TRUE(true);
}
