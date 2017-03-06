#include "process.h"
#include "include.h"
void *ProcessFun(void *param);
process::process()
{
    m_pid = 0;
    m_RecvBuf = NULL;
}
process::~process()
{
    if(m_RecvBuf)
        delete m_RecvBuf;
}
int process::ProcessThread()
{
    char Buf[1024];
    char ActionBuf[100];
    while(!cMainExitFlag)
    {
        memset(Buf,0,1024);
        if(m_RecvBuf->Get(Buf,1) < 0)
        {
            sleep(2);
            continue;
        }
        g_pLog->WriteLog(0,"Process Recv:%s\n",Buf);
        if(strlen(Buf))
        {
            memset(ActionBuf,0,100);
            g_pJson->Parse(Buf);
            g_pJson->ReadJson(ActionBuf,"action");
            g_pLog->WriteLog(0,"Action:%s",ActionBuf);
            if(strcmp(ActionBuf,"shutdown") == 0)
            {
                printf("Shutdown \n");
                sleep(2);
                MainExit(0);

                system("shutdown -h now");
            }
            if(strcmp(ActionBuf,"reboot") == 0)
            {
                printf("Reboot \n");
                sleep(2);
                MainExit(0);

                system("shutdown -r now");
            }
            if(strcmp(ActionBuf,"enableConfiguration") == 0)
            {
                printf("shineng \n");

            }
            if(strcmp(ActionBuf,"remoteConfig") == 0)
            {
                char roomName[10];
                char seat[10];
                char type[10];
                char resolution[10];

                g_pJson->ReadJson_v(roomName,"data","roomName");
                g_pJson->ReadJson_v(seat,"data","seat");
                g_pJson->ReadJson_v(type,"data","type");
                g_pJson->ReadJson_v(resolution,"data","resolution");

                g_pLog->WriteLog(0,"roomName:%s seat:%s type:%s resolution:%s",\
                                 roomName,seat,type,resolution);
                if(strlen(roomName))
                    WriteConfigString(ConfigFileName,"ROOM","ClassName",roomName);
                if(strlen(seat))
                    WriteConfigString(ConfigFileName,"ROOM","SeatName",seat);
                if(strlen(type))
                    WriteConfigString(ConfigFileName,"ROOM","Types",type);
                if(strlen(resolution))
                    WriteConfigString(ConfigFileName,"ROOM","Resolution",resolution);
                sleep(2);
                MainExit(0);
               // sleep(1);
                system("shutdown -r now");
            }
            if(strcmp(ActionBuf,"exit_spicy") == 0)
            {
                printf("kill spicy\n");
                system("sudo kill -9 $(pgrep spicy)");
            }

            if(strcmp(ActionBuf,"upgrade") == 0)
            {
                char ip[20];
                char name[50];
                char passwd[50];
                char filepath[100];
                char ftpCmd[1024];
                char MD5[100];
                memset(MD5,0,100);
                memset(ip,0,20);
                memset(name,0,50);
                memset(passwd,0,50);
                memset(filepath,0,100);
                memset(ftpCmd,0,1024);

                g_pJson->ReadJson_v(ip,"data","address");
                g_pJson->ReadJson_v(name,"data","username");
                g_pJson->ReadJson_v(passwd,"data","password");
                g_pJson->ReadJson_v(filepath,"data","path");
               // g_pJson->ReadJson_v(MD5,"data","md5");
                g_pLog->WriteLog(0,"ftp[%s] Name:%s Passwd:%s File:%s",ip,name,passwd,filepath);
                sprintf(ftpCmd,"/usr/local/shencloud/TerminalUpdate.sh %s %s %s %s",ip,name,passwd,filepath);
                g_pLog->WriteLog(0,"ftp CMD:%s",ftpCmd);
                system(ftpCmd);
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
        iRecode = m_RecvBuf->InitBuf(1024,50,EXPANDMODE);
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
