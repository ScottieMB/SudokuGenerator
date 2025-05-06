cmake_minimum_required(VERSION 3.10)

project(SudokuGenerator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "" CACHE PATH "Path to SFML's CMake config")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(sudoku
    src/main.cpp
    src/Board.cpp
    src/sfml.cpp
)

target_link_libraries(sudoku PRIVATE SFML::Graphics SFML::Window SFML::System)
