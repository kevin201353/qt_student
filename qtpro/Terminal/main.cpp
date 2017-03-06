#include <iostream>
#include "include.h"

using namespace std;

int main(int argc, char *argv[])
{
    char StartName[100];
    memset(StartName,0,100);
    int iRecode = 0;
    if(argc < 2)
    {
        printf("Parameter Error!\n");
        return 0;
    }else if(argc == 2)
    {
        if(!strcmp(argv[1],"--version"))
        {
            printf(VISION_VISON,__DATE__,__TIME__);
            return 0;
        }
    }
    if(g_pNetConfig == NULL)
    {
        g_pNetConfig = new NetConfig();
    }
    while((iRecode = getopt(argc,argv,"hHvVa:A:c:C:p:P:F:f:")) != EOF)
    {

        switch (iRecode) {
        case 'v':
        case 'V':
        {
            printf(VISION_VISON,__DATE__,__TIME__);
            return 0;
        }
            break;
        case 'c':
        case 'C':
        {
                g_strConsumerQueue = optarg;
        }break;
        case 'h':
        case 'H':
        {
            printf(HELP,argv[0]);
            return 0;
        }break;
        case 'a':
        case 'A':
        {
            g_strConsumerAdd = optarg;
            g_strProduceAdd = optarg;
        }break;
        case 'p':
        case 'P':
        {
            g_strProduceQueue = optarg;
        }break;
        case 'f':
        case 'F':
        {
            memset(ConfigFileName,0,100);
            strcpy(ConfigFileName,optarg);
            printf("Config Name[%s]\n",ConfigFileName);
            char TempBuf[1024];
            memset(TempBuf,0,1024);
            g_strConsumerAdd = "tcp://";
            GetConfigString(ConfigFileName,"ROOM","ServiceIP","192.168.120.239",TempBuf,1024);
            g_strConsumerAdd += string(TempBuf);
            g_strConsumerAdd += string(":61616");
            g_strProduceAdd = g_strConsumerAdd;
            memset(TempBuf,0,1024);
//            GetConfigString(ConfigFileName,"MQ","ConsumerQueue","edu_topic",TempBuf,50);
            g_pNetConfig->GetMacAdd(TempBuf,false);
            g_strConsumerQueue = TempBuf;
            memset(TempBuf,0,1024);
            GetConfigString(ConfigFileName,"MQ","ProduceQueue","edu_Queue",TempBuf,50);
            g_strProduceQueue = TempBuf;
            //           GetConfigString(optarg,"SERVICE","ServiceIP","192.168.120.36",g_strServerIP,25);

        }break;
        default:
            break;
        }
    }

    GetConfigString(ConfigFileName,"ROOM","Types","student",StartName,100);
    printf("StartName:%s\n",StartName);
//    if(strcmp(StartName,"student") == 0)
//    {
//        system("sudo /home/CloudClassRoom_Student");
//    }
//    if(strcmp(StartName,"teacher") == 0)
//    {
//        system("sudo /home/CloudClassRoom_Teacher");
//    }

    printf(VISION_START,__DATE__,__TIME__);
#ifndef _DEBUG
    iRecode = DameonInit();
    if(iRecode < 0)
    {
        g_pLog->WriteLog(0,"[Error] DameonInit[%d]",iRecode);
        MainExit(0);
        return -3;
    }
#endif
    if(!g_pLog)
    {
        g_pLog = new Log();
        iRecode = g_pLog->InitLog();
        if(iRecode < 0)
        {
            MainExit(0);
            return -1;
        }
    }
    g_pLog->WriteLog(0,"Init Log sucess!");
    g_pLog->WriteLog(0,"Connect ActiveMQ Server:%s Recv Queue:%s Send Queue:%s",g_strConsumerAdd.c_str()\
                     ,g_strConsumerQueue.c_str(),g_strProduceQueue.c_str());
    if(g_pProcess == NULL)
    {
        g_pProcess = new process();
        iRecode = g_pProcess->Start();
        if(iRecode < 0)
        {
            g_pLog->WriteLog(0,"Process Start Error");
            MainExit(0);
        }
    }
    activemq::library::ActiveMQCPP::initializeLibrary();

    if(g_Pconsume == NULL)
    {
        g_Pconsume = new ActiveMQConsumer();
        g_Pconsume->start(g_strConsumerAdd,g_strConsumerQueue,false,true);
        g_Pconsume->runConsumer();
    }
    if(g_Pproduce == NULL)
    {
        g_Pproduce = new ActiveMQProduce();
        g_Pproduce->start(g_strProduceAdd,g_strProduceQueue,false,false);
    }

    if(g_pJson == NULL)
    {
        g_pJson = new myJson();
    }
    if(g_PsysTemInfo == NULL)
    {
        g_PsysTemInfo = new SystemInfo();
    }
    signal(SIGCHLD,SIG_IGN);
    signal(SIGALRM,SIG_IGN);
    signal(SIGTERM,SIG_IGN);
    signal(SIGPIPE,SIG_IGN);
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    signal(SIGUSR1,MainExit);

    Regist();
    while(!cMainExitFlag)
    {
//        g_Pproduce->send("test",4);
        Ping();
        sleep(50);
    }
    return 0;
}
