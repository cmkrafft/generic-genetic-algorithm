//
// Created by Christopher Krafft on 05.10.20.
//

#ifndef GENETICALGORITHM_RANDOMMODE_H
#define GENETICALGORITHM_RANDOMMODE_H

#include "AbstractSinglePointCrossoverConfigurationMode.h"

/**
 * Random mode configuration for single point crossover method
 * Using random mode, the split will be performed at a random index.
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
