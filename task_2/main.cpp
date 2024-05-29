#include <fstream>
#include <iostream>
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

void
processFile (const std::string &filename)
{
  std::ifstream inputFile (filename);
  std::ofstream validFile ("valid_speed_data.csv");
  std::ofstream outlierFile ("outlier_data.csv");

  if (!inputFile.is_open ())
    {
      std::cerr << "Could not open the file: " << filename << std::endl;
      return;
    }

  if (!validFile.is_open () || !outlierFile.is_open ())
    {
      std::cerr << "Could not open the output files." << std::endl;
      return;
    }

  std::string line;
  std::getline (inputFile, line);
  validFile << line << std::endl;

  std::vector<SpeedData> outliers;
  std::vector<SpeedData> validData;

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

  inputFile.close ();
  validFile.close ();
  outlierFile.close ();
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
