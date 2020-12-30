cmake_minimum_required(VERSION 3.0)

project(voregen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

qt5_add_resources(QRCS kurwach/pictures.qrc)

set(voregen
    Kurwach/generator.cpp
    Kurwach/all.cpp
    Kurwach/mainwindow.cpp
    Kurwach/main.cpp
    ${QRCS}
)

add_executable(${PROJECT_NAME} ${voregen})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
