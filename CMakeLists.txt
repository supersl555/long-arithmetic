cmake_minimum_required(VERSION 3.10)

project(LongArithmetic VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(LongArithmetic main.cpp)

include_directories(long-arithmetic)
add_subdirectory(long-arithmetic)

target_link_libraries(LongArithmetic long-arithmetic)

add_subdirectory(tests)