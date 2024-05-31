#include "csv.hpp"
#include <iostream>
#include <vector>

int main() {
    CSVHandler csvHandler("test.csv");

    // Reading data from the CSV file
    std::vector<std::vector<std::string>> data = csvHandler.readFile();

    // Print the read data
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
