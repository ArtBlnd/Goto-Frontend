
# Test Module Initializations
set(CATCH2_DIR     "${Goto_C_FRONTEND_DEPS_PATH}/Catch2/")
set(CATCH2_ABS_DIR "deps/Catch2")

add_subdirectory(${CATCH2_DIR} ${CATCH2_ABS_DIR} EXCLUDE_FROM_ALL)
enable_testing()


# Testcase Definitions
AddTest(DriverTest Driver/CLIParserTest.cpp)
target_link_libraries(DriverTest goto-driver)
