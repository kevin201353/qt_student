#ifndef INCLUDE_H
#define INCLUDE_H

#include "log.h"
//#include "tcp.h"
#include "myjson.h"
#include "process.h"
#include <signal.h>
#include "activemq.h"
#include "netconfig.h"
#include "ryanConfig.h"
#include "systeminfo.h"

extern SystemInfo *g_PsysTemInfo;

extern NetConfig *g_pNetConfig;

extern Log *g_pLog;
extern char cMainExitFlag;
//extern TcpServer *g_pTcp;
extern myJson *g_pJson;
extern process *g_pProcess;
extern ActiveMQConsumer *g_Pconsume;
extern ActiveMQProduce *g_Pproduce;
extern string g_strProduceAdd;
extern string g_strConsumerAdd;
extern string g_strProduceQueue;
extern string g_strConsumerQueue;
extern char ConfigFileName[100];
int DameonInit(void);
void MainExit(int sig);
void Regist();
void Ping();

#define VISION_VISON     "                        \n\t\
  _______________________________________________ \n\t\
 |                                               |\n\t\
 |    Shencloud TerminalServer   Module          |\n\t\
 |                       (Ver 1.00)              |\n\t\
 |                                               |\n\t\
 |    Build By: GCCH      %s %s  |\n\t\
 |    Copyright (C)   Shencloud   2012-2017      |\n\t\
 |    All Rights Reserved.                       |\n\t\
 |_______________________________________________|\n"

#define VISION_START     "                        \n\t\
  _______________________________________________ \n\t\
 |                                               |\n\t\
 |    Shencloud TerminalServer   Module          |\n\t\
 |                       (Ver 1.00)              |\n\t\
 |          START                                |\n\t\
 |    Build By: GCCH      %s %s  |\n\t\
 |    Copyright (C)   Shencloud   .  2012-2017   |\n\t\
 |    All Rights Reserved.                       |\n\t\
 |_______________________________________________|\n"

#define VISION_END     "                          \n\t\
  _______________________________________________ \n\t\
 |                                               |\n\t\
 |    Shencloud TerminalServer   Module          |\n\t\
 |                       (Ver 1.00)              |\n\t\
 |          END                                  |\n\t\
 |    Build By: GCCH       %s %s  |\n\t\
 |    Copyright (C)   Shencloud      2012-2017   |\n\t\
 |    All Rights Reserved.                       |\n\t\
 |_______________________________________________|\n"


#define HELP     "                          \n\t\
    _______________________________________________ \n\t\
                                                  \n\t\
       %s HELP             \n\t\
                          (Ver 1.00)              \n\t\
                                                  \n\t\
       USAGE:                                     \n\t\
       <程序路径/程序名>  -[v|V|h|H|c|C|p|P|]       \n\t\
       -[v|V] :          程序版本号                 \n\t\
       -[h|H] :          程序帮助                  \n\t\
       -[c|C] :          接收消息队列名称            \n\t\
       -[p|P] :          发送消息队列名称            \n\t\
       -[a|A] :          activeMQ服务器地址         \n\t\
                    tcp://192.168.0.140:61616     \n\t\
       -[f|F] :          程序配置文件名称            \n\t\
                                                  \n\t\
       Copyright (C)   Shencloud      2012-2017   \n\t\
        All Rights Reserved.                       \n\t\
   _______________________________________________\n"

#endif // INCLUDE_H
