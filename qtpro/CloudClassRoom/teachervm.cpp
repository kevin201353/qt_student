#include "teachervm.h"
#include "interface.h"
#include "netconfig.h"
#include "include.h"
void *UpVMStatus(void *param);
TeacherVM::TeacherVM(QWidget *parent, const char *name,int status):QLabel(parent),m_strTeachetVMName(name),m_iStatus(status)
{
    memset(&m_VMInfo,0,sizeof(m_VMInfo));
    this->setMinimumSize(264,256);
    this->setMaximumSize(264,256);
    //this->setStyleSheet("background-color: rgb(0,0,127)");
    this->setPixmap(QPixmap(BACKGROUNDPNG));
    m_Font.setPixelSize(16);
    m_pVMNameQLabel = new QLabel(this);
    m_pVMNameQLabel->setFont(m_Font);
    m_pVMNameQLabel->setText(m_strTeachetVMName);
    m_pVMNameQLabel->setAlignment(Qt::AlignCenter);
    m_pVMNameQLabel->move(0,0);
    m_pVMNameQLabel->setMinimumSize(264,30);
    m_pVMNameQLabel->setMaximumSize(264,30);

    m_pDeskTopQLabel = new QLabel(this);
    m_pDeskTopQLabel->setMinimumSize(247,168);
    m_pDeskTopQLabel->setMaximumSize(247,168);
    m_pDeskTopQLabel->move(8,30);

    m_pStartPushButton = new QPushButton(this);
    m_pStartPushButton->setFlat(false);
    m_pStartPushButton->setMinimumSize(15,20);
    m_pStartPushButton->setMaximumSize(15,20);
    m_pStartPushButton->move(8,218);

    m_pStopPushButton = new QPushButton(this);
    m_pStopPushButton->setFlat(false);
    m_pStopPushButton->setMinimumSize(16,16);
    m_pStopPushButton->setMaximumSize(16,16);
    m_pStopPushButton->move(45,220);

    m_pRestartPushButton = new QPushButton(this);
    m_pRestartPushButton->setMinimumSize(24,24);
    m_pRestartPushButton->setMaximumSize(24,24);
    m_pRestartPushButton->move(88,215);

    m_pConnectPushButton = new QPushButton(this);
    m_pConnectPushButton->setMinimumSize(30,30);
    m_pConnectPushButton->setMaximumSize(30,30);
    m_pConnectPushButton->move(200,210);

    SetStatus(m_iStatus);

    connect(m_pStartPushButton,SIGNAL(clicked()),this,SLOT(on_StartPushButton()));
    connect(m_pStopPushButton,SIGNAL(clicked()),this,SLOT(on_StopPushButton()));
    connect(m_pRestartPushButton,SIGNAL(clicked()),this,SLOT(on_RestartPushButton()));
    connect(m_pConnectPushButton,SIGNAL(clicked()),this,SLOT(on_ConnectPushButton()));
    //this->setAttribute(Qt::WA_DeleteOnClose,true);
    connect(this,SIGNAL(StatusChanged(int)),this,SLOT(ChangeStatus(int)));

}

