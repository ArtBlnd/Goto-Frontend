cmake_minimum_required(VERSION 3.14)

project(GFWK_C_Frontend)

#
# Basic Goto-Framework Paths
#
set(GTFW_C_FRONTEND_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_C_FRONTEND_INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_C_FRONTEND_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/")
set(GTFW_C_FRONTEND_DEPS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/")

#
# Compiler Options.
#
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options("/permissive-") # Disable Non-Standard MSVC Features and Syntaxs.
    add_compile_options("/W4")          # Enable Warning Level 4
    add_compile_options("/Yupch.h")     # Enable PCH (Pre-Compiled Header)
    add_compile_options("/Ycpch.pch")   # 
endif()

#
# Directories
#
include_directories(${GTFW_C_FRONTEND_SRC_PATH})
add_subdirectory(${GTFW_C_FRONTEND_INC_PATH})

#
# Testing Options.
#
option(ENABLE_TESTS "Enables building tests using GTest" ON)
if(ENABLE_TESTS)
    include(cmake/AddTest.cmake)
    add_subdirectory(${GTFW_C_FRONTEND_TEST_PATH})
endif()