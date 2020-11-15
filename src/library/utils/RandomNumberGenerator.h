//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_RANDOMNUMBERGENERATOR_H
#define GENETICALGORITHM_RANDOMNUMBERGENERATOR_H


#include <random>

class RandomNumberGenerator {

public:
    explicit RandomNumberGenerator(const int &seed = 42);

    [[nodiscard]] int get_next(const int &lower_bound, const int &upper_bound) const;

    [[nodiscard]] double get_next(const double &lower_bound, const double &upper_bound) const;

    ~RandomNumberGenerator();

private:
    std::mt19937 *random_engine;
};


#endif //GENETICALGORITHM_RANDOMNUMBERGENERATOR_H
