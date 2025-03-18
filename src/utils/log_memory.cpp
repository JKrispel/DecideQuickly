#include "utils/log_memory.h"
#define WIN32_LEAN_AND_MEAN  
#define NOCOMM               
#define NOMINMAX             

#include <windows.h>  
#include <psapi.h>
#include <fstream>
#include <iomanip>

void logMemory(const std::string& filename) {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        double memoryMB = static_cast<double>(pmc.WorkingSetSize) / (1024 * 1024); // Keeps decimal places

        std::ofstream logFile(filename, std::ios::app);
        if (!logFile) return;

        logFile << std::fixed << std::setprecision(2) << memoryMB << "\n"; // Logs with 2 decimal places
        logFile.close();
    }
}
