#include "parser.hpp"
#include <iostream>

int
main (int argc, char **argv)
{
  Parser parser (argc, argv);

  int arg1 = parser.get ("-a", 0);
  int arg2 = parser.get ("-b", 0);
  int arg3 = parser.get ("-c", 0);

  std::cout << parser.getArg () << std::endl;

  std::cout << arg1 << std::endl;
  std::cout << arg2 << std::endl;
  std::cout << arg3 << std::endl;
  return 0;
}
