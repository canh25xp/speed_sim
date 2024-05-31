#include "common.hpp"
#include "csv.hpp"
#include "parser.hpp"
#include "simulation.hpp"

#include <iostream>

int
main (int argc, char **argv)
{
  Parser parser (argc, argv);

  // clang-format off
  int num_sensors = parser.get ("-n",   1);   // 1 sensor
  int sampling    = parser.get ("-st",  10);  // 10 seconds
  int interval    = parser.get ("-si",  1);   // 1 hour
  // clang-format on

  std::cout << parser.getArg ();
  std::cout << "Simulation started..." << std::endl;

  // Create CSVHandler instance
  CSVHandler csvHandler (DATA_FILE_NAME);

  if (!csvHandler.openFile ())
    {
      return 1;
    }

  // Write header to CSV file
  csvHandler.writeHeader ({ "id", "time", "value" });

  // The interval should be convert to seconds before passing to the
  // runSimulation: interval*60*60 However to save time, we will keep it as it.
  runSimulation (num_sensors, sampling, interval, csvHandler);

  // Close the file
  csvHandler.closeFile ();

  std::cout << "Simulation completed. Data saved to " << DATA_FILE_NAME << std::endl;
  return 0;
}
