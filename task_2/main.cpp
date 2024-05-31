#include "parser.hpp"
#include "process.hpp"
#include <string>

int
main (int argc, char *argv[])
{

  Parser parser (argc, argv);

  std::string filename = "speed_data.csv";

  for (int i = 0; i < parser.getPositionalArgCount (); ++i)
    {
      filename = parser.getPositional (i);
    }

  processFile (filename);
  return 0;
}
