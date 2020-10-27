//
// Created by Christopher Krafft on 02.10.20.
//

#ifndef GENETICALGORITHM_CHROMOSOME_H
#define GENETICALGORITHM_CHROMOSOME_H

#include <vector>
#include <string>
#include <numeric>
#include <iostream>

template<typename T>
class Chromosome {

public:
    explicit Chromosome(const std::vector<T *> *gene, double (*fitness_function)(const std::vector<T *> *), std::string (*to_string)(const T *v)) {
        this->gene = gene;

        this->fitness_function = fitness_function;

        this->to_string_function = to_string;
    }

    [[nodiscard]] double get_fitness() const {
        return this->fitness_function(this->gene);
    }

    [[maybe_unused]] const std::vector<T *> *get_gene() const {
        return this->gene;
    }

    void print() const {
        std::cout << this->to_string() << std::endl;
    }

    [[nodiscard]] std::string to_string() const {
        return "["
               + std::accumulate(gene->begin(),
                                 gene->end(),
                                 std::string{},
                                 [this](const std::string &a,
                                        const T *b) {
                                     return a + (!a.empty()
                                                 ? ", "
                                                 : "")
                                            + this->to_string_function(b);
                                 })
               + "]";
    }

    ~Chromosome() {
        delete this->gene;
    }

    double (*fitness_function)(const std::vector<T *> *);

    std::string (*to_string_function)(const T *v);

private:
    const std::vector<T *> *gene;
};


#endif //GENETICALGORITHM_CHROMOSOME_H
