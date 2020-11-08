//
// Created by Christopher Krafft on 02.10.20.
//

#ifndef GENETICALGORITHM_POPULATION_H
#define GENETICALGORITHM_POPULATION_H

#include <numeric>
#include <vector>
#include <iostream>
#include "Chromosome.h"
#include "utils/RandomNumberGenerator.h"
#include "configuration/Configuration.h"
#include "configuration/selection/tournament/TournamentSelectionConfiguration.h"
#include "configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h"
#include "configuration/crossover/singlepoint/mode/FixedMode.h"

/**
 * Generic representation of a population consisting of multiple Chromosomes
 * @tparam T Type of a chromosome's allele
 */
template<typename T>
class Population {

public:
    /**
     * Create new instance of population of chromosomes based on provided configuration
     * @param configuration Population configuration
     */
    explicit Population(const Configuration<T> *configuration) {
        // TODO: Pass Seed!
        RandomNumberGenerator initial_rnd = RandomNumberGenerator();

        this->configuration = configuration;

        this->random_number_generators = new std::vector<RandomNumberGenerator *>(configuration->get_population_size());

#ifdef USE_PARALLELISM
#pragma omp for
#endif
        for (int i = 0; i < configuration->get_population_size(); i++) {
            random_number_generators->at(i) = new RandomNumberGenerator(
                    initial_rnd.get_next(0, this->configuration->get_population_size()));
        }

        this->current_scores = nullptr;

        this->chromosomes = new std::vector<Chromosome<T> *>(this->configuration->get_population_size());

        auto possible_values = configuration->get_alleles();

#ifdef USE_PARALLELISM
#pragma omp for
#endif
        for (int i = 0; i < this->configuration->get_population_size(); i++) {
            RandomNumberGenerator *rnd = this->random_number_generators->at(i);

            std::vector<T *> *tmp_v;

            double tmp_fitness;

            do {
                tmp_v = new std::vector<T *>(this->configuration->get_chromosome_size());

                for (int j = 0; j < this->configuration->get_chromosome_size(); j++) {
                    tmp_v->at(j) = (possible_values->at(rnd->get_next(0, possible_values->size() - 1)));
                }

                tmp_fitness = (this->configuration->fitness_function)(tmp_v);

                if (tmp_fitness <= 0.0) {
                    delete tmp_v;
                }
            } while (tmp_fitness <= 0.0);

            if (tmp_fitness == -1.0) {
                std::cout << "FOO" << std::endl;
            }

            this->chromosomes->at(i) = new Chromosome<T>(
                    const_cast<std::vector<T *> * > (tmp_v),
                    this->configuration->fitness_function,
                    this->configuration->to_string);
        }

        this->current_scores = this->get_scores(this->chromosomes);
    }

    /**
     * Start calculation of next generation
     */
    void populate_next_generation() {
        auto next_generation = new std::vector<Chromosome<T> *>(this->chromosomes->size());

#ifdef USE_PARALLELISM
#pragma omp for
#endif
        for (int i = 0; i < next_generation->size(); i++) {
            auto selected_chromosomes = perform_selection(this->random_number_generators->at(i));

            next_generation->at(i) = this->perform_crossover(selected_chromosomes->first,
                                                             selected_chromosomes->second,
                                                             this->random_number_generators->at(i));

            delete selected_chromosomes;
        }

        std::for_each(this->chromosomes->begin(), this->chromosomes->end(),
                      [](const Chromosome<T> *c) { delete c; });

        delete this->chromosomes;

        this->chromosomes = next_generation;

        std::for_each(this->current_scores->begin(), this->current_scores->end(),
                      [](const std::pair<Chromosome<T> *, double> *n) { delete n; });
        delete this->current_scores;

        this->current_scores = this->get_scores(this->chromosomes);

        this->current_generation++;
    }

    /**
     * Start calculation of next n_generations generations
     * @param n_generations Number of generations to be calculation
     */
    void populate_next_generations(const unsigned long &n_generations) {
        for (unsigned long i = 0; i < n_generations; i++) {
            this->populate_next_generation();
        }
    }

    /**
     * Get all chromosomes and their current scores based on their fitness functions
     * @return Current generation of chromosomes and scores
     */
    const std::vector<std::pair<Chromosome<T> *, double> *> *get_scores() const {
        return const_cast<std::vector<std::pair<Chromosome<T> *, double> *> *>(this->get_scores(this->chromosomes));
    }

    /**
     * Get chromosomes with highest score from current generation
     * @return Best fits
     */
    const std::vector<Chromosome<T> *> *get_best() const {
        auto max_fitness = this->current_scores->at(
                std::distance(this->current_scores->begin(),
                              std::max_element(this->current_scores->begin(),
                                               this->current_scores->end(),
                                               [](const std::pair<Chromosome<T> *, double> *l,
                                                  const std::pair<Chromosome<T> *, double> *r) {
                                                   return l->second < r->second;
                                               })))->second;

        auto result_pairs = new std::vector<std::pair<Chromosome<T> *, double> *>();

        std::copy_if(this->current_scores->begin(),
                     this->current_scores->end(),
                     std::back_inserter(*result_pairs),
                     [max_fitness](const std::pair<Chromosome<T> *, double> *p) {
                         return p->second == max_fitness;
                     });

        auto result = new std::vector<Chromosome<T> *>();

        std::for_each(result_pairs->begin(),
                      result_pairs->end(),
                      [result](const std::pair<Chromosome<T> *, double> *p) {
                          result->push_back(p->first);
                      });

        delete result_pairs;

        return const_cast<std::vector<Chromosome<T> *> *>(result);
    }

