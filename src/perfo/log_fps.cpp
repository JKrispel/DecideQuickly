#include "perfo/log_fps.h"
#include "core/log_state.h"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

static float timeAccumulator = 0.0f;

void logFpsFrame(const std::string& levelName) {
    const int maxSamples = 90;
    std::string folderPath = "logs/" + levelName + "_fps";
    std::string indexFilePath = folderPath + "/number_of_files.txt";

    // Ensure folder exists
    fs::create_directories(folderPath);

    // Init or reset session
    if (currentLogFileIndex == -1 || levelName != currentLoggingLevel) {
        currentLoggingLevel = levelName;

        std::ifstream indexIn(indexFilePath);
        currentLogFileIndex = 0;
        if (indexIn.is_open()) {
            indexIn >> currentLogFileIndex;
            indexIn.close();
        }
    }

    if (loggingFinishedForSession) return;

    float deltaTime = GetFrameTime();
    timeAccumulator += deltaTime;

    if (timeAccumulator < 1.0f) return;

    timeAccumulator -= 1.0f;
    int fps = GetFPS();

    std::string logFilePath = folderPath + "/fps_" + std::to_string(currentLogFileIndex) + ".csv";

    std::ofstream logFile(logFilePath, std::ios::app);
    if (logFile.is_open()) {
        logFile << fps << "\n";
        currentSampleCount++;
        logFile.close();
    }
    else {
        std::cerr << "Error opening FPS log file: " << logFilePath << std::endl;
        return;
    }

    if (currentSampleCount >= maxSamples) {
        std::cout << "FPS log [" << currentLogFileIndex << "] for level " << levelName << " finished!\n";
        std::ofstream indexOut(indexFilePath, std::ios::trunc);
        if (indexOut.is_open()) {
            indexOut << (currentLogFileIndex + 1);
            indexOut.close();
        }
        loggingFinishedForSession = true;
    }
}
