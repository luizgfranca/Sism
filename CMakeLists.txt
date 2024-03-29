cmake_minimum_required(VERSION 3.25)
project(Sism)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VERSION 0.8.0)

find_package(sdbus-c++ REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
    application
    application/controller
    application/ui
    application/ui/component
    application/ui/component/title-header
    application/ui/component/property-value-list-row
    graphics
    module
    module/system-services-manager
    module/string-tools
    module/logger
    provider
    provider/dbus
    provider/dbus/systemd
    provider/dbus/systemd/dto
    provider/dbus
    provider/dbus/polkit
    provider/dbus/polkit/dto
    provider/systemd
    provider/polkit
    tools
    )

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    module/string-tools
    provider/dbus
    provider/dbus/systemd
    provider/dbus/systemd/dto
    provider/dbus/polkit
    provider/dbus/polkit/dto
    provider/systemd
    provider/polkit
    module/system-services-manager
    module/logger
    application/controller
    application/ui
    application/ui/component
    application/ui/component/service-details-section
    application/ui/component/title-header
    application/ui/component/property-value-list-row
    application
    )

add_executable(
    sism 
    module/string-tools/to-uppercase.cpp
    provider/dbus/systemd/dto/unit-operation-mode.cpp
    provider/systemd/unit-file.cpp
    provider/systemd/unit.cpp
    provider/systemd/systemd-provider.cpp
    provider/polkit/polkit-provider.cpp
    provider/dbus/systemd/systemd-manager.cpp
    provider/dbus/polkit/policykit-1-authority.cpp
    module/system-services-manager/system-services-manager.cpp
    application/controller/system-services-controller.cpp
    application/ui/component/service-details-section/service-details-section.cpp
    application/ui/component/title-header/title-header.cpp
    application/ui/component/property-value-list-row/property-value-list-row.cpp
    application/ui/main-window.cpp
    application/application.cpp
    main.cpp
    )

target_link_libraries(
    sism 
    PRIVATE SDBusCpp::sdbus-c++ 
    ${GTKMM_LIBRARIES}
    )

include(GNUInstallDirs)
install(
    TARGETS sism
)

set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "sism")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "luizgfc@proton.me")
set(CPACK_PACKAGE_VENDOR "Sism")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)