project(MyTests)

add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(testing tests.cpp)

target_link_libraries(testing long-arithmetic)

target_link_libraries(testing gtest gtest_main)