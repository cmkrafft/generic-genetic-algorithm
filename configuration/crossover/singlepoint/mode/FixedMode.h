//
// Created by Christopher Krafft on 05.10.20.
//

#ifndef GENETICALGORITHM_FIXEDMODE_H
#define GENETICALGORITHM_FIXEDMODE_H

#include "AbstractSinglePointCrossoverConfigurationMode.h"

class FixedMode : public AbstractSinglePointCrossoverConfigurationMode {
public:
    explicit FixedMode(const float &crossover_factor = 0.5);

    [[nodiscard]] float get_crossover_factor() const;

    ~FixedMode() override;
private:
    float crossover_factor;
};


#endif //GENETICALGORITHM_FIXEDMODE_H
