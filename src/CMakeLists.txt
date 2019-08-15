add_subdirectory("basic")
add_subdirectory("language")
add_subdirectory("driver")

add_executable(Goto-exe Main/main.cpp)
target_link_libraries(Goto-exe Goto-driver)
