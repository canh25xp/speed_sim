#include "sim.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

std::string
generateTimestamp ()
{
  time_t current_time = time (nullptr);
  struct tm *timeinfo = localtime (&current_time);
  char timestamp[20];
  strftime (timestamp, sizeof (timestamp), "%Y:%m:%d %H:%M:%S", timeinfo);
  return std::string (timestamp);
}

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
