#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

#include "parser.hpp"

#define SAVE_NAME "speed_data.csv"

using namespace std;

int num_sensors = 0;
int sampling = 0;
int interval = 0;

// Function to generate random speed within the specified range and resolution
double generateSpeed ();
// Function to generate timestamp in the format YYYY:MM:DD hh:mm:ss
string generateTimestamp ();

int
main (int argc, char **argv)
{
  Parser parser (argc, argv);
  num_sensors = parser.get ("-n", 1); // 1 sensor
  sampling = parser.get ("-st", 10);  // 10 seconds
  interval = parser.get ("-si", 1);   // 1 hour
  cout << num_sensors << endl;
  cout << sampling << endl;
  cout << interval << endl;
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
          double speed = generateSpeed ();
          string timestamp = generateTimestamp ();

          // Write data to file
          outputFile << j << ", " << timestamp << ", " << fixed
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

double
generateSpeed ()
{
  return (rand () % 15001) / 5.0; // Generating random speed between 0 and 3000
                                  // rpm with 0.2 rpm resolution
}

string
generateTimestamp ()
{
  time_t current_time = time (nullptr);
  struct tm *timeinfo = localtime (&current_time);
  char timestamp[20];
  strftime (timestamp, sizeof (timestamp), "%Y:%m:%d %H:%M:%S", timeinfo);
  return string (timestamp);
}
