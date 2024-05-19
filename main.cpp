#include "parser.hpp"
#include "sim.hpp"

#include <fstream>
#include <iostream>

#define SAVE_NAME "speed_data.csv"

int num_sensors = 0;
int sampling = 0;
int interval = 0;

int
main (int argc, char **argv)
{
  Parser parser (argc, argv);

  num_sensors = parser.get ("-n", 1); // 1 sensor
  sampling = parser.get ("-st", 10);  // 10 seconds
  interval = parser.get ("-si", 1);   // 1 hour

  std::cout << parser.getArg ();
  std::cout << "Simulation started..." << std::endl;

  // Open file for writing
  std::ofstream outputFile (SAVE_NAME);
  if (!outputFile)
    {
      std::cerr << "Error opening file." << std::endl;
      return 1;
    }

  // Write header to CSV file
  outputFile << "id,time,value" << std::endl;

  // Simulation loop
  runSimulation (num_sensors, sampling, interval, outputFile);

  // Close file
  outputFile.close ();

  std::cout << "Simulation completed. Data saved to " << SAVE_NAME
            << std::endl;
  return 0;
}
