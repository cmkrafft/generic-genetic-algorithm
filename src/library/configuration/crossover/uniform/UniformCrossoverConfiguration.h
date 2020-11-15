//
// Created by Christopher Krafft on 04.10.20.
//

#ifndef GENETICALGORITHM_UNIFORMCROSSOVERCONFIGURATION_H
#define GENETICALGORITHM_UNIFORMCROSSOVERCONFIGURATION_H


#include "../AbstractCrossoverConfiguration.h"

/**
 * Uniform crossover configuration
 * Using uniform crossover, alternately one segment of each chromosome will be inherited.
 */
class UniformCrossoverConfiguration : public AbstractCrossoverConfiguration {
public:
    ~UniformCrossoverConfiguration() override;
};


#endif //GENETICALGORITHM_UNIFORMCROSSOVERCONFIGURATION_H
