#include "loginwidget.h"
#include "myui_loginwidget.h"
#include "include.h"
#include "global.h"
#include "testnet.h"
#include <QDate>
#include <QDesktopWidget>
#include "qthread.h"
//#include "buildtime.h"
#include "type.h"

extern NetConfig   *g_pNetConfig;
extern void amq_monitor();
extern volatile bool g_resetamq;
extern bool g_bshowwaitstu;
extern volatile bool g_bSetupAmq;
extern int g_msgid;
static pthread_t g_spicypid = NULL;

LoginWidget * g_loginWnd = NULL;
void *InitThread(void *param);
static pthread_t g_xtid = 0;
static char g_szCmd[1024] = {0};
static bool g_ExitMsThread = false;
extern char buildtime[32];
bool   g_processThread = false;

MqMsgProcess  g_mqMsgProcess;

#define SPICY_LOG_PATH  "/usr/local/shencloud/log/spicy.log"

static void *thrd_exec(void *param)
{
    PIPE_SPICYLOG(g_szCmd);
    system(g_szCmd);
    return NULL;
}

extern unsigned long long g_interval_time;
extern int detect_process(char* szProcess);
static void *MonitorSpicy(void *param)
{
    while(true)
    {
        if (g_ExitMsThread)
            break;
		while(true)
	    {
	        if (g_bSetupAmq)
	        {
	           int ret = ping_net(g_strServerIP);
	           if (ret == 1)
	           {
	               break;
	           }
	        }
	        qDebug() << "MonitorSpicy wait net running.\n";
	        sleep(3);
	    }
		myHttp http;
		http.SetUrlIP(g_strServerIP);
		char data[100] = {0};
		char json[100] = {0};
		bool bjson = false;
		sprintf(data,"%s","/service/aps/timestamp");
		http.Get(data);
		http.GetData(json);
		g_pLog->WriteLog(0,"student client get timestamp http return data:%s", json);
		g_pJson->Parse(json);
		g_pJson->ReadJson(&bjson, "success");
		if (bjson)
		{
			memset(data, 0, 100);
			g_pJson->ReadJson_v(data, "data", "systemTime");
			g_pLog->WriteLog(0,"student client recv server time:%s", data);
			g_interval_time = atoll(data);
			g_pLog->WriteLog(0,"student client recv server time atoll = :%lld", g_interval_time);
			//g_interval_time = (unsigned long long)abs(g_interval_time - __GetTime());
			g_interval_time = g_interval_time - __GetTime();
			g_pLog->WriteLog(0,"student client recv server time g_interval_time = :%lld,  _GetTime = %lld", g_interval_time, __GetTime());
			
		}
         sleep(15);
    }
    return NULL;
}

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    g_loginWnd = NULL;
    g_loginWnd = this;
    InitMyMutex();
    m_pLogoQLable = ui->Logolabel;
    m_pLogoQLable->setAlignment(Qt::AlignCenter);
    //m_pLogoQLable->setPixmap(QPixmap(LOGOPNG));
    m_pLogoQLable2 = ui->label_Logo;
    m_pLogoQLable2->setAlignment(Qt::AlignCenter);
    m_pLogoQLable2->setPixmap(QPixmap(LOGOPNG2));
    m_pTimeLCDNumber = ui->TimeLcdNumber;
    m_pSoftInforLabel = ui->Informationlabel;
    m_pServerManPushButton = ui->ServerManpushButton;
    m_pSetPushButton = ui->SetpushButton;
    m_pInformationPushButton = ui->InformationpushButton;
    m_pShutdownPushButton = ui->ShutdownpushButton;
    m_pLeftPushButton = ui->LeftpushButton;
    m_pRightPushButton = ui->RightpushButton;
    //m_pEnterPushButton = ui->EnterpushButton;
    //hide information
    m_pSoftInforLabel->hide();
    m_pSetPushButton->setEnabled(false);
    m_pSetPushButton->setVisible(false);
    m_pShutdownPushButton->setEnabled(false);
    m_pShutdownPushButton->setVisible(false);
    m_pTimeLCDNumber->setEnabled(false);
    m_pTimeLCDNumber->setVisible(false);
    //hide end
    m_pClassName1 = ui->label_1;
    m_pClassName2 = ui->label_2;
    m_pClassName3 = ui->label_3;

    //setTabOrder(m_pLoginPushButton,m_pUserNameLineEdit);

    m_pRightPushButton->setMinimumSize(34,59);
    m_pRightPushButton->setFlat(false);
   // m_pRightPushButton->setStyleSheet(QStringLiteral(RIGHTPNG));
    m_pRightPushButton->setStyleSheet(RIGHTPNG);


    m_pLeftPushButton->setMinimumSize(34,59);
    m_pLeftPushButton->setFlat(false);
    //m_pLeftPushButton->setStyleSheet(QStringLiteral(LEFTPNG));
    m_pLeftPushButton->setStyleSheet(LEFTPNG);
    // m_pLeftPushButton->setText("左翻");

    m_pTimeLCDNumber->setDigitCount(25);
    m_pTimeLCDNumber->setMode(QLCDNumber::Dec);
    m_pTimeLCDNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pTimeLCDNumber->setFrameShape(QLCDNumber::NoFrame);

    m_pSetPushButton->setStyleSheet(QStringLiteral(SETLOGO));
    m_pSetPushButton->setMinimumSize(37,36);
