//
// Created by 刘镇 on 2020/6/4.
//

#include <QtWidgets/QSystemTrayIcon>
#include <QMenu>
#include "SystemTray.h"

void systemTrayInit(QWidget* mainWindow)
{
    QSystemTrayIcon *systemTray = new QSystemTrayIcon();
    systemTray->setIcon(QIcon(":/static/favicon.ico"));
    systemTray->setToolTip("SystemTray Program");
    QMenu *systemTrayMenu = new QMenu();
    QObject::connect(systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), mainWindow,
            SLOT(onSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
    systemTrayMenu->addAction("Open Main Window", mainWindow, SLOT(onBtnShowClicked()));
    systemTrayMenu->addAction("Quit", mainWindow, SLOT(onBtnCloseClicked()));
    systemTray->setContextMenu(systemTrayMenu);
    systemTray->show();
}