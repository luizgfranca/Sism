cmake_minimum_required(VERSION 3.25)
project(Sism)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(sdbus-c++ REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
    client/dbus/systemd
    application
    component/service-property
    )
include_directories(
    ${GTKMM_INCLUDE_DIRS}
    client/dbus/systemd
    application
    component/service-property
    )

add_executable(
    sism 
    main.cpp
    client/dbus/systemd/systemd-manager.cpp
    application/state.cpp
    component/service-property/service-property.cpp
    )

target_link_libraries(
    sism 
    PRIVATE SDBusCpp::sdbus-c++ 
    ${GTKMM_LIBRARIES}
    )

include(GNUInstallDirs)

install(IMPORTED_RUNTIME_ARTIFACTS SDBusCpp::sdbus-c++)

include(GNUInstallDirs)
install(
    TARGETS sism
)

include(CPack)