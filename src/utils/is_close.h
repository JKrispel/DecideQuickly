#pragma once
#include <cmath>

inline bool isClose(float a, float b, float epsilon = 5.0f) {
    return std::fabs(a - b) < epsilon;
}
