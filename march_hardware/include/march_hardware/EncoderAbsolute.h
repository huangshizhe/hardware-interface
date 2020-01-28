// Copyright 2019 Project March.

#ifndef MARCH_HARDWARE_ENCODER_ABSOLUTE_H
#define MARCH_HARDWARE_ENCODER_ABSOLUTE_H

#include <ostream>
#include "Encoder.h"

namespace march{
class EncoderAbsolute : public Encoder
{
private:
  int upperHardLimitIU;
  int lowerHardLimitIU;
  int upperSoftLimitIU;
  int lowerSoftLimitIU;
  int zeroPositionIU;
  float safetyMarginRad;

public:
  EncoderAbsolute()
    : upperHardLimitIU(0)
    , lowerHardLimitIU(0)
    , upperSoftLimitIU(0)
    , lowerSoftLimitIU(0)
    , zeroPositionIU(0)
    , safetyMarginRad(0)
  {
  }
  EncoderAbsolute(int numberOfBits, int minPositionIU, int maxPositionIU, int zeroPositionIU, float safetyMarginRad);

  bool isWithinHardLimitsIU(int positionIU);
  bool isWithinSoftLimitsIU(int positionIU);
  bool isValidTargetIU(int currentIU, int targetIU);

  int getUpperSoftLimitIU() const;
  int getLowerSoftLimitIU() const;
  int getUpperHardLimitIU() const;
  int getLowerHardLimitIU() const;

  /** @brief Override comparison operator */
  friend bool operator==(const Encoder& lhs, const Encoder& rhs)
  {
    return lhs.slaveIndex == rhs.slaveIndex && lhs.totalPositions == rhs.totalPositions &&
           lhs.upperSoftLimitIU == rhs.upperSoftLimitIU && lhs.lowerSoftLimitIU == rhs.lowerSoftLimitIU &&
           lhs.upperHardLimitIU == rhs.upperHardLimitIU && lhs.lowerHardLimitIU == rhs.lowerHardLimitIU &&
           lhs.zeroPositionIU == rhs.zeroPositionIU && lhs.safetyMarginRad == rhs.safetyMarginRad;
  }
  /** @brief Override stream operator for clean printing */
  friend ::std::ostream& operator<<(std::ostream& os, const Encoder& encoder)
  {
    return os << "slaveIndex: " << encoder.slaveIndex << ", "
              << "totalPositions: " << encoder.totalPositions << ", "
              << "upperHardLimit: " << encoder.upperHardLimitIU << ", "
              << "lowerHardLimit: " << encoder.lowerHardLimitIU << ", "
              << "upperSoftLimit: " << encoder.upperSoftLimitIU << ", "
              << "lowerSoftLimit: " << encoder.lowerSoftLimitIU << ", "
              << "zeroPositionIU: " << encoder.zeroPositionIU << ", "
              << "safetyMarginRad: " << encoder.safetyMarginRad;
  }
};

} //  namespace march
#endif  //  MARCH_HARDWARE_ENCODER_ABSOLUTE_H