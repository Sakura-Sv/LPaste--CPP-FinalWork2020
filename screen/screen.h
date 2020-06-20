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
#include <QTimer>
#include <widget/Widget.h>
#include <painterTool/PainterTool.h>

enum ResizeType {
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

const QSize winSize(200,150);       //窗口尺寸
const int grabInterval=50;          //刷新频率
const int magnificationTimes=10;    //放大倍数
const double split=0.65;             //分割
const int sizeOfMouseIcon=20;       //鼠标图标大小

class Screen : public QDialog {
Q_OBJECT
public:
    explicit Screen(QWidget *parent = 0, bool isExternalScreen = false);

signals:

    void grabSuccess();

    void beginToGrabSig();

private slots:

    void saveScreen();

    void saveScreenOther();//截图另存为
    void grabFullScreen();//全屏截图
    void copyScreen(); //右键复制到粘贴板
    void changeGrabScreen();
    void stopTimer();
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

    void initRectBottom(QPainter &);

    void containedRectInfer(QPoint, bool);

    void magnifierGlass(QPainter &);

private:
    Q_DISABLE_COPY(Screen);
    QPoint beginPos;//记录鼠标的起始位置
    QPoint endPos;//记录鼠标的结束位置
    QPoint moveBeginPos;
    QPoint moveEndPos;
    QMenu *menu; //右键菜单对象
    bool leftPres;//记录鼠标左键是否按下，按下为true
    bool move_;
    bool resize_ = false;
    QRect *rect_; //矩形截图区域
    PainterTool *painterTool = nullptr;
    int rx;
    int ry;
    int rw;
    int rh;
    ResizeType resize_type_ = None;
    ResizeType buttom_press_type = None;
    int mark_width_;
    int mark_length_l; //竖直方向
    int mark_length_w; //水平方向
    QColor mark_color_;
    QRect topRect;
    QRect leftRect;
    QRect rightRect;
    QRect bottomRect;
    QRect leftTop_l;
    QRect leftTop_w;
    QRect leftBottom_l;
    QRect leftBottom_w;
    QRect rightTop_l;
    QRect rightTop_w;
    QRect rightBottom_l;
    QRect rightBottom_w;
    QTimer *timer;
    bool isExternalScreen=false;
    bool isRGB = true;
    QString cursorPixColor = "";
public:
    QPixmap fullScreen;//全屏截图

public:
    QPoint getBeginPos();//获取鼠标的起始位置
    QPoint getEndPos();//获取鼠标的结束位置
    QPoint getMoveBeginPos();//获取鼠标的起始位置
    QPoint getMoveEndPos();//获取鼠标的结束位置
    void setBeginPos(QPoint p);//设置鼠标的起始位置
    void setEndPos(QPoint p);//设置鼠标的结束位置
    void setMoveBeginPos(QPoint p);//设置鼠标的起始位置
    void setMoveEndPos(QPoint p);//设置鼠标的结束位置
    void horizontalZoom(); //水平放缩
    void verticalZoom(); //竖直放缩
    void diagonalZoom(); //斜向放缩
};

#endif // SCREEN_H
