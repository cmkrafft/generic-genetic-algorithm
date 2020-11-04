cmake_minimum_required(VERSION 3.16)

project(Examples VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -g)

if (DEFINED CMAKE_ROOT_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/lib)
    set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/include)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/examples)
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../lib)
    set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../include)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../examples)
endif ()

add_executable(example01 example01.cpp)
add_executable(example02 example02.cpp)

set(HEADER_FILES ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Chromosome.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Population.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/RandomNumberGenerator.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/Configuration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/AbstractCrossoverConfiguration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/SinglePointCrossoverConfiguration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/AbstractSinglePointCrossoverConfigurationMode.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/FixedMode.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/RandomMode.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/UniformCrossoverConfiguration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/MutationConfiguration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/AbstractSelectionConfiguration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/ProportionateSelectionConfiguration.h ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/TournamentSelectionConfiguration.h)

set(SOURCES example01.cpp example02.cpp)

#target_link_libraries(GeneticAlgorithm LINK_PUBLIC GeneticAlgorithmLib)

target_link_libraries(example01 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libGeneticAlgorithmLib.a)
target_link_libraries(example02 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libGeneticAlgorithmLib.a)

include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

#target_include_directories(Examples PRIVATE ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})
#include(${HEADER_FILES})

add_custom_target(executable DEPENDS GeneticAlgorithm)