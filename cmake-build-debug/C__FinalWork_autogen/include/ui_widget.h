/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *btnFullScreen;
    QPushButton *btnRectScreen;
    QPushButton *btnClose;
    QPushButton *btnMin;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(271, 73);
        btnFullScreen = new QPushButton(Widget);
        btnFullScreen->setObjectName(QString::fromUtf8("btnFullScreen"));
        btnFullScreen->setGeometry(QRect(0, 0, 81, 81));
        btnRectScreen = new QPushButton(Widget);
        btnRectScreen->setObjectName(QString::fromUtf8("btnRectScreen"));
        btnRectScreen->setGeometry(QRect(80, 0, 91, 81));
        btnClose = new QPushButton(Widget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(220, 0, 51, 31));
        btnMin = new QPushButton(Widget);
        btnMin->setObjectName(QString::fromUtf8("btnMin"));
        btnMin->setGeometry(QRect(170, 0, 51, 31));

        retranslateUi(Widget);
        QObject::connect(btnFullScreen, SIGNAL(clicked()), Widget, SLOT(onBtnFullScreenClicked()));
        QObject::connect(btnRectScreen, SIGNAL(clicked()), Widget, SLOT(onBtnRectScreenClicked()));
        QObject::connect(btnMin, SIGNAL(clicked()), Widget, SLOT(onBtnMinClicked()));
        QObject::connect(btnClose, SIGNAL(clicked()), Widget, SLOT(onBtnHideClicked()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
#ifndef QT_NO_TOOLTIP
        btnFullScreen->setToolTip(QApplication::translate("Widget", "\345\205\250\345\261\217\346\210\252\345\233\276(Alt+A)", nullptr));
#endif // QT_NO_TOOLTIP
        btnFullScreen->setText(QApplication::translate("Widget", "\345\205\250\345\261\217", nullptr));
#ifndef QT_NO_SHORTCUT
        btnFullScreen->setShortcut(QApplication::translate("Widget", "Alt+A", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        btnRectScreen->setToolTip(QApplication::translate("Widget", "\345\214\272\345\237\237\346\210\252\345\233\276(Ctrl+Alt+A)", nullptr));
#endif // QT_NO_TOOLTIP
        btnRectScreen->setText(QApplication::translate("Widget", "\347\237\251\345\275\242", nullptr));
#ifndef QT_NO_SHORTCUT
        btnRectScreen->setShortcut(QApplication::translate("Widget", "F1", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        btnClose->setToolTip(QApplication::translate("Widget", "\346\234\200\345\260\217\345\214\226\345\210\260\346\211\230\347\233\230", nullptr));
#endif // QT_NO_TOOLTIP
        btnClose->setText(QApplication::translate("Widget", "x", nullptr));
#ifndef QT_NO_TOOLTIP
        btnMin->setToolTip(QApplication::translate("Widget", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnMin->setText(QApplication::translate("Widget", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
