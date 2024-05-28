#pragma once
#include "csv.hpp"

#include <string>

std::string getCurrentTimestamp ();

double getSensorValue ();

void runSimulation(int num_sensors, int sampling, int interval, CSVHandler& csvHandler);
