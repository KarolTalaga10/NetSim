// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#ifndef NETSIM_HELPERS_HPP
#define NETSIM_HELPERS_HPP

#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>
#include <functional>
#include "types.hpp"

//double get_random();
double your_num();

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;

#endif //NETSIM_HELPERS_HPP
