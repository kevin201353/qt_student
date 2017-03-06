#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "include.h"


void *WhileFun(void *param);
void *InitThread(void *param);
LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
/////////////////////////////Set UI//////////////////////////////////////////////
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->resize(g_ScreenWidth,g_ScreenHeight);
    m_pUserNameLogo = ui->UserNamelabel;
    m_pUserNameLogo->setPixmap(QPixmap(USRLOGO));

    m_pPasswdLogo = ui->Passwdlabel;
    m_pPasswdLogo->setPixmap(QPixmap(PASSWDLOGO));

    m_pLogoQLable = ui->Logolabel;
//    m_pLogoQLable->setAlignment(Qt::AlignCenter);
//    m_pLogoQLable->setPixmap(QPixmap(LOGOPNG));

    m_pShencloudNamelabel = ui->ShencloudNamelabel;
//    m_Font.setPixelSize(46);
//    m_pShencloudNamelabel->setFont(m_Font);
//    m_pShencloudNamelabel->setAlignment(Qt::AlignCenter);
//    m_pShencloudNamelabel->setStyleSheet("color: rgb(233,75,38)");
//    m_pShencloudNamelabel->setText("神云云教室");

    m_pShencloudNamelabel->setAlignment(Qt::AlignCenter);
    m_pShencloudNamelabel->setPixmap(QPixmap(LOGOPNG));

    m_pTimeLCDNumber = ui->TimeLcdNumber;
    m_pUserNameLineEdit = ui->UserNamelineEdit;
    m_pPasswdLineEdit = ui->PasswdlineEdit;
    m_pLoginPushButton = ui->LoginpushButton;
    m_pSoftInforLabel = ui->Informationlabel;
    m_Font.setPixelSize(19);
    m_pSoftInforLabel->setFont(m_Font);
    m_pSoftInforLabel->setStyleSheet("color: rgb(95,93,93)");
    m_pServerManPushButton = ui->ServerManpushButton;
    m_pSetPushButton = ui->SetpushButton;
    m_pInformationPushButton = ui->InformationpushButton;
    m_pShutdownPushButton = ui->ShutdownpushButton;
    setTabOrder(m_pUserNameLineEdit,m_pPasswdLineEdit);
    setTabOrder(m_pPasswdLineEdit,m_pLoginPushButton);
    //setTabOrder(m_pLoginPushButton,m_pUserNameLineEdit);
    m_pPasswdLineEdit->setEchoMode(QLineEdit::Password);
    m_pTimeLCDNumber->setDigitCount(25);
    m_pTimeLCDNumber->setMode(QLCDNumber::Dec);
    m_pTimeLCDNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pTimeLCDNumber->setFrameShape(QLCDNumber::NoFrame);
   // m_pTimeLCDNumber->setStyleSheet("font: 190pt");

    m_pSetPushButton->setStyleSheet(QStringLiteral(SETLOGO));
    m_pSetPushButton->setMinimumSize(37,36);
    m_pSetPushButton->setFlat(false);

    m_pInformationPushButton->setStyleSheet(QStringLiteral(INFORMATIONLOGO));
    m_pInformationPushButton->setMinimumSize(39,39);
    m_pInformationPushButton->setFlat(false);

    m_pServerManPushButton->setStyleSheet(QStringLiteral(SERVERMANLOGO));
    m_pServerManPushButton->setMinimumSize(34,34);
    m_pServerManPushButton->setFlat(false);

    m_pLoginPushButton->setStyleSheet(QStringLiteral(LOGINLOGO));
    m_pLoginPushButton->setMinimumSize(296,51);

    m_pShutdownPushButton->setStyleSheet(QStringLiteral(SHUTDOWNLOGO));
    m_pShutdownPushButton->setMinimumSize(33,37);
    m_pShutdownPushButton->setFlat(false);
   // QFont ft;
    m_pUserNameLineEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background:rgba(255,0,0,0)}");
    m_pPasswdLineEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background:rgba(255,0,0,0)}");
    m_Font.setPointSize(12);
    m_pUserNameLineEdit->setFont(m_Font);
    m_pPasswdLineEdit->setFont(m_Font);
