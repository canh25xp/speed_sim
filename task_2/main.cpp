#include "csv.hpp"
#include "parser.hpp"
#include "simulation.hpp"

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

  // Create CSVHandler instance
  CSVHandler csvHandler (SAVE_NAME);

  if (!csvHandler.openFile ())
    {
      return 1;
    }

  // Write header to CSV file
  csvHandler.writeHeader ({ "id", "time", "value" });

  // The interval should be convert to seconds before passing to the
  // Simulation: interval*60*60 However to save time, we will keep it as it.
  runSimulation (num_sensors, sampling, interval, csvHandler);

  // Close the file
  csvHandler.closeFile ();

  std::cout << "Simulation completed. Data saved to " << SAVE_NAME
            << std::endl;
  return 0;
}
