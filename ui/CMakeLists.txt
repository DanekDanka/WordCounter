cmake_minimum_required(VERSION 3.16)

project(wordcounterui LANGUAGES CXX)


find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Core Charts Qml REQUIRED)

#find_package(Qt6 REQUIRED COMPONENTS
#        Core
#        Charts
#        Qml
#)

qt_add_resources(QT_RESOURCES qml.qrc)

#add_library(${PROJECT_NAME} MODULE
#        ${QT_RESOURCES}
#)

#target_compile_definitions(${PROJECT_NAME} PRIVATE DIAGNOSTICSPLUGIN_LIBRARY)

target_link_libraries(${PROJECT_NAME}
        Qt6::Core
        Qt6::Charts
        Qt6::Qml
)

enable_plugin(${PROJECT_NAME})
