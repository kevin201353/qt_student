#include "loginwidget.h"
#include "myui_loginwidget.h"
#include "include.h"
extern NetConfig   *g_pNetConfig;

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{

    ui->setupUi(this);
    this->setAutoFillBackground(true);

    m_pLogoQLable = ui->Logolabel;
    m_pLogoQLable->setAlignment(Qt::AlignCenter);
    //m_pLogoQLable->setPixmap(QPixmap(LOGOPNG));

    m_pTimeLCDNumber = ui->TimeLcdNumber;
    m_pSoftInforLabel = ui->Informationlabel;
    m_pServerManPushButton = ui->ServerManpushButton;
    m_pSetPushButton = ui->SetpushButton;
    m_pInformationPushButton = ui->InformationpushButton;
    m_pShutdownPushButton = ui->ShutdownpushButton;
    m_pLeftPushButton = ui->LeftpushButton;
    m_pRightPushButton = ui->RightpushButton;
    m_pEnterPushButton = ui->EnterpushButton;
    m_pClassName1 = ui->label_1;
    m_pClassName2 = ui->label_2;
    m_pClassName3 = ui->label_3;

    //setTabOrder(m_pLoginPushButton,m_pUserNameLineEdit);

    m_pRightPushButton->setMinimumSize(91,169);
    m_pRightPushButton->setFlat(false);
   // m_pRightPushButton->setStyleSheet(QStringLiteral(RIGHTPNG));
    m_pRightPushButton->setStyleSheet(RIGHTPNG);


    m_pLeftPushButton->setMinimumSize(91,169);
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
    m_pSetForm = new SetForm();
    m_pGroupWigdet = ui->groupBox;
    m_pGroupWigdet->setEnabled(false);
    m_pClassNameConfig = new ClassNameConfig();
//    m_pClassNameConfig->AddClass("语文");
//    m_pClassNameConfig->AddClass("数学");
//    m_pClassNameConfig->AddClass("英语");
//    m_pClassNameConfig->AddClass("1");
//    m_pClassNameConfig->AddClass("2");
//    m_pClassNameConfig->AddClass("3");
//    m_pClassNameConfig->AddClass("4");
    m_pClassNameConfig->AddLabel(m_pClassName1);
    m_pClassNameConfig->AddLabel(m_pClassName2);
    m_pClassNameConfig->AddLabel(m_pClassName3);
    m_pClassName1->SetCheckedFlag(true);
    m_pClassNameConfig->ChooseOne();
    m_pClassNameConfig->SetLabelName();

    m_pEnterPushButton->setMinimumSize(284,66);
    m_pEnterPushButton->setStyleSheet(ENTER);
    //m_pEnterPushButton->setEnabled(false);
    connect(m_pLeftPushButton,SIGNAL(clicked()),this,SLOT(on_LeftPushButton()));
    connect(m_pRightPushButton,SIGNAL(clicked()),this,SLOT(on_RightPushButton()));
    connect(m_pClassName1,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassName2,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassName3,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pEnterPushButton,SIGNAL(clicked()),this,SLOT(on_EnterPushButton()));
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
    activemq::library::ActiveMQCPP::initializeLibrary();
    printf("asdfas");
    if(g_Pconsume == NULL)
    {
        g_Pconsume = new ActiveMQConsumer();
        g_Pconsume->start(g_strConsumerAdd,g_strConsumerQueue,true,false);
        g_Pconsume->runConsumer();
    }
    if(g_Pproduce == NULL)
    {
        g_Pproduce = new ActiveMQProduce();
        g_Pproduce->start(g_strProduceAdd,20,g_strProduceQueue,false,false);
    }
    if(g_pProcess == NULL)
    {
        g_pProcess = new process(this);
        int iRecode = g_pProcess->Start();
        if(iRecode < 0)
        {
            printf("New process Error\n");
        }
    }
    g_pNetConfig->GetMacAdd(g_strTerminalID,false);
    m_pSetRoomSeat = new SetRoomSeatDialog(this);
///////////////////////////////////////////////////////////////
    char TempBuf[1024];
    char JsonBuf[10240];
    memset(JsonBuf,0,10240);
    memset(TempBuf,0,1024);
    sprintf(TempBuf,"/edu/service/aps/configure?id=%s&roomName=%s&seat=%s",g_strTerminalID,g_strRoomNum,g_strSeatNum);
    g_pLog->WriteLog(0,"UP SeatNum RoomNum:%s",TempBuf);
    qDebug("TempBuf:%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    qDebug("UP SeatNum RoomNum%s\n",JsonBuf);
    g_pLog->WriteLog(0,"Recv Json:%s",JsonBuf);
}
void LoginWidget::OnTimeOut()
{
    *m_pTime = QDateTime::currentDateTime();
    m_pTimeLCDNumber->display(m_pTime->toString("yyyy-MM-dd HH:mm:ss"));
}
LoginWidget::~LoginWidget()
{
    cMainExitFlag = 0;
    delete m_pTime;
    delete m_pSetForm;
    delete g_pNetConfig;
    delete g_pProcess;
    delete g_pJson;
    delete g_pLog;
    delete g_pMyHttp;
    delete ui;
}

void LoginWidget::on_SetpushButton_clicked()
{
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
    this->close();
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
void LoginWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(DESKTOPMAP));
}
void LoginWidget::on_EnterPushButton()
{
    QString name = m_pClassNameConfig->GetClassName();
    QString id = m_pClassNameConfig->GetClassID();
    qDebug("Name :%s ID:%s",name.toStdString().c_str(),id.toStdString().c_str());

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
        sprintf(TempBuf,"seatNumber=%s&roomName=%s&poolId=%s",g_strSeatNum,g_strRoomNum,id.toStdString().c_str());
    }
    else
    {

    }
    qDebug("Stuself Connect Post Buf:%s",TempBuf);
    g_pMyHttp->Post("/edu/service/desktops/stu_display",TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    qDebug("Connect Json:%s",JsonBuf);
    g_pJson->Parse(JsonBuf);
    g_pJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        g_pJson->ReadJson_v(&Port,"data","sport");
        g_pJson->ReadJson_v(IP,"data","host");
        g_pJson->ReadJson_v(Ticket,"data","ticket");
        qDebug("IP:%s Port:%d Ticket:%s",IP,Port,Ticket);
        g_pProcess->m_SpicyPid = Run_Spicy(IP,(unsigned int)Port,Ticket);
    }
    else
    {

    }
}
void LoginWidget::keyPressEvent(QKeyEvent *event)
{
    if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_S))
    {
        m_pSetRoomSeat->show();
    }
}
