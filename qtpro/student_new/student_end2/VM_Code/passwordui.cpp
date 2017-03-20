#include "passwordui.h"
#include "ui_passwordui.h"
#include "QCryptographicHash"
#include <QByteArray>
#include <QDesktopWidget>
#include "mydialog.h"

#define SH_PASS_CONFIG   "admin"

bool PasswordUI::m_isAdjust = false;
PasswordUI::PasswordUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordUI)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
    ui->frame_title->setStyleSheet("background-color: rgb(0,123,214)");
    connect(ui->btn_exit, SIGNAL(clicked(bool)), this, SLOT(exit_widget()));
    connect(ui->btn_OK, SIGNAL(clicked(bool)), this, SLOT(OnOk()));
    connect(ui->btn_Cancel, SIGNAL(clicked(bool)), this, SLOT(OnCancel()));
    this->move(QApplication::desktop()->width()/2 - width()/2, QApplication::desktop()->height()/2 - height()/2);
    QByteArray ba, bb;
    QString pwd = SH_PASS_CONFIG;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(pwd);
    md.addData(ba);
    bb = md.result();
    m_strPassword.append(bb.toHex());
    m_isAdjust = false;
    ui->label_pass->setText("输入密码：");
    ui->btn_OK->setText("确定");
    ui->btn_Cancel->setText("取消");
    ui->lineEdit_pass->setText("");
    ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    this->hide();
}

PasswordUI::~PasswordUI()
{
    delete ui;
}


void PasswordUI::OnOk()
{
    m_isAdjust = false;
    QString strPass = ui->lineEdit_pass->text();
    QString newpass;
    QByteArray ba, bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(strPass);
    md.addData(ba);
    bb = md.result();
    newpass.append(bb.toHex());
    if (m_strPassword == newpass)
    {
        m_isAdjust = true;
        emit ShowPassUI();
    }else
    {
        MyDialog *pshutdlg = new MyDialog();
        pshutdlg->setText("密码错误！");
        pshutdlg->setFlag(PASSFAILD);
        pshutdlg->show();
    }
}

void PasswordUI::OnCancel()
{
    this->close();
}

void PasswordUI::exit_widget()
{
    this->close();
}

bool PasswordUI::isAdjustPass()
{
    return m_isAdjust;
}
