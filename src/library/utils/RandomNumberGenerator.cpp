//
// Created by Christopher Krafft on 03.10.20.
//

#include "RandomNumberGenerator.h"


RandomNumberGenerator::RandomNumberGenerator(const int &seed) {
    this->random_engine = new std::mt19937(seed);
}

int RandomNumberGenerator::get_next(const int &lower_bound, const int &upper_bound) const {
    return std::uniform_int_distribution<int>(lower_bound, upper_bound)(*this->random_engine);
}

double RandomNumberGenerator::get_next(const double &lower_bound, const double &upper_bound) const {
    return std::uniform_real_distribution<double>(lower_bound, upper_bound)(*this->random_engine);
}

RandomNumberGenerator::~RandomNumberGenerator() {
    delete this->random_engine;
}
