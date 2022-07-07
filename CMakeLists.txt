cmake_minimum_required(VERSION 3.16)

project(HomoDark VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH "D:/Softwares/Tools/Qt/6.2.4/msvc2019_64") # You should use your own Qt PATH.

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)


set(PROJECT_SOURCES
    src/doc_state.cpp

    src/main_window.h
    src/main_window.cpp
    src/file_handler.cpp

    src/main.cpp

    src/rcs.qrc
)

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::WebEngineWidgets)
