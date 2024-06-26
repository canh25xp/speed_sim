#pragma once
#include <fstream>
#include <string>
#include <vector>

struct SpeedData;
struct SpeedDataSummary;

namespace csv
{

class CSVHandler
{
public:
  CSVHandler (const std::string &filename);
  ~CSVHandler ();

  bool openFile (std::ios_base::openmode mode);
  void closeFile ();
  void writeHeader (const std::vector<std::string> &headers);
  void writeRow (const std::vector<std::string> &row);
  void writeRow (const SpeedData &data);
  void writeRow (const SpeedDataSummary &data);
  std::vector<std::vector<std::string> > readFile ();

private:
  std::string fileName;
  std::fstream fileStream;
};
} // namespace csv
