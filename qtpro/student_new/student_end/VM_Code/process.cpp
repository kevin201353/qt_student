#include "process.h"
#include "include.h"
#include "global.h"
#include <QDateTime>
#include <QByteArray>

void *ProcessFun(void *param);
void *ThreadForSystem(void *para);
void WaitChildren(int num)
{
    //我接受到了SIGCHLD的信号啦
    int status;
    int pid = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status))
    {
        printf("The child exit with code %d",WEXITSTATUS(status));
    }
}

process::process(LoginWidget *widget)
{
    m_pid = 0;
    m_RecvBuf = NULL;
    m_pWidget = widget;
    m_SpicyPid = -1;
    memset(&m_data,0,sizeof(m_data));
    m_data.s_IsArray = false;
    pthread_mutex_init(&m_Locak,NULL);
}
process::~process()
{
    if(m_RecvBuf)
        delete m_RecvBuf;
    pthread_mutex_destroy(&m_Locak);
}

static pthread_t g_xtid = 0;
static char g_szCmd[1024] = {0};
char g_szRetVm[1024] = {0};
static void *thrd_exec(void *param)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QByteArray ba = str.toLatin1();
    char szcmdTmp[500] = {0};
    strcpy(szcmdTmp, ba.data());
    strcat(szcmdTmp, " ----- ");
    strcat(szcmdTmp, g_szCmd);
    PIPE_SPICYLOG(szcmdTmp);
    FILE *fp;
    if ((fp = popen(g_szCmd, "r")) == NULL)
    {
        g_pLog->WriteLog(0,"zhaosenhua thrd_exec spicy cmd failed.");
    }
    pclose(fp);
    return NULL;
}

