#include "Screen.h"
#include <iostream>
#include <painterTool/PainterTool.h>

Screen::Screen(QWidget *parent, bool isExternalScreen) :
        QDialog(0) {
    initParams(isExternalScreen);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeGrabScreen()));
    timer->start(1000);
    connect(this, SIGNAL(beginToGrabSig()), this, SLOT(stopTimer()));
    menu = new QMenu(this);//创建右键菜单
    menu->addAction("复制(CTRL+C)", this, SLOT(copyScreen()));
    menu->addAction("截图另存为(ALT+C)", this, SLOT(saveScreenOther()));
    menu->addAction("全屏截图(ALT+A)", this, SLOT(grabFullScreen()));
    menu->addAction("退出截图(ESC)", this, SLOT(hide()));
    connect(this, SIGNAL(grabSuccess()), parent, SLOT(initFileList()));
    this->setWindowFlags(Qt::Tool);
    this->setStyleSheet("QDialog{background-color: rgba(255, 255, 255, 0);}");
//    setWindowOpacity(0);
}

void Screen::initParams(bool isExternalScreen) {
    beginPos = QPoint(-1, -1);
    endPos = beginPos;
    leftPres = false;
    resize_ = false;
    move_ = false;
    rect_ = new QRect(0, 0, QApplication::screens()[(int) isExternalScreen]->size().width(),
                      QApplication::screens()[(int) isExternalScreen]->size().height());
    mark_length_l = 50;
    mark_length_w = 50;
    mark_width_ = 15;
    mark_color_ = QColor(52, 228, 252);
    setMouseTracking(true);//开启鼠标实时追踪，实时的显示鼠标的位置
    this->isExternalScreen = isExternalScreen;
}

void Screen::copyScreen() //将截图复制到粘贴板
{
    QGuiApplication::clipboard()->setPixmap(fullScreen.copy(*rect_));
}

void Screen::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    this->setCursor(Qt::ArrowCursor);//设置鼠标的样式为箭头
    menu->exec(cursor().pos());//菜单显示的位置跟随鼠标
}

void Screen::mousePressEvent(QMouseEvent *e)       //--鼠标按下事件
{
    //添加menu->isActiveWindow()条件是为了在右键菜单时不进行截图区域调整
    if (!resize_ && e->button() == Qt::LeftButton && !menu->isActiveWindow())//鼠标左键按下
    {
        emit beginToGrabSig();
        leftPres = true;
        setBeginPos(e->pos());//鼠标相对窗体的位置，记录截图的开始位置
    }
    if (resize_ && e->button() == Qt::LeftButton && !menu->isActiveWindow()) {
        containedRectInfer(e->pos(), true);
        if (buttom_press_type == None && this->rect_->contains(e->pos())) {
            move_ = true;
        }
        leftPres = true;
        setMoveBeginPos(e->pos());
        painterTool->hide();
    }
}

void Screen::mouseMoveEvent(QMouseEvent *e)    //--鼠标移动事件
{
    if (resize_ && !leftPres) {
        containedRectInfer(e->pos(), false);
        update();
    }
    if (!resize_ && leftPres) {
        setEndPos(e->pos());//不断的更新截图的结束位置
        update();//重绘、触发画图事件
    }
    if (resize_ && move_ && leftPres) {
        setMoveEndPos(e->pos());
        QPoint removePath = moveEndPos - moveBeginPos;
        beginPos.setX(beginPos.x() + removePath.x());
        beginPos.setY(beginPos.y() + removePath.y());
        endPos.setX(endPos.x() + removePath.x());
        endPos.setY(endPos.y() + removePath.y());
        rect_->setRect(beginPos.x(), beginPos.y(), endPos.x() - beginPos.x(), endPos.y() - beginPos.y());
        update();
        setMoveBeginPos(e->pos());
    } else if (resize_ && leftPres) {
        setMoveEndPos(e->pos());
        switch (buttom_press_type) {
            case Left:
            case Right:
                horizontalZoom();
                break;
            case Top:
            case Bottom:
                verticalZoom();
                break;
            case LeftBottom:
            case RightTop:
            case LeftTop:
            case RightBottom:
                diagonalZoom();
                break;
            default:
                break;
        }
        update();
        setMoveBeginPos(e->pos());
    }
    update();
}

