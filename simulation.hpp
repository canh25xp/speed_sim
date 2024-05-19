#pragma once
#include <string>
#include <fstream>

std::string getCurrentTimestamp ();

double getSensorValue ();

void runSimulation(int num_sensors, int sampling, int interval, std::ofstream& outputFile);
