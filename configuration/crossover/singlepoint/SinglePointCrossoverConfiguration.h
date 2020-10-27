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

class SinglePointCrossoverConfiguration : public AbstractCrossoverConfiguration {
public:
    explicit SinglePointCrossoverConfiguration(
            AbstractSinglePointCrossoverConfigurationMode *abstract_crossover_configuration);

    [[nodiscard]] SinglePointCrossoverMode get_mode() const;

    ~SinglePointCrossoverConfiguration() override;

    [[nodiscard]] AbstractSinglePointCrossoverConfigurationMode *get_single_point_crossover_configuration() const;

private:
    SinglePointCrossoverMode single_point_crossover_mode;

    AbstractSinglePointCrossoverConfigurationMode *abstract_single_point_crossover_configuration_mode;
};


#endif //GENETICALGORITHM_SINGLEPOINTCROSSOVERCONFIGURATION_H
