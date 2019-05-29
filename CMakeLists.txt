cmake_minimum_required(VERSION 3.4)

project(GFWK_C_Frontend)

set(GTFW_SRC_PATH  "src/")
set(GTFW_INC_PATH  "src/")
set(GTFW_TEST_PATH "test/")

include_directories(${GTFW_SRC_PATH})
add_subdirectory(${GTFW_INC_PATH})

# Testing Options.
option(ENABLE_TESTS "Enables building tests using GTest" ON)
if(ENABLE_TESTS)
    include(cmake/AddTest.cmake)
    add_subdirectory(test)
endif()