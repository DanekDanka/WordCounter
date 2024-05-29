cmake_minimum_required(VERSION 3.16)

project(WordCounter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWordCounter
    main.cpp
)

qt_add_qml_module(appWordCounter
    URI WordCounter
    VERSION 1.0
    QML_FILES
        WordCounterMain.qml
)

#set_target_properties(appWordCounter PROPERTIES
##    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWordCounter
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

add_subdirectory(src)

find_package(QT NAMES Qt6 COMPONENTS Core Qml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Qml REQUIRED)

target_link_libraries(appWordCounter
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Qml
#        Qt${QT_VERSION_MAJOR}::StateMachine
        core
        filereader
        uimediator

        fabric
        filemanager
        progressbar
        histogram
        vocabularycreator
        vocabularymodel
)

include(GNUInstallDirs)
install(TARGETS appWordCounter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


