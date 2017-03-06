#include "global.h"
#include <stdlib.h>
#include "include.h"
#include "testnet.h"
#include <QDebug>
#include "loginwidget.h"
#include "waitstu2.h"

extern LoginWidget * g_loginWnd;
extern void *InitThread(void *param);
bool    g_exitMonitoramq;
pthread_t g_monitoramq;
volatile bool g_resetamq;
volatile bool g_bSetupAmq;

void call_msg_back(MsgCallBackFun fun, ReportMsg msg)
{
    fun(msg);
}

static pthread_t g_waitid = 0;
static pthread_t g_amqpid2 = 0;
bool g_bshowwaitstu = false;
static void *thrd_waitexec(void *param)
{
    g_pLog->WriteLog(0,"zhaosenhua, msg_respose waitstu show. \n");
    qDebug() << "xxxxx show waitstu";
    FILE *fp;
    if ((fp = popen("/usr/local/shencloud/waitstu", "r")) == NULL)
    {
        g_pLog->WriteLog(0, "msg_respose  USER_WAITINGDLG_SHOW  failed.");
    }
    pclose(fp);
    qDebug() << "xxxxx show waitstu finished.";
    return NULL;
}

static void *thrd_amq(void *param)
{
    while(true)
    {
        if (g_exitMonitoramq)
            break;
        if (g_resetamq && g_bSetupAmq)
        {
            ReportMsg reportmsg;
            reportmsg.action = USER_WAITINGDLG_RESET;
            call_msg_back(msg_respose, reportmsg);
            g_resetamq = false;
        }
        sleep(1);
    }
}

void amq_monitor()
{
    if(pthread_create(&g_monitoramq,NULL,thrd_amq, NULL))
    {
        printf("create Thread Error");
    }
}

void msg_respose(ReportMsg msg)
{
    switch (msg.action)
    {
        case USER_WAITINGDLG_SHOW:
            {
                //show waiting dlg show
                if (!g_bshowwaitstu)
                {
                    PIPE_WAIT("0");
                    if(pthread_create(&g_waitid,NULL,thrd_waitexec, NULL))
                    {
                        printf("create Thread Error");
                    }
                    g_bshowwaitstu = true;
                }
            }
            break;
        case USER_WAITINGDLG_EXIT:
            {
                qDebug() << "xxxxx starting exit waitstu";
                g_pLog->WriteLog(0,"zhaosenhua, msg_respose waitstu exit. \n");
                g_bshowwaitstu = false;
                PIPE_WAIT("1");
                qDebug() << "xxxxx exit waitstu";
            }
            break;
        case USER_WAITINGDLG_RESET:
        {
            g_pLog->WriteLog(0,"zhaosenhua, msg_respose reset amq prcess. \n");
            qDebug() << "zhaosenhua, msg_respose reset amq prcess. \n";
            if (g_Pconsume != NULL)
            {
                g_Pconsume->runConsumer();
                //g_resetamq = false;
            }
        }
        break;
        case USER_AMQ_RESET:
        {
            g_pLog->WriteLog(0,"zhaosenhua, msg_respose reset amq prcess, network is unreachable. \n");
            if(pthread_create(&g_amqpid2, NULL,InitThread, g_loginWnd))
            {

            }
            qDebug() << "zhaosenhua, msg_respose reset amq prcess. network is unreachable.\n";
        }
        break;
        default:
            break;
    }
}
