cmake_minimum_required(VERSION 3.17)
project(car)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Charts Quick Core Network REQUIRED)

set(project_headers mainwindow.h indicator.h)

set(project_sources mainwindow.cpp indicator.cpp)

qt5_add_resources(RESOURCES resources.qrc)

add_executable(car main.cpp ${project_headers} ${project_sources} ${RESOURCES})
qt5_use_modules(car Quick Core Network)

target_link_libraries(car Qt5::Widgets)
target_link_libraries(car Qt5::Charts)