//    m_pSetPushButton->setFlat(false);
    m_pInformationPushButton->setStyleSheet(QStringLiteral(INFORMATIONLOGO));
    m_pInformationPushButton->setMinimumSize(39,39);

    m_pServerManPushButton->setStyleSheet(QStringLiteral(SERVERMANLOGO));
    m_pServerManPushButton->setMinimumSize(34,34);

    m_pShutdownPushButton->setStyleSheet(QStringLiteral(SHUTDOWNLOGO));
    m_pShutdownPushButton->setMinimumSize(33,37);
   // QFont ft;
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    m_pTime = new QDateTime();
    m_pTimer->start();
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(OnTimeOut()));
    SetEnable(false);
    m_pClassNameConfig = new ClassNameConfig();
#if 0
    SetEnable(true);
    m_pClassNameConfig->AddClass("语文","1");
    m_pClassNameConfig->AddClass("数学","2");
    m_pClassNameConfig->AddClass("英语","3");
    m_pClassNameConfig->AddClass("1","4");
    m_pClassNameConfig->AddClass("2","5");
    m_pClassNameConfig->AddClass("3","6");
    m_pClassNameConfig->AddClass("4","7");
#endif
    m_pClassNameConfig->AddLabel(m_pClassName1);
    m_pClassNameConfig->AddLabel(m_pClassName2);
    m_pClassNameConfig->AddLabel(m_pClassName3);
    m_pClassName1->SetCheckedFlag(true);
//   m_pClassNameConfig->ChooseOne();
//    m_pClassNameConfig->SetLabelName();

