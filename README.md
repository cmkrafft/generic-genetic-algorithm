# Generic Genetic Algorithm

This project contains both the implementation of a generic genetic algorithm library and various examples.

## Prerequisites

* OpenMP (optional)
* Doxygen (optional)

## Build

Execute `cmake .` in the root directory of the project to generate Makefiles for both subprojects: the library itself and the examples.

To build the whole project execute:
```bash
cmake .
make
```

It is also possible to use the build targets `docs`, `library` or `examples` to build a specific subproject.

### OpenMP

By default the library uses [OpenMP](https://github.com/OpenMP) to enable parallel execution of certain parts of the implementation. If parallelism is not needed or wanted, it can be disabled when generated the Makefiles:
```bash
cmake . -DWITH_PARALLELISM=OFF
```

### Docker
There is a Dockerfile located at `docker/Dockerfile` which can be used to get an environment including all necessary dependencies and further tools (such as [Valgrind](https://valgrind.org/)) to get you started.

#### Manual setup

To build and run the Dockerfile use
```bash
cd docker
docker build . -t genetic-algorithm-dev-env:latest
docker run -it --rm -v ../:/workspace genetic-algorithm-dev-env:latest bash
```

#### Docker-Compose

If you have docker-compose available, `build/docker-compose.yaml` can be used to automate this process:
```bash
cd docker
docker-compose build && docker-compose up -d
docker exec -it docker_genetic-algorithm-dev-env_1 bash
```

## Usage

### Compilation

To use the built static library in your own project, you have to provide both the static library and its header files, located in the `build/include` directory, to the compiler.
E.g.:
```bash
clang++ -std=gnu++2a -I./build/include app.cpp ./build/lib/libGeneticAlgorithmLib.a -o app 
```

### Code

The following is based on *example01*, which represents a possible solution to a [Knapsack problem](https://en.wikipedia.org/wiki/Knapsack_problem): A given set of items should be packed in to a backpack whereas the value of those items should be maximized without exceeding a maximum weight limit.
In this example there will be 10 items available.

To get started, define a set of possible *allele* values, which represent the possible states of variables (= *genes*) in your result (= *chromosome*). A chromosome is – in other words – a combination of *genes*, whereas a gene contains a specific manifestation of an *allele*.
E.g., in this case `0` or `1` to indicate if a given item is supposed to be present or not and are the possible values for each *gene*

```c++
auto allele_values = const_cast<std::vector<int *> *>(
        new std::vector<int *>({
                                       new int(0),
                                       new int(1)
                               }));
```

To determine the superiority of one chromosome over another, a so called *fitness function* has to be used. It is used to calculate the fitness of each chromosome based on its characteristics, whereas a higher score is better and a negative score indicates an invalid combination of genes.
E.g., this is what the *fitness function* of the Knapsack problem could look like:
```c++
double fitness_function(const std::vector<int *> *genes) {
    // Calculate the weights for each item and sum them up
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

    // Determine if the weight exceeds the weight limit and return lowest score if weight limit is exceeded
    if (weight > 40.0) {
        return 0.0;
    }

    // Calculate and return the value of the current combination of items – which is supposed to be maximized
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
```

Since the implementation supports verbose output of *chromosomes*, it is also necessary to provide a function to be used for serialization of a single allele.
E.g.:
```c++
std::string to_string(const int *v) {
    return std::to_string(*v);
}
```

In the next step the shape of both the single *chromosome*, the *population* in general and the desired behaviour of the evolution have to be defined. The *configuration* takes the *fitness function*, the size of the total *population* (100), the length of a single *chromosome* (10) and further *configuration* regarding the *selection* and *crossover* method to be used. Additionally it is possible to configure the mutation rate for each new *chromosome*.
For further information regarding *selection*, *crossover* or *mutation*, please refer to the documentation of these classes.

```c++
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
```

The next step is to create the actual *population* based on the *configuration* provided above and start the simulation. It is not necessary to manually trigger the simulation of each new generation. Usually you might want to simulate the next *n* generations.
E.g.:
```c++
auto population = new Population<int>(config);

population->populate_next_generations(100);
```

As soon as the simulation is completed, you might want to retrieve the best chromosomes and get their current score. The first one of the best fits can be retrieved as shown below:
```c++
auto best_results = population->get_best();

std::cout << best_results->at(0)->to_string() << ": " << best_results->at(0)->get_fitness() << std::endl;
```

Executing the whole program will generate the following output:

```text
------------------------------------------------------------------------------
Possible alleles:       [0, 1]
Selection:              Tournament
- Contestants:          2
Crossover:              Single Point
- Mode:                 Fixed
-- Factor:              0.5
Mutation:
- Rate:                 0.05
------------------------------------------------------------------------------
[================================================================>] | 100.00 %
[0, 0, 0, 1, 0, 0, 0, 1, 1, 1]: 11.5
```

At first the configuration is printed to stdout after initializing the population. Populating *n* generations leads to an output showing the current progress.
As soon as the progress is completed, the best fit is printed to stdout followed by its *fitness* score.

For more detailed code please refer to one of the examples included in this repository.

## Examples

Currently there are three examples included:
* **Knapsack Problem (example01)**\
  Choosing the ten most valuable items to put in a backpack without exceeding a given weight limit 
* **Sorting ten letters (example02)**\
  Trying to sort the first ten letters of the latin alphabet
* **Traveling salesperson (example03)**\
  Calculating the shortest circular route between the five major german cities without visiting one city twice
  
