#include "include.h"
//#include <string.h>
//using namespace std;

Log *g_pLog = NULL;
//TcpServer *g_pTcp = NULL;
myJson *g_pJson = NULL;
process *g_pProcess = NULL;
char cMainExitFlag = 0;
ActiveMQConsumer *g_Pconsume = NULL;
ActiveMQProduce *g_Pproduce = NULL;
string g_strProduceAdd;
string g_strConsumerAdd;
string g_strProduceQueue;
string g_strConsumerQueue;
NetConfig *g_pNetConfig = NULL;
SystemInfo *g_PsysTemInfo = NULL;
char ConfigFileName[100];

void MainExit(int sig)
{
    if(sig == 10)
    {
        printf("Recv signal USER1\n");
    }
    cMainExitFlag = 1;

//    if(g_pTcp)
//    {
//        delete g_pTcp;
//        g_pTcp = NULL;
//    }
    if(g_pJson)
    {
        delete g_pJson;
        g_pJson = NULL;
    }
    if(g_pProcess)
    {
        delete g_pProcess;
        g_pProcess = NULL;
    }
    if(g_Pconsume)
    {
        delete g_Pconsume;
        g_Pconsume = NULL;
    }
    if(g_Pproduce)
    {
        delete g_Pproduce;
        g_Pproduce = NULL;
    }
    if(g_PsysTemInfo)
    {
        delete g_PsysTemInfo;
        g_PsysTemInfo = NULL;
    }
    if(g_pLog)
    {
        delete g_pLog;
        g_pLog = NULL;
    }
    sleep(1);
    printf(VISION_END,__DATE__,__TIME__);
}

int DameonInit(void)
{
    pid_t pid = 0;
    pid = fork();
    if(pid < 0)
    {
        return -1;
    }
    if(pid > 0)
    {
        exit(0);
    }
    if(setsid() < 0)
    {
        return -2;
    }
    pid = fork();

    if(pid < 0)
    {
        return -1;
    }
    if(pid > 0)
    {
        exit(0);
    }

    umask(0);

//    signal(SIGCHLD,SIG_IGN);
//    signal(SIGALRM,SIG_IGN);
//    signal(SIGTERM,SIG_IGN);
//    signal(SIGPIPE,SIG_IGN);
//    signal(SIGINT,SIG_IGN);
//    signal(SIGQUIT,SIG_IGN);
//    signal(SIGUSR1,MainExit);

    return 0;
}

void Regist()
{
    char SendJsonBuf[1024];
    char JsonBuf[1024];
    int iTemp = 0;
    memset(SendJsonBuf,0,1024);

    memset(JsonBuf,0,1024);
    g_pNetConfig->GetMacAdd(JsonBuf,0);
    g_pJson->WriteJson(JsonBuf,"data","id");

    memset(JsonBuf,0,1024);
    g_pNetConfig->GetIPAddr(JsonBuf);
    g_pJson->WriteJson(JsonBuf,"data","ip");

    memset(JsonBuf,0,1024);
    g_pNetConfig->GetMacAdd(JsonBuf,1);
    g_pJson->WriteJson(JsonBuf,"data","mac");

    iTemp = g_PsysTemInfo->CoreNum();
    g_pJson->WriteJson(iTemp,"data","cpu");

    memset(JsonBuf,0,1024);
    GetConfigString(ConfigFileName,"ROOM","Types","student",JsonBuf,1024);
    g_pJson->WriteJson(JsonBuf,"data","type");

    iTemp = g_PsysTemInfo->Memory();
    g_pJson->WriteJson(iTemp,"data","memory");

    memset(JsonBuf,0,1024);
    g_PsysTemInfo->Resol(JsonBuf);
    g_pJson->WriteJson(JsonBuf,"data","resolution");

    g_pJson->WriteJson("1.0.0","data","version");
    memset(JsonBuf,0,1024);
    g_pJson->Json2String(JsonBuf);
    sprintf(SendJsonBuf,"###ap_register###%s",JsonBuf);
    printf("SendJsonBuf:%s",SendJsonBuf);
    g_Pproduce->send(SendJsonBuf,strlen(SendJsonBuf));
    g_pLog->WriteLog(0,"Regist:%s",SendJsonBuf);
}

void Ping()
{
    char SendJsonBuf[1024];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(SendJsonBuf,0,1024);
    g_pNetConfig->GetMacAdd(JsonBuf,0);
    g_pJson->WriteJson(JsonBuf,"data","id");
    g_pJson->WriteJson("up","data","status");
    memset(JsonBuf,0,1024);
    g_pJson->Json2String(JsonBuf);
    sprintf(SendJsonBuf,"###ap_heartbeat###%s",JsonBuf);
    printf("SendJsonBuf:%s",SendJsonBuf);
    g_Pproduce->send(SendJsonBuf,strlen(SendJsonBuf));
    g_pLog->WriteLog(0,"Ping:%s",SendJsonBuf);

}
