#ifndef INCLUDE_H
#define INCLUDE_H

#include "teacherform.h"
#include "myhttp.h"
#include "myjson.h"
#include "netconfig.h"
#include "log.h"
#include "mydialog.h"
#include "process.h"
#include "activemq.h"

#define CONFIGNAME  "/usr/local/shencloud/Terminal.con"

extern NetConfig   *g_pNetConfig;
extern Log         *g_pLog;
extern myHttp      *g_pMyHttp;
extern myJson      *g_pMyJson;
extern TeacherForm   *g_pTeacherForm;
extern MyDialog        *g_pMyDialog;
extern struct TeacherVMSet     g_TeacherVMSet;
extern process      *g_pProcess;
extern char g_strRoomNum[100];
extern char g_strServerIP[25];
extern char g_strTeacherName[100];
extern int g_ScreenWidth;
extern int g_ScreenHeight;
extern ActiveMQConsumer *g_Pconsume;
extern ActiveMQProduce *g_Pproduce;
extern char g_strProduceAdd[1024];
extern char g_strConsumerAdd[1024];
extern char g_strProduceQueue[50];
extern char g_strConsumerQueue[50];
#endif // INCLUDE_H
#define VISION_VISON     "                        \n\t\
  _______________________________________________ \n\t\
 |                                               |\n\t\
      Shencloud CloudClassRoom_Teacher   Module          \n\t\
 |                       (Ver 1.00)              |\n\t\
 |                                               |\n\t\
 |    Build By: GCCH      %s %s  |\n\t\
 |    Copyright (C)   Shencloud   2012-2017      |\n\t\
 |    All Rights Reserved.                       |\n\t\
 |_______________________________________________|\n"