void Screen::mouseReleaseEvent(QMouseEvent *e) //--鼠标释放（松开）事件
{
    //使得起始点在左上角，结束点在右下角
    if (beginPos.x() > endPos.x()) {
        beginPos.setX(beginPos.x() + endPos.x());
        endPos.setX(beginPos.x() - endPos.x());
        beginPos.setX(beginPos.x() - endPos.x());
    }
    if (beginPos.y() > endPos.y()) {
        beginPos.setY(beginPos.y() + endPos.y());
        endPos.setY(beginPos.y() - endPos.y());
        beginPos.setY(beginPos.y() - endPos.y());
    }
    rect_->setRect(beginPos.x(), beginPos.y(), endPos.x() - beginPos.x(), endPos.y() - beginPos.y());

    if (resize_ && this->painterTool != nullptr) {
        leftPres = false;
        move_ = false;

        this->painterTool->move(rect_->x() + rect_->width() - this->painterTool->width(),
                                rect_->y() + rect_->height());
        this->painterTool->show();
        return;
    }
    if (!resize_ && e->button() == Qt::LeftButton)//鼠标左键释放
    {
        leftPres = false;
        setEndPos(e->pos());//记录截图的结束位置

        this->painterTool = new PainterTool(this);
        this->painterTool->move(endPos.x() - this->painterTool->width(), endPos.y() + mark_width_);
        this->painterTool->show();
    }
    if (!resize_)
        resize_ = true;
}

QPoint Screen::getBeginPos() {
    return beginPos;
}

QPoint Screen::getEndPos() {
    return endPos;
}

QPoint Screen::getMoveBeginPos() {
    return moveBeginPos;
}

QPoint Screen::getMoveEndPos() {
    return moveEndPos;
}

void Screen::setBeginPos(QPoint p) {
    this->beginPos = p;
}

void Screen::setEndPos(QPoint p) {
    this->endPos = p;
}

void Screen::setMoveBeginPos(QPoint p) {
    this->moveBeginPos = p;
}

void Screen::setMoveEndPos(QPoint p) {
    this->moveEndPos = p;
}

void Screen::horizontalZoom() {
    QPoint removePath = moveEndPos - moveBeginPos;
    if (buttom_press_type == Left) {
        beginPos.setX(beginPos.x() + removePath.x());
    } else {
        endPos.setX(endPos.x() + removePath.x());
    }
    rect_->setRect(beginPos.x(), beginPos.y(), endPos.x() - beginPos.x(), endPos.y() - beginPos.y());
}

void Screen::verticalZoom() {
    QPoint removePath = moveEndPos - moveBeginPos;
    if (buttom_press_type == Top) {
        beginPos.setY(beginPos.y() + removePath.y());
    } else {
        endPos.setY(endPos.y() + removePath.y());
    }
    rect_->setRect(beginPos.x(), beginPos.y(), endPos.x() - beginPos.x(), endPos.y() - beginPos.y());
}

void Screen::diagonalZoom() {
    QPoint removePath = moveEndPos - moveBeginPos;
    if (buttom_press_type == LeftTop) {
        beginPos.setX(beginPos.x() + removePath.x());
        beginPos.setY(beginPos.y() + removePath.y());
    } else if (buttom_press_type == LeftBottom) {
        beginPos.setX(beginPos.x() + removePath.x());
        endPos.setY(endPos.y() + removePath.y());
    } else if (buttom_press_type == RightBottom) {
        endPos.setX(endPos.x() + removePath.x());
        endPos.setY(endPos.y() + removePath.y());
    } else if (buttom_press_type == RightTop) {
        endPos.setX(endPos.x() + removePath.x());
        beginPos.setY(beginPos.y() + removePath.y());
    }
    rect_->setRect(beginPos.x(), beginPos.y(), endPos.x() - beginPos.x(), endPos.y() - beginPos.y());
}

