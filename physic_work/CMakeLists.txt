cmake_minimum_required(VERSION 3.10)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)

add_executable(calc
        main.cpp
        src/Dimension.cpp
        src/Unit.cpp
        src/Quantity.cpp
        src/Parser.cpp
)