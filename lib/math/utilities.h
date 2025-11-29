#pragma once

#include <cmath>
#include <random>
#define  infinity INFINITY

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

