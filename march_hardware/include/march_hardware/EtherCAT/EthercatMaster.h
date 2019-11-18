// Copyright 2019 Project March.
#ifndef MARCH_HARDWARE_ETHERCAT_ETHERCATMASTER_H
#define MARCH_HARDWARE_ETHERCAT_ETHERCATMASTER_H
#include <vector>
#include <string>
#include <thread>  // NOLINT(build/c++11)

#include <march_hardware/Joint.h>

namespace march4cpp
{
class EthercatMaster
{
  std::string ifname;      // Network interface name, check ifconfig
  char IOmap[4096];        // Holds the mapping of the SOEM message
  int expectedWKC;         // Expected working counter
  std::thread EcatThread;  // Handler for parallel thread

  std::vector<Joint>* jointListPtr;
  int maxSlaveIndex;
  int ecatCycleTimems;

public:
  bool isOperational = false;  // Is SOEM in operational state

  explicit EthercatMaster(std::vector<Joint>* jointListPtr, std::string ifname, int maxSlaveIndex, int ecatCycleTime);

  void start();
  void stop();

  // Parallel thread
  void ethercatLoop();

  void sendProcessData();

  int receiveProcessData();

  void monitorSlaveConnection();
};

}  // namespace march4cpp
#endif  // MARCH_HARDWARE_ETHERCAT_ETHERCATMASTER_H
