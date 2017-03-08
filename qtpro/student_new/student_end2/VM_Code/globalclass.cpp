#include "netconfig.h"
#include "include.h"
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

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

struct msg_st data;
void msg_recv(char* dataT)
{
    long int msgtype = 1;
    if (msgrcv(g_msgid, (void*)&data, MAX_TEXT, msgtype, IPC_NOWAIT) == -1)
    {
        fprintf(stderr, "msgrcv failed width errno: %d\n", errno);
    }
    strcpy(dataT, (char*)data.text);
}

//return 0: net Unreachable
int ping_net(char *ip)
{
    if (ip != NULL)
    {
        char szbuf[100] = {0};
        char data[100] = {0};
        sprintf(szbuf, "sudo ping %s -c 4 > /usr/local/shencloud/log/ping_net.log", ip);
        system(szbuf);
        FILE *fp = fopen("/usr/local/shencloud/log/ping_net.log", "r");
        if (fp != NULL)
        {
            while(fgets(data, 100, fp) != NULL)
            {
                if (strstr(data, "ttl=")!= NULL && strstr(data, "time=") != NULL)
                {
                    return 1;
                }else if (strstr(data, "Destination Host Unreachable"))
                {
                    return 0;
                }
            }
            fclose(fp);
        }
    }
    return 0;
}

//current time millls
long __GetTime()
{
    struct timeval iTime;
    gettimeofday(&iTime, NULL);
    //long lTime = ((long)iTime.tv_sec) * 1000000 + (long)iTime.tv_usec;
    long lTime = ((long)iTime.tv_sec) * 1000;
    return lTime;
}
