//
// Created by Christopher Krafft on 05.10.20.
//

#ifndef GENETICALGORITHM_RANDOMMODE_H
#define GENETICALGORITHM_RANDOMMODE_H

#include "AbstractSinglePointCrossoverConfigurationMode.h"

class RandomMode : public AbstractSinglePointCrossoverConfigurationMode {
public:
    RandomMode();

    ~RandomMode() override;

private:
};


#endif //GENETICALGORITHM_RANDOMMODE_H
