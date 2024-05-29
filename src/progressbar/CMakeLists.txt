cmake_minimum_required(VERSION 3.16)

project(progressbar LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED
        src/ProgressBar.cpp
        include/ProgressBar.h
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE

        PUBLIC
        Qt${QT_VERSION_MAJOR}::Core

)