int process::ProcessThread()
{
    myHttp http;
    http.SetUrlIP(g_strServerIP);
    char Buf[102400];
    char ActionBuf[100];
    char TerminID[100][100];
    int iRecode = 0;
    int i = 0;
    int iConnectNum = 0;
    cMainExitFlag = 1;
    char MessageBuf[1024];
    bool ReturnCode = false;
    memset(MessageBuf,0,1024);
    sprintf(MessageBuf,"###ap_confirmclassstatus###{\"data\":{\"id\":\"%s\"}}",g_strTerminalID);
    signal(SIGCHLD,WaitChildren);
    bool bMsg_Running = false;
    while(cMainExitFlag)
    {
        memset(Buf,0,102400);
        memset(ActionBuf,0,100);
        //g_pLog->WriteLog(0,"zhaosenhua ProcessThread isArray value is : %d .", m_data.s_IsArray);
        if(!m_data.s_IsArray)
        {
            qDebug("sleep 2");
            //g_pLog->WriteLog(0,"zhaosenhua ProcessThread isArray sleeping  xxx .");
            sleep(2);
            continue;
        }
        m_data.s_IsArray = false;
        printf("Process Recv:%s\n",Buf);
        strncpy(Buf,m_data.Data,DATABUFLEN);
        g_pLog->WriteLog(0,"zhaosenhua processThread view buf  : %s ",Buf);
//        qDebug() << QString(Buf);
//        //test
//        strcpy(Buf, "");
//        sleep(1);
//        continue;
//        //test
        if(Buf)
        {
            bMsg_Running = false;
            g_pJson->Parse(Buf);
            g_pJson->ReadJson(ActionBuf,"action");
            g_pLog->WriteLog(0,"Action:%s",ActionBuf);
            qDebug("Action:%s",ActionBuf);
            iRecode = g_pJson->ReadJson_v(TerminID,"data","receiveApIds",100);

            for(i = 0;i < iRecode && i < 100;i++)
            {
                qDebug("TerminID[%d]:%s",i,TerminID[i]);
                if(strcmp(TerminID[i],g_strTerminalID) == 0)
                {
                    bMsg_Running = true;
                    break;
                }
            }
//            if(i == iRecode)
//            {
//                //g_pLog->WriteLog(0,"zhaosenhua ProcessThread i == iRecode  llll.");
//                continue;
//            }
            if (!bMsg_Running)
                continue;
            g_pLog->WriteLog(0,"zhaosenhua 222 Action:%s", ActionBuf);
            if(strcmp(ActionBuf,"begin") == 0)
            {
                ReportMsg reportmsg;
                reportmsg.action = USER_WAITINGDLG_SHOW;
                call_msg_back(msg_respose, reportmsg);
                memset(g_szRetVm, 0, 1024);
                memset(g_szCmd, 0, 1024);
                memset(MessageBuf,0,1024);
                sprintf(MessageBuf,"###ap_confirmclassstatus###{\"data\":{\"id\":\"%s\"}}",g_strTerminalID);
                //shangke  diao yong jie kou
                printf("\nbegin\n");
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
                qDebug("Connect Post Buf:%s",TempBuf);
                g_pLog->WriteLog(0,"Connect Post Buf:%s",TempBuf);
                http.Post("/service/desktops/stu_display",TempBuf);
                http.GetData(JsonBuf);
                qDebug("Connect Json:%s",JsonBuf);
                g_pLog->WriteLog(0,"Connect Json:%s",JsonBuf);
                g_pJson->Parse(JsonBuf);
                ReturnCode = false;
                g_pJson->ReadJson(&ReturnCode,"success");
                if(ReturnCode)
                {
                    iConnectNum = 0;
                    m_pWidget->m_pGroupWigdet->setEnabled(false);
                    g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                    g_pJson->ReadJson_v(&Port,"data","port");
                    g_pJson->ReadJson_v(IP,"data","host");
                    g_pJson->ReadJson_v(Ticket,"data","ticket");
                    memset(m_strVmID,0,50);
                    g_pJson->ReadJson_v(m_strVmID,"data","vmId");
                    qDebug("IP:%s Port:%d Ticket:%s VmID:%s",IP,Port,Ticket,m_strVmID);
                    g_pLog->WriteLog(0,"IP:%s Port:%d Ticket:%s VmID:%s",IP,Port,Ticket,m_strVmID);

                    system("cat /tmp/data_*");
                    system("rm -f /tmp/data_*");
                    system("kill -9 $(pgrep spicy)");
                    //system("killall -9 spicy");
 //                   m_SpicyPid = Run_Spicy(IP,(unsigned int)Port,Ticket);
                    sprintf(g_szCmd, "spicy.sh -h %s -p %d -f > %s", IP, Port, "/usr/local/shencloud/log/spicy.log");
                    strcpy(g_szRetVm, g_szCmd);
                    if (pthread_create(&g_xtid, NULL, thrd_exec, NULL) != 0)
                    {
                        g_pLog->WriteLog(0,"zhaosenhua create spicy thread failed.");
                    }
                    //g_pLog->WriteLog(0,"Class Press ID:%d",m_SpicyPid);
                    int ncount = 0;
                    //bool bcontinue = false;
                    while(access("/tmp/data_port",F_OK))
                    {
//                        if(m_SpicyPid < 0)
//                        {
//                            bcontinue = true;
//                            break;
//                        }
                        if (ncount >= 10)
                        {
                            //bcontinue = true;
                            break;
                        }
                        ncount++;
                        sleep(1);
                    }
//                    if (bcontinue)
//                    {
//                        reportmsg.action = USER_WAITINGDLG_EXIT;
//                        call_msg_back(msg_respose, reportmsg);
//                    }
//                    pthread_join(g_xtid, NULL);
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
                    char append[1024];
                    memset(append,0,1024);
                    sprintf(append,"vmId=%s&connected=true&apIp=%s&apMac=%s&dsPort=%s&dsXor=%s",\
                            m_strVmID,m_strIP,m_strMac,port,data_xor);
                    g_pLog->WriteLog(0,"Report Action:%s",append);
                    http.Post("/service/aps/report_action",append);
                    memset(JsonBuf,0,1024);
                    http.GetData(JsonBuf);
                    g_pJson->Parse(JsonBuf);
                    g_pLog->WriteLog(0,"Begin Up:%s\n",JsonBuf);
                    ReturnCode = false;
                    g_pJson->ReadJson(&ReturnCode,"success");
                    if(ReturnCode)
                    {
                        g_pLog->WriteLog(0,"Report connect[true] Success");
                    }
                    else
                    {
                        g_pLog->WriteLog(0,"Report connect[true] Error");
                    }
                }
                else
                {
                    iConnectNum++;
                    if(iConnectNum == 5)
                    {
                        iConnectNum = 0;
                        //xianshi tan chuang
                    }
                }
            }
            if(strcmp(ActionBuf,"over") == 0)
            {
                ReportMsg reportmsg;
                reportmsg.action = USER_WAITINGDLG_EXIT;
                call_msg_back(msg_respose, reportmsg);
                memset(g_szRetVm, 0, 1024);
                memset(MessageBuf,0,1024);
                sprintf(MessageBuf,"###ap_confirmclassstatus###{\"data\":{\"id\":\"%s\"}}",g_strTerminalID);
                char JsonBuf[1024];
                memset(JsonBuf,0,1024);
                g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                //xiake
                m_pWidget->m_pGroupWigdet->setEnabled(false);
                system("sudo kill -9 $(pgrep spicy)");
                //system("killall -9 spicy");
                printf("\nover\n");
                char append[100];
                memset(append,0,100);
                sprintf(append,"vmId=%s&connected=false",m_strVmID);
                g_pLog->WriteLog(0,"Over UP Post:%s",append);
                http.Post("/service/aps/report_action",append);
                http.GetData(JsonBuf);
                g_pLog->WriteLog(0,"Over UP:%s\n",JsonBuf);
                g_pJson->Parse(JsonBuf);
                ReturnCode = false;
                g_pJson->ReadJson(&ReturnCode,"success");
                if(ReturnCode)
                {
                    g_pLog->WriteLog(0,"Report connect[false] Success");
                }
                else
                {
                    g_pLog->WriteLog(0,"Report connect[false] Error");
                }
            }
            if(strcmp(ActionBuf,"freeStudy") == 0)
            {
                memset(MessageBuf,0,1024);
                sprintf(MessageBuf,"###ap_confirmclassstatus###{\"data\":{\"id\":\"%s\"}}",g_strTerminalID);
                //zixi
                char JsonBuf[102400];
                char ClassName[MAXCLASS][100];
                char ClassID[MAXCLASS][100];
                bool Recode = false;
                memset(JsonBuf,0,102400);
                qDebug("\nfreeStudy\n");
                sprintf(JsonBuf,"qp.filterWhere={\"room_name\":\"%s\"}",g_strRoomNum);
                g_pLog->WriteLog(0,"Freestudy Get Connect Post:%s",JsonBuf);
                http.Post("/service/desktop_pools/list",JsonBuf);
                memset(JsonBuf,0,102400);
                http.GetData(JsonBuf);
                qDebug("Recv Connect:%s",JsonBuf);
                g_pLog->WriteLog(0,"Recv Connect:%s",JsonBuf);
                g_pJson->Parse(JsonBuf);
                g_pJson->ReadJson(&Recode,"success");
                if(Recode)
                {
                    m_pWidget->m_pClassNameConfig->m_iClassNum = 0;
                    m_pWidget->SetChecked();
                    g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                    int iRecode = g_pJson->ReadJson(ClassName,"data","list","name",MAXCLASS);
                    iRecode = g_pJson->ReadJson(ClassID,"data","list","id",MAXCLASS);
                    g_pLog->WriteLog(0,"Study:%d",iRecode);
                    for(int i = 0;i < iRecode;i++)
                    {
                        m_pWidget->m_pClassNameConfig->AddClass(ClassName[i],ClassID[i]);
                    }
                    m_pWidget->m_pGroupWigdet->setEnabled(true);
                    m_pWidget->m_pClassNameConfig->ChooseOne();
                    m_pWidget->m_pClassNameConfig->SetLabelName();
                }
                else
                {
                    //tan chuang
                }
            }
            if(strcmp(ActionBuf,"start_demonstrate") == 0)
            {
                memset(MessageBuf,0,1024);
                sprintf(MessageBuf,"###ap_confirmclassshowstatus###{\"data\":{\"id\":\"%s\"}}",g_strTerminalID);
                //system("sudo rm /usr/local/shencloud/spicy.sh");
                //system("sudo ps -ef | grep spicy |grep -v grep |grep -v spicy.sh | awk 'NR==1{print $8\" \"$9\" \"$10\" \"$11\" \"$12\" \"$13\" \"$14\" \"$15}' >> /usr/local/shencloud/spicy.sh");
                g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                char nodeList[100][100];
                char leafList[100][100];
                char nodeSysCmd[1024];
                char leafSysCmd[1024];
                int  ichoose = -1;
                pthread_t pid;
                memset(nodeSysCmd,0,1024);
                memset(leafSysCmd,0,1024);
                iRecode = g_pJson->ReadJson_v(nodeList,"data","nodeList",100);
                g_pJson->ReadJson_v(nodeSysCmd,"data","nodeCommand");
                g_pLog->WriteLog(0,"start_demonstrate:nodeCommand[%s]",nodeSysCmd);

                for(i = 0;i < iRecode;i++)
                {
                    if(strcmp(nodeList[i],g_strTerminalID) == 0)
                    {
                        ichoose = 0;
                        break;
                    }
                }
                iRecode = g_pJson->ReadJson_v(leafList,"data","leafList",100);
                g_pJson->ReadJson_v(leafSysCmd,"data","leafCommand");
                g_pLog->WriteLog(0,"start_demonstrate:leafCommand[%s]",leafSysCmd);
                for(i = 0;i < iRecode;i++)
                {
                    if(strcmp(leafList[i],g_strTerminalID) == 0)
                    {
                        ichoose = 1;
                        break;
                    }
                }
                switch (ichoose)
                {
                    case 0:
                    {
                        //system("kill -9 $(pgrep spicy)");
                        system("sudo killall -9 spicy");
                        system("sudo usr/local/shencloud/disable_input.sh &");
                        strcat(nodeSysCmd, " >>/usr/local/shencloud/log/Eclass.log");
                        if(pthread_create(&pid,NULL,ThreadForSystem,nodeSysCmd))
                        {
                            printf("create Thread Error");
                        }
                    }break;
                    case 1:
                    {
                        //system("kill -9 $(pgrep spicy)");
                        system("sudo killall -9 spicy");
                        system("sudo usr/local/shencloud/disable_input.sh &");
                        strcat(leafSysCmd, " >>/usr/local/shencloud/log/Eclass.log");
                        if(pthread_create(&pid,NULL,ThreadForSystem,leafSysCmd))
                        {
                            printf("create Thread Error");
                        }
                    }
                    break;
                    default:qDebug("Error List");
                }
            }
            if(strcmp(ActionBuf,"stop_demonstrate") == 0)
            {
                system("sudo /usr/local/shencloud/enable_input.sh &");
                pthread_t pid;
                char Buf[1024];
                memset(Buf,0,1024);
                memset(MessageBuf,0,1024);
                sprintf(MessageBuf,"###ap_confirmclassshowstatus###{\"data\":{\"id\":\"%s\"}}",g_strTerminalID);
                g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                system("sudo kill -9 $(pgrep eclass_client)");
                system("sudo chmod +x /usr/local/shencloud/spicy.sh");
                if(pthread_create(&pid,NULL,ThreadForSystem,(void *)g_szRetVm/*"sudo /usr/local/shencloud/spicy.sh"*/))
                {
                    printf("create Thread Error");
                }
                //sleep(5);
                //system("sudo rm /usr/local/shencloud/spicy.sh");
            }
        }
        sleep(1);
    }
    return 0;
}
void *ThreadForSystem(void *para)
{
    char SystemBuf[1024];
    memset(SystemBuf,0,1024);
    char *p = (char *)para;
    if(p)
    {
        strcpy(SystemBuf,p);
        printf("sysTem:%s\n",SystemBuf);
        system(SystemBuf);
    }
}
void process::Lock()
{
    pthread_mutex_lock(&m_Locak);
}

void process::UnLock()
{
    pthread_mutex_unlock(&m_Locak);
}

int process::Start()
{
    NetConfig netconfig;
    memset(m_strIP,0,20);
    netconfig.GetIPAddr(m_strIP);
    memset(m_strMac,0,50);
    netconfig.GetMacAdd(m_strMac,true);
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