//    m_pEnterPushButton->setMinimumSize(284,66);
//    m_pEnterPushButton->setStyleSheet(ENTER);
    //m_pEnterPushButton->setEnabled(false);
    //170303
    //test
    //m_pGroupWigdet->setEnabled(true);
    //test end
    connect(m_pLeftPushButton,SIGNAL(clicked()),this,SLOT(on_LeftPushButton()));
    connect(m_pRightPushButton,SIGNAL(clicked()),this,SLOT(on_RightPushButton()));
    connect(m_pClassName1,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassName2,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassName3,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    //connect(m_pEnterPushButton,SIGNAL(clicked()),this,SLOT(on_EnterPushButton()));
    connect(m_pClassName1,SIGNAL(LabelDoubleclicked()),this,SLOT(on_LableDoubleClicked()));
    connect(m_pClassName2,SIGNAL(LabelDoubleclicked()),this,SLOT(on_LableDoubleClicked()));
    connect(m_pClassName3,SIGNAL(LabelDoubleclicked()),this,SLOT(on_LableDoubleClicked()));
    m_passui = new PasswordUI();
    connect(m_passui, SIGNAL(ShowPassUI()),this,SLOT(on_ShowPassUI()));
    //m_waitstuDialog = new WaitstuDialog();
    m_waitstu = new waitstu2();
    connect(m_waitstu, SIGNAL(wait_showPassUI()), this, SLOT(on_SetpushButton_clicked()));
    connect(m_waitstu, SIGNAL(wait_shutdown()), this, SLOT(on_ShutdownpushButton_clicked()));
    g_pNetConfig = new NetConfig();
    if(g_pLog == NULL)
    {
        g_pLog = new Log();
        g_pLog->InitLog();
    }
    if(g_pJson == NULL)
    {
        g_pJson = new myJson();
    }
    if(g_pMyHttp == NULL)
    {
        g_pMyHttp = new myHttp();
        g_pMyHttp->SetUrlIP(QString(g_strServerIP));
    }
    g_ExitMsThread = false;
    g_processThread = false;
//    MySetConnectVm(false);
 
//    if(g_pProcess == NULL)
//    {
//        g_pProcess = new process(this);
//        int iRecode = g_pProcess->Start();
//        if(iRecode < 0)
//        {
//            printf("New process Error\n");
//        }
//    }
    initConfig();
    g_mqMsgProcess.start();
    g_bSetupAmq = false;
    //create_msg_queue();
    wait_net_setup();
    g_resetamq = false;
    g_exitMonitoramq = false;
    g_bshowwaitstu = false;
    amq_monitor();
    m_pqthread = NULL;
    m_pqthread = new qthread();
    connect(m_pqthread, SIGNAL(NoticeShow()), this, SLOT(UpdateNetOffDialog()));
    connect(m_pqthread, SIGNAL(NoticeHide()), this, SLOT(HideNetOffDialog()));
    m_pqthread->start();
    m_pSetRoomSeat = new SetRoomSeatDialog(this);
    m_bExitThread = false;
    m_pMyDialog = new MyDialog();
    m_pSetForm = new SetForm();
    m_pSetForm->move(QApplication::desktop()->width()/2 - m_pSetForm->width()/2, QApplication::desktop()->height()/2 - m_pSetForm->height()/2);
    m_pServerManPushButton->hide();
    m_pInformationPushButton->hide();
//    QDate *date = new QDate();
//    QDate date2 = date->currentDate();
//    QString strdate = date2.toString("yyyyMMdd");
//    QString strsoft = m_pSoftInforLabel->text();
//    strsoft += ": V1.5_";
//    strsoft += new QString(buildtime);
//    m_pSoftInforLabel->setText(strsoft);
//    if (date)
//    {
//        delete date;
//        date = NULL;
//    }
#ifdef ARM
	if(pthread_create(&g_spicypid,NULL,MonitorSpicy,this))
	{
	}
#endif

    if(pthread_create(&g_amqpid,NULL,InitThread,this))
    {
    }
    this->hide();
    ReportMsg reportmsg;
    reportmsg.action = USER_WAITINGDLG_SHOW;
    call_msg_back(msg_respose, reportmsg);
}
void LoginWidget::SetEnable(bool flag)
{
    m_pLeftPushButton->setEnabled(flag);
    m_pRightPushButton->setEnabled(flag);
    m_pClassName1->setEnabled(flag);
    m_pClassName2->setEnabled(flag);
    m_pClassName3->setEnabled(flag);
}
void *InitThread(void *param)
{
    if (param == NULL)
        return NULL;

    LoginWidget *pLoginWidget = (LoginWidget *)param;
    g_resetamq = false;
    while(true)
    {
        if (g_bSetupAmq)
        {
           int ret = ping_net(g_strServerIP);
           if (ret == 1)
           {
               break;
           }
        }
        qDebug() << "wait net running.\n";
        sleep(2);
    }
    activemq::library::ActiveMQCPP::initializeLibrary();
    g_Pconsume = NULL;
    g_Pproduce = NULL;
    if(g_Pconsume == NULL)
    {
        g_Pconsume = new ActiveMQConsumer();
        g_Pconsume->start(g_strConsumerAdd,g_strConsumerQueue,false,false);
    }
    if(g_Pproduce == NULL)
    {
        g_Pproduce = new ActiveMQProduce();
    }
    if(g_Pconsume != NULL)
    {
        g_Pconsume->runConsumer();
    }
    if (g_Pproduce != NULL)
    {
        g_Pproduce->start(g_strProduceAdd,20,g_strProduceQueue,false,false);
    }
    g_mqMsgProcess.GetAddrMac();
#ifdef ARM
	myHttp http;
	http.SetUrlIP(g_strServerIP);
	char data[100] = {0};
	char json[100] = {0};
	bool bjson = false;
	sprintf(data,"%s","/service/aps/timestamp");
	http.Get(data);
	http.GetData(json);
	g_pLog->WriteLog(0,"student client get timestamp http return data initthread:%s", json);
	g_pJson->Parse(json);
	g_pJson->ReadJson(&bjson, "success");
	if (bjson)
	{
		memset(data, 0, 100);
		g_pJson->ReadJson_v(data, "data", "systemTime");
		g_pLog->WriteLog(0,"InitThread student client recv server time:%s", data);
		g_interval_time = atoll(data);
		g_pLog->WriteLog(0,"student client recv server time atoll = :%lld", g_interval_time);
		//g_interval_time = (unsigned long long)abs(g_interval_time - __GetTime());
		g_interval_time = g_interval_time - __GetTime();
		g_pLog->WriteLog(0,"student client recv server time g_interval_time = :%lld,  _GetTime = %lld", g_interval_time, __GetTime());
	}
#endif
	
 //   g_pProcess->GetAddrMac();
    ///////////////////////////////////////////////////////////////
//    char TempBuf[1024];
//    char JsonBuf[10240];
//    memset(JsonBuf,0,10240);
//    memset(TempBuf,0,1024);
//    sprintf(TempBuf,"/service/aps/config?id=%s&roomName=%s&seat=%s&reboot=false&sync=false",g_strTerminalID,g_strRoomNum,g_strSeatNum);
//    g_pLog->WriteLog(0,"UP SeatNum RoomNum:%s",TempBuf);
//   // qDebug("TempBuf:%s",TempBuf);
//    myHttp http;
//    http.SetUrlIP(g_strServerIP);
//    http.Get(TempBuf);
//    http.GetData(JsonBuf);
//    qDebug("xxxxxx amq UP SeatNum RoomNum%s\n",JsonBuf);
//    g_pLog->WriteLog(0,"Recv Json:%s",JsonBuf);

    ///////////////////////////////////////////////////////////////
    /// \brief strClassRoomName
    ///
#if 0
    char strClassRoomName[20][100];
    memset(JsonBuf,0,10240);
    memset(TempBuf,0,1024);
    sprintf(TempBuf, "/service/rooms/list?qp.sortby=name&qp.direction=asc");
    http.Get(TempBuf);
    http.GetData(JsonBuf);
    g_pLog->WriteLog(0,"Recv Json:%s", JsonBuf);
    memset(strClassRoomName, 0, sizeof(strClassRoomName));
    myJson *pMyJson = new myJson();
    int iRecode = 0;
    pMyJson->Parse(JsonBuf);
    iRecode = pMyJson->ReadJson(strClassRoomName, "data", "list", "name", 20);
    for (int i=0; i<iRecode; i++)
    {
        if (strcmp(g_strRoomNum, strClassRoomName[i]) == 0)
        {
            pLoginWidget->m_pSetForm->m_pRoomNumcomboBox->addItem(QString(g_strRoomNum));
            break;
        }
    }
    for (int i=0; i<iRecode; i++)
    {
        if (strcmp(g_strRoomNum, strClassRoomName[i]) != 0)
        {
            pLoginWidget->m_pSetForm->m_pRoomNumcomboBox->addItem(QString(strClassRoomName[i]));
        }
    }

    if (pMyJson)
        delete pMyJson;
    pLoginWidget->m_pSetForm->m_pRoomNumcomboBox->setCurrentIndex(0);
#endif
}
void *WhileFun(void *param)
{
    if (param == NULL)
        return NULL;

    LoginWidget *p = (LoginWidget *)param;
        p->Thread();
}