void Screen::paintEvent(QPaintEvent *) {
    QPainter painter(this); //将当前窗体对象设置为画布
    QPen pen;
    pen.setColor(Qt::white);//设置笔色
    pen.setWidth(1);     //画笔线条宽度
    painter.setPen(pen);

    this->rx = beginPos.x() < endPos.x() ? beginPos.x() : endPos.x();//矩形截图区域左上角x坐标
    this->ry = beginPos.y() < endPos.y() ? beginPos.y() : endPos.y();//矩形截图区域右上角x坐标
    this->rw = beginPos.x() < endPos.x() ? endPos.x() - beginPos.x() : beginPos.x() - endPos.x();//矩形截图区域宽度
    this->rh = beginPos.y() < endPos.y() ? endPos.y() - beginPos.y() : beginPos.y() - endPos.y();//矩形截图区域高度

    QRect rect = QRect(rx, ry, rw, rh);//矩形截图区域
    if (rx != -1 && rw > 0 && rh > 0)//防止第一次就重绘 并且宽高大于0时才进行截图操作
    {
        painter.drawPixmap(rect, fullScreen, rect);//重绘截图矩形部分，即恢复原图，达到去除幕布效果
        painter.drawRect(rx, ry, rw, rh);//画截图矩形
        this->drawResizeMark(painter);
        //截图区域大小位置提示
        if (ry > 10)//避免看不到提示,在截图矩形上边不接近屏幕上边时，提示在截图矩形的上边的上面
        {
            painter.drawText(rx + 2, ry - 8,
                             tr("Zoom Range:(%1,%2) - (%3,%4)  Zoom Size:(%5 x %6)")
                                     .arg(rx).arg(ry).arg(rx + rw)
                                     .arg(ry + rh).arg(rw).arg(rh));
        } else//在截图矩形上边接近屏幕上边时，提示在截图矩形的上边的下面
        {
            painter.drawText(rx + 2, ry + 12,
                             tr("Zoom Range:(%1,%2) - (%3,%4)  Zoom Size:(%5 x %6)")
                                     .arg(rx).arg(ry).arg(rx + rw)
                                     .arg(ry + rh).arg(rw).arg(rh));
        }
    }
    initRectBottom(painter);
    drawResizeMark(painter);

    //实时显示鼠标的位置
    if (!resize_) {
        painter.drawText(cursor().pos().x(), cursor().pos().y(),
                         tr("(%1,%2)").arg(cursor().pos().x()).arg(cursor().pos().y()));
    } else {
        painter.drawText(endPos.x(), endPos.y(),
                         tr("(%1,%2)").arg(endPos.x()).arg(endPos.y()));
    }
    magnifierGlass(painter);
}

void Screen::showEvent(QShowEvent *) //--窗体show事件
{
    //设置透明度实现模糊背景
    setWindowOpacity(0.7);
}

void Screen::saveScreen() {
    QString fileName =
            SCREEN_CACHE + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".bmp";
    fullScreen.copy(*rect_).save(fileName, "bmp");
    this->close();
    emit grabSuccess();
}

void Screen::saveScreenOther()//截图另存为
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "截图另存为", "test.bmp", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0) {
        fullScreen.copy(*rect_).save(fileName, "bmp");
        this->close();
    }
}

void Screen::grabFullScreen()//全屏截图
{
    endPos.setX(-1);//此时避免画截图矩形
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "保存全屏截图", "test.bmp", "Image Files (*.bmp)");

    if (fileName.length() > 0) {
        fullScreen.save(fileName, "bmp");
        close();
    }
    this->hide();
}

void Screen::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) {
        hide();
    } else if (e->key() == Qt::Key_C && e->modifiers() == Qt::ControlModifier) {
        QGuiApplication::clipboard()->setPixmap(fullScreen.copy(*rect_));
    } else if (e->key() == Qt::Key_C && e->modifiers() == Qt::AltModifier) {
        saveScreenOther();
    } else if (e->key() == Qt::Key_A && e->modifiers() == Qt::AltModifier) {
        grabFullScreen();
    } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        saveScreen();
    } else if (e->key() == Qt::Key_S) {
        isRGB = !isRGB;
        update();
    } else if (e->key() == Qt::Key_C) {
        QApplication::clipboard()->setText(cursorPixColor);
    } else {
        e->ignore();
    }
}

void Screen::drawResizeMark(QPainter &painter) {
    switch (resize_type_) {
        case Right: {
            painter.fillRect(rightRect, mark_color_);
            break;
        }
        case Left: {
            painter.fillRect(leftRect, mark_color_);
            break;
        }
        case Bottom: {
            painter.fillRect(bottomRect, mark_color_);
            break;
        }
        case Top: {
            painter.fillRect(topRect, mark_color_);
            break;
        }
        case RightBottom: {
            painter.fillRect(rightBottom_l, mark_color_);
            painter.fillRect(rightBottom_w, mark_color_);
            break;
        }
        case RightTop: {
            painter.fillRect(rightTop_w, mark_color_);
            painter.fillRect(rightTop_l, mark_color_);
            break;
        }
        case LeftTop: {
            painter.fillRect(leftTop_w, mark_color_);
            painter.fillRect(leftTop_l, mark_color_);
            break;
        }
        case LeftBottom: {
            painter.fillRect(leftBottom_l, mark_color_);
            painter.fillRect(leftBottom_w, mark_color_);
            break;
        }
        default: {
            break;
        }
    }
}

