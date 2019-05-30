
# Test Module Initializations
set(gtest_hide_internal_symbols ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt      ON CACHE BOOL "" FORCE)

add_subdirectory(gtest/ EXCLUDE_FROM_ALL)
enable_testing()

set_target_properties(gtest PROPERTIES FOLDER test)
set_target_properties(gtest_main PROPERTIES FOLDER test)

include_directories(gtest/googletest/include)

# Testcases
AddTest(Test-DriverCLIParserTest Driver/CLIParserTest.cpp)
target_link_libraries(Test-DriverCLIParserTest gtfw-driver)