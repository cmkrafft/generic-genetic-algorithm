CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(GeneticAlgorithmLib VERSION 0.0.1 DESCRIPTION "A generic genetic algorithm implementation")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -g)

IF (DEFINED CMAKE_ROOT_OUTPUT_DIRECTORY)
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/build/lib)
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/build/lib)
    SET(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_ROOT_OUTPUT_DIRECTORY}/build/include)
    SET(CMAKE_CURRENT_PATH ${CMAKE_ROOT_OUTPUT_DIRECTORY}/src/geneticalgorithm/implementation)
ELSE ()
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../build/lib)
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../build/lib)
    SET(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../build/include)
    SET(CMAKE_CURRENT_PATH ${CMAKE_BINARY_DIR})

    OPTION(WITH_PARALLELISM "Use OpenMP for parallelization" ON)
ENDIF ()

ADD_LIBRARY(GeneticAlgorithmLib Chromosome.cpp Chromosome.h Population.cpp Population.h utils/ProgressBar.cpp utils/ProgressBar.h utils/RandomNumberGenerator.cpp utils/RandomNumberGenerator.h configuration/Configuration.cpp configuration/Configuration.h configuration/crossover/AbstractCrossoverConfiguration.cpp configuration/crossover/AbstractCrossoverConfiguration.h configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.cpp configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.cpp configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h configuration/crossover/singlepoint/mode/FixedMode.cpp configuration/crossover/singlepoint/mode/FixedMode.h configuration/crossover/singlepoint/mode/RandomMode.cpp configuration/crossover/singlepoint/mode/RandomMode.h configuration/crossover/uniform/UniformCrossoverConfiguration.cpp configuration/crossover/uniform/UniformCrossoverConfiguration.h configuration/mutation/MutationConfiguration.cpp configuration/mutation/MutationConfiguration.h configuration/selection/AbstractSelectionConfiguration.cpp configuration/selection/AbstractSelectionConfiguration.h configuration/selection/proportionate/ProportionateSelectionConfiguration.cpp configuration/selection/proportionate/ProportionateSelectionConfiguration.h configuration/selection/tournament/TournamentSelectionConfiguration.cpp configuration/selection/tournament/TournamentSelectionConfiguration.h)
SET_TARGET_PROPERTIES(GeneticAlgorithmLib PROPERTIES VERSION ${PROJECT_VERSION})
TARGET_INCLUDE_DIRECTORIES(GeneticAlgorithmLib PUBLIC src/implementation/geneticalgorithm)

IF (WITH_PARALLELISM)
    MESSAGE("Building with OpenMP")
    FIND_PACKAGE(OpenMP REQUIRED)

    ADD_DEFINITIONS(-DUSE_PARALLELISM)
    TARGET_LINK_LIBRARIES(GeneticAlgorithmLib PRIVATE OpenMP::OpenMP_CXX)
ELSE ()
    MESSAGE("Building without OpenMP")
ENDIF ()

#install(TARGETS GeneticAlgorithmLib
#        LIBRARY DESTINATION lib)
#
#install(FILES ${PUBLIC_HEADERS}
#        DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include/GeneticAlgorithmLib)

SET_TARGET_PROPERTIES(GeneticAlgorithmLib PROPERTIES PUBLIC_HEADER "Chromosome.h;Population.h;utils/ProgressBar.h;utils/RandomNumberGenerator.h;configuration/Configuration.h;configuration/crossover/AbstractCrossoverConfiguration.h;configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h;configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h;configuration/crossover/singlepoint/mode/FixedMode.h;configuration/crossover/singlepoint/mode/RandomMode.h;configuration/crossover/uniform/UniformCrossoverConfiguration.h;configuration/mutation/MutationConfiguration.h;configuration/selection/AbstractSelectionConfiguration.h;configuration/selection/proportionate/ProportionateSelectionConfiguration.h;configuration/selection/tournament/TournamentSelectionConfiguration.h")

SET(HEADER_FILES Chromosome.h Population.h utils/ProgressBar.h utils/RandomNumberGenerator.h configuration/Configuration.h configuration/crossover/AbstractCrossoverConfiguration.h configuration/crossover/singlepoint/SinglePointCrossoverConfiguration.h configuration/crossover/singlepoint/mode/AbstractSinglePointCrossoverConfigurationMode.h configuration/crossover/singlepoint/mode/FixedMode.h configuration/crossover/singlepoint/mode/RandomMode.h configuration/crossover/uniform/UniformCrossoverConfiguration.h configuration/mutation/MutationConfiguration.h configuration/selection/AbstractSelectionConfiguration.h configuration/selection/proportionate/ProportionateSelectionConfiguration.h configuration/selection/tournament/TournamentSelectionConfiguration.h)

SET(PublicHeaders ${HEADER_FILES})
SET(PublishedHeaders "")
FOREACH (Header IN LISTS PublicHeaders)
    #get_filename_component(HeaderFilename "${Header}" NAME)
    SET(Output "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/${Header}")
    MESSAGE(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/${Header})
    LIST(APPEND PublishedHeaders "${Output}")
    ADD_CUSTOM_COMMAND(
            OUTPUT "${Output}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${Header}"
            "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/${Header}"
            MAIN_DEPENDENCY "${Header}"
            COMMENT "Publishing ${HeaderFilename}"
            VERBATIM
    )
ENDFOREACH ()
ADD_CUSTOM_TARGET(
        publish_headers
        ALL
        DEPENDS ${PublishedHeaders}
        SOURCES ${PublicHeaders}
)

INCLUDE_DIRECTORIES(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

#install(TARGETS GeneticAlgorithmLib
#        LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
#        #PUBLIC_HEADER DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}
#        )
#
#install(FILES Population.h Chromosome.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})
#
#install(DIRECTORY ${CMAKE_CURRENT_PATH}/configuration # source directory
#        DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY} # target directory
#        FILES_MATCHING # install only matched files
#        PATTERN "*.h" # select header files
#        )
#
#install(DIRECTORY ${CMAKE_CURRENT_PATH}/utils # source directory
#        DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY} # target directory
#        FILES_MATCHING # install only matched files
#        PATTERN "*.h" # select header files
#        )

ADD_CUSTOM_TARGET(library DEPENDS GeneticAlgorithmLib)