void Screen::initRectBottom(QPainter &painter) {
    int centerX = (endPos.x() + beginPos.x()) / 2;
    int centerY = (endPos.y() + beginPos.y()) / 2;
    this->mark_length_l = this->rect_->height() / 8;
    this->mark_length_w = this->rect_->width() / 8;
    int lessLen;

    if (mark_length_l > mark_length_w) {
        lessLen = mark_length_w;
    } else { lessLen = mark_length_l; }

    this->mark_width_ = lessLen / 5;
    if (mark_width_ < 5) {
        mark_width_ = 5;
    } else if (mark_width_ > 12) {
        mark_width_ = 12;
    }

    rightRect = QRect(endPos.x() - mark_width_ / 2,
                      centerY - mark_length_l,
                      mark_width_,
                      mark_length_l * 2);
    leftRect = QRect(beginPos.x() - mark_width_ / 2,
                     centerY - mark_length_l,
                     mark_width_,
                     mark_length_l * 2);
    bottomRect = QRect(centerX - mark_length_w,
                       endPos.y() - mark_width_ / 2,
                       mark_length_w * 2,
                       mark_width_);
    topRect = QRect(centerX - mark_length_w,
                    beginPos.y() - mark_width_ / 2,
                    mark_length_w * 2,
                    mark_width_);
    rightBottom_l = QRect(endPos.x() - mark_width_ / 2,
                          endPos.y() - lessLen + mark_width_ / 2,
                          mark_width_,
                          lessLen);
    rightBottom_w = QRect(endPos.x() - lessLen + mark_width_ / 2,
                          endPos.y() - mark_width_ / 2,
                          lessLen,
                          mark_width_);
    rightTop_w = QRect(endPos.x() - lessLen + mark_width_ / 2,
                       beginPos.y() - mark_width_ / 2,
                       lessLen,
                       mark_width_);
    rightTop_l = QRect(endPos.x() - mark_width_ / 2,
                       beginPos.y() - mark_width_ / 2,
                       mark_width_,
                       lessLen);
    leftTop_w = QRect(beginPos.x() - mark_width_ / 2,
                      beginPos.y() - mark_width_ / 2,
                      lessLen,
                      mark_width_);
    leftTop_l = QRect(beginPos.x() - mark_width_ / 2,
                      beginPos.y() - mark_width_ / 2,
                      mark_width_,
                      lessLen);
    leftBottom_l = QRect(beginPos.x() - mark_width_ / 2,
                         endPos.y() - lessLen + mark_width_ / 2,
                         mark_width_,
                         lessLen);
    leftBottom_w = QRect(beginPos.x() - mark_width_ / 2,
                         endPos.y() - mark_width_ / 2,
                         lessLen,
                         mark_width_);
}

void Screen::containedRectInfer(QPoint pos, bool isPress) {
    if (isPress) {
        if (this->rect_->contains(pos)) {
            setCursor(Qt::CrossCursor);
        }
        if (topRect.contains(pos)) {
            buttom_press_type = Top;
            setCursor(Qt::SizeVerCursor);
        } else if (bottomRect.contains(pos)) {
            buttom_press_type = Bottom;
            setCursor(Qt::SizeVerCursor);
        } else if (leftRect.contains(pos)) {
            buttom_press_type = Left;
            setCursor(Qt::SizeHorCursor);
        } else if (rightRect.contains(pos)) {
            buttom_press_type = Right;
            setCursor(Qt::SizeHorCursor);
        } else if (leftTop_l.contains(pos) || leftTop_w.contains(pos)) {
            buttom_press_type = LeftTop;
            setCursor(Qt::SizeFDiagCursor);
        } else if (rightTop_l.contains(pos) || rightTop_w.contains(pos)) {
            buttom_press_type = RightTop;
            setCursor(Qt::SizeBDiagCursor);
        } else if (leftBottom_l.contains(pos) || leftBottom_w.contains(pos)) {
            buttom_press_type = LeftBottom;
            setCursor(Qt::SizeBDiagCursor);
        } else if (rightBottom_l.contains(pos) || rightBottom_w.contains(pos)) {
            buttom_press_type = RightBottom;
            setCursor(Qt::SizeFDiagCursor);
        } else if (!this->rect_->contains(pos)) {
            buttom_press_type = None;
            setCursor(Qt::ArrowCursor);
        }
    } else {
        if (this->rect_->contains(pos)) {
            setCursor(Qt::CrossCursor);
        }
        if (topRect.contains(pos)) {
            resize_type_ = Top;
            setCursor(Qt::SizeVerCursor);
        } else if (bottomRect.contains(pos)) {
            resize_type_ = Bottom;
            setCursor(Qt::SizeVerCursor);
        } else if (leftRect.contains(pos)) {
            resize_type_ = Left;
            setCursor(Qt::SizeHorCursor);
        } else if (rightRect.contains(pos)) {
            resize_type_ = Right;
            setCursor(Qt::SizeHorCursor);
        } else if (leftTop_l.contains(pos) || leftTop_w.contains(pos)) {
            resize_type_ = LeftTop;
            setCursor(Qt::SizeFDiagCursor);
        } else if (rightTop_l.contains(pos) || rightTop_w.contains(pos)) {
            resize_type_ = RightTop;
            setCursor(Qt::SizeBDiagCursor);
        } else if (leftBottom_l.contains(pos) || leftBottom_w.contains(pos)) {
            resize_type_ = LeftBottom;
            setCursor(Qt::SizeBDiagCursor);
        } else if (rightBottom_l.contains(pos) || rightBottom_w.contains(pos)) {
            resize_type_ = RightBottom;
            setCursor(Qt::SizeFDiagCursor);
        } else if (!this->rect_->contains(pos)) {
            resize_type_ = None;
            setCursor(Qt::ArrowCursor);
        }
    }
}

