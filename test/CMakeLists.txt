set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

add_subdirectory (gtest EXCLUDE_FROM_ALL)
enable_testing()

include_directories(gtest/googletest/include)
link_directories(gtest/lib)

AddTest(DriverTest
    Driver/CLIParserTest.cpp
)