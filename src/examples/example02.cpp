#include <iostream>
#include <configuration/selection/proportionate/ProportionateSelectionConfiguration.h>
#include <configuration/crossover/singlepoint/mode/FixedMode.h>
#include <configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h>
#include <configuration/mutation/MutationConfiguration.h>
#include <configuration/Configuration.h>
#include <Population.h>
#include "vector"


double fitness_function(const std::vector<char *> *genes) {
    for (int i = 0; i < genes->size(); i++) {
        auto count = std::count(genes->begin(), genes->end(), genes->at(i));
        if (count > 1) {
            return -1L;
        }
    }

    double score = 0;

    if (*genes->at(0) + 1 == *genes->at(1)) {
        score += 1.0;
    }

    for (int i = 1; i < genes->size() - 1; i++) {
        if (*genes->at(i) - 1 == *genes->at(i - 1)) {
            score += 0.5;
        }

        if (*genes->at(i) + 1 == *genes->at(i + 1)) {
            score += 0.5;
        }
    }

    if (*genes->at(genes->size() - 1) == *genes->at(genes->size() - 2) + 1) {
        score += 1.0;
    }

    return score;
}

std::string to_string(const char *v) {
    return std::string(1, *v);
}

int main() {
    auto allele_values = const_cast<std::vector<char *> *>(
            new std::vector<char *>({
                                            new char('A'), new char('B'),
                                            new char('C'), new char('D'),
                                            new char('E'), new char('F'),
                                            new char('G'), new char('H'),
                                            new char('I'), new char('J'),
                                    }));

    auto config = const_cast<Configuration<char> *>(
            new Configuration<char>(fitness_function,
                                    allele_values,
                                    50,
                                    10,
                                    new ProportionateSelectionConfiguration(2),
                                    new SinglePointCrossoverConfiguration(
                                            new FixedMode()),
                                    new MutationConfiguration(0.05),
                                    to_string));

    auto population = new Population<char>(config);

    population->populate_next_generations(50);

    auto best_results = population->get_best();

    std::cout << best_results->at(0)->to_string() << ": " << best_results->at(0)->get_fitness() << std::endl;

    delete best_results;

    delete config;
    delete population;

    std::for_each(allele_values->begin(), allele_values->end(), [](const char *i) { delete i; });
    delete allele_values;

    return 0;
}
