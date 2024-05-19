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

using namespace std;

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

  cout << parser.getArg ();
  cout << "Simulation started..." << endl;

  // Open file for writing
  ofstream outputFile (SAVE_NAME);
  if (!outputFile)
    {
      cerr << "Error opening file." << endl;
      return 1;
    }

  // Write header to CSV file
  outputFile << "id,time,value" << endl;

  // Simulation loop
  time_t start_time = time (nullptr);
  for (int i = 1; i <= interval; i += sampling)
    {
      for (int j = 1; j <= num_sensors; ++j)
        {
          // Generate random speed and timestamp
          double speed = getSensorValue ();
          string timestamp = getCurrentTimestamp ();

          // Write data to file
          outputFile << j << "," << timestamp << "," << fixed
                     << setprecision (1) << speed << endl;
        }

      // Wait for sampling time
      this_thread::sleep_for (chrono::seconds (sampling));
    }

  // Close file
  outputFile.close ();

  cout << "Simulation completed. Data saved to " << SAVE_NAME << endl;
  return 0;
}

