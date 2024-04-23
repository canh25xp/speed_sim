#include <CLI/CLI.hpp>
#include <iostream>

using namespace std;

#define GET(...) add_option(__VA_ARGS__)
#define HAS(...) add_flag(__VA_ARGS__)

int num_sensors = 0;
int sampling = 0;
int interval = 0;

int main(int argc, char **argv) {
  CLI::App parser{"Speed sensor simulation and data analaysis"};
  argv = parser.ensure_utf8(argv);

  parser.GET("-n", num_sensors, "model file path");
  parser.GET("-st", sampling, "file or folder or 0(webcam)");
  parser.GET("-si", interval, "data file path");

  CLI11_PARSE(parser, argc, argv);

  cout << num_sensors << endl;
  cout << sampling << endl;
  cout << interval << endl;

  return 0;
}
