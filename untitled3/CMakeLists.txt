cmake_minimum_required(VERSION 3.22)
project(nazwa)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG a33701196adfad74917046096bf5a2aa0ab0bb50
)

FetchContent_MakeAvailable(fmt)

add_executable(nazwa main.cpp)
target_link_libraries(nazwa fmt)