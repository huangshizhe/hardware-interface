// Copyright 2018 Project March.

#include "gtest/gtest.h"
#include <gmock/gmock.h>

#include "march_hardware/Joint.h"
#include "march_hardware/TemperatureGES.h"
#include "march_hardware/IMotionCube.h"
#include "mocks/MockEncoderIncremental.cpp"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::AtMost;

class TestEncoderIncremental : public ::testing::Test
{
protected:
  const float increment = 10;
};

TEST_F(TestEncoderIncremental, EncoderIncremental)
{
  MockEncoderIncremental mockEncoderIncremental;

  EXPECT_CALL(mockEncoderIncremental, getIncrementDeg()).Times(AtLeast(1));
  ON_CALL(mockEncoderIncremental, getIncrementDeg()).WillByDefault(Return(increment));

  ASSERT_EQ(increment, mockEncoderIncremental.getIncrementDeg());
}
