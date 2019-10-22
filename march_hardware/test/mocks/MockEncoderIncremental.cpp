#include "gmock/gmock.h"  // Brings in Google Mock.
#include "march_hardware/EncoderIncremental.h"

class MockEncoderIncremental : public march4cpp::EncoderIncremental
{
public:
  MOCK_METHOD0(getIncrementDeg, float());
  MOCK_METHOD0(getIncrementRad, float());
  MOCK_METHOD0(getIncrement, float());
};