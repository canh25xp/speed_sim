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

  csv::CSVHandler csvHandler (DATA_FILE_NAME);

  if (!csvHandler.openFile (std::ios::out))
    {
      return 1;
    }

  csvHandler.writeHeader ({ "id", "time", "value" });

  // The interval should be normalize to seconds before passing to the function: interval*60*60
  // However to save time, we will keep it as it.
  runSimulation (num_sensors, sampling, interval, csvHandler);

  return 0;
}
