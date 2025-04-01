#include "utils/calculate_stats.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <iomanip>

namespace fs = std::filesystem;

// Split string by semicolon
static std::vector<std::string> splitString(const std::string& input, char delimiter = ';') {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        if (!item.empty()) {
            tokens.push_back(item);
        }
    }
    return tokens;
}

// Load numeric values from a file, skipping and limiting
static std::vector<double> loadValues(const std::string& filepath, int skip = 0, int max = 3600) {
    std::ifstream file(filepath);
    std::vector<double> values;
    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        if (skip > 0) {
            --skip;
            continue;
        }

        std::istringstream iss(line);
        double value;
        if (iss >> value) {
            values.push_back(value);
            if (++count == max) break;
        }
    }
    return values;
}

void calculateLevelAverage(const std::string& levelNames, int minFiles) {
    std::vector<std::string> levels = splitString(levelNames);
    std::string outputPath = "logs/avg_exec.csv";

    for (const std::string& levelName : levels) {
        std::string folderPath = "logs/" + levelName;
        std::string indexFilePath = folderPath + "/number_of_files.txt";

        if (!fs::exists(folderPath)) {
            std::cerr << "No data directory found for level: " << levelName << std::endl;
            continue;
        }

        int totalFiles = 0;
        std::ifstream indexIn(indexFilePath);
        if (indexIn.is_open()) {
            indexIn >> totalFiles;
            indexIn.close();
        }

        if (totalFiles < minFiles) {
            std::cerr << "Not enough CSV logs for level " << levelName
                << " (found " << totalFiles << ", need " << minFiles << ")\n";
            continue;
        }

        double totalSum = 0.0;
        int totalSamples = 0;

        for (int i = 0; i < totalFiles; ++i) {
            std::string path = folderPath + "/exec_time_" + std::to_string(i) + ".csv";
            auto values = loadValues(path, 1800);  // skip first 30 seconds
            if (!values.empty()) {
                totalSum += std::accumulate(values.begin(), values.end(), 0.0);
                totalSamples += static_cast<int>(values.size());
            }
        }

        if (totalSamples > 0) {
            double average = totalSum / totalSamples;
            std::ofstream out(outputPath, std::ios::app);
            out << levelName << "," << std::fixed << std::setprecision(6) << average << "\n";
            std::cout << "Average execution time for level [" << levelName << "]: "
                << std::fixed << std::setprecision(6) << average << " ms" << std::endl;
        }
        else {
            std::cerr << "No valid samples to average for " << levelName << std::endl;
        }
    }
}
