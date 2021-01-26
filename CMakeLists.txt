cmake_minimum_required (VERSION 3.0)

project(kursach)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Cwork/Qt/5.14.2/msvc2017_64")

install(DIRECTORY ${PROJECT_SOURCE_DIR}/Kurwach/images/ DESTINATION bin/images)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(
kursach
	"Kurwach/generator.cpp"  
	"Kurwach/all.cpp" 
	"Kurwach/mainwindow.cpp" 
	"Kurwach/main.cpp" 
	"Kurwach/generator.h" 
	"Kurwach/all.h" 
	"Kurwach/mainwindow.h"
)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)
target_link_libraries(kursach PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

install(TARGETS kursach DESTINATION bin)

install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION bin)

install(FILES $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> DESTINATION bin/platforms)
install(FILES $<TARGET_FILE:Qt5::QWindowsDirect2DIntegrationPlugin> DESTINATION bin/platforms)
