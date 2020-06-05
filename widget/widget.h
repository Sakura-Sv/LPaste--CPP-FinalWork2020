#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets/QtWidgets>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

public slots:

    void onBtnShowClicked();

    void onBtnHideClicked();

    void onSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);

    void onBtnFullScreenClicked();

    void onBtnRectScreenClicked();

    void onBtnMinClicked();

    void onBtnCloseClicked();

    void onBtnPasteClicked();

    void switchSlots(int vkCode);

    void initFileList(bool isInit = false);

    void rollbackOffset();

protected:
    void enterEvent(QEvent *e);  //--鼠标进入事件
    void leaveEvent(QEvent *e);  //--鼠标离开事件
    void mousePressEvent(QMouseEvent *e);       //--鼠标按下事件
    void mouseMoveEvent(QMouseEvent *e);       //--鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *e);   //--鼠标释放（松开）事件
    void cleanInvalidFiles(QList<QFileInfo> &);
    void systemTrayInitFinished();
private:
    Ui::Widget *ui;
private:
    bool leftPress;
    QPoint beginPos;
    QList<QFileInfo> pasteCacheList;
    int pasteCacheListSize;
    int offset;
};

#endif // WIDGET_H
