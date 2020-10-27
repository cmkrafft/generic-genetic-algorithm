//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_TOURNAMENTSELECTIONCONFIGURATION_H
#define GENETICALGORITHM_TOURNAMENTSELECTIONCONFIGURATION_H


#include "../AbstractSelectionConfiguration.h"

class TournamentSelectionConfiguration : public AbstractSelectionConfiguration {
public:
    explicit TournamentSelectionConfiguration(const long &n_contestants = 2);

    [[nodiscard]] long get_n_contestants() const;

    ~TournamentSelectionConfiguration() override;

private:
    long n_contestants;
};


#endif //GENETICALGORITHM_TOURNAMENTSELECTIONCONFIGURATION_H
