#include <iostream>
#include <configuration/selection/tournament/TournamentSelectionConfiguration.h>
#include <configuration/selection/proportionate/ProportionateSelectionConfiguration.h>
#include <configuration/crossover/singlepoint/mode/FixedMode.h>
#include <configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h>
#include <configuration/crossover/uniform/UniformCrossoverConfiguration.h>
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
    auto set = const_cast<std::vector<char *> *>(new std::vector<char *>({
                                                                                 new char('A'), new char('B'),
                                                                                 new char('C'), new char('D'),
                                                                                 new char('E'), new char('F'),
                                                                                 new char('G'), new char('H'),
                                                                                 new char('I'), new char('J'),
                                                                         }));


    auto s = new TournamentSelectionConfiguration(2);
    auto s2 = new ProportionateSelectionConfiguration(2);

    auto cm = new FixedMode();
    //auto cm2 = new RandomMode();

    auto c = new SinglePointCrossoverConfiguration(cm);
    auto c2 = new UniformCrossoverConfiguration();

    auto m = new MutationConfiguration(0.00);

    auto avg_scores = new std::vector<double>();

    auto config = const_cast<Configuration<char> *>(new Configuration<char>(fitness_function, set, 60, 10, s2, c, m,
                                                                            to_string));

    auto population = new Population<char>(config);

    avg_scores->push_back(population->get_avg_score());

    const unsigned int n_iterations = 50;

    for (int i = 0; i < n_iterations; i++) {
        population->populate_next_generation();

        avg_scores->push_back(population->get_avg_score());
    }

    auto best_results = population->get_best();

    std::cout << best_results->at(0)->to_string() << std::endl;

    delete best_results;

    std::cout << "AVGs" << std::endl;

    for (int i = 0; i < n_iterations; i++) {
        std::cout << i << ": " << avg_scores->at(i) << std::endl;
    }

    auto best = population->get_best();

    std::for_each(best->begin(), best->end(), [](Chromosome<char> * v) {
        v->print();
    });


    delete avg_scores;

    delete config;
    delete population;

    delete m;
    delete s;
    delete s2;
    delete c;
    delete c2;

    std::for_each(set->begin(), set->end(), [](const char *i) { delete i; });
    delete set;

    return 0;
}
