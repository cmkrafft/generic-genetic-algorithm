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


double fitness_function(const std::vector<int *> *gene) {
    double weight = (*gene->at(0) * 20)
                    + (*gene->at(1) * 5)
                    + (*gene->at(2) * 13)
                    + (*gene->at(3) * 9)
                    + (*gene->at(4) * 11)
                    + (*gene->at(5) * 6)
                    + (*gene->at(6) * 13)
                    + (*gene->at(7) + 17)
                    + (*gene->at(8) + 3)
                    + (*gene->at(9) + 7);

    if (weight > 40.0) {
        return 0.0;
    }

    return (*gene->at(0) * 5)
           + (*gene->at(1) * 2)
           + (*gene->at(2) * 0.5)
           + (*gene->at(3) * 3)
           + (*gene->at(4) * 2.5)
           + (*gene->at(5) * 0.75)
           + (*gene->at(6) * 1.3)
           + (*gene->at(7) + 2.2)
           + (*gene->at(8) + 1.8)
           + (*gene->at(9) + 1.5);
}

std::string to_string(const int *v) {
    return std::to_string(*v);
}

int main() {
    auto set = const_cast<std::vector<int *> *>(new std::vector<int *>({
                                                                               /*new char('A'), new char('B'),
                                                                               new char('C'), new char('D'),
                                                                               new char('E'), new char('F'),
                                                                               new char('G'), new char('H'),
                                                                               new char('I'), new char('J')*/

                                                                               new int(0), new int(1)
/*                                                                                 , new int(2),
                                                                                 new int(3), new int(4), new int(5),
                                                                                 new int(6), new int(7), new int(8),
                                                                                 new int(9)*/
                                                                       }));
    auto s = new TournamentSelectionConfiguration(2);
    auto s2 = new ProportionateSelectionConfiguration(2);

    auto cm = new FixedMode();
    //auto cm2 = new RandomMode();

    auto c = new SinglePointCrossoverConfiguration(cm);
    auto c2 = new UniformCrossoverConfiguration();

    auto m = new MutationConfiguration(0.05);

    auto avg_scores = new std::vector<double>();

    auto config = const_cast<Configuration<int> *>(new Configuration<int>(fitness_function, set, 100, 10, s2, c2, m,
                                                                          to_string));

    auto population = new Population<int>(config);

    avg_scores->push_back(population->get_avg_score());

    const unsigned int n_iterations = 100;

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


    delete avg_scores;

    delete config;
    delete population;

    delete m;
    delete s;
    delete s2;
    delete c;
    delete c2;

    std::for_each(set->begin(), set->end(), [](const int *i) { delete i; });
    delete set;

    return 0;
}
