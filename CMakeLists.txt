 cmake_minimum_required(VERSION 3.15)
 project(C__Final2020)

 set(CMAKE_PREFIX_PATH "‪D:\\Qt\\5.12.8\\mingw73_32\\")
 set(CMAKE_CXX_STANDARD 14)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTOUIC ON)
 set(CMAKE_AUTORCC ON)


 find_package(Qt5 COMPONENTS Widgets REQUIRED)
 find_package(Qt5 COMPONENTS Core REQUIRED)

 add_executable(C__Final2020 main.cpp resources/systemTray.qrc
         screen/Screen.cpp screen/Screen.h
         systemTray/SystemTray.h systemTray/SystemTray.cpp
         widget/Widget.cpp widget/Widget.h widget/Widget.ui
         lowLevelKeyBoardHook/LowLevelKeyBoardHook.h lowLevelKeyBoardHook/LowLevelKeyBoardHook.cpp
         pasteLabel/PasteLabel.cpp pasteLabel/PasteLabel.h
         painterTool/PainterTool.cpp painterTool/PainterTool.h painterTool/PainterTool.ui magnifierGlass/MagnifierGlass.cpp magnifierGlass/MagnifierGlass.h)

 target_link_libraries(C__Final2020 Qt5::Widgets)