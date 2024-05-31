#include "process.hpp"
#include "csv.hpp"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct SpeedData
{
  int id;
  std::string time;
  double value;
};

struct SummaryData
{
  std::string max_time;
  double max_value;
  std::string min_time;
  double min_value;
  double sum;
  int count;
};

std::tm
parseTime (const std::string &timeStr)
{
  std::tm tm = {};
  std::istringstream ss (timeStr);
  ss >> std::get_time (&tm, "%Y:%m:%d %H:%M:%S");
  return tm;
}

std::string
formatTime (const std::tm &tm)
{
  std::ostringstream oss;
  oss << std::put_time (&tm, "%Y:%m:%d %H:%M:%S");
  return oss.str ();
}

void
processFile (const std::string &filename)
{
  std::ifstream inputFile (filename);
  CSVHandler validFile ("valid_speed_data.csv");
  CSVHandler outlierFile ("outlier_data.csv");
  CSVHandler summaryFile ("data_summary.csv");

  if (!inputFile.is_open ())
    {
      std::cerr << "Could not open the file: " << filename << std::endl;
      return;
    }

  if (!validFile.openFile () || !outlierFile.openFile ()
      || !summaryFile.openFile ())
    {
      std::cerr << "Could not open the output files." << std::endl;
      return;
    }

  std::string line;
  std::getline (inputFile, line); // Read header
  validFile.writeHeader ({ "id", "time", "value" });
  outlierFile.writeHeader ({ "id", "time", "value" });
  summaryFile.writeHeader ({ "id", "parameter", "time", "value" });

  std::vector<SpeedData> outliers;
  std::vector<SpeedData> validData;
  std::map<int, std::map<std::string, SummaryData> > summaries;

  while (std::getline (inputFile, line))
    {
      std::istringstream ss (line);
      std::string idStr, timeStr, valueStr;
      std::getline (ss, idStr, ',');
      std::getline (ss, timeStr, ',');
      std::getline (ss, valueStr, ',');

      SpeedData data;
      data.id = std::stoi (idStr);
      data.time = timeStr;
      data.value = std::stod (valueStr);

      if (data.value < LOWER_BOUND || data.value > UPPER_BOUND)
        {
          outliers.push_back (data);
        }
      else
        {
          validData.push_back (data);

          std::tm tm = parseTime (timeStr);
          tm.tm_min = 0;
          tm.tm_sec = 0;
          std::string hourTime = formatTime (tm);

          SummaryData &summary = summaries[data.id][hourTime];
          if (summary.count == 0 || data.value > summary.max_value)
            {
              summary.max_value = data.value;
              summary.max_time = data.time;
            }
          if (summary.count == 0 || data.value < summary.min_value)
            {
              summary.min_value = data.value;
              summary.min_time = data.time;
            }
          summary.sum += data.value;
          summary.count++;
        }
    }

  for (const auto &data : outliers)
    {
      outlierFile.writeRow ({ std::to_string (data.id), data.time,
                              std::to_string (data.value) });
    }

  for (const auto &data : validData)
    {
      validFile.writeRow ({ std::to_string (data.id), data.time,
                            std::to_string (data.value) });
    }

  for (const auto &sensorData : summaries)
    {
      int id = sensorData.first;
      for (const auto &hourlyData : sensorData.second)
        {
          const std::string &hourTime = hourlyData.first;
          const SummaryData &summary = hourlyData.second;
          double mean = summary.sum / summary.count;

          summaryFile.writeRow ({ std::to_string (id), "max", summary.max_time,
                                  std::to_string (summary.max_value) });
          summaryFile.writeRow ({ std::to_string (id), "min", summary.min_time,
                                  std::to_string (summary.min_value) });
          summaryFile.writeRow ({ std::to_string (id), "mean", hourTime,
                                  std::to_string (mean) });
        }
    }

  inputFile.close ();
  validFile.closeFile ();
  outlierFile.closeFile ();
  summaryFile.closeFile ();
}
