#pragma once
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

void log_execution_time(double execution_time, const std::string& filename = "frame_times.csv");