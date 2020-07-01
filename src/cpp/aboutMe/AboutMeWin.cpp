//
// Created by 刘镇 on 2020/6/20.
//

#include "AboutMeWin.h"
#include "ui_AboutMeWin.h"

AboutMeWin::AboutMeWin(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AboutMeWin) {
    ui->setupUi(this);
    this->setWindowTitle("About Me");
    this->setProperty("CanMove", true);
    auto *scene = new QGraphicsScene();
    auto *image = new QImage(":/static/avatar.jpg");
    scene->addPixmap(QPixmap::fromImage(*image));
    setWindowFlag(Qt::FramelessWindowHint, true);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    this->show();
}