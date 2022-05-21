cmake_minimum_required(VERSION 3.21)
project(GtkCalculator C)

set(CMAKE_C_STANDARD 11)

add_executable(GtkCalculator main.c events.c events.h)

FIND_PACKAGE(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(ADWAITA REQUIRED IMPORTED_TARGET libadwaita-1)

target_link_libraries(GtkCalculator PRIVATE PkgConfig::GTK)
target_link_libraries(GtkCalculator PRIVATE PkgConfig::ADWAITA)