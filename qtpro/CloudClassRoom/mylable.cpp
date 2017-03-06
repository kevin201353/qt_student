#include "mylable.h"
#include "tcp.h"
#include "myhttp.h"
#include "myjson.h"

extern myHttp *g_pMyHttp;
extern myJson *g_pMyJson;
extern Log         *g_pLog;
myLable::myLable(QWidget *parent):QLabel(parent)
{
    memset(m_strIP,0,IPLEN);
    memset(m_strID,0,NAMELEN);
    m_bFrontLableEnable = false;
    m_bEnable = false;
    m_iSocket = 0;
    m_bThreadFlag = false;
    m_bExit = false;
    m_OldPosX = 0;
    m_OldPosY = 0;
    m_bDoubleCheckFlag = false;
    m_bConnectFlag =false;
    this->setScaledContents(true);
    this->setPixmap(QPixmap(NORMALPIC));
    this->resize(300,200);
    this->setMinimumSize(300,200);
    m_pNameLabel = new QLabel(this);
    m_pNameLabel->move(0,0);
    m_pNameLabel->setMinimumSize(300,20);
    m_pNameLabel->setStyleSheet("color:rgb(255,0,0)");
   // m_pNameLabel->setText("姓名:张三     座位号:D2");
    m_pNameLabel->setText("");
    //m_pNameLabel->setAlignment(Qt::AlignCenter);
    //    this->setMaximumSize(300,200);
    m_pFrontLabel = new QLabel(this);
    m_pFrontLabel->setAlignment(Qt::AlignCenter);
    m_pFrontLabel->move(230,130);
    m_pFrontLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_pFrontLabel->setPixmap(QPixmap(SOMEONEHANDUP));
    m_pFrontLabel->setVisible(false);

//    pFrontLabel->setStyleSheet("background:transparent");
//    label->setAttribute(Qt::WA_TranslucentBackground);

    m_pDarkScreenAction = new QAction("启动",this);
    m_pDarkScreenAction->setEnabled(false);
    m_pRestartAction = new QAction("关闭",this);
    m_pStudentShowAction = new QAction("重启桌面",this);
    m_pStudentShowAction->setEnabled(false);
    m_pSendFileAction = new QAction("重启终端",this);
    m_pRemoteAction = new QAction("远程协助",this);
    m_pRemoteAction->setEnabled(false);
    m_Font.setPixelSize(18);

    m_pDarkScreenAction->setFont(m_Font);
    m_pRestartAction->setFont(m_Font);
    m_pStudentShowAction->setFont(m_Font);
    m_pSendFileAction->setFont(m_Font);
    m_pRemoteAction->setFont(m_Font);



    m_pDarkScreenAction->setEnabled(m_bEnable);
    m_pRestartAction->setEnabled(m_bEnable);
    m_pStudentShowAction->setEnabled(m_bEnable);
    m_pSendFileAction->setEnabled(m_bEnable);
    m_pRemoteAction->setEnabled(m_bEnable);

    m_pDarkScreenAction->setIcon(QIcon(DARKSCREENICON));
    m_pRestartAction->setIcon(QIcon(RESTARTICON));
    m_pStudentShowAction->setIcon(QIcon(STUDENTSHOWICON));
    m_pSendFileAction->setIcon(QIcon(SENDFILEICON));
    m_pRemoteAction->setIcon(QIcon(REMOTEACTIONICON));

    //this->addAction(m_pDarkScreenAction);
    this->addAction(m_pRestartAction);
    //this->addAction(m_pStudentShowAction);
    this->addAction(m_pSendFileAction);
    //this->addAction(m_pRemoteAction);

    connect(m_pDarkScreenAction, SIGNAL(triggered()), this, SLOT(DarkScreenFun()));
    connect(m_pRestartAction, SIGNAL(triggered()), this, SLOT(RestartFun()));
    connect(m_pStudentShowAction, SIGNAL(triggered()), this, SLOT(StudentShowFun()));
    connect(m_pSendFileAction, SIGNAL(triggered()), this, SLOT(SendFileFun()));
    connect(m_pRemoteAction, SIGNAL(triggered()), this, SLOT(RemoteFun()));
    memset(m_strIP,0,IPLEN);
    m_iPort = 0;
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_pid = 0;
    if(pthread_create(&m_pid,NULL,ThreadFun,this))
    {
        printf("Create pthread Error!\n");
    }
    m_bThreadEXIT = false;
    //this->setAttribute(Qt::WA_DeleteOnClose,true);
}
void *ThreadFun(void *param)
{
    myLable *pLable = (myLable*)param;
    QImage  image;
    QPixmap jpeg;
    TcpClient tcp;
    struct jpegheader head;
    unsigned char jpegbody[102400];
    int iRecode = 0;
    char* magic = "SCDM";
    pLable->m_bThreadEXIT = false;
    //qDebug("Start Thread[%d]",pLable->m_pid);
    while(!pLable->m_bExit)
    {
        sleep(1);
        qDebug("Start Thread[%ld] Port[%d]",pLable->m_pid,pLable->m_iPort+10000);
        if(pLable->m_bThreadFlag)
        {
            //chu li shiping shuju
//            sleep(1);
            if(!pLable->m_bConnectFlag)
            {
                if(pLable->m_iPort > 0 && strlen(pLable->m_strIP) > 6)
                {
                    g_pLog->WriteLog(0,"Start Connect:IP[%s] Port[%d]",pLable->m_strIP,pLable->m_iPort+10000);
                    char PortTemp[10];
                    memset(PortTemp,0,10);
                    sprintf(PortTemp,"%d",pLable->m_iPort+10000);
                    iRecode = tcp.CreateSocket(pLable->m_strIP,PortTemp);
                    iRecode = tcp.Connect();
                    g_pLog->WriteLog(0,"Connect Recode[%d]",iRecode);
                    if(iRecode == 0)
                    {
                        pLable->m_bConnectFlag = true;
                    }
                }
                else
                {
                    continue;
                }
            }
            memset(&head,0,sizeof(head));
            memset(jpegbody,0,102400);
            if((iRecode = tcp.ReadTCP(&head,sizeof(head))) < 0)
            {
                    pLable->m_bConnectFlag = false;
                    continue;
            }
            if(iRecode != sizeof(head))
            {
               // g_pLog->WriteLog(0,"Read Head Error!");
            }
//            qDebug("[%d]header.width=%d",pLable->m_iPort+10000,head.width);
//            qDebug("[%d]header.height=%d",pLable->m_iPort+10000,head.height);
//            qDebug("[%d]header.serial=%d",pLable->m_iPort+10000,head.serial);
//            qDebug("[%d]header.size=%d",pLable->m_iPort+10000,head.size);
//            qDebug("[%d]header.magic=%s",pLable->m_iPort+10000,head.magic);

            if(strncmp(head.magic,magic,4))
            {
                pLable->m_bConnectFlag = false;
                continue;
            }
            if(head.size > 102400)
            {
                pLable->m_bConnectFlag = false;
                continue;
            }
            if((iRecode = tcp.ReadTCP(jpegbody,head.size)) < 0)
            {
                pLable->m_bConnectFlag = false;
                continue;
            }
 //           qDebug("header.size=%d BufLen=%d iRecode:%d",head.size,strlen((const char *)jpegbody),iRecode);
            //pimage =new QImage(head.width,head.height,QImage::Format_ARGB32);
            image.setPixel(head.width,head.height,QImage::Format_ARGB32);
            if(image.loadFromData((uchar*)jpegbody,head.size,"JPG"))
            {
                jpeg=QPixmap::fromImage(image);
                if(!pLable->m_bExit)
                    pLable->setPixmap(QPixmap(jpeg));
            }
            else
            {

            }
            //delete pimage;
        }
        else
        {
            sleep(1);
        }
    }
    //fclose(f);
    pLable->m_bThreadEXIT = true;
    qDebug("!===PORT[%d]=========m_bThreadEXIT[%d]",pLable->m_iPort+10000,pLable->m_bThreadEXIT);
    return 0;
}
void myLable::DarkScreenFun()
{

}
void myLable::RestartFun()
{
    g_pLog->WriteLog(0,"Restart");
    char TempBuf[100];
    char JsonBuf[1024];
    bool RetuenCode = false;
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    sprintf(TempBuf,"/service/aps/shutdown?ids[0]=%s",m_strID);
     g_pLog->WriteLog(0,"Shut Down Terminal Get:%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);
     g_pLog->WriteLog(0,"ReadJson:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&RetuenCode,"success");
    if(RetuenCode)
    {
        qDebug("Success");
    }
    else
    {
        qDebug("false");
    }
}
void myLable::StudentShowFun()
{
    qDebug("StudentShow");
}
void myLable::SendFileFun()
{
    qDebug("SendFile");
    char TempBuf[100];
    char JsonBuf[1024];
    bool RetuenCode = false;
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    sprintf(TempBuf,"/service/aps/reboot?ids[0]=%s",m_strID);
     g_pLog->WriteLog(0,"Reboot Terminal Get:%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);
     g_pLog->WriteLog(0,"ReadJson:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&RetuenCode,"success");
    if(RetuenCode)
    {
        qDebug("Success");
    }
    else
    {
        qDebug("false");
    }

}
void myLable::RemoteFun()
{
    qDebug("RemoteFun");
}
myLable::~myLable()
{
    m_bExit = true;
    //while(!m_bThreadEXIT);
    //sleep(2);
    if(m_pDarkScreenAction)
        delete m_pDarkScreenAction;
    if(m_pRestartAction)
        delete m_pRestartAction;
    if(m_pStudentShowAction)
        delete m_pStudentShowAction;
    if(m_pSendFileAction)
        delete m_pSendFileAction;
    if(m_pRemoteAction)
        delete m_pRemoteAction;
}

void myLable::ShowUpHand(bool flag)
{
    if(!m_bFrontLableEnable)
        return ;
    if(flag)
    {
        m_pFrontLabel->setVisible(flag);
    }
    else
    {
        m_pFrontLabel->setVisible(flag);
    }
}
void myLable::Enable(bool flag)
{

    if(flag)
    {
        m_bEnable = true;
        m_bFrontLableEnable = true;
        m_bThreadFlag = true;
        //m_pDarkScreenAction->setEnabled(m_bEnable);
        m_pRestartAction->setEnabled(m_bEnable);
        //m_pStudentShowAction->setEnabled(m_bEnable);
        m_pSendFileAction->setEnabled(m_bEnable);
        //m_pRemoteAction->setEnabled(m_bEnable);
    }
    else
    {
        m_bEnable = false;
        m_bFrontLableEnable = false;
        m_pDarkScreenAction->setEnabled(m_bEnable);
        m_pRestartAction->setEnabled(m_bEnable);
        m_pStudentShowAction->setEnabled(m_bEnable);
        m_pSendFileAction->setEnabled(m_bEnable);
        m_pRemoteAction->setEnabled(m_bEnable);
        memset(m_strIP,0,IPLEN);
        memset(m_strID,0,NAMELEN);
        m_iSocket = 0;
        m_bThreadFlag = false;
    }
}

void myLable::SetIPPort(const char *ip,const int port)
{
    if(ip == NULL)
        return ;
    strncpy(m_strIP,ip,IPLEN);
    //strncpy(m_strPort,port,PORTLEN);
    qDebug("IP:%s       PORT:%d",ip,port);
    m_iPort = port;
}
void myLable::SetName(const char *name,const char *seat,const char *ID)
{
//    if(name == NULL&&seat == NULL)
//        return ;
    strncpy(m_strID,ID,NAMELEN);
    char Buf[100];
    memset(Buf,0,100);
    sprintf(Buf,"姓名:%s     座位号:%s",name,seat);
     qDebug("Buf:%s",Buf);
    m_pNameLabel->setText(Buf);
}
void myLable::SetSocket(int sock)
{
    if(sock <= 0)
        return ;
    m_iSocket = sock;
}
void myLable::mousePressEvent(QMouseEvent *ev)
{

}
void myLable::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(m_bEnable)
    {
//        m_bDoubleCheckFlag = !m_bDoubleCheckFlag;
//        if(m_bDoubleCheckFlag)
//        {
//            this->move(0,0);
//            this->resize(1920,1080);
//            this->raise();
//        }
//        else
//        {
//            this->move(m_OldPosX,m_OldPosY);
//            this->resize(300,200);
//        }
    }
    else
    {

    }
}
void myLable::RemberPos(int x, int y)
{
    m_OldPosX = x;
    m_OldPosY = y;
}
