//
// Created by Christopher Krafft on 05.10.20.
//

#include "FixedMode.h"

FixedMode::FixedMode(const float &crossover_factor) {
    this->crossover_factor = crossover_factor;
}

float FixedMode::get_crossover_factor() const {
    return this->crossover_factor;
}

FixedMode::~FixedMode() = default;
