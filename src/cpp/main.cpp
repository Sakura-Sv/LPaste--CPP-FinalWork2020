//
// Created by 刘镇 on 2020/6/2.
//

#include <QApplication>
#include "widget/Widget.h"
#include <winbase.h>

int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR pCmdLine,
        INT nCmdShow){
    if(QSysInfo::kernelType() != "winnt"){
        return 0;
    }
    QDir dir;
    dir.mkdir("D:/temp");
    dir.mkdir("D:/temp/LPaste");
    dir.mkdir("D:/temp/LPaste/ScreenCache");
    QApplication a(nCmdShow, (char **)CommandLineToArgvW(GetCommandLineW(), &nCmdShow));
    Widget w;
    return a.exec();
}
