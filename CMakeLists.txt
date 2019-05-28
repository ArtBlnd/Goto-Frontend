cmake_minimum_required(VERSION 3.4)
project(GFWK_C_Frontend)

include_directories(src)
add_subdirectory(src)


option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    include(cmake/AddTest.cmake)
    add_subdirectory(test)
endif()