#include "setform.h"
#include "ui_setform.h"
#include "netconfig.h"
#include <pthread.h>
#include "include.h"

extern NetConfig   *g_pNetConfig;
SetForm::SetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetForm)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()& ~Qt::WindowMinMaxButtonsHint);
    this->setFixedSize(this->width(), this->height());
    this->setWindowTitle("设置");
    m_Font.setPixelSize(15);
    m_pSavePushButton = ui->SavepushButton;
    m_pCancelPushButton = ui->CancelpushButton;
    m_pSetTabWidget = ui->SetTabWidget;
    m_pSetTabWidget->setFont(m_Font);
    m_pSetTabWidget->setTabText(0,"网络设置");
    m_pSetTabWidget->setTabText(1,"系统设置");

    m_pSavePushButton->setFont(m_Font);
    m_pSavePushButton->setText("保存");
    m_pSavePushButton->setStyleSheet("background-color:rgb(0,123,214);color:rgb(255,255,255)");

    m_pCancelPushButton->setFont(m_Font);
    m_pCancelPushButton->setStyleSheet("background-color:rgb(0,123,214);color:rgb(255,255,255)");
    m_pCancelPushButton->setText("取消");

    m_IPGroupBox = ui->IPgroupBox;
    m_DNSGroupBox = ui->DNSgroupBox;
    m_IPGroupBox->setTitle("IP设置");
    m_DNSGroupBox->setTitle("DNS设置");

    m_pIPLineEdit = ui->IPlineEdit;
    m_pChildIPLineEdit = ui->ChildIPlineEdit;
    m_pGetWayLineEdit = ui->GetWaylineEdit;
    m_pDNS1LineEdit = ui->DNS1lineEdit;
    m_pDNS2LineEdit = ui->DNS2lineEdit;
    m_pDNS3LineEdit = ui->DNS3lineEdit;

    QRegExp    RegIPLineEdit("(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])");       //expand reg
    m_pRegValue = new QRegExpValidator(RegIPLineEdit);

    m_pIPLineEdit->setValidator(m_pRegValue);
    m_pChildIPLineEdit->setValidator(m_pRegValue);
    m_pGetWayLineEdit->setValidator(m_pRegValue);
    m_pDNS1LineEdit->setValidator(m_pRegValue);
    m_pDNS2LineEdit->setValidator(m_pRegValue);
    m_pDNS3LineEdit->setValidator(m_pRegValue);

    m_pAutoSetIP = ui->AutoSetIPradioButton;
    m_pAutoSetDNS = ui->AutoSetDNSradioButton;
    m_pNoDHCPSetDNS = ui->ManualSetDNSradioButton;
    m_pNoDHCPSetIP = ui->ManualSetIPradioButton;
    m_pLoagingFrame = new LoadingFrame(this);
    m_pLoagingFrame->hide();
}

SetForm::~SetForm()
{
    delete m_pRegValue;
    delete ui;
}
void SetForm::SetIPLineEdit(const char *ip)
{
    QString IP(ip);
    m_pIPLineEdit->setText(IP);
}
void SetForm::SetMaskIPLineEdit(const char *ip)
{
    QString IP(ip);
    m_pChildIPLineEdit->setText(IP);
}
void SetForm::SetGateWayIPLineEdit(const char *ip)
{
    QString IP(ip);
    m_pGetWayLineEdit->setText(IP);
}
void SetForm::SetDNS1LineEdit(const char *ip)
{
    QString IP(ip);
    m_pDNS1LineEdit->setText(IP);
}
void SetForm::SetDNS2LineEdit(const char *ip)
{
    QString IP(ip);
    m_pDNS2LineEdit->setText(IP);
}
void SetForm::SetDNS3LineEdit(const char *ip)
{
    QString IP(ip);
    m_pDNS3LineEdit->setText(IP);
}
void SetForm::on_CancelpushButton_clicked()
{
    this->close();
}

