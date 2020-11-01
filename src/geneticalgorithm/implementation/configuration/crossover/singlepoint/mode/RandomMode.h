//
// Created by Christopher Krafft on 05.10.20.
//

#ifndef GENETICALGORITHM_RANDOMMODE_H
#define GENETICALGORITHM_RANDOMMODE_H

#include "AbstractSinglePointCrossoverConfigurationMode.h"

/**
 * Random mode configuration for single point crossover method
 */
class RandomMode : public AbstractSinglePointCrossoverConfigurationMode {
public:
    /**
     * Initialize random mode configuration
     */
    RandomMode();

    ~RandomMode() override;

private:
};


#endif //GENETICALGORITHM_RANDOMMODE_H
