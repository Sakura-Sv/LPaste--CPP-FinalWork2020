#include <QApplication>
#include <widget/Widget.h>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
