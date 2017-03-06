#include "process.h"
#include "include.h"
void *ProcessFun(void *param);
process::process(LoginWidget *widget)
{
    m_pid = 0;
    m_RecvBuf = NULL;
    m_pWidget = widget;
    m_SpicyPid = -1;
}
process::~process()
{
    if(m_RecvBuf)
        delete m_RecvBuf;
}
int process::ProcessThread()
{
    myHttp http;
    http.SetUrlIP(g_strServerIP);
    char Buf[1024];
    char ActionBuf[100];
    cMainExitFlag = 1;
    while(cMainExitFlag)
    {
        memset(Buf,0,1024);
        memset(ActionBuf,0,100);
        if(m_RecvBuf->Get(Buf,1) < 0)
        {
            sleep(2);
            continue;
        }
        printf("Process Recv:%s\n",Buf);
        //g_Pproduce->send(Buf,strlen(Buf));
        if(Buf)
        {
            g_pJson->Parse(Buf);
            g_pJson->ReadJson(ActionBuf,"action");
            g_pLog->WriteLog(0,"Action:%s",ActionBuf);
            if(strcmp(ActionBuf,"begin") == 0)
            {
                //shangke  diao yong jie kou
                printf("\nbegin\n");
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
                    sprintf(TempBuf,"seatNumber=%s&roomName=%s",g_strSeatNum,g_strRoomNum);
                }
                else
                {

                }
                qDebug("Connect Post Buf:%s",TempBuf);
                http.Post("/edu/service/desktops/stu_display",TempBuf);
                http.GetData(JsonBuf);
                qDebug("Connect Json:%s",JsonBuf);
                g_pJson->Parse(JsonBuf);
                g_pJson->ReadJson(&ReturnCode,"success");
                if(ReturnCode)
                {
                    g_pJson->ReadJson_v(&Port,"data","sport");
                    g_pJson->ReadJson_v(IP,"data","host");
                    g_pJson->ReadJson_v(Ticket,"data","ticket");
                    qDebug("IP:%s Port:%d Ticket:%s",IP,Port,Ticket);
                    m_SpicyPid = Run_Spicy(IP,(unsigned int)Port,Ticket);
                }
            }
            if(strcmp(ActionBuf,"over") == 0)
            {
                //xiake
                char SysTempBuf[100];
                memset(SysTempBuf,0,100);
                sprintf(SysTempBuf,"kill -9 %d",m_SpicyPid);
                if(m_SpicyPid > 0)
                    system(SysTempBuf);
                printf("\nover\n");
            }
            if(strcmp(ActionBuf,"freeStudy") == 0)
            {
                //zixi
                char JsonBuf[102400];
                char ClassName[MAXCLASS][100];
                char ClassID[MAXCLASS][100];
                bool Recode = false;
                memset(JsonBuf,0,102400);
                qDebug("\nfreeStudy\n");
                strcpy(JsonBuf,"q.field=cluster&q.value=Default");
                http.Post("/edu/service/desktop_pools/list",JsonBuf);
                memset(JsonBuf,0,102400);
                http.GetData(JsonBuf);
                qDebug("%s",JsonBuf);
                g_pJson->Parse(JsonBuf);
                g_pJson->ReadJson(&Recode,"success");
                if(Recode)
                {
                    int iRecode = g_pJson->ReadJson(ClassName,"data","name",MAXCLASS);
                    iRecode = g_pJson->ReadJson(ClassID,"data","id",MAXCLASS);
                    for(int i = 0;i < iRecode;i++)
                    {
                        m_pWidget->m_pClassNameConfig->AddClass(ClassName[i],ClassID[i]);
                    }
                    m_pWidget->m_pGroupWigdet->setEnabled(true);
                }
                else
                {
                    //tan chuang
                }
            }
        }
        sleep(1);
    }
    return 0;
}
int process::Start()
{
    int iRecode = 0;
    if(m_RecvBuf == NULL)
    {
        m_RecvBuf = new ListBuf();
        iRecode = m_RecvBuf->InitBuf(1024,1024,EXPANDMODE);
        if(iRecode < 0)
        {
            g_pLog->WriteLog(0,"Init Recv Buf Error!");
            return -1;
        }
    }
    if(pthread_create(&m_pid,NULL,ProcessFun,this))
    {
        printf("Create Error!\n");
    }
    return 0;
}

void *ProcessFun(void *param)
{
    process *Temp = (process*)param;
    Temp->ProcessThread();
    return NULL;
}
