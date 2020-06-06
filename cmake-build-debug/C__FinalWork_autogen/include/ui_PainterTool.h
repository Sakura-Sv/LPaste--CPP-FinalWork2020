/********************************************************************************
** Form generated from reading UI file 'PainterTool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTERTOOL_H
#define UI_PAINTERTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PainterTool
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QWidget *PainterTool)
    {
        if (PainterTool->objectName().isEmpty())
            PainterTool->setObjectName(QString::fromUtf8("PainterTool"));
        PainterTool->resize(270, 50);
        PainterTool->setWindowOpacity(0.000000000000000);
        pushButton = new QPushButton(PainterTool);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 51, 51));
        pushButton_2 = new QPushButton(PainterTool);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 0, 51, 51));
        pushButton_3 = new QPushButton(PainterTool);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(110, 0, 51, 51));
        pushButton_4 = new QPushButton(PainterTool);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(160, 0, 51, 51));
        pushButton_5 = new QPushButton(PainterTool);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(220, 0, 51, 51));

        retranslateUi(PainterTool);
        QObject::connect(pushButton_5, SIGNAL(clicked()), PainterTool, SLOT(saveScreen()));

        QMetaObject::connectSlotsByName(PainterTool);
    } // setupUi

    void retranslateUi(QWidget *PainterTool)
    {
        PainterTool->setWindowTitle(QApplication::translate("PainterTool", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("PainterTool", "\347\224\273\347\254\224", nullptr));
        pushButton_2->setText(QApplication::translate("PainterTool", "\347\210\267\350\277\230\346\262\241\346\203\263\345\245\275", nullptr));
        pushButton_3->setText(QApplication::translate("PainterTool", "\345\233\236\351\200\200", nullptr));
        pushButton_4->setText(QApplication::translate("PainterTool", "\345\211\215\350\277\233", nullptr));
        pushButton_5->setText(QApplication::translate("PainterTool", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PainterTool: public Ui_PainterTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTERTOOL_H
