//
// Created by Christopher Krafft on 04.10.20.
//

#include "SinglePointCrossoverConfiguration.h"
#include "mode/FixedMode.h"
#include "mode/RandomMode.h"
#include <iostream>

SinglePointCrossoverConfiguration::SinglePointCrossoverConfiguration(
        AbstractSinglePointCrossoverConfigurationMode *abstract_single_point_crossover_configuration) {

    if (dynamic_cast<const FixedMode *>(abstract_single_point_crossover_configuration)) {
        this->single_point_crossover_mode = FIXED;
    } else if (dynamic_cast<const RandomMode *>(abstract_single_point_crossover_configuration)) {
        this->single_point_crossover_mode = RANDOM;
    }

    this->abstract_single_point_crossover_configuration_mode = abstract_single_point_crossover_configuration;
}

SinglePointCrossoverMode SinglePointCrossoverConfiguration::get_mode() const {
    return this->single_point_crossover_mode;
}

SinglePointCrossoverConfiguration::~SinglePointCrossoverConfiguration() {
    delete this->abstract_single_point_crossover_configuration_mode;
}

AbstractSinglePointCrossoverConfigurationMode *SinglePointCrossoverConfiguration::get_single_point_crossover_configuration() const {
    return this->abstract_single_point_crossover_configuration_mode;
}