// Copyright 2019 Project March.

#include <march_hardware/EtherCAT/EthercatIO.h>
#include <march_hardware/EncoderIncremental.h>
#include <cmath>
#include <ros/ros.h>

namespace march4cpp
{
EncoderIncremental::EncoderIncremental(int numberOfBits)
{
  ROS_ASSERT_MSG(numberOfBits > 0 && numberOfBits <= 32, "Encoder resolution of %d is not within range (0, 32)",
                 numberOfBits);
  this->totalPositions = static_cast<int>(pow(2, numberOfBits) - 1);

  this->slaveIndex = -1;
}

float EncoderIncremental::getIncrementRad(uint8_t IncrementByteOffset)
{
  return IUtoRad(getIncrementIU(IncrementByteOffset));
}

int EncoderIncremental::getIncrementIU(uint8_t IncrementByteOffset)
{
  if (this->slaveIndex == -1)
  {
    ROS_FATAL("Encoder has slaveIndex of -1");
  }
  union bit32 return_byte = get_input_bit32(this->slaveIndex, IncrementByteOffset);
  ROS_DEBUG("Encoder read (IU): %d", return_byte.i);
  return return_byte.i;
}

float EncoderIncremental::IUtoRad(int iu)
{
  return static_cast<float>iu * 2 * M_PI / totalPositions;
}

void EncoderIncremental::setSlaveIndex(int slaveIndex)
{
  this->slaveIndex = slaveIndex;
}

int EncoderIncremental::getSlaveIndex() const
{
  return this->slaveIndex;
}
}  // namespace march4cpp
