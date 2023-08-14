project(Sism)
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# First, find sdbus-c++
find_package(sdbus-c++ REQUIRED)

# Use the sdbus-c++ target in SDBusCpp namespace
add_executable(exe main.cpp)
target_link_libraries(exe PRIVATE SDBusCpp::sdbus-c++)