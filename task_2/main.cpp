#include "common.hpp"
#include "parser.hpp"
#include "process.hpp"
#include <string>

int
main (int argc, char *argv[])
{
  Parser parser (argc, argv);

  std::string filename = parser.get (0, DATA_FILE_NAME);
  bool sort            = parser.has("-s");

  processFile (filename);
  return 0;
}
