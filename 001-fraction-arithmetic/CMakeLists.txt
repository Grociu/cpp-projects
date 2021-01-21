# Requires at least version 3.11 for the GoogleTest module
cmake_minimum_required(VERSION 3.11)

# Project name, version and description
project(Fractions
        VERSION 0.0.1
        DESCRIPTION "Fraction arithmetic implemented in C++")

# Sets a flag to require the C++11 Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sets the path for the Google Test package located in the projets directory
set(GTest_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../googletest-distribution/lib/cmake/GTest)

# Gets the GoogleTest package
find_package(GTest CONFIG REQUIRED)

# Creates the libraries from the classes directory
add_library(Fraction classes/fraction.cpp)

# Creates the main Executible from main.cpp
add_executable(fractions main.cpp)

# Links the libraries from classes folder to the main project
target_link_libraries(fractions LINK_PUBLIC Fraction)

# Sets the current directory as the installation directory for the CMake installation command
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

# Defines the installation instruction
install(TARGETS fractions
        DESTINATION ${CMAKE_INSTALL_PREFIX})
