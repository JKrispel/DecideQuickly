#pragma once
#include <string>

inline int currentSampleCount = 0;
inline bool loggingFinishedForSession = false;

inline int currentLogFileIndex = -1;
inline std::string currentLoggingLevel = "";

inline void resetLoggingSession() {
    currentSampleCount = 0;
    loggingFinishedForSession = false;
    currentLogFileIndex = -1;
    currentLoggingLevel = "";
}
