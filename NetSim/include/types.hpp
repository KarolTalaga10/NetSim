// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP

#include <cstdint>
#include <deque>
#include <functional>
//#include "package.hpp"

using ElementID = uint64_t;
using size_t = std::size_t;
using Time = uint64_t;
using TimeOffset = uint64_t;
using ProbabilityGenerator = std::function<double(void)>;
#endif //NETSIM_TYPES_HPP
