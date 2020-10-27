//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_CONFIGURATION_H
#define GENETICALGORITHM_CONFIGURATION_H

#include "selection/AbstractSelectionConfiguration.h"
#include "crossover/AbstractCrossoverConfiguration.h"
#include "selection/tournament/TournamentSelectionConfiguration.h"
#include "selection/proportionate/ProportionateSelectionConfiguration.h"
#include "crossover/singlepoint/SinglePointCrossoverConfiguration.h"
#include "crossover/uniform/UniformCrossoverConfiguration.h"
#include "mutation/MutationConfiguration.h"

enum Selection {
    TOURNAMENT_SELECTION,
    PROPORTIONATE_SELECTION,
};

enum Crossover {
    SINGLEPOINT_CROSSOVER,
    UNIFORM_CROSSOVER,
};

template<typename T>
class Configuration {

public:
    Configuration(double (*fitness_function)(const std::vector<T *> *),
                  const std::vector<T *> *possible_values,
                  unsigned long n_population,
                  unsigned long n_chromosome,
                  const AbstractSelectionConfiguration *abstract_selection_configuration,
                  const AbstractCrossoverConfiguration *abstract_crossover_configuration,
                  const MutationConfiguration *mutation_configuration,
                  std::string (*to_string)(const T *)) {
        this->n_chromosome = n_chromosome;
        this->n_population = n_population;
        std::cout << "Initialized Population Configuration:" << std::endl;
        std::cout << "Selection:\t";

        if (dynamic_cast<const TournamentSelectionConfiguration *>(abstract_selection_configuration)) {
            std::cout << "Tournament" << std::endl;
            this->selection = TOURNAMENT_SELECTION;
        } else if (dynamic_cast<const ProportionateSelectionConfiguration *>(abstract_selection_configuration)) {
            std::cout << "Proportionate" << std::endl;
            this->selection = PROPORTIONATE_SELECTION;
        } else {
            throw std::logic_error("No valid selection configuration provided.");
        }

        std::cout << "Crossover:\t";

        if (dynamic_cast<const SinglePointCrossoverConfiguration *>(abstract_crossover_configuration)) {
            std::cout << "Single Point" << std::endl;
            this->crossover = SINGLEPOINT_CROSSOVER;

            std::cout << "- Mode:\t\t"
                      << (((SinglePointCrossoverConfiguration *) abstract_crossover_configuration)->get_mode() == FIXED
                          ? "Fixed" : "Random") << std::endl;
        } else if (dynamic_cast<const UniformCrossoverConfiguration *>(abstract_crossover_configuration)) {
            std::cout << "Uniform" << std::endl;
            this->crossover = UNIFORM_CROSSOVER;
        } else {
            throw std::logic_error("No valid crossover configuration provided.");
        }

        this->selection_configuration = abstract_selection_configuration;
        this->crossover_configuration = abstract_crossover_configuration;
        this->mutation_configuration = mutation_configuration;

        this->fitness_function = fitness_function;
        this->possible_values = possible_values;
        this->to_string = to_string;
    }

    [[nodiscard]] Selection get_selection_type() const {
        return this->selection;
    }

    [[nodiscard]] Crossover get_crossover_type() const {
        return this->crossover;
    }

    [[nodiscard]] const AbstractSelectionConfiguration *get_selection_configuration() const {
        return this->selection_configuration;
    }

    [[nodiscard]] const AbstractCrossoverConfiguration *get_crossover_configuration() const {
        return this->crossover_configuration;
    }

    [[nodiscard]] const MutationConfiguration *get_mutation_configuration() const {
        return this->mutation_configuration;
    }

    const std::vector<T *> *get_possible_values() const {
        return this->possible_values;
    }

    double (*fitness_function)(const std::vector<T *> *);

    std::string (*to_string)(const T *v);

    [[nodiscard]] unsigned long get_population_size() const {
        return this->n_population;
    }

    [[nodiscard]] unsigned long get_chromosome_size() const {
        return this->n_chromosome;
    }

private:
    Selection selection;
    Crossover crossover;

    unsigned long n_population;
    unsigned long n_chromosome;

    const AbstractSelectionConfiguration *selection_configuration{};
    const AbstractCrossoverConfiguration *crossover_configuration{};

    const MutationConfiguration *mutation_configuration{};

    const std::vector<T *> *possible_values;
};


#endif //GENETICALGORITHM_CONFIGURATION_H
