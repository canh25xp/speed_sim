#pragma once
#include <ctime>
#include <string>

const int LOWER_BOUND = 850;
const int UPPER_BOUND = 1650;

struct SpeedData;

struct SummaryData;

std::tm parseTime (const std::string &timeStr);

std::string formatTime (const std::tm &tm);

void processFile (const std::string &filename);
