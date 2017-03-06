#include "process.h"
#include "include.h"
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

process::process()
{
    m_pid = 0;
    m_RecvBuf = NULL;
    m_SpicyPid = -1;
    m_bExit = false;
    memset(&m_data,0,sizeof(m_data));
    m_data.s_IsArray = false;
    IsBack = false;
}
process::~process()
{
    m_bExit = true;
    sleep(2);
    if(m_RecvBuf)
        delete m_RecvBuf;
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
    char MessageBuf[1024];
    bool ReturnCode = false;
    memset(MessageBuf,0,1024);
    sprintf(MessageBuf,"###ap_confirmclassshowstatus###{\"data\":{\"id\":\"%s\"}}",m_strTerminalID);
    signal(SIGCHLD,WaitChildren);
    while(!m_bExit)
    {
        memset(Buf,0,102400);
        memset(ActionBuf,0,100);
/*        if(m_RecvBuf->Get(Buf,1) < 0)
        {
            sleep(2);
            continue;
        }*/
        if(!m_data.s_IsArray)
        {
            sleep(2);
            continue;
        }
        if(IsBack)
        {
            sleep(2);
            continue;
        }
        m_data.s_IsArray = false;
        printf("Process Recv:%s\n",Buf);
        strncpy(Buf,m_data.Data,DATABUFLEN);
        //g_Pproduce->send(Buf,strlen(Buf));
        if(Buf)
        {
            g_pMyJson->Parse(Buf);
            g_pMyJson->ReadJson(ActionBuf,"action");
            g_pLog->WriteLog(0,"Action:%s",ActionBuf);
            qDebug("Action:%s",ActionBuf);
            iRecode = g_pMyJson->ReadJson_v(TerminID,"data","receiveApIds",100);
            for(i = 0;i < iRecode && i < 100;i++)
            {
                qDebug("TerminID[%d]:%s",i,TerminID[i]);
                if(strcmp(TerminID[i],m_strTerminalID) == 0)
                    break;
            }
            if(i == iRecode)
                continue;
            if(strcmp(ActionBuf,"start_demonstrate") == 0)
            {
                system("/usr/bin/disable_input.sh &");
/*
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $8}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $9}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $10}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $11}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $12}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $13}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $14}' >> spicy.sh");
                system("echo " ">> spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk '{print $15}' >> spicy.sh");
*/
                system("rm /home/spicy.sh");
                system("ps -ef | grep spicy |grep -v grep |grep -v defunct | awk 'NR==1{print $8\"|\"$9\"|\"$10\"|\"$11\"|\"$12\"|\"$13\"|\"$14\"|\"$15}' >> spicy.sh");



                g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                char nodeList[100][100];
                char leafList[100][100];
                char nodeSysCmd[100];
                char leafSysCmd[100];
                int  ichoose = -1;
                pthread_t pid;
                memset(nodeSysCmd,0,100);
                memset(leafSysCmd,0,100);
                iRecode = g_pMyJson->ReadJson_v(nodeList,"data","nodeList",100);
                g_pMyJson->ReadJson_v(nodeSysCmd,"data","nodeCommand");
                g_pLog->WriteLog(0,"start_demonstrate:nodeCommand[%s]",nodeSysCmd);

                for(i = 0;i < iRecode;i++)
                {
                    if(strcmp(nodeList[i],m_strTerminalID) == 0)
                    {
                        ichoose = 0;
                        break;
                    }
                }
                iRecode = g_pMyJson->ReadJson_v(leafList,"data","leafList",100);
                g_pMyJson->ReadJson_v(leafSysCmd,"data","leafCommand");
                g_pLog->WriteLog(0,"start_demonstrate:leafCommand[%s]",leafSysCmd);
                for(i = 0;i < iRecode;i++)
                {
                    if(strcmp(leafList[i],m_strTerminalID) == 0)
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
                    system("killall -9 spicy");

                        if(pthread_create(&pid,NULL,ThreadForSystem,nodeSysCmd))
                        {
                            printf("create Thread Error");
                        }
                    }break;
                    case 1:
                    {
                        //system("kill -9 $(pgrep spicy)");
                    system("killall -9 spicy");
                        if(pthread_create(&pid,NULL,ThreadForSystem,leafSysCmd))
                        {
                            printf("create Thread Error");
                        }
                    }break;
                    default:qDebug("Error List");
                }
            }
            if(strcmp(ActionBuf,"stop_demonstrate") == 0)
            {
                system("/usr/bin/enable_input.sh &");
                pthread_t pid;
                char Buf[1024];
                memset(Buf,0,1024);
                g_Pproduce->send(MessageBuf,strlen(MessageBuf));
                system("kill -9 $(pgrep eclass_client)");
                FILE *pf = fopen("/home/spicy.sh","r");
                if(pf)
                {
                    fread(Buf,1024,1,pf);
                    g_pLog->WriteLog(0,"Buf:%s",Buf);
                }
                if(strlen(Buf))
                {
                    QString temp(Buf);
                    temp.replace("|"," ");
                    memset(Buf,0,1024);
                    strcpy(Buf,temp.toStdString().c_str());
                }
                if(pf)
                    fclose(pf);

                pf = fopen("/home/spicy.sh","w");
                if(pf)
                {
                    fwrite(Buf,strlen(Buf),1,pf);
                    g_pLog->WriteLog(0,"Buf:%s",Buf);
                }
                fclose(pf);
                system("chmod +x spicy.sh");
                if(pthread_create(&pid,NULL,ThreadForSystem,(void *)"/home/spicy.sh"))
                {
                    printf("create Thread Error");
                }
                sleep(5);
                system("rm /home/spicy.sh");
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
        strcpy(SystemBuf,p);
    printf("sysTem:%s\n",SystemBuf);
    system(SystemBuf);

}
int process::Start()
{
    int iRecode = 0;
    NetConfig netconfig;
/*    if(m_RecvBuf == NULL)
    {
        m_RecvBuf = new ListBuf();
        iRecode = m_RecvBuf->InitBuf(102400,10,EXPANDMODE);
        if(iRecode < 0)
        {
            g_pLog->WriteLog(0,"Init Recv Buf Error!");
            return -1;
        }
    }*/
    memset(m_strIP,0,20);
    netconfig.GetIPAddr(m_strIP);
    memset(m_strMac,0,50);
    netconfig.GetMacAdd(m_strMac,true);
    netconfig.GetMacAdd(m_strTerminalID,false);
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
