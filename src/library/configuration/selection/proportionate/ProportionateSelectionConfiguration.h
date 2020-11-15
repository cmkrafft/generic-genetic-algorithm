//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_PROPORTIONATESELECTIONCONFIGURATION_H
#define GENETICALGORITHM_PROPORTIONATESELECTIONCONFIGURATION_H

#include "../AbstractSelectionConfiguration.h"

/**
 * Proportionate selection-specific configuration
 */
class ProportionateSelectionConfiguration : public AbstractSelectionConfiguration {
public:
    /**
     * Initialize proportionate selection-specific configuration
     * @param n_contestants Number of contestants to be taken into account at the same time
     */
    explicit ProportionateSelectionConfiguration(const long &n_contestants = 2);

    /**
     * Get contestants to be taken into account at the same time
     */
    [[nodiscard]] long get_n_contestants() const;

    ~ProportionateSelectionConfiguration() override;

private:
    long n_contestants;
};


#endif //GENETICALGORITHM_PROPORTIONATESELECTIONCONFIGURATION_H
