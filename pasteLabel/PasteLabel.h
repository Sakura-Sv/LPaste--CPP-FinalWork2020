//
// Created by 刘镇 on 2020/6/4.
//

#ifndef C__FINALWORK_PASTELABEL_H
#define C__FINALWORK_PASTELABEL_H

#include <QLabel>
#include <QtCore/QFileInfo>

class PasteLabel : public QLabel{
    Q_OBJECT
public:
    explicit PasteLabel(QWidget * parent, QFileInfo file);
    ~PasteLabel();

signals:
    void pasteHide(QFileInfo file);
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
    Q_DISABLE_COPY(PasteLabel);
    QFileInfo file;
    QPoint mousePoint;
    bool mouse_press;
    int pixmapWidth;
    int pixmapHeight;
    qreal zoomTimes=1.0;
};

#endif //C__FINALWORK_PASTELABEL_H
