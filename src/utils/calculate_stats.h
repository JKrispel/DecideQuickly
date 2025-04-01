#pragma once
#include <string>

// Calculates average execution time from multiple log files for a given level
void calculateLevelAverage(const std::string& levelNames, int minFiles = 3);