void LoginWidget::initConfig()
{
    g_pNetConfig->GetMacAdd(g_strTerminalID,false);
    strcat(g_strConsumerQueue, "edu_");
    strcat(g_strConsumerQueue, g_strTerminalID);
    GetConfigString(CONFIGNAME,"MQ","ProduceQueue","edu_Queue",g_strProduceQueue,50);
    GetConfigString(CONFIGNAME,"ROOM","ServiceIP","192.168.120.36",g_strServerIP,25);
    qDebug("Service:%s",g_strServerIP);
    strcpy(g_strConsumerAdd,"tcp://");
    strcat(g_strConsumerAdd,g_strServerIP);
    strcat(g_strConsumerAdd,":61616");
    strcpy(g_strProduceAdd,g_strConsumerAdd);
    qDebug("ActiveMQ Server:%s Recv Queue:%s Send Queue:%s",g_strConsumerAdd, g_strConsumerQueue,g_strProduceQueue);
    qDebug(g_strProduceAdd);
    GetConfigString(CONFIGNAME,"ROOM","ClassName","Default",g_strRoomNum,100);
    GetConfigString(CONFIGNAME,"ROOM","SeatName","A1",g_strSeatNum,20);
    qDebug("%s %s",g_strRoomNum, g_strSeatNum);
    char szVer[100] = {0};
    strcpy(szVer, "V1.1_");
    strcat(szVer, (char*)buildtime);
    WriteConfigString(CONFIGNAME, "ROOM", "Version", szVer);
}