void Screen::changeGrabScreen() {
//    hide();
//    this->fullScreen = QApplication::screens()[(int) this->isExternalScreen]->grabWindow(0);
//    show();
}

void Screen::stopTimer() {
    timer->stop();
}

void Screen::magnifierGlass(QPainter &painter) {
    int cursorX = (int) cursor().pos().x();
    int cursorY = (int) cursor().pos().y();
    if (resize_ && !move_ && !rect_->contains(cursorX, cursorY)) {
        return;
    }
    int pixX = cursorX + 20;
    int pixY = cursorY + 20;
    int winH = (int) winSize.height();
    int winW = (int) winSize.width();
    QPixmap glassRect = fullScreen.copy(cursorX - winW / magnificationTimes / 2,
                                        cursorY - winH * split / magnificationTimes / 2,
                                        winW / magnificationTimes,
                                        winH * split / magnificationTimes);
    painter.drawPixmap(pixX, pixY,
                       winW,
                       winH, glassRect);
    QPixmap cursorPix = glassRect.copy(winW / magnificationTimes / 2,
                                       winH * split / magnificationTimes / 2,
                                       1, 1);//截图1个像素
    QColor color = cursorPix.toImage().pixel(0, 0);
    if (color.red() > 100 && color.blue() > 100 && color.green() > 100)    //调节方框颜色，使得更容易区分
        painter.setPen(QColor(0, 0, 0));
    else
        painter.setPen(QColor(255, 255, 255));
    // 解释背景方块
    painter.fillRect(pixX, pixY + winH,
                     winW, winH * (1 - split),
                     QColor(0, 0, 0));
    // 色块
    painter.fillRect(pixX + winW / 20, pixY + winH + winH / 20, winW / 4, winH / 5, color);
    // 准心  外准心
    painter.drawRect(pixX + winW / 2, pixY + winH / 2,
                     10, 14);
    painter.drawRect(pixX + winW / 2, pixY + winH / 2,
                     10, 14);

    // 准心 内准心
    painter.fillRect(pixX + winW / 2, pixY + winH / 2,
                     10, 14, color);
    painter.drawRect(pixX, pixY + winH / 2,
                     winW, 14);
    painter.drawRect(pixX + winW / 2, pixY,
                     10, winH);

    painter.setPen(QColor(255, 255, 255));
    // 解释区域边框
    painter.drawRect(pixX, pixY + winH,
                     winW, winH * (1 - split));
    // 放大区域边框
    painter.drawRect(pixX, pixY, winW, winH);
    // 解释语言
    QString theColor;
    if (isRGB) {
        theColor = QString().sprintf("%d, %d, %d", color.red(), color.green(),
                                     color.blue());
        painter.drawText(pixX + winW / 20 + winW / 4 + winW / 20, pixY + winH + winH / 8, "RGB");
        painter.drawText(pixX + winW / 20 + winW / 4 + winW / 20, pixY + winH + winH / 4,
                         theColor);       //根据透明度算法复原原色素值
    } else {
        theColor = QString("#") + QString::number(color.red(), 16).right(2) +
                   QString::number(color.green(), 16).right(2) +
                   QString::number(color.blue(), 16).right(2);
        painter.drawText(pixX + winW / 20 + winW / 4 + winW / 20, pixY + winH + winH / 8, "HEX");
        painter.drawText(pixX + winW / 20 + winW / 4 + winW / 20, pixY + winH + winH / 4,
                         theColor);
    }
    cursorPixColor = theColor;
}