void TeacherVM::SetStatus(int status)
{
    switch(status)
    {
    case CLOSE:
        m_pDeskTopQLabel->setPixmap(QPixmap(DESKTOPCLOSEPNG));
        m_pStartPushButton->setStyleSheet(QStringLiteral(STARTENABLE));
        m_pStartPushButton->setEnabled(true);
        m_pStopPushButton->setStyleSheet(QStringLiteral(STOPDISABLE));
        m_pStopPushButton->setEnabled(false);
        m_pRestartPushButton->setStyleSheet(QStringLiteral(RESTDISABLE));
        m_pRestartPushButton->setEnabled(false);
        m_pConnectPushButton->setStyleSheet(QStringLiteral(CONNECTDISABLE));
        m_pConnectPushButton->setEnabled(false);
        break;
    case RESTART:
        m_pDeskTopQLabel->setPixmap(QPixmap(DESKTOPRESTART));
        m_pStartPushButton->setStyleSheet(QStringLiteral(STARTDISABLE));
        m_pStartPushButton->setEnabled(false);
        m_pStopPushButton->setStyleSheet(QStringLiteral(STOPENABLE));
        m_pStopPushButton->setEnabled(false);
        m_pRestartPushButton->setStyleSheet(QStringLiteral(RESTDISABLE));
        m_pRestartPushButton->setEnabled(false);
        m_pConnectPushButton->setStyleSheet(QStringLiteral(CONNECTDISABLE));
        m_pConnectPushButton->setEnabled(false);
        break;
    case USING:
        m_pDeskTopQLabel->setPixmap(QPixmap(DESKTOPUSING));
        m_pStartPushButton->setStyleSheet(QStringLiteral(STARTDISABLE));
        m_pStartPushButton->setEnabled(false);
        m_pStopPushButton->setStyleSheet(QStringLiteral(STOPENABLE));
        m_pStopPushButton->setEnabled(true);
        m_pRestartPushButton->setStyleSheet(QStringLiteral(RESTENABLE));
        m_pRestartPushButton->setEnabled(true);
        m_pConnectPushButton->setStyleSheet(QStringLiteral(CONNECTENABLE));
        m_pConnectPushButton->setEnabled(true);
        break;
    case ERROR:
        m_pDeskTopQLabel->setPixmap(QPixmap(DESKTOPERROR));
        m_pStartPushButton->setStyleSheet(QStringLiteral(STARTDISABLE));
        m_pStartPushButton->setEnabled(false);
        m_pStopPushButton->setStyleSheet(QStringLiteral(STOPDISABLE));
        m_pStopPushButton->setEnabled(false);
        m_pRestartPushButton->setStyleSheet(QStringLiteral(RESTDISABLE));
        m_pRestartPushButton->setEnabled(false);
        m_pConnectPushButton->setStyleSheet(QStringLiteral(CONNECTDISABLE));
        m_pConnectPushButton->setEnabled(false);
        break;
    case WARNING:
        m_pDeskTopQLabel->setPixmap(QPixmap(DESKTOPWARNING));
        m_pStartPushButton->setStyleSheet(QStringLiteral(STARTDISABLE));
        m_pStartPushButton->setEnabled(false);
        m_pStopPushButton->setStyleSheet(QStringLiteral(STOPENABLE));
        m_pStopPushButton->setEnabled(true);
        m_pRestartPushButton->setStyleSheet(QStringLiteral(RESTENABLE));
        m_pRestartPushButton->setEnabled(true);
        m_pConnectPushButton->setStyleSheet(QStringLiteral(CONNECTENABLE));
        m_pConnectPushButton->setEnabled(true);
        break;
    }

}
void TeacherVM::SetVMInfo(const char *VMid)
{
    if(VMid != NULL)
    {
        strcpy(m_VMInfo.s_strVMID,VMid);
    }
}

