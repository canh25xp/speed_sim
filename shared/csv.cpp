#include "csv.hpp"
#include "common.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

CSVHandler::CSVHandler (const std::string &fileName)
    : fileName (fileName), fileOpened (false)
{
}

CSVHandler::~CSVHandler ()
{
  this->closeFile ();
}

bool
CSVHandler::openFile ()
{
  outputFile.open (fileName);
  if (!outputFile)
    {
      std::cerr << "Error opening file: " << fileName << std::endl;
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

void
CSVHandler::writeRow (const SpeedData &data)
{
  std::ostringstream oss;
  oss << std::fixed << std::setprecision (1) << data.value;
  writeRow ({ std::to_string (data.id), data.time, oss.str () });
}

void
CSVHandler::writeRow (const SpeedDataSummary &data)
{
  std::ostringstream oss;
  oss << std::fixed << std::setprecision (1) << data.value;
  writeRow ({ std::to_string (data.id), data.parameter, data.time, oss.str () });
}

std::vector<std::vector<std::string> >
CSVHandler::readFile ()
{
  inputFile.open (fileName);
  if (!inputFile)
    {
      std::cerr << "Error opening file for reading: " << fileName << std::endl;
      return {};
    }

  std::vector<std::vector<std::string> > data;
  std::string line;

  std::getline (inputFile, line); // Read header

  while (getline (inputFile, line))
    {
      std::istringstream ss (line);
      std::vector<std::string> row;
      std::string cell;

      while (getline (ss, cell, ','))
        {
          row.push_back (cell);
        }

      data.push_back (row);
    }

  inputFile.close ();
  return data;
}