void LoginWidget::SetChecked()
{
    m_pClassName1->SetCheckedFlag(true);
}
void LoginWidget::Thread()
{
    char JsonBuf[1024];
    bool Recode = false;
    bool BackScreen  = false;
    bool USB = false;
    myHttp http;
    http.SetUrlIP(g_strServerIP);
    char GetBuf[100];
    memset(GetBuf,0,100);
    sprintf(GetBuf,"/service/classes/stu_askfor?apId=%s",g_strTerminalID);
    while(!m_bExitThread)
    {
        memset(JsonBuf,0,1024);
        http.Get(GetBuf);
        http.GetData(JsonBuf);
        qDebug("While %s:",JsonBuf);
        g_pJson->Parse(JsonBuf);
        g_pJson->ReadJson(&Recode,"success");
        if(Recode)
        {
            g_pJson->ReadJson_v(&BackScreen,"data","enableBlack");
            g_pJson->ReadJson_v(&USB,"data","enableUSB");
            qDebug("enbaleBack:%d enableUSB:%d",BackScreen,USB);
            if(BackScreen)
            {
                //system("");
            }
            else
            {
                //system("");
            }
            if(USB)
            {
                //system("");
            }
            else
            {
                //system("");
            }
        }
        else
        {

        }
        sleep(2);
    }
}
void LoginWidget::OnTimeOut()
{
    *m_pTime = QDateTime::currentDateTime();
    m_pTimeLCDNumber->display(m_pTime->toString("yyyy-MM-dd HH:mm:ss"));
}

LoginWidget::~LoginWidget()
{
    cMainExitFlag = 0;
    g_exitMonitoramq = true;
    m_bExitThread = true;
    if(m_pMyDialog)
        delete m_pMyDialog;
    delete m_pTime;
    delete m_pSetForm;
    delete g_pNetConfig;
    delete g_pProcess;
    delete g_pJson;
    delete g_pLog;
    delete g_pMyHttp;
    if(g_LoadingFrame)
        delete g_LoadingFrame;
//    if (g_Loadingwnd != NULL)
//    {
//        delete g_Loadingwnd;
//        g_Loadingwnd = NULL;
//    }
//    msg_queue_del();
    pthread_join(g_monitoramq, NULL);
    if (m_pqthread)
    {
        m_pqthread->stop();
        delete m_pqthread;
    }
//    if (m_waitstuDialog)
//    {
//        delete m_waitstuDialog;
//        m_waitstuDialog = NULL;
//    }
    if (m_waitstu)
    {
        delete m_waitstu;
        m_waitstu = NULL;
    }
    g_ExitMsThread = true;
    MyMutex_destroy();
    delete ui;
}

void LoginWidget::on_SetpushButton_clicked()
{
    m_passui->show();
//    if (passui->isAdjustPass())
//    {
//        g_pNetConfig->ReadFile();
//        if(g_pNetConfig->m_pNetConfig->s_bIP)
//        {
//            m_pSetForm->SetDHCPSetIPTrue();
//        }
//        else
//        {
//            m_pSetForm->SetNoDHCPSetIPTrue();
//        }
//        if(g_pNetConfig->m_pNetConfig->s_bDNS)
//        {
//            m_pSetForm->SetDHCPSetDNSTrue();
//        }
//        else
//        {
//            m_pSetForm->SetNoDHCPSetDNSTrue();
//        }
//        m_pSetForm->SetIPLineEdit(g_pNetConfig->m_pNetConfig->s_strIP);
//        m_pSetForm->SetMaskIPLineEdit(g_pNetConfig->m_pNetConfig->s_strIPMask);
//        m_pSetForm->SetGateWayIPLineEdit(g_pNetConfig->m_pNetConfig->s_strGateWay);

//        m_pSetForm->SetDNS1LineEdit(g_pNetConfig->m_pNetConfig->s_strDNS[0]);
//        m_pSetForm->SetDNS2LineEdit(g_pNetConfig->m_pNetConfig->s_strDNS[1]);
//        m_pSetForm->SetDNS3LineEdit(g_pNetConfig->m_pNetConfig->s_strDNS[2]);

//        m_pSetForm->setWindowModality(Qt::ApplicationModal);
//        m_pSetForm->show();
//    }
}

