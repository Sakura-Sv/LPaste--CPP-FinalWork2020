//
// Created by 刘镇 on 2020/6/5.
//

#include "PainterTool.h"
#include "ui_PainterTool.h"
#include <iostream>

PainterTool::PainterTool(QWidget * parent):
    QWidget(parent),
    ui(new Ui::PainterTool) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint |
                         Qt::WindowStaysOnTopHint);
    connect(this, SIGNAL(saveSgn()), parent, SLOT(saveScreen()));
}

void PainterTool::saveScreen() {
    emit saveSgn();
}

void PainterTool::printOnScreen() {
    QMessageBox::warning(this, "In development!", "////////////////////////////", QMessageBox::Ok);
}

void PainterTool::unknown(){
    QMessageBox::warning(this, "In development!", "////////////////////////////", QMessageBox::Ok);
}

void PainterTool::rollback(){
    QMessageBox::warning(this, "In development!", "////////////////////////////", QMessageBox::Ok);
}

void PainterTool::goahead(){
    QMessageBox::warning(this, "In development!", "////////////////////////////", QMessageBox::Ok);
}