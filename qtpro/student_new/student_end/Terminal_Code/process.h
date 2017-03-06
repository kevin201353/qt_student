#ifndef PROCESS_H
#define PROCESS_H

#include <pthread.h>
#include "listbuf.h"
#include "loginwidget.h"

class process
{
public:
    process(LoginWidget *widget);
    ~process();
    int Start();
    int ProcessThread();
    ListBuf *m_RecvBuf;
    pid_t   m_SpicyPid;
private:
    pthread_t m_pid;
    LoginWidget *m_pWidget;

};

#endif // PROCESS_H
