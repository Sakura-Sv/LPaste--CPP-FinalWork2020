#include "Screen.h"
#include <QDir>
#include <QDateTime>
#include <iostream>
#include <painterTool/PainterTool.h>

Screen::Screen(QWidget *parent, bool isExternalScreen) :
        QDialog(0) {
    initParams(isExternalScreen);
    menu = new QMenu(this);//创建右键菜单
    menu->addAction("复制(CTRL+C)", this, SLOT(copyScreen()));
    menu->addAction("截图另存为(ALT+C)", this, SLOT(saveScreenOther()));
    menu->addAction("全屏截图(ALT+A)", this, SLOT(grabFullScreen()));
    menu->addAction("退出截图(ESC)", this, SLOT(hide()));
    connect(this, SIGNAL(grabSuccess()), parent, SLOT(initFileList()));
    this->setWindowFlags(Qt::Tool);
}

void Screen::initParams(bool isExternalScreen){
    beginPos = QPoint(-1, -1);
    endPos = beginPos;
    leftPres = false;
    resize_ = false;
    move_ = false;
    rect_ = new QRect(0, 0, QApplication::screens()[(int)isExternalScreen]->size().width(), QApplication::screens()[(int)isExternalScreen]->size().height());
    setCursor(Qt::CrossCursor);
    setMouseTracking(true);//开启鼠标实时追踪，实时的显示鼠标的位置
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
    if (e->button() == Qt::LeftButton && !menu->isActiveWindow())//鼠标左键按下
    {
        leftPres = true;
        setBeginPos(e->pos());//鼠标相对窗体的位置，记录截图的开始位置
    }
}

void Screen::mouseMoveEvent(QMouseEvent *e)    //--鼠标移动事件
{
    if (leftPres) {
        setEndPos(e->pos());//不断的更新截图的结束位置
        update();//重绘、触发画图事件
    }

}

void Screen::mouseReleaseEvent(QMouseEvent *e) //--鼠标释放（松开）事件
{
    if(resize_ && this->painterTool != nullptr){
        return;
    }
    if (e->button() == Qt::LeftButton)//鼠标左键释放
    {
        leftPres = false;
        setEndPos(e->pos());//记录截图的结束位置

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
    }
    this->painterTool = new PainterTool(this);
    this->painterTool->move(endPos.x() - this->painterTool->width(), endPos.y());
    this->painterTool->show();
    if(!resize_)
        resize_ = true;
}

QPoint Screen::getBeginPos() {
    return beginPos;
}

QPoint Screen::getEndPos() {
    return endPos;
}

void Screen::setBeginPos(QPoint p) {
    this->beginPos = p;
}

void Screen::setEndPos(QPoint p) {
    this->endPos = p;
}

void Screen::paintEvent(QPaintEvent *) {

    QPainter painter(this); //将当前窗体对象设置为画布
    QPen pen;
    pen.setColor(Qt::red);//设置笔色
    pen.setWidth(1);     //画笔线条宽度
    painter.setPen(pen);//设置画笔

    int lx = beginPos.x() < endPos.x() ? beginPos.x() : endPos.x();//矩形截图区域左上角x坐标
    int ly = beginPos.y() < endPos.y() ? beginPos.y() : endPos.y();//矩形截图区域右上角x坐标
    int w = beginPos.x() < endPos.x() ? endPos.x() - beginPos.x() : beginPos.x() - endPos.x();//矩形截图区域宽度
    int h = beginPos.y() < endPos.y() ? endPos.y() - beginPos.y() : beginPos.y() - endPos.y();//矩形截图区域高度

    QRect rect = QRect(lx, ly, w, h);//矩形截图区域
    if (!resize_ && lx != -1 && w > 0 && h > 0)//防止第一次就重绘 并且宽高大于0时才进行截图操作
    {
        painter.drawPixmap(rect, fullScreen, rect);//重绘截图矩形部分，即恢复原图，达到去除幕布效果
        painter.drawRect(lx, ly, w, h);//画截图矩形
        this->drawResizeMark(painter);
        //截图区域大小位置提示
        if (ly > 10)//避免看不到提示,在截图矩形上边不接近屏幕上边时，提示在截图矩形的上边的上面
        {
            painter.drawText(lx + 2, ly - 8,
                             tr("Zoom Range:(%1,%2) - (%3,%4)  Zoom Size:(%5 x %6)").arg(lx).arg(ly).arg(lx + w).arg(ly + h).arg(
                                     w).arg(h));
        } else//在截图矩形上边接近屏幕上边时，提示在截图矩形的上边的下面
        {
            painter.drawText(lx + 2, ly + 12,
                             tr("Zoom Range:(%1,%2) - (%3,%4)  Zoom Size:(%5 x %6)").arg(lx).arg(ly).arg(lx + w).arg(ly + h).arg(
                                     w).arg(h));
        }
    }

    //实时显示鼠标的位置
    painter.drawText(cursor().pos().x(), cursor().pos().y(),
                     tr("(%1,%2)").arg(cursor().pos().x()).arg(cursor().pos().y()));
}

