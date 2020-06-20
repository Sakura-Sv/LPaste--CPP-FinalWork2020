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

 add_executable(C__Final2020 WIN32 src/cpp/main.cpp
         src/resources/systemTray.qrc src/resources/AboutMeWin.qrc
         src/cpp/screen/Screen.cpp src/cpp/screen/Screen.h
         src/cpp/systemTray/SystemTray.h src/cpp/systemTray/SystemTray.cpp
         src/cpp/widget/Widget.cpp src/cpp/widget/Widget.h src/cpp/widget/Widget.ui
         src/cpp/lowLevelKeyBoardHook/LowLevelKeyBoardHook.h src/cpp/lowLevelKeyBoardHook/LowLevelKeyBoardHook.cpp
         src/cpp/pasteLabel/PasteLabel.cpp src/cpp/pasteLabel/PasteLabel.h
         src/cpp/painterTool/PainterTool.cpp src/cpp/painterTool/PainterTool.h src/cpp/painterTool/PainterTool.ui
         src/cpp/aboutMe/AboutMeWin.cpp src/cpp/aboutMe/AboutMeWin.h src/cpp/aboutMe/AboutMeWin.ui)

# target_link_options(C__Final2020 PRIVATE )

 target_link_libraries(C__Final2020 Qt5::Widgets )
