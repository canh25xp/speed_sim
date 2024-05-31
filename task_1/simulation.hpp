#pragma once
#include <string>

namespace csv
{
class CSVHandler;
}

std::string getCurrentTimestamp ();

double getSensorValue ();

void runSimulation (int num_sensors, int sampling, int interval, csv::CSVHandler &csvHandler);
