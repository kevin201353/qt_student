#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    m_pTextLabel = ui->Textlabel;
    m_pOKPushButton = ui->OKpushButton;
    m_pCancelPushButton = ui->CancelpushButton;
    this->setWindowModality(Qt::ApplicationModal);
    this->setMinimumSize(400,200);
    this->setMaximumSize(400,200);
    m_Font.setPixelSize(15);
    m_pTextLabel->setFont(m_Font);
    m_pOKPushButton->setMinimumSize(149,39);
    m_pOKPushButton->setMaximumSize(149,39);
    m_pOKPushButton->setStyleSheet(DIALOGOKPNG);
    m_pCancelPushButton->setMinimumSize(149,39);
    m_pCancelPushButton->setMaximumSize(149,39);
    m_pCancelPushButton->setStyleSheet(DIALOGCANCELPNG);
    this->setWindowTitle("提示");
   // this->setAttribute(Qt::WA_TranslucentBackground);
   // this->setStyleSheet("background:rgba(255,255,255,0);border:none;");
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
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
