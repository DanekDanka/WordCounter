cmake_minimum_required(VERSION 3.16)

project(core LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED
        src/core.cpp
        include/core.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
#        Qt${QT_VERSION_MAJOR}::Core
        fabric
        filemanager
        filereader
        progressbar
        uimediator
        histogram
        vocabularycreator
        vocabularymodel

        PUBLIC
)
