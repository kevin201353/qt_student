#include "qthread.h"
#include <QDebug>

extern bool g_bSetupAmq;
qthread::qthread()
{
    m_stop = false;
}

qthread::~qthread()
{
    m_stop = true;
}

void qthread::run()
{
    while(!m_stop)
    {
        if (!g_bSetupAmq)
        {
            qDebug() << "start show netoff dailog.\n";
            emit NoticeShow();
        }else
        {
            emit NoticeHide();
        }
        sleep(2);
    }
}

void qthread::stop()
{
    m_stop = true;
}


qthreadPing::qthreadPing()
{

}

qthreadPing::~qthreadPing()
{

}

QString  g_strPing;
void qthreadPing::run()
{
    char szcmd[100] = {0};
    strcpy(szcmd, m_szPing.toStdString().c_str());
    //strcat(szcmd, " -c 10");
    FILE *pp = popen(szcmd, "r");
    if (pp)
    {
        char tmp[512] = {0};
        while (fgets(tmp, sizeof(tmp), pp) != NULL)
        {
            if (tmp[strlen(tmp) -1] == '\n')
            {
                tmp[strlen(tmp) - 1] = '\0';
            }
            g_strPing = QString::fromStdString(tmp);
            emit NoticeMsg();
        }
        pclose(pp);
    }
}

