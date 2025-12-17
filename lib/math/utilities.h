#ifndef UTILITIES_H
#define UTILITIES_H

#include <random>
#include <cmath>
#include <cstdlib>
#include <iostream>
#define  infinity INFINITY
#define PI 3.1415
inline double random_double() {
    static thread_local std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    static thread_local std::mt19937 generator;
    return distribution(generator);
}
inline double random_double_range(double a,double b)
{
    return a+(random_double()+1.0)*.5*(b-a);
}
inline double degtorad(double deg)
{
return deg/180*PI;
}
#endif
