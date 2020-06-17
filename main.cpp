#include <QApplication>
#include <widget/Widget.h>
#include <iostream>

int main(int argc, char *argv[]) {
    if(QSysInfo::kernelType() != "winnt"){
        return 0;
    }

    QDir dir;
    dir.mkdir("D:/temp");
    dir.mkdir("D:/temp/LPaste");
    dir.mkdir("D:/temp/LPaste/ScreenCache");

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
