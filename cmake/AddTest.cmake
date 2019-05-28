
macro(AddTest TestName)
    add_executable(${TestName} ${ARGN} )
    target_link_libraries(${TestName} gtest gtest_main)
    add_test(${TestName} ${TestName})
endmacro()