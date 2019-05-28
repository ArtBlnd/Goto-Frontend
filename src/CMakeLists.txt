add_subdirectory(basic)
add_subdirectory(parser)
add_subdirectory(driver)

add_executable(gtfw-exe main.cpp)
target_link_libraries(gtfw-exe gtfw-driver)