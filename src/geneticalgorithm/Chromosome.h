//
// Created by Christopher Krafft on 02.10.20.
//

#ifndef GENETICALGORITHM_CHROMOSOME_H
#define GENETICALGORITHM_CHROMOSOME_H

#include <vector>
#include <string>
#include <numeric>
#include <iostream>

/**
 * Generic representation of a Chromosome. Consisting of n elements, so called "genes".
 * @tparam T Type of an allele
 */
template<typename T>
class Chromosome {

public:
    /**
     * Generate new instance of Chromosome for given data type
     * @param genes Representation of genes of given type
     * @param fitness_function Function pointer to fitness function. Used to determine chromosome's fitness.
     * @param to_string  Function pointer to to_string function. Used to serialize chromosome, e.g. when calling print.
     */
    explicit Chromosome(const std::vector<T *> *genes, double (*fitness_function)(const std::vector<T *> *),
                        std::string (*to_string)(const T *v)) {
        this->genes = genes;

        this->fitness_function = fitness_function;

        this->to_string_function = to_string;
    }

    /**
     * Get current chromosome representation
     * @return Chromosome vector
     */
    [[maybe_unused]] const std::vector<T *> *get_genes() const {
        return this->genes;
    }

    /**
     * Get current chromosome's fitness based on fitness_function
     * @return Fitness value
     */
    [[nodiscard]] double get_fitness() const {
        return this->fitness_function(this->genes);
    }


    /**
     * Function pointer to chromosome's fitness function
     * @return Fitness value
     */
    double (*fitness_function)(const std::vector<T *> *);

    /**
     * Get string representation of chromosome
     * @return String representation
     */
    [[nodiscard]] std::string to_string() const {
        return "["
               + std::accumulate(genes->begin(),
                                 genes->end(),
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

    /**
     * Print current chromosome's values using to_string function for serialization
     */
    void print() const {
        std::cout << this->to_string() << std::endl;
    }

    /**
     * Function pointer to to_string function
     * @param v Value to be serialized
     * @return String representation
     */
    std::string (*to_string_function)(const T *v);

    ~Chromosome() {
        delete this->genes;
    }

private:
    const std::vector<T *> *genes;
};


#endif //GENETICALGORITHM_CHROMOSOME_H
