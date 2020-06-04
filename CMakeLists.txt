cmake_minimum_required(VERSION 3.15)
project(C__FinalWork)

set(CMAKE_PREFIX_PATH "‪D:\\Qt\\5.12.8\\mingw73_32\\")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(C__FinalWork main.cpp resources/systemTray.qrc screen/screen.cpp screen/screen.h systemTray/SystemTray.h
        systemTray/SystemTray.cpp widget/widget.cpp widget/widget.h widget/widget.ui lowLevelKeyBoardHook/LowLevelKeyBoardHook.h lowLevelKeyBoardHook/LowLevelKeyBoardHook.cpp)

target_link_libraries(C__FinalWork Qt5::Widgets)