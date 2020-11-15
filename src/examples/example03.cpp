#include <iostream>
#include <configuration/selection/tournament/TournamentSelectionConfiguration.h>
#include <configuration/crossover/singlepoint/mode/FixedMode.h>
#include <configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h>
#include <configuration/mutation/MutationConfiguration.h>
#include <configuration/Configuration.h>
#include <Population.h>
#include "vector"
#include "map"


std::map<std::string *, std::map<std::string *, int> *> *distances;


double fitness_function(const std::vector<std::string *> *genes) {
    if (genes->at(0) != genes->at(genes->size() - 1)) {
        return -1L;
    }

    for (int i = 0; i < genes->size() - 2; i++) {
        auto count = std::count(genes->begin(), genes->end() - 1, genes->at(i));
        if (count > 1) {
            return -1L;
        }
    }

    int sum = 0;

    for (int i = 0; i < genes->size() - 2; i++) {
        sum += (*(*distances)[genes->at(i)])[genes->at(i + 1)];
    }

    return 1.0 / sum * 100.0;
}

std::string to_string(const std::string *v) {
    return *v;
}

void fill_distances(std::vector<std::string *> *cities,
                    std::map<std::string *, std::map<std::string *, int> *> *distance_map) {
    for (int i = 0; i < cities->size(); i++) {
        distances->insert(std::make_pair(cities->at(i), new std::map<std::string *, int>()));

        for (int j = 0; j < cities->size(); j++) {
            if (i == j) {
                continue;
            }

            distances->find(cities->at(i))->second->insert(std::make_pair(cities->at(j), -1));
        }
    }

    auto berlin = cities->at(0);
    auto hamburg = cities->at(1);
    auto munich = cities->at(2);
    auto cologne = cities->at(3);
    auto frankfurt = cities->at(4);

    (*(*distances)[berlin])[hamburg] = 284;
    (*(*distances)[berlin])[munich] = 586;
    (*(*distances)[berlin])[cologne] = 584;
    (*(*distances)[berlin])[frankfurt] = 551;

    (*(*distances)[hamburg])[berlin] = 289;
    (*(*distances)[hamburg])[munich] = 777;
    (*(*distances)[hamburg])[cologne] = 432;
    (*(*distances)[hamburg])[frankfurt] = 497;

    (*(*distances)[munich])[berlin] = 584;
    (*(*distances)[munich])[hamburg] = 778;
    (*(*distances)[munich])[cologne] = 574;
    (*(*distances)[munich])[frankfurt] = 392;

    (*(*distances)[cologne])[berlin] = 573;
    (*(*distances)[cologne])[hamburg] = 432;
    (*(*distances)[cologne])[munich] = 575;
    (*(*distances)[cologne])[frankfurt] = 191;

    (*(*distances)[frankfurt])[berlin] = 551;
    (*(*distances)[frankfurt])[hamburg] = 498;
    (*(*distances)[frankfurt])[munich] = 393;
    (*(*distances)[frankfurt])[cologne] = 190;
}

int main() {
    auto berlin = new std::string("Berlin");
    auto hamburg = new std::string("Hamburg");
    auto munich = new std::string("Munich");
    auto cologne = new std::string("Cologne");
    auto frankfurt = new std::string("Frankfurt");

    auto cities = new std::vector<std::string *>();

    cities->push_back(berlin);
    cities->push_back(hamburg);
    cities->push_back(munich);
    cities->push_back(cologne);
    cities->push_back(frankfurt);

    distances = new std::map<std::string *, std::map<std::string *, int> *>();

    fill_distances(cities, distances);

    auto allele_values = const_cast<std::vector<std::string *> *>(
            new std::vector<std::string *>({
                                                   berlin,
                                                   hamburg,
                                                   munich,
                                                   cologne,
                                                   frankfurt
                                           }));

    auto config = const_cast<Configuration<std::string> *>(
            new Configuration<std::string>(fitness_function,
                                           allele_values,
                                           100,
                                           6,
                                           new TournamentSelectionConfiguration(2),
                                           new SinglePointCrossoverConfiguration(
                                                   new FixedMode()),
                                           new MutationConfiguration(0.05),
                                           to_string));

    auto population = new Population<std::string>(config);

    population->populate_next_generations(10);

    auto best_results = population->get_best();

    std::cout << best_results->at(0)->to_string() << ": " << best_results->at(0)->get_fitness() << std::endl;

    delete best_results;

    delete config;
    delete population;

    delete (*distances)[berlin];
    delete (*distances)[hamburg];
    delete (*distances)[munich];
    delete (*distances)[cologne];
    delete (*distances)[frankfurt];

    delete distances;

    std::for_each(allele_values->begin(), allele_values->end(), [](const std::string *i) { delete i; });
    delete allele_values;

    return 0;
}
