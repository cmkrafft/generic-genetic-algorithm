cmake_minimum_required(VERSION 3.16)

project(GeneticAlgorithm VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -g)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
set(CMAKE_ROOT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src/geneticalgorithm/implementation)
add_subdirectory(src/geneticalgorithm/examples)


find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(
            docs ALL

            COMMAND doxygen docsconf
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
endif ()