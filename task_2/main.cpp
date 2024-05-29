#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const int LOWER_BOUND = 850;
const int UPPER_BOUND = 850;

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
  std::ofstream validFile ("valid_speed_data.csv");
  std::ofstream outlierFile ("outlier_data.csv");
  std::ofstream summaryFile ("data_summary.csv");

  if (!inputFile.is_open ())
    {
      std::cerr << "Could not open the file: " << filename << std::endl;
      return;
    }

  if (!validFile.is_open () || !outlierFile.is_open ()
      || !summaryFile.is_open ())
    {
      std::cerr << "Could not open the output files." << std::endl;
      return;
    }

  std::string line;
  std::getline (inputFile, line); // Read header
  validFile << line << std::endl;

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

  outlierFile << "number of outliers: " << outliers.size () << std::endl;
  outlierFile << "id,time,value" << std::endl;
  for (const auto &data : outliers)
    {
      outlierFile << data.id << "," << data.time << "," << data.value
                  << std::endl;
    }

  for (const auto &data : validData)
    {
      validFile << data.id << "," << data.time << "," << data.value
                << std::endl;
    }

  summaryFile << "id,parameter,time,value" << std::endl;
  for (const auto &sensorData : summaries)
    {
      int id = sensorData.first;
      for (const auto &hourlyData : sensorData.second)
        {
          const std::string &hourTime = hourlyData.first;
          const SummaryData &summary = hourlyData.second;
          double mean = summary.sum / summary.count;

          summaryFile << id << ",max," << summary.max_time << ","
                      << summary.max_value << std::endl;
          summaryFile << id << ",min," << summary.min_time << ","
                      << summary.min_value << std::endl;
          summaryFile << id << ",mean," << hourTime << "," << mean
                      << std::endl;
        }
    }

  inputFile.close ();
  validFile.close ();
  outlierFile.close ();
  summaryFile.close ();
}

int
main (int argc, char *argv[])
{
  std::string filename = "speed_data.csv";
  if (argc > 1)
    {
      filename = argv[1];
    }

  processFile (filename);
  return 0;
}
