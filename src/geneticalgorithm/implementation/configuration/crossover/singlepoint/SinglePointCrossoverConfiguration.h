//
// Created by Christopher Krafft on 04.10.20.
//

#ifndef GENETICALGORITHM_SINGLEPOINTCROSSOVERCONFIGURATION_H
#define GENETICALGORITHM_SINGLEPOINTCROSSOVERCONFIGURATION_H

#include "../AbstractCrossoverConfiguration.h"
#include "mode/AbstractSinglePointCrossoverConfigurationMode.h"

enum SinglePointCrossoverMode {
    FIXED,
    RANDOM
};

/**
 * Configuration for single point crossover-method
 */
class SinglePointCrossoverConfiguration : public AbstractCrossoverConfiguration {
public:
    /**
     * Initialize configuration for single point crossover-method
     * @param abstract_crossover_configuration Configuration object for single point crossover-method
     */
    explicit SinglePointCrossoverConfiguration(
            AbstractSinglePointCrossoverConfigurationMode *abstract_crossover_configuration);

    /**
     * Get configured single point crossover-mode
     * @return Single point crossover-mode
     */
    [[nodiscard]] SinglePointCrossoverMode get_mode() const;

    /**
     * Get single point crossover configuration
     * @return Single point crossover configuration
     */
    [[nodiscard]] AbstractSinglePointCrossoverConfigurationMode *get_single_point_crossover_configuration() const;

    ~SinglePointCrossoverConfiguration() override;

private:
    SinglePointCrossoverMode single_point_crossover_mode;

    AbstractSinglePointCrossoverConfigurationMode *abstract_single_point_crossover_configuration_mode;
};


#endif //GENETICALGORITHM_SINGLEPOINTCROSSOVERCONFIGURATION_H
