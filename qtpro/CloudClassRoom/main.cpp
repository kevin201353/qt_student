#include "loginwidget.h"
#include <QApplication>
#include "ryanConfig.h"
#include "include.h"
#include <QDesktopWidget>
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
    GetConfigString(CONFIGNAME,"ROOM","ClassName","Default",g_strRoomNum,100);
    GetConfigString(CONFIGNAME,"ROOM","ServiceIP","192.168.0.164:9090",g_strServerIP,25);
    strcpy(g_strConsumerAdd,"tcp://");
    strcat(g_strConsumerAdd,g_strServerIP);
    strcat(g_strConsumerAdd,":61616");
    strcpy(g_strProduceAdd,g_strConsumerAdd);
//    GetConfigString(CONFIGNAME,"ROOM","ServiceIP","192.168.120.239:61616",g_strConsumerAdd,1024);
//    GetConfigString(CONFIGNAME,"MQ","ProduceAdd","tcp://192.168.120.239:61616",g_strProduceAdd,1024);
    GetConfigString(CONFIGNAME,"MQ","ConsumerQueue","edu_topic",g_strConsumerQueue,50);
    GetConfigString(CONFIGNAME,"MQ","ProduceQueue","edu_Queue",g_strProduceQueue,50);

    QApplication a(argc, argv);
    g_ScreenWidth = QApplication::desktop()->width();
    g_ScreenHeight = QApplication::desktop()->height();
    qDebug("%d*%d",g_ScreenWidth,g_ScreenHeight);
    LoginWidget w;
#if 0
    w.show();
#else
    w.showFullScreen();
#endif

    return a.exec();
}
