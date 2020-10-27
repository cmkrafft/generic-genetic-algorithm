//
// Created by Christopher Krafft on 04.10.20.
//

#ifndef GENETICALGORITHM_MUTATIONCONFIGURATION_H
#define GENETICALGORITHM_MUTATIONCONFIGURATION_H


class MutationConfiguration {
public:
    explicit MutationConfiguration(const float &mutation_rate = 0.05);

    [[nodiscard]] float get_mutation_rate() const;

private:
    float mutation_rate;
};


#endif //GENETICALGORITHM_MUTATIONCONFIGURATION_H
