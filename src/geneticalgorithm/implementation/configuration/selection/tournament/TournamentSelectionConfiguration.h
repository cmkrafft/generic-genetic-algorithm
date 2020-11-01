//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_TOURNAMENTSELECTIONCONFIGURATION_H
#define GENETICALGORITHM_TOURNAMENTSELECTIONCONFIGURATION_H


#include "../AbstractSelectionConfiguration.h"

/**
 * Tournament selection-specific configuration
 */
class TournamentSelectionConfiguration : public AbstractSelectionConfiguration {
public:
    /**
     * Initialize tournament selection-specific configuration
     * @param n_contestants Number of contestants to be taken into account at the same time
     */
    explicit TournamentSelectionConfiguration(const long &n_contestants = 2);

    /**
     * Get configured number of contestants
     * @return Number of contestants
     */
    [[nodiscard]] long get_n_contestants() const;

    ~TournamentSelectionConfiguration() override;

private:
    long n_contestants;
};


#endif //GENETICALGORITHM_TOURNAMENTSELECTIONCONFIGURATION_H
