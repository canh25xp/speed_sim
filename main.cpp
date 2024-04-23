#include <CLI/CLI.hpp>
#include <iostream>

using namespace std;

#define GET(...) add_option(__VA_ARGS__)
#define HAS(...) add_flag(__VA_ARGS__)

int num_sensors = 0;
int sampling = 0;
int interval = 0;

int main(int argc, char** argv) {
    CLI::App app{"Speed sensor simulation and data analaysis "};
    argv = app.ensure_utf8(argv);

    app.add_option("-n", num_sensors, "number of sensors");
    app.add_option("-s", sampling, "sampling time");
    app.add_option("-i", interval, "simulation interval");

    CLI11_PARSE(app, argc, argv);
    
    cout << num_sensors << endl;
    cout << sampling << endl;
    cout << interval << endl;

    return 0;
}
