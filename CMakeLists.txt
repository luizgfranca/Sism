project(Sism)
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(sdbus-c++ REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(app main.cpp)

target_link_libraries(
    app 
    PRIVATE SDBusCpp::sdbus-c++ 
    ${GTKMM_LIBRARIES}
    )