#include "loginwidget.h"
#include <QApplication>
#include "ryanConfig.h"
#include "include.h"
#include "waitstu2.h"
#include "stwidget.h"

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
    QFont  font;
    font.setFamily("Ms Shell Dlg 2");
    a.setFont(font);
    //w.show();
    //stwidget st;
    //st.show();
    return a.exec();
}
