cmake_minimum_required(VERSION 3.14..3.16)
project(placer)

set(CMAKE_CXX_STANDARD 11)
set(SOURCES
        src/circuit/Circuit.cpp
        src/circuit/Parser.cpp

        src/dataStructures/Die.cpp
        src/dataStructures/Instance.cpp
        src/dataStructures/Net.cpp
        src/dataStructures/Pin.cpp

        src/algorithm/place.cpp
        src/algorithm/math/matrixSolver.cpp

        src/etc/example.cpp
        src/etc/dbTutorial.cpp

        )

add_executable(placer src/main.cpp ${SOURCES})
target_include_directories(placer PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/algorithm
        ${PROJECT_SOURCE_DIR}/include/circuit
        ${PROJECT_SOURCE_DIR}/include/dataStructures
        )

add_executable(evaluator src/main_evalutor.cpp ${SOURCES})
target_include_directories(evaluator PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/algorithm
        ${PROJECT_SOURCE_DIR}/include/circuit
        ${PROJECT_SOURCE_DIR}/include/dataStructures
        ${PROJECT_SOURCE_DIR}/include/etc
        )

add_subdirectory(submodule/OpenDB)
target_link_libraries(placer PRIVATE opendb)
target_link_libraries(evaluator PRIVATE opendb)
