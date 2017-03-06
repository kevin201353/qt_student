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

    QRegExp    RegIPLineEdit("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}"
                             "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");       //expand reg
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
    m_pServerIPLineEdit = ui->ServerIPlineEdit;
    m_pServerIPLineEdit->setValidator(m_pRegValue);
    m_pServerIPLineEdit->setText(g_strServerIP);
    m_pAutoSetIP->setText("DHCP动态获取");
    m_pAutoSetDNS->setText("DHCP动态获取");
    m_pNoDHCPSetDNS->setText("静态获取");
    m_pNoDHCPSetIP->setText("静态获取");
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
////////////////////////////
bool SetForm::isInvalidNetmask(const char *subnet)
{
    unsigned int b = 0, n[4];
    sscanf(subnet, "%u.%u.%u.%u", &n[3], &n[2], &n[1], &n[0]);
    for(int i = 0; i < 4; i++)
        b += n[i] << (i * 8);
    b = ~b + 1;
    if((b & (b - 1)) == 0)
        return false;
    return true;
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

    g_pMyHttp->SetUrlIP(pTemp->m_strServerIP);
    memset(g_strServerIP,0,25);
    strncpy(g_strServerIP,pTemp->m_strServerIP.toStdString().c_str(),25);
    WriteConfigString(CONFIGNAME,"ROOM","ServiceIP",g_strServerIP);

    pTemp->SetLoadingFram(false);
    //pTemp->SetSalveEnable(true);
    pTemp->setEnabled(true);

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
    this->setEnabled(false);
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

void SetForm::on_ServerIPlineEdit_textChanged(const QString &arg1)
{
    m_strServerIP = arg1;
}

void SetForm::on_IPlineEdit_textChanged(const QString &arg1)
{
    if(!arg1.length())
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pIPLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
        return ;
    }
     QString args = arg1;
    int iRecode = 0;
    int pos;
    iRecode = m_pRegValue->validate(args,pos);
    if(iRecode == 1)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        m_pIPLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(false);
    }
    if(iRecode == 2)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pIPLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
    }
}

void SetForm::on_ChildIPlineEdit_textChanged(const QString &arg1)
{
    if(!arg1.length())
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pChildIPLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
        return ;
    }
     QString args = arg1;
    int iRecode = 0;
    int pos;
    iRecode = m_pRegValue->validate(args,pos);
    if(iRecode == 1)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        m_pChildIPLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(false);
    }
    if(iRecode == 2)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pChildIPLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
    }
}

void SetForm::on_GetWaylineEdit_textChanged(const QString &arg1)
{
    if(!arg1.length())
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pGetWayLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
        return ;
    }
     QString args = arg1;
    int iRecode = 0;
    int pos;
    iRecode = m_pRegValue->validate(args,pos);
    if(iRecode == 1)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        m_pGetWayLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(false);
    }
    if(iRecode == 2)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pGetWayLineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
    }
}

void SetForm::on_DNS1lineEdit_textChanged(const QString &arg1)
{
    if(!arg1.length())
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pDNS1LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
        return ;
    }
     QString args = arg1;
    int iRecode = 0;
    int pos;
    iRecode = m_pRegValue->validate(args,pos);
    if(iRecode == 1)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        m_pDNS1LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(false);
    }
    if(iRecode == 2)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pDNS1LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
    }
}

void SetForm::on_DNS2lineEdit_textChanged(const QString &arg1)
{
    if(!arg1.length())
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pDNS2LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
        return ;
    }
     QString args = arg1;
    int iRecode = 0;
    int pos;
    iRecode = m_pRegValue->validate(args,pos);
    if(iRecode == 1)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        m_pDNS2LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(false);
    }
    if(iRecode == 2)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pDNS2LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
    }
}

void SetForm::on_DNS3lineEdit_textChanged(const QString &arg1)
{
    if(!arg1.length())
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pDNS3LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
        return ;
    }
     QString args = arg1;
    int iRecode = 0;
    int pos;
    iRecode = m_pRegValue->validate(args,pos);
    if(iRecode == 1)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::red);
        m_pDNS3LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(false);
    }
    if(iRecode == 2)
    {
        QPalette palette;
        palette.setColor(QPalette::Text,Qt::black);
        m_pDNS3LineEdit->setPalette(palette);
        m_pSavePushButton->setEnabled(true);
    }
}
