cmake_minimum_required(VERSION 3.10)

# Name your project and set C++ version
project(SudokuGenerator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Let user specify SFML_DIR when configuring
set(SFML_DIR "" CACHE PATH "Path to SFML's CMake config")

# Look for SFML
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Add source files
add_executable(sudoku
    src/main.cpp
    src/Board.cpp
    src/sfml.cpp
)

# Link SFML libraries
target_link_libraries(sudoku PRIVATE SFML::Graphics SFML::Window SFML::System)