
add_library(goto-driver STATIC
    CommandLine.cpp
    CommandLine.h
    Driver.cpp
    Driver.h
    DriverOption.cpp
    DriverOption.h
)

target_link_libraries(goto-driver goto-parser)
