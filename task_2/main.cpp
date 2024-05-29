#include "process.hpp"
#include <string>

int
main (int argc, char *argv[])
{
  std::string filename = "speed_data.csv";
  if (argc > 1)
    {
      filename = argv[1];
    }

  processFile (filename);
  return 0;
}
