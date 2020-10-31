//
// Created by Christopher Krafft on 05.10.20.
//

#ifndef GENETICALGORITHM_FIXEDMODE_H
#define GENETICALGORITHM_FIXEDMODE_H

#include "AbstractSinglePointCrossoverConfigurationMode.h"

/**
 * Fixed mode configuration for single point crossover method
 */
class FixedMode : public AbstractSinglePointCrossoverConfigurationMode {
public:
    /**
     * Initialize fixed mode configuration
     * @param crossover_factor Crossover proportion for first chromosome, i.e. 0.5 == 50% of each chromosome
     */
    explicit FixedMode(const float &crossover_factor = 0.5);

    /**
     * Get configuration crossover factor
     * @return Crossover factor
     */
    [[nodiscard]] float get_crossover_factor() const;

    ~FixedMode() override;
private:
    float crossover_factor;
};


#endif //GENETICALGORITHM_FIXEDMODE_H
