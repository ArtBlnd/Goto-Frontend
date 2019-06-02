cmake_minimum_required(VERSION 3.14)

project(GFWK_C_Frontend)

set(GTFW_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compile Options.
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options("/permissive-") # Disable Non-Standard MSVC Features and Syntaxs.
else()
    
endif()

# Testing Options.
option(ENABLE_TESTS "Enables building tests using GTest" ON)
if(ENABLE_TESTS)
    include(cmake/AddTest.cmake)
    add_subdirectory(${GTFW_TEST_PATH})
endif()

include_directories(${GTFW_SRC_PATH})
add_subdirectory(${GTFW_INC_PATH})