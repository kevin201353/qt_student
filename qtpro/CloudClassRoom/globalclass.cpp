#include "include.h"

NetConfig   *g_pNetConfig = NULL;
Log         *g_pLog = NULL;
myHttp      *g_pMyHttp = NULL;
myJson      *g_pMyJson = NULL;
TeacherForm   *g_pTeacherForm = NULL;
MyDialog        *g_pMyDialog = NULL;
process      *g_pProcess = NULL;
struct TeacherVMSet     g_TeacherVMSet;
ActiveMQConsumer *g_Pconsume = NULL;
ActiveMQProduce *g_Pproduce = NULL;

char g_strProduceAdd[1024];
char g_strConsumerAdd[1024];
char g_strProduceQueue[50];
char g_strConsumerQueue[50];

char g_strRoomNum[100];
char g_strServerIP[25];
char g_strTeacherName[100];
int g_ScreenWidth = 0;
int g_ScreenHeight = 0;