void LoginWidget::on_ShowPassUI()
{
    m_passui->hide();
    m_passui->setpasstext("");
    g_pNetConfig->ReadFile();
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
    MyDialog *pshutdlg = new MyDialog();
    pshutdlg->setText("您确认要关机？");
    pshutdlg->setFlag(SHUTDOWN);
    pshutdlg->show();
}

void LoginWidget::on_InformationpushButton_clicked()
{
    qDebug("About");
}
void LoginWidget::on_LeftPushButton()
{
    m_pClassNameConfig->MinusInode();
    m_pClassNameConfig->SetLabelName();
}
void LoginWidget::on_RightPushButton()
{
    m_pClassNameConfig->AddInode();
    m_pClassNameConfig->SetLabelName();
}
void LoginWidget::on_LabelChecked()
{
    m_pClassNameConfig->ChooseOne();
    m_pClassNameConfig->SetLabelName();
}

void LoginWidget::on_LableDoubleClicked()
{
    //double course
    qDebug("LoginWidget::on_LableDoubleClicked  !!!!!!! .\n");
    on_EnterPushButton();
}

void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(DESKTOPMAP));
}

static pthread_t g_contid = 0;
static void *thrd_connect(void *)
{
    LoginWidget  *loginWid = (LoginWidget  *)g_loginWnd;
    if (loginWid == NULL)
        return NULL;
	myHttp http;
	http.SetUrlIP(g_strServerIP);
    QString name = loginWid->m_pClassNameConfig->GetClassName();
    QString id = loginWid->m_pClassNameConfig->GetClassID();
    qDebug("Name :%s ID:%s",name.toStdString().c_str(),id.toStdString().c_str());
    g_pLog->WriteLog(0,"Name :%s ID:%s",name.toStdString().c_str(),id.toStdString().c_str());
    bool ReturnCode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    int Port = 0;
    char IP[20];
    char Ticket[50];
    memset(IP,0,20);
    memset(Ticket,0,50);
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    if(strlen(g_strRoomNum)!= 0 && strlen(g_strSeatNum) != 0)
    {
        sprintf(TempBuf,"seatNumber=%s&roomName=%s&courseId=%s",g_strSeatNum,g_strRoomNum,id.toStdString().c_str());
    }
    g_pLog->WriteLog(0,"Stuself Connect Post Buf:%s",TempBuf);
   // qDebug("Stuself Connect Post Buf:%s",TempBuf);
    int run_count = 0;
    while(run_count <= 180)  //tree miniture exit
    {
        http.Post("/service/desktops/stu_display",TempBuf);
        http.GetData(JsonBuf);
        //qDebug("Connect Json:%s",JsonBuf);
        g_pLog->WriteLog(0,"Connect Json:%s",JsonBuf);
        g_pJson->Parse(JsonBuf);
        ReturnCode = false;
        g_pJson->ReadJson(&ReturnCode,"success");
        if(ReturnCode)
        {
            g_pJson->ReadJson_v(&Port,"data","port");
            g_pJson->ReadJson_v(IP,"data","host");
            g_pJson->ReadJson_v(Ticket,"data","ticket");
            memset(g_pProcess->m_strVmID,0,50);
            g_pJson->ReadJson_v(g_pProcess->m_strVmID,"data","vmId");
            qDebug("IP:%s Port:%d Ticket:%s",IP,Port,Ticket);
            g_pLog->WriteLog(0,"IP:%s Port:%d Ticket:%s VmID:%s",IP,Port,Ticket,g_pProcess->m_strVmID);
            system("cat /tmp/data_*");
            system("rm -f /tmp/data_*");
            sprintf(g_szCmd, "sudo spicy -h %s -p %d -f > %s 2>&1", IP, Port, "/usr/local/shencloud/log/spicy.log");
            if (pthread_create(&g_xtid, NULL, thrd_exec, NULL) != 0)
            {
                g_pLog->WriteLog(0,"zhaosenhua create spicy thread failed.");
            }
            int ncount = 0;
            while(access("/tmp/data_port",F_OK))
            {
                if (ncount >= 20)
                {
                    break;
                }
                ncount++;
                sleep(1);
            }
            system("cat /tmp/data_*");
            char port[20];
            memset(port,0,20);
            FILE *pf = fopen("/tmp/data_port","r");
            if(pf != NULL)
            {
                fread(port,20,1,pf);
                g_pLog->WriteLog(0,"/tmp/data_port:%s",port);
                fclose(pf);
            }
            char data_xor[20];
            memset(data_xor,0,20);
            pf = fopen("/tmp/data_xor","r");
            if(pf != NULL)
            {
                fread(data_xor,20,1,pf);
                g_pLog->WriteLog(0,"/tmp/data_xor:%s",data_xor);
                fclose(pf);
            }
            char append[1024];
            memset(append,0,1024);
            sprintf(append,"vmId=%s&connected=true&apIp=%s&apMac=%s&dsPort=%s&dsXor=%s",\
                    g_pProcess->m_strVmID,g_pProcess->m_strIP,g_pProcess->m_strMac,port,data_xor);
            g_pLog->WriteLog(0,"Report Action:%s",append);
            http.Post("/service/aps/report_action",append);
            memset(JsonBuf,0,1024);
            http.GetData(JsonBuf);
            g_pLog->WriteLog(0,"student report action:%s\n",JsonBuf);
            g_pJson->Parse(JsonBuf);
            g_pJson->ReadJson(&ReturnCode,"success");
            if(ReturnCode)
            {
                g_pLog->WriteLog(0,"Report connect[true] Success");
                break;
            }
            else
            {
                g_pLog->WriteLog(0,"Report connect[true] Error");
            }
        }
        run_count++;
        sleep(1);
    }//while
    ReportMsg reportmsg;
    reportmsg.action = USER_WAITINGDLG_EXIT;
    call_msg_back(msg_respose, reportmsg);
    return NULL;
}

