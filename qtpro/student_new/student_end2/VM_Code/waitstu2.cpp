#include "waitstu2.h"
#include "ui_waitstu2.h"
#include <QPainter>
#include <QDesktopWidget>
#include <QDebug>
#include <QPalette>

#define DESKTOPMAP3   "/usr/local/shencloud/image1/50_22.png"

waitstu2::waitstu2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waitstu2)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
//    this->setWindowFlags(this->windowFlags()& ~Qt::WindowMinMaxButtonsHint);
//    QDesktopWidget *desktopWidget = QApplication::desktop();
//    QRect deskRect = desktopWidget->availableGeometry();
//    this->setGeometry(QRect((deskRect.width() - width())/2, (deskRect.height() - this->height())/2, width(), height()));
    QPixmap pixmap(DESKTOPMAP3);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

waitstu2::~waitstu2()
{
    delete ui;
}

void waitstu2::waitstushow()
{
    this->showFullScreen();
}

void waitstu2::waitstuhide()
{
    this->hide();
}
