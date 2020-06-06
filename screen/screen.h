#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>//右键菜单
#include <QPaintEvent>
#include <QPainter>//画笔
#include <QPixmap>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>
#include <QShowEvent>
#include <QClipboard>
#include <QKeyEvent>
#include <QRect>
#include <QFile>
#include <widget/Widget.h>
#include <painterTool/PainterTool.h>

enum ResizeType
{
    None,
    Left,
    Right,
    Top,
    Bottom,
    LeftTop,
    RightTop,
    LeftBottom,
    RightBottom
};

class Screen : public QDialog {
Q_OBJECT
public:
    explicit Screen(QWidget *parent=0, bool isExternalScreen = false);

signals:
    void grabSuccess();
private slots:
    void saveScreen();
    void saveScreenOther();//截图另存为
    void grabFullScreen();//全屏截图
    void copyScreen(); //右键复制到粘贴板
protected:
    void contextMenuEvent(QContextMenuEvent *);  //--右键菜单事件
    void mousePressEvent(QMouseEvent *e);       //--鼠标按下事件
    void mouseMoveEvent(QMouseEvent *e);       //--鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *e);   //--鼠标释放（松开）事件
    void paintEvent(QPaintEvent *);          //--画图事件
    void showEvent(QShowEvent *);           //--窗体show事件
    void keyPressEvent(QKeyEvent *e);      //--按键事件
    void initParams(bool);
    void drawResizeMark(QPainter &);
private:
    QPoint beginPos;//记录鼠标的起始位置
    QPoint endPos;//记录鼠标的结束位置
    QMenu *menu; //右键菜单对象
    bool leftPres;//记录鼠标左键是否按下，按下为true
    bool resize_ = false;
    bool move_;
    QRect *rect_; //矩形截图区域
    PainterTool * painterTool = nullptr;
    int markWide_;
    int markLength_;
    int markMarginBoard_;
    QColor markColor_;
private:
public:
    QPixmap fullScreen;//全屏截图

public:
    QPoint getBeginPos();//获取鼠标的起始位置
    QPoint getEndPos();//获取鼠标的结束位置
    void setBeginPos(QPoint p);//设置鼠标的起始位置
    void setEndPos(QPoint p);//设置鼠标的结束位置
};

#endif // SCREEN_H
