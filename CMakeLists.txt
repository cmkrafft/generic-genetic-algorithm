CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(GeneticAlgorithm VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -g)

OPTION(WITH_PARALLELISM "Use OpenMP for parallelization" ON)

SET(CMAKE_ROOT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

ADD_SUBDIRECTORY(src/library)
ADD_SUBDIRECTORY(src/examples)


FIND_PACKAGE(Doxygen)
IF (DOXYGEN_FOUND)
    ADD_CUSTOM_TARGET(
            docs ALL

            COMMAND doxygen doxygen.conf
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
ENDIF ()