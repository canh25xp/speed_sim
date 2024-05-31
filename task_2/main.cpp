#include "common.hpp"
#include "parser.hpp"
#include "process.hpp"
#include <string>

int
main (int argc, char *argv[])
{
  Parser parser (argc, argv);

  std::string filename = parser.getPositional (0, SAVE_NAME);

  processFile (filename);
  return 0;
}
