//
// Created by Christopher Krafft on 03.10.20.
//

#include "TournamentSelectionConfiguration.h"

TournamentSelectionConfiguration::TournamentSelectionConfiguration(const long &n_contestants)
        : AbstractSelectionConfiguration() {
    this->n_contestants = n_contestants;
}

long TournamentSelectionConfiguration::get_n_contestants() const {
    return this->n_contestants;
}

TournamentSelectionConfiguration::~TournamentSelectionConfiguration() = default;
