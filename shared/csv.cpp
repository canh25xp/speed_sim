#include "csv.hpp"
#include "common.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

CSVHandler::CSVHandler (const std::string &fileName)
    : fileName (fileName)
{
}

CSVHandler::~CSVHandler ()
{
  CSVHandler::closeFile ();
}

bool
CSVHandler::openFile (std::ios_base::openmode mode)
{
  fileStream.open (fileName, mode);
  return fileStream.is_open ();
}

void
CSVHandler::closeFile ()
{
  if (fileStream.is_open ())
    {
      fileStream.close ();
    }
}

void
CSVHandler::writeHeader (const std::vector<std::string> &headers)
{
  for (size_t i = 0; i < headers.size (); ++i)
    {
      fileStream << headers[i];
      if (i < headers.size () - 1)
        {
          fileStream << ",";
        }
    }
  fileStream << std::endl;
}

void
CSVHandler::writeRow (const std::vector<std::string> &row)
{
  for (size_t i = 0; i < row.size (); ++i)
    {
      fileStream << row[i];
      if (i < row.size () - 1)
        {
          fileStream << ",";
        }
    }
  fileStream << std::endl;
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
  if (!fileStream.is_open () || fileStream.eof ())
    {
      std::cerr << "Error opening file for reading: " << fileName << std::endl;
      return {};
    }

  std::vector<std::vector<std::string> > data;
  std::string line;

  std::getline (fileStream, line); // Read header

  while (getline (fileStream, line))
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

  fileStream.close ();
  return data;
}
