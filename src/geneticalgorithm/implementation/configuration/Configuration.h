//
// Created by Christopher Krafft on 03.10.20.
//

#ifndef GENETICALGORITHM_CONFIGURATION_H
#define GENETICALGORITHM_CONFIGURATION_H

#include "crossover/AbstractCrossoverConfiguration.h"
#include "selection/tournament/TournamentSelectionConfiguration.h"
#include "selection/proportionate/ProportionateSelectionConfiguration.h"
#include "crossover/singlepoint/SinglePointCrossoverConfiguration.h"
#include "crossover/uniform/UniformCrossoverConfiguration.h"
#include "mutation/MutationConfiguration.h"
#include "selection/AbstractSelectionConfiguration.h"

enum Selection {
    TOURNAMENT_SELECTION,
    PROPORTIONATE_SELECTION,
};

enum Crossover {
    SINGLE_POINT_CROSSOVER,
    UNIFORM_CROSSOVER,
};

/**
 * Configuration defining population size, selection and mutation methods, fitness function and more
 * @tparam T Type of chromosome's allele
 */
template<typename T>
class Configuration {

public:
    /**
     * Initialize a configuration object to control the genetic algorithms behaviour
     * @param fitness_function Function pointer to fitness function to be used to determine chromosome's fitness score
     * @param alleles Set of possible allele values
     * @param n_population Population size
     * @param n_chromosome Chromosome size
     * @param abstract_selection_configuration Configuration object for selection method
     * @param abstract_crossover_configuration Configuration object for crossover method
     * @param mutation_configuration Configuration object for mutation method
     * @param to_string Function pointer to to_string function, used to serialize chromosomes
     */
    Configuration(double (*fitness_function)(const std::vector<T *> *),
                  const std::vector<T *> *alleles,
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
            this->crossover = SINGLE_POINT_CROSSOVER;

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
        this->alleles = alleles;
        this->to_string = to_string;
    }

    /**
     * Get the configured selection method type
     * @return Selection type
     */
    [[nodiscard]] Selection get_selection_type() const {
        return this->selection;
    }

    /**
     * Get the configured crossover method type
     * @return Crossover type
     */
    [[nodiscard]] Crossover get_crossover_type() const {
        return this->crossover;
    }

    /**
     * Get configuration for selection method
     * @return Selection configuration
     */
    [[nodiscard]] const AbstractSelectionConfiguration *get_selection_configuration() const {
        return this->selection_configuration;
    }

    /**
     * Get configuration for crossover method
     * @return Crossover configuration
     */
    [[nodiscard]] const AbstractCrossoverConfiguration *get_crossover_configuration() const {
        return this->crossover_configuration;
    }

    /**
     * Get configuration for mutation method
     * @return Mutation configuration
     */
    [[nodiscard]] const MutationConfiguration *get_mutation_configuration() const {
        return this->mutation_configuration;
    }

    /**
     * Get possible values for alleles
     * @return Possible values
     */
    const std::vector<T *> *get_alleles() const {
        return this->alleles;
    }

    /**
     * Function pointer to fitness function
     * @return Score
     */
    double (*fitness_function)(const std::vector<T *> *);

    /**
     * Function pointer to to_string function
     * @param v Value to be serialized
     * @return String representation
     */
    std::string (*to_string)(const T *v);

    /**
     * Get total population size, i.e. number of chromosomes
     * @return Population size
     */
    [[nodiscard]] unsigned long get_population_size() const {
        return this->n_population;
    }

    /**
     * Get defined length of single chromosome
     * @return Chromosome size
     */
    [[nodiscard]] unsigned long get_chromosome_size() const {
        return this->n_chromosome;
    }

private:
    Selection selection{};
    Crossover crossover{};

    unsigned long n_population{};
    unsigned long n_chromosome{};

    const AbstractSelectionConfiguration *selection_configuration{};
    const AbstractCrossoverConfiguration *crossover_configuration{};

    const MutationConfiguration *mutation_configuration{};

    const std::vector<T *> *alleles;
};


#endif //GENETICALGORITHM_CONFIGURATION_H
