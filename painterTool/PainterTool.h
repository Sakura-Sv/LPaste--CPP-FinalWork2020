//
// Created by 刘镇 on 2020/6/5.
//

#ifndef C__FINALWORK_PAINTERTOOL_H
#define C__FINALWORK_PAINTERTOOL_H

#include <QWidget>

namespace Ui{
    class PainterTool;
}

class PainterTool : public QWidget {
Q_OBJECT

signals:
    void saveSgn();

public:
    PainterTool(QWidget *);

protected:

private:
    Ui::PainterTool *ui;
private slots:
    void saveScreen();
};


#endif //C__FINALWORK_PAINTERTOOL_H
