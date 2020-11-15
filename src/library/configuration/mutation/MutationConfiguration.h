//
// Created by Christopher Krafft on 04.10.20.
//

#ifndef GENETICALGORITHM_MUTATIONCONFIGURATION_H
#define GENETICALGORITHM_MUTATIONCONFIGURATION_H

/**
 * Mutation configuration
 */
class MutationConfiguration {
public:
    /**
     * Initialize mutation configuration
     * @param mutation_rate Probability of mutation, e.g. 0.05 == 5%
     */
    explicit MutationConfiguration(const float &mutation_rate = 0.05);

    /**
     * Get configured mutation rate
     * @return Mutation rate
     */
    [[nodiscard]] float get_mutation_rate() const;

private:
    float mutation_rate;
};


#endif //GENETICALGORITHM_MUTATIONCONFIGURATION_H
