#include <iostream>
#include <configuration/selection/tournament/TournamentSelectionConfiguration.h>
#include <configuration/crossover/singlepoint/mode/FixedMode.h>
#include <configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h>
#include <configuration/mutation/MutationConfiguration.h>
#include <configuration/Configuration.h>
#include <Population.h>
#include "vector"


double fitness_function(const std::vector<int *> *genes) {
    double weight = (*genes->at(0) * 20)
                    + (*genes->at(1) * 5)
                    + (*genes->at(2) * 13)
                    + (*genes->at(3) * 9)
                    + (*genes->at(4) * 11)
                    + (*genes->at(5) * 6)
                    + (*genes->at(6) * 13)
                    + (*genes->at(7) + 17)
                    + (*genes->at(8) + 3)
                    + (*genes->at(9) + 7);

    if (weight > 40.0) {
        return 0.0;
    }

    return (*genes->at(0) * 5)
           + (*genes->at(1) * 2)
           + (*genes->at(2) * 0.5)
           + (*genes->at(3) * 3)
           + (*genes->at(4) * 2.5)
           + (*genes->at(5) * 0.75)
           + (*genes->at(6) * 1.3)
           + (*genes->at(7) + 2.2)
           + (*genes->at(8) + 1.8)
           + (*genes->at(9) + 1.5);
}

std::string to_string(const int *v) {
    return std::to_string(*v);
}

int main() {
    auto allele_values = const_cast<std::vector<int *> *>(
            new std::vector<int *>({
                                           new int(0),
                                           new int(1)
                                   }));

    auto config = const_cast<Configuration<int> *>(
            new Configuration<int>(fitness_function,
                                   allele_values,
                                   100,
                                   10,
                                   new TournamentSelectionConfiguration(2),
                                   new SinglePointCrossoverConfiguration(
                                           new FixedMode()),
                                   new MutationConfiguration(0.05),
                                   to_string));

    auto population = new Population<int>(config);

    population->populate_next_generations(100);

    auto best_results = population->get_best();

    std::cout << best_results->at(0)->to_string() << ": " << best_results->at(0)->get_fitness() << std::endl;

    delete best_results;

    delete config;
    delete population;

    std::for_each(allele_values->begin(), allele_values->end(), [](const int *i) { delete i; });
    delete allele_values;

    return 0;
}
