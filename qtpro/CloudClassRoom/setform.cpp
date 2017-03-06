#include "setform.h"
#include "ui_setform.h"
#include "netconfig.h"
#include <pthread.h>
#include "myhttp.h"
#include "include.h"
#include "ryanConfig.h"

extern NetConfig   *g_pNetConfig;
extern myHttp       *g_pMyHttp;

SetForm::SetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetForm)
{

    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()& ~Qt::WindowMinMaxButtonsHint);
    this->setFixedSize(this->width(), this->height());
    this->setWindowTitle("设置");
   // this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    m_Font.setPixelSize(15);
    m_pSavePushButton = ui->SavepushButton;
    m_pCancelPushButton = ui->CancelpushButton;
    m_pSetTabWidget = ui->SetTabWidget;
    m_pSetTabWidget->setFont(m_Font);
    m_pSetTabWidget->setTabText(0,"网络设置");
    m_pSetTabWidget->setTabText(1,"系统设置");

    m_pSavePushButton->setFont(m_Font);
    m_pSavePushButton->setText("保存");
    m_pSavePushButton->setStyleSheet("background-color:rgb(1,123,214);color:rgb(255,255,255)");

    m_pCancelPushButton->setFont(m_Font);
    m_pCancelPushButton->setStyleSheet("background-color:rgb(1,123,214);color:rgb(255,255,255)");
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
    m_pServerIPLineEdit = ui->ServerIPlineEdit;
    m_pRoomNumLineEdit = ui->RoomNumlineEdit;

    QRegExp    RegIPLineEdit("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}"
                             "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");       //expand reg
    m_pRegValue = new QRegExpValidator(RegIPLineEdit);

    m_pIPLineEdit->setValidator(m_pRegValue);
    m_pChildIPLineEdit->setValidator(m_pRegValue);
    m_pGetWayLineEdit->setValidator(m_pRegValue);
    m_pDNS1LineEdit->setValidator(m_pRegValue);
    m_pDNS2LineEdit->setValidator(m_pRegValue);
    m_pDNS3LineEdit->setValidator(m_pRegValue);
    m_pServerIPLineEdit->setValidator(m_pRegValue);
    m_pServerIPLineEdit->setText(g_strServerIP);
    m_pRoomNumLineEdit->setText(g_strRoomNum);
    m_StrRoomNum = m_pRoomNumLineEdit->text();
    m_StrServerIP = m_pServerIPLineEdit->text();
    g_pMyHttp->SetUrlIP(m_StrServerIP);
    m_pAutoSetIP = ui->AutoSetIPradioButton;
    m_pAutoSetDNS = ui->AutoSetDNSradioButton;
    m_pNoDHCPSetDNS = ui->ManualSetDNSradioButton;
    m_pNoDHCPSetIP = ui->ManualSetIPradioButton;
    m_pLoagingFrame = new LoadingFrame(this);
    m_pLoagingFrame->hide();
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
    myHttp http;
   SetForm *pTemp = (SetForm *)param;
   char SystemCmd[1024];
   memset(SystemCmd,0,1024);
   sprintf(SystemCmd,"sudo ifdown %s",ETH0);
   system(SystemCmd);
   memset(SystemCmd,0,1024);
   sprintf(SystemCmd,"sudo ifup %s",ETH0);
   system(SystemCmd);


   strncpy(g_strRoomNum,pTemp->m_pRoomNumLineEdit->text().toStdString().c_str(),100);
   strncpy(g_strServerIP,pTemp->m_pServerIPLineEdit->text().toStdString().c_str(),25);
   // sleep(5);
   WriteConfigString(CONFIGNAME,"ROOM","ClassName",g_strRoomNum);
   WriteConfigString(CONFIGNAME,"ROOM","ServiceIP",g_strServerIP);
   http.SetUrlIP(g_strServerIP);
   g_pMyHttp->SetUrlIP(pTemp->m_StrServerIP);

////////////////////////////////
   char TempBuf[1024];
   char JsonBuf[10240];
   char strTerminalID[100];
   NetConfig netconfig;
   memset(JsonBuf,0,10240);
   memset(TempBuf,0,1024);
   memset(strTerminalID,0,100);
   netconfig.GetMacAdd(strTerminalID,false);
   sprintf(TempBuf,"/service/aps/configure?id=%s&roomName=%s&seat=",strTerminalID,g_strRoomNum);
   g_pLog->WriteLog(0,"UP SeatNum RoomNum:%s",TempBuf);
  // qDebug("TempBuf:%s",TempBuf);
   http.Get(TempBuf);
   http.GetData(JsonBuf);
  // qDebug("UP SeatNum RoomNum%s\n",JsonBuf);
   g_pLog->WriteLog(0,"Recv Json:%s",JsonBuf);
