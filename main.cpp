#include <iostream>
#include "cli.hpp"

using namespace std;

int num_sensors = 0;
int sampling = 0;
int interval = 0;

int main(int argc, char** argv) {
    Parser parser(argc, argv);
    num_sensors = parser.get("-n", 0);
    sampling = parser.get("-st", 0);
    interval = parser.get("-si", 0);
    cout << num_sensors << endl;
    cout << sampling << endl;
    cout << interval << endl;
    return 0;
}