void TeacherVM::on_StartPushButton()
{
    bool ReturnCode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pStartPushButton->setEnabled(false);
    m_iStatus = CLOSE;
    if(strlen(m_VMInfo.s_strVMID))
    {
        g_pLog->WriteLog(0,"VMID:%s",m_VMInfo.s_strVMID);
        sprintf(TempBuf,"/service/desktops/start?ids[0]=%s",m_VMInfo.s_strVMID);
    }
    g_pMyHttp->Get(TempBuf);
    g_pLog->WriteLog(0,"Start Teacher VM:%s",TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Start Teacher VM Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        SetStatus(RESTART);
        pthread_t pid;
        if(pthread_create(&pid,NULL,UpVMStatus,this))
        {
            SetStatus(m_iStatus);
        }
        //sleep(5);
    }
    else
    {
        m_pStartPushButton->setEnabled(true);
    }
}
void *UpVMStatus(void *param)
{
    TeacherVM *p = (TeacherVM*)param;
        p->CheckVMStatus();
        return NULL;
}
void TeacherVM::CheckVMStatus()
{
    int ContinueNum = 10;
    char TempBuf[200];
    char JsonBuf[102400];
    char strVMID[TEACHERVMNUM][100];
    int VMStatus[TEACHERVMNUM];
    bool ReturnCode = false;
    myHttp http;
    http.SetUrlIP(g_strServerIP);
    while(ContinueNum--)
    {
        sleep(10);
        memset(TempBuf,0,200);
        memset(JsonBuf,0,102400);
        sprintf(TempBuf,"/service/desktops/list?qp.filterWhere={\"type\":\"teacher\",\"seat\":\"%s\"}",\
                g_strTeacherName);
        g_pLog->WriteLog(0,"CheckVMStatus Get VM Teacher VM:%s",TempBuf);
        http.Get(TempBuf);
        memset(JsonBuf,0,102400);
        http.GetData(JsonBuf);
        g_pLog->WriteLog(0,"CheckVMStatus Get Teacher VM Recv Json:%s",JsonBuf);
        ReturnCode = false;
        g_pMyJson->Parse(JsonBuf);
        g_pMyJson->ReadJson(&ReturnCode,"success");
        if(ReturnCode)
        {
            memset(strVMID,0,sizeof(strVMID));
            memset(VMStatus,0,sizeof(VMStatus));
            int iRecode = g_pMyJson->ReadJson(strVMID,"data","list","id",TEACHERVMNUM);
            iRecode = g_pMyJson->ReadJson(VMStatus,"data","list","status",TEACHERVMNUM);
            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
            {
                if(strcmp(strVMID[i],m_VMInfo.s_strVMID) == 0)
                {
                    switch(VMStatus[i])
                    {
                    case 2:m_iStatus = USING;
                        break;
                    case 1:m_iStatus = CLOSE;
                        break;
                    case 3:m_iStatus = RESTART;
                        break;
                    case 8:m_iStatus = WARNING;
                        break;
                    default:m_iStatus = ERROR;
                        break;
                    }
                    //SetStatus(m_iStatus);
                    emit StatusChanged(m_iStatus);
                    if(m_iStatus == USING)
                    {
                        for(int j = 0;j < g_TeacherVMSet.s_VMNum;j++)
                        {
                            if(strcmp(g_TeacherVMSet.s_pVMInfo[j].s_strVMID,m_VMInfo.s_strVMID) == 0)
                            {
                                g_TeacherVMSet.s_pVMInfo[j].s_VMStatus = USING;
                                break;
                            }
                        }
                        return ;
                    }
                }
            }
        }
        else
        {
            break;
        }

    }
}
void TeacherVM::ChangeStatus(int Status)
{
    SetStatus(Status);
}
void TeacherVM::on_StopPushButton()
{
    bool ReturnCode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pStopPushButton->setEnabled(false);
    if(strlen(m_VMInfo.s_strVMID))
    {
        qDebug("VMID:%s",m_VMInfo.s_strVMID);
        sprintf(TempBuf,"/service/desktops/shutdown?ids[0]=%s",m_VMInfo.s_strVMID);
    }
    g_pMyHttp->Get(TempBuf);
    g_pLog->WriteLog(0,"Stop Teacher VM:%s",TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Stop Teacher VM Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        SetStatus(CLOSE);
        for(int j = 0;j < g_TeacherVMSet.s_VMNum;j++)
        {
            if(strcmp(g_TeacherVMSet.s_pVMInfo[j].s_strVMID,m_VMInfo.s_strVMID) == 0)
            {
                g_TeacherVMSet.s_pVMInfo[j].s_VMStatus = CLOSE;
                break;
            }
        }
    }
    m_pStopPushButton->setEnabled(true);
}
void TeacherVM::on_RestartPushButton()
{
    bool ReturnCode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pRestartPushButton->setEnabled(false);
    m_iStatus = USING;
    if(strlen(m_VMInfo.s_strVMID))
    {
        sprintf(TempBuf,"/service/desktops/reboot?ids[0]=%s&isSave=",m_VMInfo.s_strVMID);
    }
    g_pMyHttp->Get(TempBuf);
    g_pLog->WriteLog(0,"Restart Teacher VM:%s",TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Restart Teacher VM Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        SetStatus(RESTART);
        pthread_t pid;
        if(pthread_create(&pid,NULL,UpVMStatus,this))
        {
            SetStatus(m_iStatus);
        }
    }
    else
    {
        m_pRestartPushButton->setEnabled(true);
    }
}
void TeacherVM::on_ConnectPushButton()
{
    int Pid = -1;
    bool ReturnCode = false;
    char TempBuf[100];
    char JsonBuf[102400];
    int Port = 0;
    char IP[20];
    char Ticket[50];
    memset(IP,0,20);
    memset(Ticket,0,50);
    memset(JsonBuf,0,102400);
    memset(TempBuf,0,100);
    m_pConnectPushButton->setEnabled(false);
    if(strlen(m_VMInfo.s_strVMID))
    {
        sprintf(TempBuf,"vmId=%s&roomName=%s",m_VMInfo.s_strVMID,g_strRoomNum);
    }
    g_pLog->WriteLog(0,"Connect Teacher VM:%s",TempBuf);
    g_pMyHttp->Post("/service/desktops/tec_display",TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Connect Teacher VM Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        g_pMyJson->ReadJson_v(&Port,"data","port");
        g_pMyJson->ReadJson_v(IP,"data","host");
        g_pMyJson->ReadJson_v(Ticket,"data","ticket");
        g_pLog->WriteLog(0,"IP:%s Port:%d Ticket:%s",IP,Port,Ticket);

        system("cat /tmp/data_*");
        system("rm -f /tmp/data_port");
        system("rm -f /tmp/data_xor");
        Pid = Run_Spicy(IP,(unsigned int)Port,Ticket);

        g_pLog->WriteLog(0,"Class Press ID:%d",Pid);
        while(access("/tmp/data_port",F_OK))
        {
            if(Pid < 0)
                break;
        }

        system("cat /tmp/data/data_*");
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
        char IP[20];
        memset(IP,0,20);
        char Mac[50];
        memset(Mac,0,50);
        g_pNetConfig->GetIPAddr(IP);
        g_pNetConfig->GetMacAdd(Mac,true);
        char append[1024];
        memset(append,0,1024);
        sprintf(append,"vmId=%s&connected=true&apIp=%s&apMac=%s&dsPort=%s&dsXor=%s",\
                m_VMInfo.s_strVMID,IP,Mac,port,data_xor);
        g_pLog->WriteLog(0,"Report Action:%s",append);
        g_pMyHttp->Post("/service/aps/report_action",append);
        memset(JsonBuf,0,102400);
        g_pMyHttp->GetData(JsonBuf);
        g_pMyJson->Parse(JsonBuf);
        g_pLog->WriteLog(0,"Start Up:%s\n",JsonBuf);
        g_pMyJson->ReadJson(&ReturnCode,"success");
        if(ReturnCode)
        {
            g_pLog->WriteLog(0,"Report connect[true] Success");
        }
        else
        {
            g_pLog->WriteLog(0,"Report connect[true] Error");
        }
        wait(&Pid);

        memset(append,0,1024);
        memset(JsonBuf,0,102400);
        sprintf(append,"vmId=%s&connected=false",\
                m_VMInfo.s_strVMID);
        g_pMyHttp->Post("/service/aps/report_action",append);
        g_pMyHttp->GetData(JsonBuf);
        g_pLog->WriteLog(0,"Over UP:%s\n",JsonBuf);
        g_pMyJson->Parse(JsonBuf);
        g_pMyJson->ReadJson(&ReturnCode,"success");
        if(ReturnCode)
        {
            g_pLog->WriteLog(0,"Report connect[false] Success");
        }
        else
        {
            g_pLog->WriteLog(0,"Report connect[false] Error");
        }
    }
    m_pConnectPushButton->setEnabled(true);
}
