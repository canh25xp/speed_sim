#pragma once
#include <string>
#include <vector>

struct Argument
{
  Argument ();

  Argument (const std::string &name, const std::string &value = "");

  std::string name;
  std::string value;
};

class Parser
{
public:
  // Parser constructor
  //
  // @param argc: number of command line arguments
  // @param argv: array of command line arguments
  Parser (int &argc, char **argv);

  // to check if argument exist
  //
  // @param name: argument name, return true if argument exist
  bool has (const std::string &name);

  // get argument by name, if not exist, return default argument
  const std::string get (const std::string &name, const std::string &def = "");

  // get argument by name, if not exist, return default argument
  const int get (const std::string &name, const int &def);

  // get argument by name, if not exist, return default argument
  const float get (const std::string &name, const float &def);

  // Return the number of arguments has passed to program
  int getArgCount ();

  // Get argument string, return a formatted string contains passed arguments
  // and their value
  std::string getArg ();

private:
  std::vector<std::string> tokens;

  std::vector<Argument> arguments;

  int argCount = 0;
};
