// Copyright 2018 Project March.

#include "march_hardware_interface/march_pdb_state_interface.h"
#include "gtest/gtest.h"
#include <sstream>

class TestPdbStateInterface : public ::testing::Test
{
protected:
  march::PowerDistributionBoard power_distribution_board_read_;
  bool master_shutdown_allowed_command = false;
  bool all_high_voltage_on_off_command = true;
  PowerNetOnOffCommand power_net_on_off_command_;

  void SetUp() override
  {
    power_distribution_board_read_ = march::PowerDistributionBoard();
    master_shutdown_allowed_command = false;
    all_high_voltage_on_off_command = true;
    power_net_on_off_command_ = PowerNetOnOffCommand();
  }
};

TEST_F(TestPdbStateInterface, GeName)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);
  EXPECT_EQ("PDBhandle", marchPdbStateHandle.getName());
}

TEST_F(TestPdbStateInterface, GetPowerDistributionBoardEquals)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);
  EXPECT_TRUE(power_distribution_board_read_ == *marchPdbStateHandle.getPowerDistributionBoard());
}

TEST_F(TestPdbStateInterface, GetPowerDistributionBoardNotEqual)
{
  NetMonitorOffsets currentOffsets = NetMonitorOffsets(5, 9, 13, 17, 3, 2, 1, 4);
  NetDriverOffsets netDriverOffsets = NetDriverOffsets(4, 3, 2);
  BootShutdownOffsets stateOffsets = BootShutdownOffsets(0, 0, 1);
  march::PowerDistributionBoard pdb = march::PowerDistributionBoard(1, currentOffsets, netDriverOffsets, stateOffsets);
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);
  EXPECT_FALSE(pdb == *marchPdbStateHandle.getPowerDistributionBoard());
}

TEST_F(TestPdbStateInterface, SetMasterShutdownAllowedTrue)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  EXPECT_FALSE(master_shutdown_allowed_command);
  marchPdbStateHandle.setMasterShutdownAllowed(true);
  EXPECT_TRUE(master_shutdown_allowed_command);
}
TEST_F(TestPdbStateInterface, SetMasterShutdownAllowedFalse)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  EXPECT_FALSE(master_shutdown_allowed_command);
  marchPdbStateHandle.setMasterShutdownAllowed(false);
  EXPECT_FALSE(master_shutdown_allowed_command);
}

TEST_F(TestPdbStateInterface, HighVoltageNetEnableDisable)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  EXPECT_TRUE(all_high_voltage_on_off_command);
  marchPdbStateHandle.setMasterShutdownAllowed(true);
  EXPECT_TRUE(all_high_voltage_on_off_command);
}
TEST_F(TestPdbStateInterface, TurnLowNetOn)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  // Check if the power net type is undefined
  EXPECT_EQ(PowerNetType(), power_net_on_off_command_.getType());
  marchPdbStateHandle.turnNetOnOrOff(PowerNetType("low_voltage"), true, 1);
  EXPECT_EQ(PowerNetType("low_voltage"), power_net_on_off_command_.getType());
  EXPECT_EQ(1, power_net_on_off_command_.getNetNumber());
  EXPECT_TRUE(power_net_on_off_command_.isOnOrOff());
}

TEST_F(TestPdbStateInterface, TurnLowNetOff)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  // Check if the power net type is undefined
  EXPECT_EQ(PowerNetType(), power_net_on_off_command_.getType());
  marchPdbStateHandle.turnNetOnOrOff(PowerNetType("low_voltage"), false, 1);
  EXPECT_EQ(PowerNetType("low_voltage"), power_net_on_off_command_.getType());
  EXPECT_EQ(1, power_net_on_off_command_.getNetNumber());
  EXPECT_FALSE(power_net_on_off_command_.isOnOrOff());
}
TEST_F(TestPdbStateInterface, TurnHighNetOn)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  // Check if the power net type is undefined
  EXPECT_EQ(PowerNetType(), power_net_on_off_command_.getType());
  marchPdbStateHandle.turnNetOnOrOff(PowerNetType("high_voltage"), true, 1);
  EXPECT_EQ(PowerNetType("high_voltage"), power_net_on_off_command_.getType());
  EXPECT_EQ(1, power_net_on_off_command_.getNetNumber());
  EXPECT_TRUE(power_net_on_off_command_.isOnOrOff());
}

TEST_F(TestPdbStateInterface, TurnHighNetOff)
{
  MarchPdbStateHandle marchPdbStateHandle("PDBhandle", &power_distribution_board_read_,
                                          &master_shutdown_allowed_command, &all_high_voltage_on_off_command,
                                          &power_net_on_off_command_);

  // Check if the power net type is undefined
  EXPECT_EQ(PowerNetType(), power_net_on_off_command_.getType());
  marchPdbStateHandle.turnNetOnOrOff(PowerNetType("high_voltage"), false, 1);
  EXPECT_EQ(PowerNetType("high_voltage"), power_net_on_off_command_.getType());
  EXPECT_EQ(1, power_net_on_off_command_.getNetNumber());
  EXPECT_FALSE(power_net_on_off_command_.isOnOrOff());
}