    /**
     * Get average score of all chromosomes based on their fitness_function
     * @return Average chromosome fitness
     */
    [[nodiscard]] double get_avg_score() const {
        auto scores = new std::vector<double>();

        std::for_each(this->current_scores->begin(), this->current_scores->end(),
                      [&scores](const std::pair<Chromosome<T> *, double> *p) { scores->push_back(p->second); });

        double sum = std::accumulate(scores->begin(), scores->end(), 0.0);

        delete scores;

        return sum / this->chromosomes->size();
    }

    /**
     * Get the number of performed simulations
     * @return Number of performed simulations
     */
    [[nodiscard]] unsigned long get_number_of_performed_simulations() const {
        return const_cast<unsigned long>(this->current_generation);
    }

    /**
     * Get chromosomes of population
     * @return Chromosomes
     */
    std::vector<Chromosome<T> *> *get_chromosomes() const {
        return this->chromosomes;
    }

    /**
     * Print current population's chromosomes using to_string function for serialization
     */
    void print() const {
        std::cout << this->to_string() << std::endl;
    }

    /**
     * Get string representation of population
     * @return String representation
     */
    [[nodiscard]] std::string to_string() const {
        return "["
               + std::accumulate(this->chromosomes->begin(),
                                 this->chromosomes->end(),
                                 std::string{},
                                 [](const std::string &outer_a, const Chromosome<T> *outer_b) {
                                     return outer_a
                                            + (!outer_a.empty()
                                               ? ",\n"
                                               : "")
                                            + (!outer_a.empty()
                                               ? " "
                                               : "")
                                            + outer_b->to_string();
                                 })
               + "]";
    }

    ~Population() {
        std::for_each(this->chromosomes->begin(), this->chromosomes->end(), [](const Chromosome<T> *n) { delete n; });
        delete this->chromosomes;

        std::for_each(this->current_scores->begin(), this->current_scores->end(),
                      [](const std::pair<Chromosome<T> *, double> *n) { delete n; });
        delete this->current_scores;

        std::for_each(this->random_number_generators->begin(), this->random_number_generators->end(),
                      [](const RandomNumberGenerator *n) { delete n; });
        delete this->random_number_generators;
    }

private:
    std::vector<Chromosome<T> *> *chromosomes;
    std::vector<RandomNumberGenerator *> *random_number_generators{};
    const Configuration<T> *configuration;

    unsigned long current_generation{};

    std::vector<std::pair<Chromosome<T> *, double> *> *current_scores;

    /**
     * Get scores for a given set of chromosomes
     * @return Set of chromosomes
     */
    std::vector<std::pair<Chromosome<T> *, double> *> *get_scores(std::vector<Chromosome<T> *> *sample) const {
        auto results = new std::vector<std::pair<Chromosome<T> *, double> *>(sample->size());

#ifdef USE_PARALLELISM
#pragma omp for
#endif
        for (int i = 0; i < sample->size(); i++) {
            results->at(i) = new std::pair(sample->at(i), sample->at(i)->get_fitness());
        }

        return results;
    }

    /**
     * Perform crossover for two chromosomes using specific instance of RandomNumberGenerator
     * @param first First chromosome
     * @pararm second Second chromosome
     * @param rnd Instance of RandomNumberGenerator
     * @return Resulting chromosome
     */
    Chromosome<T> *perform_crossover(Chromosome<T> *first, Chromosome<T> *second, RandomNumberGenerator *rnd) const {
        auto *v = new std::vector<T *>(this->chromosomes->at(0)->get_genes()->size());

        int split_index;

        switch (this->configuration->get_crossover_type()) {
            case (SINGLE_POINT_CROSSOVER): {
                auto conf = (SinglePointCrossoverConfiguration *) this->configuration->get_crossover_configuration();

                switch (conf->get_mode()) {
                    case (RANDOM):
                        split_index = rnd->get_next(0, this->chromosomes->at(0)->get_genes()->size() - 1);

                        break;
                    case (FIXED): {
                        auto fixed_conf = (FixedMode *) conf->get_single_point_crossover_configuration();

                        split_index =
                                fixed_conf->get_crossover_factor() * this->chromosomes->at(0)->get_genes()->size();

                        break;
                    }
                }

                for (int i = 0; i < split_index; i++) {
                    v->at(i) = first->get_genes()->at(i);
                }

                for (int i = split_index; i < this->chromosomes->at(0)->get_genes()->size(); i++) {
                    v->at(i) = second->get_genes()->at(i);
                }

                break;
            }
            case (UNIFORM_CROSSOVER): {
                for (int i = 0; i < this->chromosomes->at(0)->get_genes()->size(); i += 2) {
                    v->at(i) = first->get_genes()->at(i);
                }

                for (int i = 1; i < this->chromosomes->at(0)->get_genes()->size(); i += 2) {
                    v->at(i) = first->get_genes()->at(i);
                }

                break;
            }
        }

        auto mutation = rnd->get_next(0, 99) <
                        this->configuration->get_mutation_configuration()->get_mutation_rate() * 100;

        if (mutation) {
            auto mutation_index = rnd->get_next(0, v->size() - 1);

            v->at(mutation_index) = this->configuration->get_alleles()->at(
                    rnd->get_next(0, this->configuration->get_alleles()->size() - 1));
        }


        auto *result = new Chromosome<T>(
                const_cast<std::vector<T *> * > (v), this->configuration->fitness_function,
                this->configuration->to_string);

        return result;
    }

