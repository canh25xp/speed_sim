#pragma once
#include <string>

#define DATA_FILE_NAME "speed_data.csv"
#define VALID_FILE_NAME "valid_speed_data.csv"
#define OUTLIER_FILE_NAME "outlier_data.csv"
#define SUMMARY_FILE_NAME "data_summary.csv"
#define SORTED_FILE_NAME "sorted_speed_data.csv"

struct SpeedData
{
  int id;
  std::string time;
  double value;
};

struct SpeedDataSummary
{
  int id;
  std::string parameter;
  std::string time;
  double value;
};

struct SummaryData
{
  std::string max_time;
  double max_value;
  std::string min_time;
  double min_value;
  double sum;
  int count;
};
