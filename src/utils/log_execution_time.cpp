#include "utils/log_execution_time.h"
#include <fstream>
#include <iostream>
#include <chrono>

void logExecutionTime(double execution_time, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << execution_time << "\n";
        file.close();
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}
