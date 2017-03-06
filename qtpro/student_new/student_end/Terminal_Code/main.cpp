#include "loginwidget.h"
#include <QApplication>
#include "ryanConfig.h"
#include "include.h"

int main(int argc, char *argv[])
{
    GetConfigString(CONFIGNAME,"MQ","ConsumerAdd","tcp://192.168.120.239:61616",g_strConsumerAdd,1024);
    GetConfigString(CONFIGNAME,"MQ","ProduceAdd","tcp://192.168.120.239:61616",g_strProduceAdd,1024);
    GetConfigString(CONFIGNAME,"MQ","ConsumerQueue","edu_topic",g_strConsumerQueue,50);
    GetConfigString(CONFIGNAME,"MQ","ProduceQueue","edu_Queue",g_strProduceQueue,50);
    qDebug("ActiveMQ Server:%s Recv Queue:%s Send Queue:%s",g_strConsumerAdd,g_strConsumerQueue,g_strProduceQueue);
    GetConfigString(CONFIGNAME,"SERVICE","ServiceIP","192.168.120.36",g_strServerIP,25);
    qDebug("Service:%s",g_strServerIP);
    GetConfigString(CONFIGNAME,"ROOM","ClassName","Default",g_strRoomNum,100);
    GetConfigString(CONFIGNAME,"ROOM","SeatName","A1",g_strSeatNum,20);
    qDebug("%s %s",g_strRoomNum,g_strSeatNum);
    QApplication a(argc, argv);
    LoginWidget w;
#if 0
    w.show();
#else
    w.showFullScreen();
#endif

    return a.exec();
}
