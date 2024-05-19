#include "parser.hpp"
#include "sim.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

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
  for (int i = 1; i <= interval; i += sampling)
    {
      for (int j = 1; j <= num_sensors; ++j)
        {
          // Generate random speed and timestamp
          double speed = getSensorValue ();
          std::string timestamp = getCurrentTimestamp ();

          // Write data to file
          outputFile << j << "," << timestamp << "," << std::fixed
                     << std::setprecision (1) << speed << std::endl;
        }

      // Wait for sampling time
      std::this_thread::sleep_for (std::chrono::seconds (sampling));
    }

  // Close file
  outputFile.close ();

  std::cout << "Simulation completed. Data saved to " << SAVE_NAME << std::endl;
  return 0;
}