///////////////////new person Class////////////////////////////////////////
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    m_pTime = new QDateTime();
    m_pTimer->start();
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(OnTimeOut()));
    g_pMyDialog = new MyDialog();
    m_pLoadingFrame = new LoadingFrame(this);
    m_pLoadingFrame->hide();
/////////////////////////////New global Class//////////////////////////////////////////////////
    if(g_pMyHttp == NULL)
    {
        g_pMyHttp = new myHttp();
    }
    if(g_pTeacherForm == NULL)
    {
        g_pTeacherForm = new TeacherForm();
    }
    if(g_pNetConfig == NULL)
    {
        g_pNetConfig = new NetConfig();
    }
    if(g_pLog == NULL)
    {
        g_pLog = new Log();
        g_pLog->InitLog();
    }
    if(g_pProcess == NULL)
    {
        g_pProcess = new process();
        int iRecode = g_pProcess->Start();
        if(iRecode < 0)
        {
            printf("New process Error\n");
        }
    }
    qDebug("Start initializeLibrary");
    pthread_t pid;
    if(pthread_create(&pid,NULL,InitThread,this))
    {

    }
    g_pMyJson = new myJson();
    m_pSetForm = new SetForm();

    m_pServerManPushButton->hide();
    m_pInformationPushButton->hide();
}
void *InitThread(void *param)
{
    sleep(10);
    activemq::library::ActiveMQCPP::initializeLibrary();
    myHttp http;
    http.SetUrlIP(g_strServerIP);
    qDebug("Start runConsumer");
    if(g_Pconsume == NULL)
    {
        g_Pconsume = new ActiveMQConsumer();
        g_Pconsume->start(g_strConsumerAdd,g_strConsumerQueue,true,false);
        g_Pconsume->runConsumer();
    }
    qDebug("Start runProduce");
    if(g_Pproduce == NULL)
    {
        g_Pproduce = new ActiveMQProduce();
        g_Pproduce->start(g_strProduceAdd,20,g_strProduceQueue,false,false);
    }
    ////////////////////////////////////////////////////////////
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
    /////////////////////////////////////////////////////////////

}
void LoginWidget::OnTimeOut()
{
    *m_pTime = QDateTime::currentDateTime();
    m_pTimeLCDNumber->display(m_pTime->toString("yyyy-MM-dd HH:mm:ss"));
    g_pTeacherForm->SetClock(m_pTime);
}
LoginWidget::~LoginWidget()
{
    if(g_pTeacherForm)
    {
        delete g_pTeacherForm;
    }
    if(g_pNetConfig)
    {
        delete g_pNetConfig;
    }
    if(g_pLog)
    {
        delete g_pLog;
    }
    if(g_pMyHttp)
    {
        delete  g_pMyHttp;
    }
    if(g_pMyJson)
    {
        delete g_pMyJson;
    }
    if(m_pTime)
    {
        delete m_pTime;
    }
    if(g_pMyDialog)
    {
        delete g_pMyDialog;
    }
    if(g_pProcess)
    {
        delete g_pProcess;
    }
    if(g_Pconsume)
    {
        delete g_Pconsume;
    }
    delete ui;
}
const char *LoginWidget::GetUserName()
{
    return  m_UserName.toStdString().c_str();
}
const char *LoginWidget::GetPasswd()
{
    return m_Passwd.toStdString().c_str();
}

