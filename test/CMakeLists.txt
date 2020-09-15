cmake_minimum_required(VERSION 3.12.4)
project(Test)

add_subdirectory(${CMAKE_SOURCE_DIR}/test/googletest)
add_executable(TestCPP TestTask.cpp)
set_target_properties(TestCPP
                      PROPERTIES
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON
                      )

target_include_directories(TestCPP PRIVATE BulkLibrary)
target_link_libraries(TestCPP PRIVATE gtest gtest_main BulkLibrary)

add_test(NAME TestCPP COMMAND TestCPP)