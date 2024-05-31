#include "simulation.hpp"
#include "common.hpp"
#include "csv.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <thread>

std::string
getCurrentTimestamp ()
{
  // Get the current time
  std::time_t now = std::time (nullptr);

  // Convert it to local time representation
  std::tm *localTime = std::localtime (&now);

  // Create a string stream to format the timestamp
  std::ostringstream timestamp;
  timestamp << std::put_time (localTime, "%Y:%m:%d %H:%M:%S");

  return timestamp.str ();
}

double
getSensorValue ()
{
  // Generating random speed between 0 and 3000 rpm with 0.2 rpm resolution
  return (rand () % 15001) / 5.0;
}

void
runSimulation (int num_sensors, int sampling, int interval,
               CSVHandler &csvHandler)
{
  // Simulation loop
  for (int i = 1; i <= interval; i += sampling)
    {
      for (int id = 1; id <= num_sensors; ++id)
        {
          // Generate random speed and timestamp
          double speed = getSensorValue ();
          std::string timestamp = getCurrentTimestamp ();
          SpeedData speedData = { id, timestamp, speed };
          // Write data to file
          csvHandler.writeRow(speedData);
        }

      // Wait for sampling time
      std::this_thread::sleep_for (std::chrono::seconds (sampling));
    }
}
