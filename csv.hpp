#pragma once

#include <fstream>
#include <string>
#include <vector>

class CSVHandler
{
public:
  CSVHandler (const std::string &filename);
  bool openFile ();
  void closeFile ();
  void writeHeader (const std::vector<std::string> &headers);
  void writeRow (const std::vector<std::string> &row);

private:
  std::string filename;
  std::ofstream outputFile;
  bool fileOpened;
};