void LoginWidget::on_LoginpushButton_clicked()
{

    bool LoginFlag = false;
    char VMNameBuf[TEACHERVMNUM][100];
    int  VMStatus[TEACHERVMNUM];
    m_UserName = m_pUserNameLineEdit->text();
    m_Passwd = m_pPasswdLineEdit->text();
    m_pLoadingFrame->show();
    this->setEnabled(false);
    char TempBuf[100];
    char JsonBuf[202400];
    memset(TempBuf,0,100);
    sprintf(TempBuf,"username=%s&password=%s",m_UserName.toStdString().c_str()\
                    ,m_Passwd.toStdString().c_str());
    g_pLog->WriteLog(0,"Login %s",TempBuf);
    g_pMyHttp->Post("/service/users/login",TempBuf);

    memset(JsonBuf,0,202400);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Login Recv Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&LoginFlag,"success");
    if(LoginFlag)
    {
///////////////////////////Get Teacher VM////////////////////////////////////////////
        memset(TempBuf,0,100);
        sprintf(TempBuf,"/service/desktops/list?qp.filterWhere={\"type\":\"teacher\",\"seat\":\"%s\"}",\
                m_UserName.section('@',0,0).toStdString().c_str());
        g_pLog->WriteLog(0,"Get Teacher VM:%s",TempBuf);
        g_pMyHttp->Get(TempBuf);
        memset(JsonBuf,0,202400);
        g_pMyHttp->GetData(JsonBuf);
        g_pLog->WriteLog(0,"Get Teacher VM Recv Json:%s",JsonBuf);
        LoginFlag = false;
        g_pMyJson->Parse(JsonBuf);
        g_pMyJson->ReadJson(&LoginFlag,"success");
        if(LoginFlag)
        {
            memset(VMNameBuf,0,sizeof(VMNameBuf));
            int iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","list","name",TEACHERVMNUM);
            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
            {
                qDebug("Name[%d]:%s",i,VMNameBuf[i]);
                strncpy(g_TeacherVMSet.s_pVMInfo[i].s_strName,VMNameBuf[i],100);
            }

            iRecode = g_pMyJson->ReadJson(VMStatus,"data","list","status",TEACHERVMNUM);
            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
            {
                qDebug("Status[%d]:%d",i,VMStatus[i]);
                switch(VMStatus[i])
                {
                case 2:g_TeacherVMSet.s_pVMInfo[i].s_VMStatus = USING;
                    break;
                case 1:g_TeacherVMSet.s_pVMInfo[i].s_VMStatus = CLOSE;
                    break;
                case 3:g_TeacherVMSet.s_pVMInfo[i].s_VMStatus = RESTART;
                    break;
                case 8:g_TeacherVMSet.s_pVMInfo[i].s_VMStatus = WARNING;
                    break;
                default:g_TeacherVMSet.s_pVMInfo[i].s_VMStatus = ERROR;
                    break;
                }
            }
            memset(VMNameBuf,0,sizeof(VMNameBuf));
            iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","list","id",TEACHERVMNUM);
            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
            {
                qDebug("id[%d]:%s",i,VMNameBuf[i]);
                strncpy(g_TeacherVMSet.s_pVMInfo[i].s_strVMID,VMNameBuf[i],100);
            }
            g_pLog->WriteLog(0,"Teacher VM Num:%d",iRecode);
            if(iRecode < TEACHERVMNUM)
                g_TeacherVMSet.s_VMNum =    iRecode;
            else
                g_TeacherVMSet.s_VMNum = TEACHERVMNUM;
            g_pTeacherForm->SetTeacherVM();
        }
        else
        {
            g_pMyDialog->setText("获取教师虚拟机失败");
            m_pLoadingFrame->hide();
            this->setEnabled(true);
            g_pMyDialog->show();
            return ;
        }
//////////////////////////////////Get Class Name//////////////////////////
        g_pLog->WriteLog(0,"Start Get Class Name List");
        memset(TempBuf,0,100);
        //strcpy(TempBuf,"q.field=cluster&q.value=Default");
        sprintf(TempBuf,"qp.filterWhere={\"room_name\":\"%s\"}",g_strRoomNum);
        g_pLog->WriteLog(0,"Get Pools Post:%s",TempBuf);
        g_pMyHttp->Post("/service/desktop_pools/list",TempBuf);
        memset(JsonBuf,0,102400);
        g_pMyHttp->GetData(JsonBuf);
        g_pLog->WriteLog(0,"Get desktop_pool Recv Json:%s",JsonBuf);
        LoginFlag = false;
        g_pMyJson->Parse(JsonBuf);
        g_pMyJson->ReadJson(&LoginFlag,"success");
        if(LoginFlag)
        {
            char IDBuf[MAXCLASS][100];
            char RoomNameBuf[MAXCLASS][100];
            memset(IDBuf,0,sizeof(IDBuf));
            memset(RoomNameBuf,0,sizeof(RoomNameBuf));
            memset(VMNameBuf,0,sizeof(VMNameBuf));
            int iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","list","name",MAXCLASS);
            iRecode = g_pMyJson->ReadJson(IDBuf,"data","list","id",MAXCLASS);
            iRecode = g_pMyJson->ReadJson(RoomNameBuf,"data","list","roomName",MAXCLASS);
            if(iRecode == 0)
            {
                g_pTeacherForm->SetStartClassPushButton(false);
            }
            for(int i = 0; i < iRecode && i < MAXCLASS;i++)
            {
                g_pLog->WriteLog(0,"Class Name[%d]:%s ID:%s RoomID:%s",i,VMNameBuf[i],IDBuf[i],RoomNameBuf[i]);
                g_pTeacherForm->m_pClassNameConfig->AddClass(QString(VMNameBuf[i]),\
                                                             QString(IDBuf[i]),\
                                                             QString(RoomNameBuf[i]));
            }
            g_pLog->WriteLog(0,"Get Class Name Num:%d",iRecode);
            g_pTeacherForm->m_pClassNameConfig->ChooseOne();
            g_pTeacherForm->m_pClassNameConfig->SetLabelName();
        }
        else
        {
            g_pMyDialog->setText("获取课程列表失败");
            m_pLoadingFrame->hide();
            this->setEnabled(true);
            g_pMyDialog->show();
            return ;
        }

//////////////////////////Get Grand Name/////////////////////////////////
        g_pLog->WriteLog(0,"Start Get Grand Name List");
        g_pTeacherForm->SetClass();
////////////////////////Get VM///////////////////////////////////
        memset(TempBuf,0,100);
        g_pMyHttp->Get("/service/aps/list?qp.filterWhere={\"type\":\"student\",\"status\":0}");
        g_pLog->WriteLog(0,"Get Terminal:/service/aps/list?qp.filterWhere={\"type\":\"student\",\"status\":0}}");
        memset(JsonBuf,0,102400);
        g_pMyHttp->GetData(JsonBuf);
        g_pLog->WriteLog(0,"Get Terminal Recv Json:%s",JsonBuf);
        LoginFlag = false;
        g_pMyJson->Parse(JsonBuf);
        g_pMyJson->ReadJson(&LoginFlag,"success");
        if(LoginFlag)
        {
            char IDBuf[TERMINALMAX][100];
            char RoomNameBuf[TERMINALMAX][100];
            char HostAddr[TERMINALMAX][100];
            int Port[TERMINALMAX];
            memset(IDBuf,0,sizeof(IDBuf));
            memset(RoomNameBuf,0,sizeof(RoomNameBuf));
            memset(HostAddr,0,sizeof(HostAddr));
            memset(Port,0,sizeof(Port));
            memset(VMNameBuf,0,sizeof(VMNameBuf));
            int iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","list","id",TERMINALMAX);
            iRecode = g_pMyJson->ReadJson(IDBuf,"data","list","seat",TERMINALMAX);
            iRecode = g_pMyJson->ReadJson(RoomNameBuf,"data","list","StuName",TERMINALMAX);
            iRecode = g_pMyJson->ReadJson(HostAddr,"data","list","hostAddress",TERMINALMAX);
            iRecode = g_pMyJson->ReadJson(Port,"data","list","consolePort",TERMINALMAX);
            for(int i = 0; i < iRecode && i < TERMINALMAX;i++)
            {
                strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strName,RoomNameBuf[i]);
                strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strIP,VMNameBuf[i]);
                strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strSeat,IDBuf[i]);
                strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strHostIP,HostAddr[i]);
                g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_iPort = Port[i];

            }
            if(iRecode < TERMINALMAX)
                g_pTeacherForm->m_TerminalSet.s_TerminalNum = iRecode;
            else
                g_pTeacherForm->m_TerminalSet.s_TerminalNum = TERMINALMAX;
            g_pLog->WriteLog(0,"Get Terminal Num:%d",g_pTeacherForm->m_TerminalSet.s_TerminalNum);
            g_pTeacherForm->SetTerminal();
        }
        else
        {
            g_pMyDialog->setText("终端列表失败");
            m_pLoadingFrame->hide();
            this->setEnabled(true);

            g_pMyDialog->show();
            return ;
        }

