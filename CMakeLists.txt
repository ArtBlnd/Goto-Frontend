cmake_minimum_required(VERSION 3.4)

project(GFWK_C_Frontend)

set(GTFW_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_INC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(GTFW_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${GTFW_SRC_PATH})
add_subdirectory(${GTFW_INC_PATH})

# Compile Options.
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        # GLOBAL COMPILER FLAGS
        /std:c++17      # Enable C++17 Features.
        /permissive-    # Disable Non-Standard MSVC Features and Syntaxs.
        /MP             # Enable Multi-Process Compilations
        /W4             # Enable Warning Level At Level-3
        /Yupch.h        # Enable Precompiled-Header for pch.h

        # RELEASE COMPILER FLAGS
        $<$<CONFIG:Release>:
		/Gw             # Enable Whole Program Global Optimization
		/GS-            # Disable Buffer Security Check
		/GL             # Enable Link Time Code Generation Optimization.
    )
endif()

# Testing Options.
option(ENABLE_TESTS "Enables building tests using GTest" ON)
if(ENABLE_TESTS)
    include(cmake/AddTest.cmake)
    add_subdirectory(${GTFW_TEST_PATH})
endif()