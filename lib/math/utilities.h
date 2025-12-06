#pragma once

#include "vec3.h"
#include <cmath>
#include <random>
#define  infinity INFINITY
#define PI 3.1415
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double_range(double a,double b)
{
    static std::uniform_real_distribution<double> distribution(a, b);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double degtorad(double deg)
{
return deg/180*PI;
}
