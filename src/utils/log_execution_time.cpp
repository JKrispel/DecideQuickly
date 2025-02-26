#include "utils/log_execution_time.h"

void log_execution_time(double execution_time) {
    std::ofstream file("frame_times.csv", std::ios::app);
    if (file.is_open()) {
        file << execution_time << "\n";
        file.close();
    }
    else {
        std::cerr << "Error opening CSV file!" << std::endl;
    }
}
