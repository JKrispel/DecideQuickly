#include "utils/log_execution_time.h"
#include "core/log_state.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void logExecutionTime(double execution_time, const std::string& levelName) {
    const int maxSamples = 5400;
    std::string folderPath = "logs/" + levelName + "_times";
    std::string indexFilePath = folderPath + "/number_of_files.txt";

    // Initialize or reset if level changed
    if (currentLogFileIndex == -1 || levelName != currentLoggingLevel) {
        currentLoggingLevel = levelName;

        // Read current file index from file
        std::ifstream indexIn(indexFilePath);
        currentLogFileIndex = 0;
        if (indexIn.is_open()) {
            indexIn >> currentLogFileIndex;
            indexIn.close();
        }
    }

    // Stop if the current session is already complete
    if (loggingFinishedForSession) {
        return;
    }

    // Finalize if max sample count reached
    if (currentSampleCount >= maxSamples) {
        std::cout << "exec time [" << currentLogFileIndex << "] for level " << levelName << " finished!\n";

        // Write updated file index for future runs
        std::ofstream indexOut(indexFilePath, std::ios::trunc);
        if (indexOut.is_open()) {
            indexOut << (currentLogFileIndex + 1);
            indexOut.close();
        }

        loggingFinishedForSession = true;
        return;
    }

    // Log execution time
    std::string logFilePath = folderPath + "/exec_time_" + std::to_string(currentLogFileIndex) + ".csv";
    std::ofstream logFile(logFilePath, std::ios::app);
    if (logFile.is_open()) {
        logFile << execution_time << "\n";
        currentSampleCount++;
        logFile.close();
    }
    else {
        std::cerr << "Error opening file: " << logFilePath << std::endl;
    }
}
