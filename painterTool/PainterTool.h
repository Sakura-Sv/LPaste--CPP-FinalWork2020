//
// Created by 刘镇 on 2020/6/5.
//

#ifndef C__FINALWORK_PAINTERTOOL_H
#define C__FINALWORK_PAINTERTOOL_H

#include <QWidget>
#include <QtWidgets/QMessageBox>

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
    Q_DISABLE_COPY(PainterTool);
private slots:
    void saveScreen();
    void printOnScreen();
    void unknown();
    void rollback();
    void goahead();
};


#endif //C__FINALWORK_PAINTERTOOL_H
