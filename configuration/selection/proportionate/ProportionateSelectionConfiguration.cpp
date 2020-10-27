//
// Created by Christopher Krafft on 03.10.20.
//

#include "ProportionateSelectionConfiguration.h"

ProportionateSelectionConfiguration::ProportionateSelectionConfiguration(const long &n_contestants)
        : AbstractSelectionConfiguration() {
    this->n_contestants = n_contestants;
}

long ProportionateSelectionConfiguration::get_n_contestants() const {
    return this->n_contestants;
}

ProportionateSelectionConfiguration::~ProportionateSelectionConfiguration() = default;
