//
// Created by 刘镇 on 2020/6/20.
//

#ifndef C__FINAL2020_ABOUTMEWIN_H
#define C__FINAL2020_ABOUTMEWIN_H

#include<QWidget>
#include <QDialog>

namespace Ui {
    class AboutMeWin;
}

const QString AVATAR_PATH = ":/static/avatar.jpg";

class AboutMeWin : public QDialog {
Q_OBJECT

public:
    explicit AboutMeWin(QWidget *);

    ~AboutMeWin() {}

private:
    Ui::AboutMeWin *ui;
    Q_DISABLE_COPY(AboutMeWin);
};


#endif //C__FINAL2020_ABOUTMEWIN_H