////////////////////////////////////////////////////
    }
    else
    {
        memset(TempBuf,0,100);
        g_pMyJson->ReadJson(TempBuf,"data","message");
        g_pMyDialog->setText(QString(TempBuf));
        g_pMyDialog->show();
        m_pLoadingFrame->hide();
        this->setEnabled(true);
        return ;
    }

    this->setEnabled(true);

    m_pLoadingFrame->hide();

    g_pTeacherForm->setWindowModality(Qt::ApplicationModal);

    g_pTeacherForm->SetTeachetName(m_UserName);

    g_pTeacherForm->SetClassRoom(m_pSetForm->m_StrRoomNum);

    g_pTeacherForm->showFullScreen();

    g_pTeacherForm->setEnabled(true);

    pthread_t ThreadID;
    if(pthread_create(&ThreadID,NULL,WhileFun,this))
    {

    }
    memset(g_strTeacherName,0,100);
    strcpy(g_strTeacherName,m_UserName.section('@',0,0).toStdString().c_str());
    g_pProcess->setEXIT(false);
}
void *WhileFun(void *param)
{
    LoginWidget *p = (LoginWidget *)param;
        g_pTeacherForm->ThreadFunWhile();
}
void LoginWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        on_LoginpushButton_clicked();
    }
}

void LoginWidget::on_SetpushButton_clicked()
{
    g_pNetConfig->ReadFile();
    qDebug("asdfasdf:%d",g_pNetConfig->m_pNetConfig->s_bIP);
    if(g_pNetConfig->m_pNetConfig->s_bIP)
    {
        m_pSetForm->SetDHCPSetIPTrue();
    }
    else
    {
        m_pSetForm->SetNoDHCPSetIPTrue();
    }
    if(g_pNetConfig->m_pNetConfig->s_bDNS)
    {
        m_pSetForm->SetDHCPSetDNSTrue();
    }
    else
    {
        m_pSetForm->SetNoDHCPSetDNSTrue();
    }
    m_pSetForm->SetIPLineEdit(g_pNetConfig->m_pNetConfig->s_strIP);
    m_pSetForm->SetMaskIPLineEdit(g_pNetConfig->m_pNetConfig->s_strIPMask);
    m_pSetForm->SetGateWayIPLineEdit(g_pNetConfig->m_pNetConfig->s_strGateWay);

    m_pSetForm->SetDNS1LineEdit(g_pNetConfig->m_pNetConfig->s_strDNS[0]);
    m_pSetForm->SetDNS2LineEdit(g_pNetConfig->m_pNetConfig->s_strDNS[1]);
    m_pSetForm->SetDNS3LineEdit(g_pNetConfig->m_pNetConfig->s_strDNS[2]);


    m_pSetForm->setWindowModality(Qt::ApplicationModal);
    m_pSetForm->show();
}

void LoginWidget::on_ShutdownpushButton_clicked()
{
    //this->close();
    g_pMyDialog->setText("确定关机！");
    g_pMyDialog->setFlag(SHUTDOWN);
    g_pMyDialog->show();
}

void LoginWidget::on_InformationpushButton_clicked()
{
    qDebug("About");
}
void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(DESKTOPMAP));
}
