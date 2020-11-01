cmake_minimum_required(VERSION 3.16)

project(GeneticAlgorithm VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -g)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(GeneticAlgorithmLib src/geneticalgorithm/Chromosome.cpp src/geneticalgorithm/Chromosome.h src/geneticalgorithm/Population.cpp src/geneticalgorithm/Population.h src/geneticalgorithm/utils/RandomNumberGenerator.cpp src/geneticalgorithm/utils/RandomNumberGenerator.h src/geneticalgorithm/configuration/Configuration.cpp src/geneticalgorithm/configuration/Configuration.h src/geneticalgorithm/configuration/crossover/AbstractCrossoverConfiguration.cpp src/geneticalgorithm/configuration/crossover/AbstractCrossoverConfiguration.h src/geneticalgorithm/configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.cpp src/geneticalgorithm/configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h src/geneticalgorithm/configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.cpp src/geneticalgorithm/configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h src/geneticalgorithm/configuration/crossover/singlepoint/mode/FixedMode.cpp src/geneticalgorithm/configuration/crossover/singlepoint/mode/FixedMode.h src/geneticalgorithm/configuration/crossover/singlepoint/mode/RandomMode.cpp src/geneticalgorithm/configuration/crossover/singlepoint/mode/RandomMode.h src/geneticalgorithm/configuration/crossover/uniform/UniformCrossoverConfiguration.cpp src/geneticalgorithm/configuration/crossover/uniform/UniformCrossoverConfiguration.h src/geneticalgorithm/configuration/mutation/MutationConfiguration.cpp src/geneticalgorithm/configuration/mutation/MutationConfiguration.h src/geneticalgorithm/configuration/selection/AbstractSelectionConfiguration.cpp src/geneticalgorithm/configuration/selection/AbstractSelectionConfiguration.h src/geneticalgorithm/configuration/selection/proportionate/ProportionateSelectionConfiguration.cpp src/geneticalgorithm/configuration/selection/proportionate/ProportionateSelectionConfiguration.h src/geneticalgorithm/configuration/selection/tournament/TournamentSelectionConfiguration.cpp src/geneticalgorithm/configuration/selection/tournament/TournamentSelectionConfiguration.h)
set_target_properties(GeneticAlgorithmLib PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(GeneticAlgorithmLib PRIVATE src/geneticalgorithm)

target_link_libraries(GeneticAlgorithmLib PRIVATE OpenMP::OpenMP_CXX)

add_custom_target(library DEPENDS GeneticAlgorithmLib)

add_executable(GeneticAlgorithm src/main.cpp)

target_link_libraries(GeneticAlgorithm PRIVATE GeneticAlgorithmLib)

add_custom_target(executable DEPENDS GeneticAlgorithm)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(
            docs ALL

            COMMAND doxygen docsconf
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
endif (DOXYGEN_FOUND)