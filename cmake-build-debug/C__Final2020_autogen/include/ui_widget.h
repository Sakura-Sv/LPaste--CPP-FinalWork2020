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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *btnFullScreen;
    QPushButton *btnRectScreen;
    QPushButton *btnClose;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(100, 141);
        btnFullScreen = new QPushButton(Widget);
        btnFullScreen->setObjectName(QString::fromUtf8("btnFullScreen"));
        btnFullScreen->setGeometry(QRect(0, 70, 101, 71));
        btnRectScreen = new QPushButton(Widget);
        btnRectScreen->setObjectName(QString::fromUtf8("btnRectScreen"));
        btnRectScreen->setGeometry(QRect(0, 20, 51, 51));
        btnClose = new QPushButton(Widget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(50, 20, 51, 51));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 101, 16));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(Widget);
        QObject::connect(btnFullScreen, SIGNAL(clicked()), Widget, SLOT(onBtnFullScreenClicked()));
        QObject::connect(btnRectScreen, SIGNAL(clicked()), Widget, SLOT(onBtnRectScreenClicked()));
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
        label->setText(QApplication::translate("Widget", "My Snipaste", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
