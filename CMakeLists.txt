cmake_minimum_required(VERSION 3.4)

project(GFWK_C_Frontend)

set(GTFW_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/")

set(CMAKE_CXX_EXTENSIONS OFF)

# Compile Options.
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS}
        # GLOBAL COMPILER FLAGS
        /std:c++17      # Enable C++17 Features.
        /permissive-    # Disable Non-Standard MSVC Features and Syntaxs.
        /MP             # Enable Multi-Process Compilations
        /W4             # Enable Warning Level At Level-3
        /Yupch.h        # Enable Precompiled-Header for pch.h
    )
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# Testing Options.
option(ENABLE_TESTS "Enables building tests using GTest" ON)
if(ENABLE_TESTS)
    include(cmake/AddTest.cmake)
    add_subdirectory(${GTFW_TEST_PATH})
endif()

include_directories(${GTFW_SRC_PATH})
add_subdirectory(${GTFW_INC_PATH})