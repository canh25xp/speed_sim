#pragma once
#include <string>

class CSVHandler;

std::string getCurrentTimestamp ();

double getSensorValue ();

void runSimulation(int num_sensors, int sampling, int interval, CSVHandler& csvHandler);
