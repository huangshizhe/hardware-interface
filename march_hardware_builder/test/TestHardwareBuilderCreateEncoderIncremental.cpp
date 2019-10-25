// Copyright 2019 Project March.

#include "gtest/gtest.h"
#include "ros/ros.h"
#include <gmock/gmock.h>
#include <ros/package.h>
#include <march_hardware_builder/HardwareConfigExceptions.h>
#include <march_hardware_builder/HardwareBuilder.h>

using ::testing::Return;
using ::testing::AtLeast;

class EncoderIncrementalTest : public ::testing::Test
{
protected:
  std::string base_path;
  HardwareBuilder hardwareBuilder;

  void SetUp() override
  {
    base_path = ros::package::getPath("march_hardware_builder").append("/test/yaml/encoderIncremental");
  }

  std::string fullPath(const std::string& relativePath)
  {
    return this->base_path.append(relativePath);
  }
};

class EncoderIncrementalDeathTest : public EncoderIncrementalTest
{
};

TEST_F(EncoderIncrementalTest, ValidEncoderIncrementalHip)
{
  std::string fullPath = this->fullPath("/encoderIncremental_correct_1.yaml");
  YAML::Node encoderIncrementalConfig = YAML::LoadFile(fullPath);

  march4cpp::EncoderIncremental actualEncoderIncremental = march4cpp::EncoderIncremental(12);
  march4cpp::EncoderIncremental createdEncoderIncremental =
                                hardwareBuilder.createEncoderIncremental(encoderIncrementalConfig);
  ASSERT_EQ(actualEncoderIncremental, createdEncoderIncremental);
}

TEST_F(EncoderIncrementalTest, ValidEncoderIncrementalAnkle)
{
  std::string fullPath = this->fullPath("/encoderIncremental_correct_2.yaml");
  YAML::Node encoderIncrementalConfig = YAML::LoadFile(fullPath);

  march4cpp::EncoderIncremental actualEncoderIncremental = march4cpp::EncoderIncremental(13);
  march4cpp::EncoderIncremental createdEncoderIncremental =
                                hardwareBuilder.createEncoderIncremental(encoderIncrementalConfig);
  ASSERT_EQ(actualEncoderIncremental, createdEncoderIncremental);
}

TEST_F(EncoderIncrementalTest, NoResolution)
{
  std::string fullPath = this->fullPath("/encoderIncremental_no_resolution.yaml");
  YAML::Node encoderIncrementalConfig = YAML::LoadFile(fullPath);

  ASSERT_THROW(hardwareBuilder.createEncoderIncremental(encoderIncrementalConfig), MissingKeyException);
}

TEST_F(EncoderIncrementalDeathTest, IncorrectResolution)
{
  std::string fullPath = this->fullPath("/encoderIncremental_incorrect_resolution.yaml");
  YAML::Node encoderIncrementalConfig = YAML::LoadFile(fullPath);

  ASSERT_DEATH(hardwareBuilder.createEncoderIncremental(encoderIncrementalConfig),
               "Incremental encoder resolution of -1 is not within range \\(0, 32\\)");
}
