#include "Widget.h"
#include "ui_widget.h"
#include "screen/Screen.h"
#include "systemTray/systemTray.h"
#include "lowLevelKeyBoardHook/LowLevelKeyBoardHook.h"
#include "pasteLabel/PasteLabel.h"
#include <functional>
#include <algorithm>


Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget) {
    ui->setupUi(this);
    beginPos = this->pos();
    leftPress = false;
    this->setProperty("CanMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint |
                         Qt::WindowStaysOnTopHint);
    this->desktopWidget = QApplication::desktop();
    LowLevelKeyboardHook *globalKBHook = new LowLevelKeyboardHook();
    globalKBHook->setKeyboardCall(std::bind(&Widget::switchSlots, this, std::placeholders::_1));
    mySystemTray::systemTrayInit(this);
    initFileList(true);
}

Widget::~Widget() {
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)//鼠标左键按下
    {
        leftPress = true;
        beginPos = e->pos();//鼠标相对窗体的位置
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if (leftPress) {//当前鼠标相对窗体的位置-刚按下左键时的相对位置=鼠标移动的大小
        this->move(e->pos() - beginPos + this->pos());
        //           鼠标移动的大小+窗体原来的位置=窗体移动后的位置
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    leftPress = false;
}

void Widget::enterEvent(QEvent *e)
{
    if (this->pos().y() <= 0)
    {
        move(pos().x(), 0);
    }

}

void Widget::leaveEvent(QEvent *e)
{
    if (this->pos().y() <= 0)
    {
        move(pos().x(), -29);
    }
}

void Widget::onBtnShowClicked() {
    this->show();
}

void Widget::onBtnHideClicked() {
    this->hide();
}

void Widget::onBtnFullScreenClicked()
{
    //获取全屏截图
    QPixmap qPixmap = QApplication::primaryScreen()->grabWindow(this->desktopWidget->winId());
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "", tr("Config Files (*.bmp)"));
    if (fileName.length() > 0 && qPixmap.save(fileName, "bmp")) {
        QMessageBox::information(this, "Tips:", "Save successfully!", QMessageBox::Ok);
    }
}

void Widget::onBtnRectScreenClicked()
{
    if (windowState() != Qt::WindowMinimized) {
        setWindowState(Qt::WindowMinimized);
    }
    QTime _Timer = QTime::currentTime().addMSecs(0);
    while (QTime::currentTime() < _Timer) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    if(desktopWidget->screenCount() != 1){
        adjustCurrentScreen();
    }
    auto *m = new Screen(this);
//    while(!beginToGrap) {
    m->fullScreen = QApplication::screens()[(int) this->isExternScreen]->grabWindow(0);
    m->showFullScreen();
//    }
}

void Widget::onBtnMinClicked()
{
    if (windowState() != Qt::WindowMinimized) {
        setWindowState(Qt::WindowMinimized);
    }
}

void Widget::onSystemTrayClicked(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;
        case QSystemTrayIcon::Unknown:
        case QSystemTrayIcon::Context:
        case QSystemTrayIcon::MiddleClick:
            break;
    }
}

void Widget::onBtnCloseClicked()
{
    this->close();
}

void Widget::onBtnPasteClicked() {
    new PasteLabel(this, this->pasteCacheList[offset--]);
}

void Widget::switchSlots(int vkCode) {
    switch(vkCode){
        case VK_F1:{
            onBtnRectScreenClicked();
            return;
        }
        case VK_F3:{
            if(offset != -1) {
                onBtnPasteClicked();
            }
            return;
        }
        default:{return;}
    }
}

void Widget::initFileList(bool isInit){
    QDir *pasteCacheDir = new QDir(SCREEN_CACHE);
    QStringList filter;
    filter<<"*.bmp";
    pasteCacheDir->setNameFilters(filter);
    QList<QFileInfo> tempList = *new QList<QFileInfo>(pasteCacheDir->entryInfoList(filter));
    std::sort(tempList.begin(), tempList.end(), [](QFileInfo a, QFileInfo b){return a.fileName() < b.fileName();});
    if(isInit)
        cleanInvalidFiles(tempList);
    this->pasteCacheList = tempList;
    this->pasteCacheListSize = tempList.size();
    this->offset = tempList.size() - 1;
}

void Widget::closePaste(QFileInfo file){
    pasteCacheList.move(this->pasteCacheList.indexOf(file), offset + 1);
    ++offset;
}

void Widget::cleanInvalidFiles(QList<QFileInfo> & tempList){
    if(tempList.size()>20){
        tempList.erase(tempList.begin()+20, tempList.end());
    }
    qint64 cacheTime = QDateTime::currentDateTime().addDays(-2).toMSecsSinceEpoch();
    QString cacheTimeFileName = QString::number(cacheTime) + ".bmp";
    for(const auto& file: tempList){
        if(file.fileName() < cacheTimeFileName){
            file.dir().remove(file.fileName());
            tempList.removeOne(file);
        }
    }
}

void Widget::adjustCurrentScreen() {
    POINT mousePos;
    GetCursorPos(&mousePos);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    if(mousePos.x > width || mousePos.x < 0 || mousePos.y > height || mousePos.y < 0 )
    {
//        this->desktopWidget->setGeometry()
        this->isExternScreen = true;
    }
    this->isExternScreen = false;
}