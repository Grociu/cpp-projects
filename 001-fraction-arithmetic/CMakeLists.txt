# Requires at least version 3.11 for the GoogleTest module
cmake_minimum_required(VERSION 3.11)

# Project name, version and description
project(Fractions
        VERSION 0.0.1
        DESCRIPTION "Fraction arithmetic implemented in C++")

# Sets a flag to require the C++11 Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#######################################################################
# These commands implement the Google Test library at configure time
# Originally copied from https://crascit.com/2015/07/25/cmake-gtest/
#######################################################################

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include"
    )
endif()

# Now simply link your own targets against gtest, gmock, etc. as appropriate

########################################################################
# Project Libraries
########################################################################

# Creates the libraries from the classes directory
add_library(Fraction classes/fraction.cpp)
#add_library(DivideByZero classes/dividebyzero.cpp)
#######################################################################
# Unit Tests
#######################################################################

# Add an executable unittest file
add_executable(fractions_unittest tests/unittest.cpp)

# Link unittest executable against gtest and project libraries
target_link_libraries(fractions_unittest gtest)
target_link_libraries(fractions_unittest Fraction)
#target_link_libraries(fractions_unittest DivideByZero)

# Enable testing with CMake Test functionality (Ctrl+Shift+P Cmake Test in VSC)
enable_testing()
add_test(NAME runUnitTests_fraction COMMAND fractions_unittest)

########################################################################
# Main Project Files
########################################################################

# Creates the main Executible from main.cpp
add_executable(fractions_main main.cpp)

# Links the project libraries to the main executable
target_link_libraries(fractions_main Fraction)

########################################################################
# Installation
########################################################################

# Sets the current directory as the installation directory for the CMake installation command
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

# Defines the installation instructions
install(TARGETS fractions_unittest
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS fractions_main
        DESTINATION ${CMAKE_INSTALL_PREFIX})
