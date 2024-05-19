#include "csv.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

CSVHandler::CSVHandler (const std::string &filename)
    : filename (filename), fileOpened (false)
{
}

bool
CSVHandler::openFile ()
{
  outputFile.open (filename);
  if (!outputFile)
    {
      std::cerr << "Error opening file: " << filename << std::endl;
      return false;
    }
  fileOpened = true;
  return true;
}

void
CSVHandler::closeFile ()
{
  if (fileOpened)
    {
      outputFile.close ();
      fileOpened = false;
    }
}

void
CSVHandler::writeHeader (const std::vector<std::string> &headers)
{
  for (size_t i = 0; i < headers.size (); ++i)
    {
      outputFile << headers[i];
      if (i < headers.size () - 1)
        {
          outputFile << ",";
        }
    }
  outputFile << std::endl;
}

void
CSVHandler::writeRow (const std::vector<std::string> &row)
{
  for (size_t i = 0; i < row.size (); ++i)
    {
      outputFile << row[i];
      if (i < row.size () - 1)
        {
          outputFile << ",";
        }
    }
  outputFile << std::endl;
}
