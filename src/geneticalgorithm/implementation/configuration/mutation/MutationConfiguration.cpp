//
// Created by Christopher Krafft on 04.10.20.
//

#include "MutationConfiguration.h"

MutationConfiguration::MutationConfiguration(const float &mutation_rate) {
    this->mutation_rate = mutation_rate;
}

float MutationConfiguration::get_mutation_rate() const {
    return this->mutation_rate;
}
