#include "common.hpp"
#include "parser.hpp"
#include <iostream>

int
main (int argc, char **argv)
{
  Parser parser (argc, argv);

  std::string inputFileName = parser.get (0, DATA_FILE_NAME);
  std::string outputFileName = parser.get (1);
  std::cout << inputFileName << " " << outputFileName << std::endl;
  return 0;
}
