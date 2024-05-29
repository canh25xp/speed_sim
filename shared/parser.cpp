#include "parser.hpp"
#include <algorithm>
#include <stdexcept>

Parser::Parser (int &argc, char **argv)
{
  bool expectValue = false;
  for (int i = 1; i < argc; ++i)
    {
      std::string token = std::string (argv[i]);
      if (token.find ("-") == 0)
        {
          tokens.push_back (token);
          expectValue = true;
        }
      else if (expectValue)
        {
          tokens.push_back (token);
          expectValue = false;
        }
      else
        {
          positionalArguments.push_back (token);
          positionalArgCount++;
        }
    }
}

bool
Parser::has (const std::string &name)
{
  auto itr = std::find (this->tokens.begin (), this->tokens.end (), name);
  if (itr != this->tokens.end ())
    {
      if ((itr + 1) != this->tokens.end () && (*(itr + 1)).find ("-") != 0)
        {
          arguments.push_back (Argument (name, "true"));
          argCount++;
          return true;
        }
      else
        {
          arguments.push_back (Argument (name, "false"));
          return false;
        }
    }

  arguments.push_back (Argument (name, "false"));
  return false;
}

const std::string
Parser::get (const std::string &name, const std::string &def)
{
  std::string ret = def;

  auto itr = std::find (this->tokens.begin (), this->tokens.end (), name);
  if (itr != this->tokens.end ())
    {
      if ((itr + 1) != this->tokens.end () && (*(itr + 1)).find ("-") != 0)
        {
          // Argument found with a value
          argCount++;
          ret = *(itr + 1);
        }
      else
        {
          // Argument found without a value
          throw std::invalid_argument ("Missing value for argument: " + name);
        }
    }

  arguments.push_back (Argument (name, ret));
  return ret;
}

const int
Parser::get (const std::string &name, const int &def)
{
  return std::stoi (get (name, std::to_string (def)));
}

const float
Parser::get (const std::string &name, const float &def)
{
  return std::stof (get (name, std::to_string (def)));
}

const std::string
Parser::getPositional (int index, const std::string &def)
{
  if (index < positionalArguments.size ())
    {
      return positionalArguments[index];
    }
  return def;
}

int
Parser::getPositionalArgCount ()
{
  return positionalArgCount;
}

int
Parser::getArgCount ()
{
  return argCount;
}

std::string
Parser::getArg ()
{
  std::string buffer;

  for (auto &arg : arguments)
    {
      buffer += arg.name;
      buffer += " = ";
      buffer += arg.value;
      buffer += "\n";
    }

  return buffer;
}

Argument::Argument () {}

Argument::Argument (const std::string &name, const std::string &value)
{
  this->name = name;
  this->value = value;
}
