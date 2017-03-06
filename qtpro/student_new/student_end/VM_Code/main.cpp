#include "loginwidget.h"
#include <QApplication>
#include "ryanConfig.h"
#include "include.h"
#include "waitstu2.h"

extern void *WhileFun(void *param);
int main(int argc, char *argv[])
{
    int iRecode = 0;
    while((iRecode = getopt(argc,argv,"vV")) != EOF)
    {

        switch (iRecode) {
            case 'v':
            case 'V':
            {
                printf(VISION_VISON,__DATE__,__TIME__);
                return 0;
            }
        }
    }
    GetConfigString(CONFIGNAME,"MQ","ConsumerQueue","edu_topic",g_strConsumerQueue,50);
    GetConfigString(CONFIGNAME,"MQ","ProduceQueue","edu_Queue",g_strProduceQueue,50);
    qDebug("ActiveMQ Server:%s Recv Queue:%s Send Queue:%s",g_strConsumerAdd,g_strConsumerQueue,g_strProduceQueue);
    GetConfigString(CONFIGNAME,"ROOM","ServiceIP","192.168.120.36",g_strServerIP,25);
    qDebug("Service:%s",g_strServerIP);
    strcpy(g_strConsumerAdd,"tcp://");
    strcat(g_strConsumerAdd,g_strServerIP);
    strcat(g_strConsumerAdd,":61616");
    strcpy(g_strProduceAdd,g_strConsumerAdd);

    GetConfigString(CONFIGNAME,"ROOM","ClassName","Default",g_strRoomNum,100);
    GetConfigString(CONFIGNAME,"ROOM","SeatName","A1",g_strSeatNum,20);
    qDebug("%s %s",g_strRoomNum,g_strSeatNum);
    QApplication a(argc, argv);
    LoginWidget w;
    w.showFullScreen();
    w.show();
    return a.exec();
}