    /**
     * Perform selection according to configured selection method
     * @param rnd Random number generator to be used
     * @return Pair of selected chromosomes
     */
    std::pair<Chromosome<T> *, Chromosome<T> *> *perform_selection(RandomNumberGenerator *rnd) const {
        auto first = select_chromosome(rnd);
        Chromosome<T> *second;

        do {
            second = select_chromosome(rnd);
        } while (first == second);

        return new std::pair<Chromosome<T> *, Chromosome<T> *>(first, second);
    }

    /**
     * Perform selection method as configured for population
     * @param rnd RandomNumberGenerator to be used for selection methods
     * @return Selected chromosome
     */
    Chromosome<T> *select_chromosome(RandomNumberGenerator *rnd) const {
        switch (this->configuration->get_selection_type()) {
            case (PROPORTIONATE_SELECTION): {
                return this->perform_proportionate_selection(rnd);
            }
            case (TOURNAMENT_SELECTION): {
                return this->perform_tournament_selection(rnd);
            }
            default: {
                return nullptr;
            }
        }
    }

    /**
     * Perform proportionate selection
     * @param rnd RandomNumberGenerator to be used for selection
     * @return Selected chromosome
     */
    Chromosome<T> *perform_proportionate_selection(RandomNumberGenerator *rnd) const {
        auto results = this->current_scores;
        auto chromosomes_with_positive_scores = new std::vector<const std::pair<Chromosome<T> *, double> *>();

        std::for_each(results->begin(), results->end(),
                      [chromosomes_with_positive_scores](const std::pair<Chromosome<T> *, double> *p) {
                          if (p->second > 0.0) {
                              chromosomes_with_positive_scores->push_back(p);
                          }
                      });

        double sum = std::accumulate(chromosomes_with_positive_scores->begin(), chromosomes_with_positive_scores->end(), 0.0, [](double accumulator, const std::pair<Chromosome<T> *, double> *p) {
            return accumulator + p->second;
        });

        auto rnd_share = rnd->get_next(0.0, sum);

        for (int i = 0; i < chromosomes_with_positive_scores->size(); i++) {
            if (chromosomes_with_positive_scores->at(i)->first->get_fitness() > rnd_share) {
                return chromosomes_with_positive_scores->at(i)->first;
            }

            rnd_share -= chromosomes_with_positive_scores->at(i)->first->get_fitness();
        }

        delete chromosomes_with_positive_scores;

        return (Chromosome<T> *) nullptr;
    }

    /**
     * Perform tournament selection
     * @param rnd RandomNumberGenerator to be used for selection
     * @return Selected chromosome
     */
    Chromosome<T> *perform_tournament_selection(RandomNumberGenerator *rnd) const {
        auto tournament_selection_configuration = (TournamentSelectionConfiguration *)
                this->configuration->get_selection_configuration();

        auto contestants = new std::vector<Chromosome<T> *>(
                tournament_selection_configuration->get_n_contestants());
        auto contestant_indexes = new std::vector<int>(
                tournament_selection_configuration->get_n_contestants(), -1);

        for (int j = 0; j < tournament_selection_configuration->get_n_contestants(); j++) {
            int rnd_index;

            do {
                rnd_index = rnd->get_next(0, this->chromosomes->size() - 1);
            } while (std::find(contestant_indexes->begin(), contestant_indexes->end(), rnd_index) !=
                     contestant_indexes->end());

            contestant_indexes->at(j) = rnd_index;
            contestants->at(j) = this->chromosomes->at(rnd_index);
        }

        auto contestants_results = this->get_scores(contestants);

        auto result = std::max_element(contestants_results->begin(), contestants_results->end(),
                                       [](const std::pair<Chromosome<T> *, double> *l,
                                          const std::pair<Chromosome<T> *, double> *r) {
                                           return l->second < r->second;
                                       });

        Chromosome<T> *r = contestants->at(std::distance(contestants_results->begin(), result));

        delete contestants;
        delete contestant_indexes;

        std::for_each(contestants_results->begin(), contestants_results->end(),
                      [](const std::pair<Chromosome<T> *, double> *p) { delete p; });

        delete contestants_results;

        return r;
    }
};


#endif //GENETICALGORITHM_POPULATION_H
