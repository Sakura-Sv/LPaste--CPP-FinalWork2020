//
// Created by 刘镇 on 2020/6/4.
//

#include <QtWidgets/QLabel>
#include <QMouseEvent>
#include <iostream>
#include "PasteLabel.h"

PasteLabel::PasteLabel(QWidget *parent, QFileInfo file) : QLabel() {
    this->mouse_press = false;
    this->file = file;
    connect(this, SIGNAL(pasteHide(QFileInfo)), parent, SLOT(closePaste(QFileInfo)));
    this->setPixmap(*new QPixmap(file.absoluteFilePath()));
    this->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    this->setMinimumSize(200, 200);
    this->setCursor(Qt::SizeFDiagCursor);
    this->pixmapWidth = this->pixmap()->width();
    this->pixmapHeight = this->pixmap()->height();
    this->setScaledContents(true);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::Tool |
                         Qt::WindowStaysOnTopHint);
    this->show();
}

PasteLabel::~PasteLabel() {}

void PasteLabel::mousePressEvent(QMouseEvent *event) {
    if ((event->button() == Qt::LeftButton)) {
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
    }
}

void PasteLabel::mouseMoveEvent(QMouseEvent *event) {
    if (mouse_press) {
        move(event->globalPos() - mousePoint);
    }
}

void PasteLabel::mouseReleaseEvent(QMouseEvent *event) {
    mouse_press = false;
}

void PasteLabel::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        hide();
        emit pasteHide(file);
    } else {
        event->ignore();
    }
}

void PasteLabel::wheelEvent(QWheelEvent *event) {
    if (event->delta() > 0)
        onZoomInImage();
    else
        onZoomOutImage();
}

void PasteLabel::onZoomInImage() {
    zoomTimes += 0.05;
    this->resize(zoomTimes * this->pixmapWidth, zoomTimes * this->pixmapHeight);
}

void PasteLabel::onZoomOutImage() {
    zoomTimes -= 0.05;
    this->resize(zoomTimes * this->pixmapWidth, zoomTimes * this->pixmapHeight);
}
