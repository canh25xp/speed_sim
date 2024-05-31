#include "common.hpp"
#include "parser.hpp"
#include "process.hpp"
#include <string>

int
main (int argc, char *argv[])
{
  Parser parser (argc, argv);

  // clang-format off
  std::string filename = parser.get (0, DATA_FILE_NAME);
  bool sort            = parser.has ("-s");
  // clang-format on

  processFile (filename);
  return 0;
}
