//
// Created by 刘镇 on 2020/6/4.
//

#ifndef C__FINALWORK_PASTELABEL_H
#define C__FINALWORK_PASTELABEL_H

#include <QLabel>

class PasteLabel : public QLabel{
    Q_OBJECT
public:
    explicit PasteLabel(QWidget * parent, QString path);
    ~PasteLabel();
    PasteLabel(const PasteLabel&);

signals:
    void pasteHide();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
private slots:
    void onZoomInImage();
    void onZoomOutImage();
private:
    QPoint mousePoint;
    bool mouse_press;
    int pixmapWidth;
    int pixmapHeight;
    qreal zoomTimes=1.0;
};

#endif //C__FINALWORK_PASTELABEL_H