void LoginWidget::on_EnterPushButton()
{
    
    ReportMsg reportmsg;
    reportmsg.action = USER_WAITINGDLG_SHOW;
    call_msg_back(msg_respose, reportmsg);
    
    //m_pEnterPushButton->setEnabled(false);
    if(pthread_create(&g_contid,NULL,thrd_connect, NULL))
    {
        printf("create Thread Error");
    }
}
void LoginWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug("---------%8x", event->key());
    switch(event->key())
    {
        case Qt::Key_Left:
            {
                if (m_pClassNameConfig)
                    m_pClassNameConfig->MoveLeft();
            }
            break;
        case Qt::Key_Right:
            {
                if (m_pClassNameConfig)
                    m_pClassNameConfig->MoveRigth();
            }
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            {
                if (m_pClassNameConfig != NULL && m_pClassNameConfig->m_iClassNum)
                {
                    on_EnterPushButton();
                }
            }
            break;
    }
}

void LoginWidget::createPipe()
{
    int res = 0;
    if (access(FIFO_PIPE, F_OK) == -1)
    {
        //Pipe file is not exist
        res = mkfifo(FIFO_PIPE, S_IRUSR | S_IWUSR);
        if (res != 0)
        {
             g_pLog->WriteLog(0,"Error, could not create fifo %s \n", FIFO_PIPE);
             return;
        }
    }
}

void LoginWidget::UpdateNetOffDialog()
{

    if (m_pMyDialog)
    {
        qDebug() << "hide netoff dailog 0000.";
        if (!m_pMyDialog->getShow())
        {
            qDebug() << "hide netoff dailog.";
            m_pMyDialog->setShow(true);
            m_pMyDialog->show();
            m_pMyDialog->setNetOff("网络异常，请联系管理员!", 5);
        }
    }
}

void LoginWidget::HideNetOffDialog()
{
    if (m_pMyDialog)
    {
        qDebug() << "hide netoff dailog 11111.";
        m_pMyDialog->setShow(false);
        m_pMyDialog->hide();
    }
}
