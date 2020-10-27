//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_PROPORTIONATESELECTIONCONFIGURATION_H
#define GENETICALGORITHM_PROPORTIONATESELECTIONCONFIGURATION_H


#include "../AbstractSelectionConfiguration.h"

class ProportionateSelectionConfiguration : public AbstractSelectionConfiguration {
public:
    explicit ProportionateSelectionConfiguration(const long &n_contestants = 2);

    [[nodiscard]] long get_n_contestants() const;

    ~ProportionateSelectionConfiguration() override;

private:
    long n_contestants;
};


#endif //GENETICALGORITHM_PROPORTIONATESELECTIONCONFIGURATION_H
