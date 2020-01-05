// Karol Talaga 302929, Mateusz Bahyrycz 284336, Zbigniew Żeglecki 302947

#include "helpers.hpp"

std::random_device rd;
std::mt19937 rng(rd());

double get_random() {
    return std::generate_canonical<double, 10>(rng);
}

double your_num() {
    return 0.2;
}