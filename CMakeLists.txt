cmake_minimum_required(VERSION 3.17)
project(car)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

set(project_headers mainwindow.h)

set(project_sources mainwindow.cpp)

add_executable(car main.cpp ${project_headers} ${project_sources})

target_link_libraries(car Qt5::Widgets)
target_link_libraries(car Qt5::Charts)