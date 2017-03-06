#include "netconfig.h"
#include "include.h"
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>

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
LoadingFrame *g_LoadingFrame;


////////////////////////////////
//msg queue
#define  MAX_TEXT   100
struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};
void msg_queue_del();
void msg_send(char* dataTmp);
int g_msgid = -1;
void create_msg_queue()
{
    if (g_msgid != -1)
    {
        msg_queue_del();
        g_msgid = -1;
    }
    g_msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (g_msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        //exit(EXIT_FAILURE);
    }
    msg_send("0");
}

void msg_send(char* dataTmp)
{
    struct msg_st data;
    data.msg_type = 1;
    strcpy(data.text, dataTmp);
    if (msgsnd(g_msgid, (void*)&data, MAX_TEXT, 0) == -1)
    {
        fprintf(stderr, "msgsnd failed\n");
        //exit(EXIT_FAILURE);
    }
}

void msg_queue_del()
{
    if (g_msgid != -1)
    {
        if (msgctl(g_msgid, IPC_RMID, 0) == -1)
        {
            fprintf(stderr, "msgctl(IPC_RMID) failed.\n");
            //exit(EXIT_FAILURE);
        }
        g_msgid = -1;
    }
}
