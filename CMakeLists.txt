cmake_minimum_required(VERSION 3.21)

project(cppFinanzOrg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Quick Qml Core Gui Network Charts)

set(SOURCES
    src/main.cpp
    src/AppPaths.cpp
    src/models/tableModel.cpp
    src/models/dataModel.cpp
    src/models/chartModel.cpp

    src/controllers/CSVReader.cpp
    src/controllers/calculator.cpp
    src/controllers/category.cpp
)

set(HEADER)

add_executable(cppFinanzOrg
    ${SOURCES}
    resource.qrc
)

target_link_libraries(cppFinanzOrg PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Quick Qt6::Network Qt6::Qml Qt6::Charts -lstdc++)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
endif()