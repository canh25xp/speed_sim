#pragma once
#include <string>

#define SAVE_NAME "speed_data.csv"

struct SpeedData {
    int id;
    std::string time;
    double value;
};

struct SummaryData {
    std::string max_time;
    double max_value;
    std::string min_time;
    double min_value;
    double sum;
    int count;
};
