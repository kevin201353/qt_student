#include "netconfig.h"
#include "include.h"

NetConfig   *g_pNetConfig;
process     *g_pProcess = NULL;
myJson      *g_pJson = NULL;
ActiveMQConsumer *g_Pconsume = NULL;
ActiveMQProduce *g_Pproduce = NULL;
char g_strProduceAdd[1024];
char g_strConsumerAdd[1024];
char g_strProduceQueue[50];
char g_strConsumerQueue[50];
char g_strRoomNum[100];
char g_strSeatNum[20];
char g_strTerminalID[30];
Log *g_pLog;
myHttp *g_pMyHttp = NULL;
char g_strServerIP[25];
char cMainExitFlag;