void SetForm::on_AutoSetIPradioButton_clicked(bool checked)
{
    if(checked)
    {
        m_bDHCP_IP = true;
        m_pIPLineEdit->setEnabled(false);
        m_pChildIPLineEdit->setEnabled(false);
        m_pGetWayLineEdit->setEnabled(false);
        m_pAutoSetDNS->setEnabled(true);
    }
}

void SetForm::on_ManualSetIPradioButton_clicked(bool checked)
{
    if(checked)
    {
        m_bDHCP_IP = false;
        m_pIPLineEdit->setEnabled(true);
        m_pChildIPLineEdit->setEnabled(true);
        m_pGetWayLineEdit->setEnabled(true);
        m_pAutoSetDNS->setEnabled(false);
        m_pNoDHCPSetDNS->setChecked(true);
        on_ManualSetDNSradioButton_clicked(true);
    }
}

void SetForm::on_AutoSetDNSradioButton_clicked(bool checked)
{
    if(checked)
    {
        m_bDHCP_DNS = true;
        m_pDNS1LineEdit->setEnabled(false);
        m_pDNS2LineEdit->setEnabled(false);
        m_pDNS3LineEdit->setEnabled(false);
    }
}

void SetForm::on_ManualSetDNSradioButton_clicked(bool checked)
{
    if(checked)
    {
        m_bDHCP_DNS = false;
        m_pDNS1LineEdit->setEnabled(true);
        m_pDNS2LineEdit->setEnabled(true);
        m_pDNS3LineEdit->setEnabled(true);
    }
}
void *SystemThread(void *param)
{
   SetForm *pTemp = (SetForm *)param;
   char SystemCmd[1024];
   memset(SystemCmd,0,1024);
   sprintf(SystemCmd,"sudo ifdown %s",ETH0);
   system(SystemCmd);
   memset(SystemCmd,0,1024);
   sprintf(SystemCmd,"sudo ifup %s",ETH0);
   system(SystemCmd);

   pTemp->SetLoadingFram(false);
   pTemp->SetSalveEnable(true);

}
void SetForm::on_SavepushButton_clicked()
{
    pthread_t pid;
    memset(g_pNetConfig->m_pNetConfig,0,sizeof(g_pNetConfig->m_pNetConfig));
    g_pNetConfig->m_pNetConfig->s_bDNS = m_bDHCP_DNS;
    g_pNetConfig->m_pNetConfig->s_bIP = m_bDHCP_IP;
    strcpy(g_pNetConfig->m_pNetConfig->s_strIP,m_pIPLineEdit->text().toStdString().c_str());
    strcpy(g_pNetConfig->m_pNetConfig->s_strIPMask,m_pChildIPLineEdit->text().toStdString().c_str());
    strcpy(g_pNetConfig->m_pNetConfig->s_strGateWay,m_pGetWayLineEdit->text().toStdString().c_str());

    strcpy(g_pNetConfig->m_pNetConfig->s_strDNS[0],m_pDNS1LineEdit->text().toStdString().c_str());
    strcpy(g_pNetConfig->m_pNetConfig->s_strDNS[1],m_pDNS2LineEdit->text().toStdString().c_str());
    strcpy(g_pNetConfig->m_pNetConfig->s_strDNS[2],m_pDNS3LineEdit->text().toStdString().c_str());

    g_pNetConfig->WriteFile();

    m_pLoagingFrame->show();
    m_pSavePushButton->setEnabled(false);
    if(pthread_create(&pid,NULL,SystemThread,this))
    {
        printf("Create Thread Error!\n");
    }
}

void SetForm::on_ClassRoomNumllineEdit_textEdited(const QString &arg1)
{
    memset(g_strRoomNum,0,10);
    strcpy(g_strRoomNum,arg1.toStdString().c_str());
}

void SetForm::on_SeatNumlineEdit_textEdited(const QString &arg1)
{
    memset(g_strSeatNum,0,10);
    strcpy(g_strSeatNum,arg1.toStdString().c_str());
}