void Screen::showEvent(QShowEvent *) //--窗体show事件
{
    //设置透明度实现模糊背景
    setWindowOpacity(0.7);

}

void Screen::saveScreen() {
    QString fileName = QDir::currentPath() + "/screenCache/" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".bmp";
    fullScreen.copy(*rect_).save(fileName, "bmp");
    this->close();
    emit grabSuccess();
}

void Screen::saveScreenOther()//截图另存为
{
    QString fileName = QFileDialog::getSaveFileName(this, "截图另存为", "test.bmp", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0) {
        fullScreen.copy(*rect_).save(fileName, "bmp");
        this->close();
    }
}

void Screen::grabFullScreen()//全屏截图
{
    endPos.setX(-1);//此时避免画截图矩形
    QString fileName = QFileDialog::getSaveFileName(this, "保存全屏截图", "test.bmp", "Image Files (*.bmp)");

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
    } else {
        e->ignore();
    }
}

void Screen::drawResizeMark(QPainter &painter)
{
    int centerX = (endPos.x() - beginPos.x())/2;
    int centerY = (endPos.y() - beginPos.y())/2;
//    switch (resize_type_) {
//        case Right:{
//            QRect mark = QRect( f_width - mark_wide_,
//                                f_half_height - mark_length_,
//                                mark_wide_,
//                                mark_length_ + mark_length_);
//            painter.fillRect(mark, mark_color_);
//            break;
//        }
//        case Left:{
//            QRect mark = QRect( f_x,
//                                f_half_height - mark_length_,
//                                mark_wide_,
//                                mark_length_ + mark_length_);
//            painter.fillRect(mark, mark_color_);
//            break;
//        }
//        case Bottom:{
//            QRect mark = QRect( f_half_width - mark_length_,
//                                f_height - mark_wide_,
//                                mark_length_ + mark_length_,
//                                mark_wide_);
//            painter.fillRect(mark, mark_color_);
//            break;
//        }
//        case Top:{
//            QRect mark = QRect( f_half_width - mark_length_,
//                                f_y,
//                                mark_length_ + mark_length_,
//                                mark_wide_);
//            painter.fillRect(mark, mark_color_);
//            break;
//        }
//        case RightBottom:{
//            QRect mark1 = QRect( f_width - mark_wide_,
//                                 f_height - mark_length_,
//                                 mark_wide_,
//                                 mark_length_);
//            QRect mark2 = QRect( f_width - mark_length_,
//                                 f_height - mark_wide_,
//                                 mark_length_,
//                                 mark_wide_);
//            painter.fillRect(mark1, mark_color_);
//            painter.fillRect(mark2, mark_color_);
//            break;
//        }
//        case RightTop:{
//            QRect mark1 = QRect( f_width - mark_length_,
//                                 f_y,
//                                 mark_length_,
//                                 mark_wide_);
//            QRect mark2 = QRect( f_width - mark_wide_,
//                                 f_y,
//                                 mark_wide_,
//                                 mark_length_);
//            painter.fillRect(mark1, mark_color_);
//            painter.fillRect(mark2, mark_color_);
//            break;
//        }
//        case LeftTop:{
//            QRect mark1 = QRect(f_x,
//                                f_y,
//                                mark_length_,
//                                mark_wide_);
//            QRect mark2 = QRect(f_x,
//                                f_y,
//                                mark_wide_,
//                                mark_length_);
//            painter.fillRect(mark1, mark_color_);
//            painter.fillRect(mark2, mark_color_);
//            break;
//        }
//        case LeftBottom:{
//            QRect mark1 = QRect(f_x,
//                                f_height - mark_length_,
//                                mark_wide_,
//                                mark_length_);
//            QRect mark2 = QRect(f_x,
//                                f_height - mark_wide_,
//                                mark_length_,
//                                mark_wide_);
//            painter.fillRect(mark1, mark_color_);
//            painter.fillRect(mark2, mark_color_);
//            break;
//        }
//        default:{ break; }
//    }
}
