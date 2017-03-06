#include "mydialog.h"
#include "ui_mydialog.h"
#include <QDesktopWidget>
#include <QDebug>

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowTitle("提示");
    m_pTextLabel = ui->Textlabel;
    m_pOKPushButton = ui->OKpushButton;
    m_pCancelPushButton = ui->CancelpushButton;
    this->setWindowModality(Qt::ApplicationModal);
//    this->setMinimumSize(400,200);
//    this->setMaximumSize(400,200);
    m_Font.setPixelSize(20);
    m_pTextLabel->setFont(m_Font);
    m_pOKPushButton->setMinimumSize(100,39);
    m_pOKPushButton->setMaximumSize(100,39);
    m_pOKPushButton->setStyleSheet(DIALOGOKPNG);
    m_pCancelPushButton->setMinimumSize(100,39);
    m_pCancelPushButton->setMaximumSize(100,39);
    m_pCancelPushButton->setStyleSheet(DIALOGCANCELPNG);
   // this->setAttribute(Qt::WA_TranslucentBackground);
   // this->setStyleSheet("background:rgba(255,255,255,0);border:none;");
    ui->title_bar->setStyleSheet("background-color: rgb(0,123,214)");
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(exit_widget()));
    ui->btnClose->setVisible(true);
    this->move(QApplication::desktop()->width()/2 - width()/2, QApplication::desktop()->height()/2 - height()/2);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_OKpushButton_clicked()
{

    switch(m_flag)
    {
        case SHUTDOWN:system("shutdown -h now");
        break;
    }

    this->close();
}

void MyDialog::on_CancelpushButton_clicked()
{
    this->close();
}

void MyDialog::setText(QString Text)
{
    m_pTextLabel->setText(Text);
}
void MyDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
   // painter.drawPixmap(0,0,width(),height(),QPixmap(DIALOGPNG));

}

void MyDialog::exit_widget()
{
    close();
}

void MyDialog::setNetOff(QString text, int flag)
{
    m_flag = flag;
    m_content = text;
    m_pTextLabel->setText(text);
    m_nCount = 10;
    m_timer = NULL;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(1000);
}

void MyDialog::update()
{
    if (m_nCount == 0)
    {
        if (m_timer != NULL)
        {
            m_timer->stop();
            delete m_timer;
            m_timer = NULL;
            this->hide();
        }
    }
    QString str;
    str = str.number(m_nCount, 10);
    QString strMsg;
    strMsg = m_content + " " + "(" + str + ")";
    qDebug() << strMsg;
    m_pTextLabel->setText(strMsg);
    m_nCount--;
}
