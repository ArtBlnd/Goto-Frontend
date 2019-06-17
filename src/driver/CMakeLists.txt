
add_library(gtfw-driver STATIC
    CommandLine.cpp
    CommandLine.h
    Driver.cpp
    Driver.h
    DriverOption.cpp
    DriverOption.h
)

target_link_libraries(gtfw-driver gtfw-parser)