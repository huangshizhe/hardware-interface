// Copyright 2019 Project March.

#ifndef PROJECT_ENCODER_INCREMENTAL_H
#define PROJECT_ENCODER_INCREMENTAL_H

#include <ostream>

namespace march4cpp
{
class EncoderIncremental
{
private:
    int slaveIndex;
    int totalPositions;


public:
  EncoderIncremental()
    : slaveIndex(-1)
    , totalPositions(0)
  {
  }

  EncoderIncremental(int numberOfBits);

  float getIncrementRad(uint8_t IncrementByteOffset);

  int getIncrementIU(uint8_t IncrementByteOffset);

  float IUtoRad(int iu);

  void setSlaveIndex(int slaveIndex);
  int getSlaveIndex() const;

  /** @brief Override comparison operator */
  friend bool operator==(const EncoderIncremental& lhs, const EncoderIncremental& rhs)
  {
      return lhs.slaveIndex == rhs.slaveIndex && lhs.totalPositions == rhs.totalPositions;
  }
  /** @brief Override stream operator for clean printing */
  friend ::std::ostream& operator<<(std::ostream& os, const EncoderIncremental& encoderIncremental)
  {
      return os << "slaveIndex: " << encoderIncremental.slaveIndex << ", "
              << "totalPositions: " << encoderIncremental.totalPositions;
  }
};
}  // namespace march4cpp

#endif  // PROJECT_ENCODER_INCREMENTAL_H