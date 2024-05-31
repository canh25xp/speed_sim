#include "process.hpp"
#include "common.hpp"
#include "csv.hpp"
#include <ctime>
#include <format>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

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
  CSVHandler inputFile (filename);
  CSVHandler validFile (VALID_FILE_NAME);
  CSVHandler outlierFile (OUTLIER_FILE_NAME);
  CSVHandler summaryFile (SUMMARY_FILE_NAME);

  validFile.openFile ();
  outlierFile.openFile ();
  summaryFile.openFile ();

  std::vector<SpeedData> outliers;
  std::vector<SpeedData> validData;
  std::map<int, std::map<std::string, SummaryData> > summaries;

  for (const auto &row : inputFile.readFile ())
    {
      std::string idStr = row[0];
      std::string timeStr = row[1];
      std::string valueStr = row[2];

      SpeedData data = { std::stoi (idStr), timeStr, std::stod (valueStr) };

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

  outlierFile.writeRow ({ std::format ("number of outliers: {}", outliers.size ()) });
  outlierFile.writeHeader ({ "id", "time", "value" });
  for (const auto &data : outliers)
    {
      outlierFile.writeRow (data);
    }

  validFile.writeHeader ({ "id", "time", "value" });
  for (const auto &data : validData)
    {
      validFile.writeRow (data);
    }

  summaryFile.writeHeader ({ "id", "parameter", "time", "value" });
  for (const auto &sensorData : summaries)
    {
      int id = sensorData.first;
      for (const auto &hourlyData : sensorData.second)
        {
          const std::string &hourTime = hourlyData.first;
          const SummaryData &summary = hourlyData.second;
          double mean = summary.sum / summary.count;
          SpeedDataSummary max{ id, "max", summary.max_time, summary.max_value };
          SpeedDataSummary min{ id, "min", summary.min_time, summary.min_value };
          SpeedDataSummary avg{ id, "mean", hourTime, summary.max_value };

          summaryFile.writeRow (max);
          summaryFile.writeRow (min);
          summaryFile.writeRow (avg);
        }
    }
}
