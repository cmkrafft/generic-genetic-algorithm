cmake_minimum_required(VERSION 3.16)

project(GeneticAlgorithmLib VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -g)

if (DEFINED CMAKE_ROOT_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/lib)
    set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/include)
    set(CMAKE_CURRENT_PATH ${CMAKE_ROOT_OUTPUT_DIRECTORY}/src/geneticalgorithm/implementation)
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../lib)
    set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../include)
    set(CMAKE_CURRENT_PATH ${CMAKE_BINARY_DIR})

    option(WITH_PARALLELISM "Use OpenMP for parallelization" ON)
endif ()

add_library(GeneticAlgorithmLib Chromosome.cpp Chromosome.h Population.cpp Population.h utils/RandomNumberGenerator.cpp utils/RandomNumberGenerator.h configuration/Configuration.cpp configuration/Configuration.h configuration/crossover/AbstractCrossoverConfiguration.cpp configuration/crossover/AbstractCrossoverConfiguration.h configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.cpp configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.cpp configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h configuration/crossover/singlepoint/mode/FixedMode.cpp configuration/crossover/singlepoint/mode/FixedMode.h configuration/crossover/singlepoint/mode/RandomMode.cpp configuration/crossover/singlepoint/mode/RandomMode.h configuration/crossover/uniform/UniformCrossoverConfiguration.cpp configuration/crossover/uniform/UniformCrossoverConfiguration.h configuration/mutation/MutationConfiguration.cpp configuration/mutation/MutationConfiguration.h configuration/selection/AbstractSelectionConfiguration.cpp configuration/selection/AbstractSelectionConfiguration.h configuration/selection/proportionate/ProportionateSelectionConfiguration.cpp configuration/selection/proportionate/ProportionateSelectionConfiguration.h configuration/selection/tournament/TournamentSelectionConfiguration.cpp configuration/selection/tournament/TournamentSelectionConfiguration.h)
set_target_properties(GeneticAlgorithmLib PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(GeneticAlgorithmLib PRIVATE src/implementation/geneticalgorithm)

if (WITH_PARALLELISM)
    MESSAGE("Building with OpenMP")
    find_package(OpenMP REQUIRED)

    add_definitions(-DUSE_PARALLELISM)
    target_link_libraries(GeneticAlgorithmLib PRIVATE OpenMP::OpenMP_CXX)
else ()
    MESSAGE("Building without OpenMP")
endif ()

#install(TARGETS GeneticAlgorithmLib
#        LIBRARY DESTINATION lib)
#
#install(FILES ${PUBLIC_HEADERS}
#        DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include/GeneticAlgorithmLib)

set_target_properties(GeneticAlgorithmLib PROPERTIES PUBLIC_HEADER "Chromosome.h;Population.h;utils/RandomNumberGenerator.h;configuration/Configuration.h;configuration/crossover/AbstractCrossoverConfiguration.h;configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h;configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h;configuration/crossover/singlepoint/mode/FixedMode.h;configuration/crossover/singlepoint/mode/RandomMode.h;configuration/crossover/uniform/UniformCrossoverConfiguration.h;configuration/mutation/MutationConfiguration.h;configuration/selection/AbstractSelectionConfiguration.h;configuration/selection/proportionate/ProportionateSelectionConfiguration.h;configuration/selection/tournament/TournamentSelectionConfiguration.h")

set(HEADER_FILES Chromosome.h Population.h utils/RandomNumberGenerator.h configuration/Configuration.h configuration/crossover/AbstractCrossoverConfiguration.h configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h configuration/crossover/singlepoint/mode/FixedMode.h configuration/crossover/singlepoint/mode/RandomMode.h configuration/crossover/uniform/UniformCrossoverConfiguration.h configuration/mutation/MutationConfiguration.h configuration/selection/AbstractSelectionConfiguration.h configuration/selection/proportionate/ProportionateSelectionConfiguration.h configuration/selection/tournament/TournamentSelectionConfiguration.h)

INSTALL(TARGETS GeneticAlgorithmLib
        LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        #PUBLIC_HEADER DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}
        )

INSTALL(FILES Population.h Chromosome.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

install(DIRECTORY ${CMAKE_CURRENT_PATH}/configuration # source directory
        DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY} # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
        )

install(DIRECTORY ${CMAKE_CURRENT_PATH}/utils # source directory
        DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY} # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
        )

add_custom_target(library DEPENDS GeneticAlgorithmLib)
