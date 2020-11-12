CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(GeneticAlgorithm VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -g)

OPTION(WITH_PARALLELISM "Use OpenMP for parallelization" ON)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
SET(CMAKE_ROOT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

ADD_SUBDIRECTORY(src/geneticalgorithm/implementation)
ADD_SUBDIRECTORY(src/geneticalgorithm/examples)


FIND_PACKAGE(Doxygen)
IF (DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(
            docs ALL

            COMMAND doxygen docsconf
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
ENDIF ()