////////////////////////////////////////////////
   pTemp->SetLoadingFram(false);
   //pTemp->SetSalveEnable(true);
   pTemp->setEnabled(true);
}
bool SetForm::isInvalidNetmask(const char *subnet)
{
    unsigned int b = 0, n[4];
    sscanf(subnet, "%u.%u.%u.%u", &n[3], &n[2], &n[1], &n[0]);
    for(int i = 0; i < 4; i++)
        b += n[i] << (i * 8);
    b = ~b + 1;
    if((b & (b - 1)) == 0)
        return 0;
    return 1;
}
void SetForm::on_SavepushButton_clicked()
{
    pthread_t pid;

    bool failed = true;
    QMessageBox msgBox(this);
    QPushButton *ensureButton = msgBox.addButton(tr("确 定"), QMessageBox::ActionRole);
    msgBox.setWindowTitle("提示");
    msgBox.setIcon(QMessageBox::Warning);

    if(m_pIPLineEdit->text().isEmpty())
        msgBox.setText("保存配置失败，IP地址不能为空！");
    else if(m_pIPLineEdit->text().count('.') != 3 || m_pIPLineEdit->text().section('.', -1).isEmpty())
        msgBox.setText("保存配置失败，无效的IP地址！");
    else if(m_pChildIPLineEdit->text().isEmpty())
        msgBox.setText("保存配置失败，子网掩码不能为空！");
    else if(m_pChildIPLineEdit->text().count('.') != 3 ||
            m_pChildIPLineEdit->text().section('.', -1).isEmpty() ||
            isInvalidNetmask(m_pChildIPLineEdit->text().toStdString().c_str()))
        msgBox.setText("保存配置失败，无效的子网掩码！");
    else if(m_pGetWayLineEdit->text().isEmpty())
        msgBox.setText("保存配置失败，默认网关不能为空！");
    else if(m_pGetWayLineEdit->text().count('.') != 3 || m_pGetWayLineEdit->text().section('.', -1).isEmpty())
        msgBox.setText("保存配置失败，无效的默认网关！");
    else if(m_pDNS1LineEdit->text().isEmpty())
        msgBox.setText("保存配置失败，首选 DNS 服务器不能为空！");
    else if(!(m_pDNS1LineEdit->text().isEmpty()) && (m_pDNS1LineEdit->text().count('.') != 3 || m_pDNS1LineEdit->text().section('.', -1).isEmpty()))
        msgBox.setText("保存配置失败，无效的备选 DNS 服务器地址！");
    else if(!(m_pDNS2LineEdit->text().isEmpty()) && (m_pDNS2LineEdit->text().count('.') != 3 || m_pDNS2LineEdit->text().section('.', -1).isEmpty()))
        msgBox.setText("保存配置失败，无效的备选 DNS 服务器地址！");
    else if(!(m_pDNS3LineEdit->text().isEmpty()) && (m_pDNS3LineEdit->text().count('.') != 3 || m_pDNS3LineEdit->text().section('.', -1).isEmpty()))
        msgBox.setText("保存配置失败，无效的备选 DNS 服务器地址！");
    else if(!(m_pServerIPLineEdit->text().isEmpty()) && (m_pServerIPLineEdit->text().count('.') != 3 || m_pServerIPLineEdit->text().section('.', -1).isEmpty()))
        msgBox.setText("保存配置失败，无效的服务器地址！");

    else
    {
        msgBox.setIcon(QMessageBox::NoIcon);
        msgBox.setText("保存配置成功！");
        failed = false;
    }
    if(failed)
    {
        msgBox.show();
        msgBox.exec();
        if(msgBox.clickedButton() == ensureButton)
            msgBox.close();
        if(failed)
            return ;
    }

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

void SetForm::on_ServerIPlineEdit_textChanged(const QString &arg1)
{
    m_StrServerIP = arg1;
//    memset(g_strServerIP,0,sizeof(g_strServerIP));
//    strcpy(g_strServerIP,m_StrServerIP.toStdString().c_str());
}

void SetForm::on_RoomNumlineEdit_textEdited(const QString &arg1)
{
    m_StrRoomNum = arg1;
//    memset(g_strRoomNum,0,sizeof(g_strRoomNum));
//    strcpy(g_strRoomNum,m_StrRoomNum.toStdString().c_str());
}
/*
void SetForm::changeEvent(QEvent *event)
{
    if(event->type() != QEvent::WindowStateChange)
        return ;
    if(this->windowState() == Qt::WindowMinimized)
    {
        this->close();
    }
}
*/
