//
// Created by 刘镇 on 2020/6/4.
//

#include <QtWidgets/QSystemTrayIcon>
#include <QMenu>
#include "SystemTray.h"

void mySystemTray::systemTrayInit(QWidget *mainWindow)
{
    auto *systemTray = new QSystemTrayIcon();
    systemTray->setIcon(QIcon(":/static/favicon.ico"));
    systemTray->setToolTip("SystemTray Program");
    auto *systemTrayMenu = new QMenu();
    QObject::connect(systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), mainWindow,
            SLOT(onSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
    systemTrayMenu->addAction("Open Main Window", mainWindow, SLOT(onBtnShowClicked()));
    systemTrayMenu->addAction("Grab Screen        F1", mainWindow, SLOT(onBtnRectScreenClicked()));
    systemTrayMenu->addAction("Paste ScrrenShot   F3", mainWindow, SLOT(onBtnPasteClicked()));
    systemTrayMenu->addAction("About Me   ", mainWindow, SLOT(onBtnAboutMeClicked()));
    systemTrayMenu->addAction("Quit", mainWindow, SLOT(onBtnCloseClicked()));
    systemTray->setContextMenu(systemTrayMenu);
    systemTray->setToolTip("LPaste");
    systemTray->show();
    mySystemTrayInitFinished(systemTray);
}

void mySystemTray::mySystemTrayInitFinished(QSystemTrayIcon * systemTray) {
    systemTray->showMessage("App is ready",
            "Just Enjoy it!\nLet's try to tap F1!\n"
                 "                         --from LiuZhen",
                 QSystemTrayIcon::MessageIcon::Information,
                 5000);
}