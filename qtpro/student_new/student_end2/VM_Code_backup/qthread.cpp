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
        }
        sleep(2);
    }
}

void qthread::stop()
{
    m_stop = true;
}
