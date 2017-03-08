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
    QApplication a(argc, argv);
    LoginWidget w;
    w.showFullScreen();
    w.show();
    return a.exec();
}
