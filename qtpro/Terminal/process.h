#ifndef PROCESS_H
#define PROCESS_H

#include <pthread.h>
#include "listbuf.h"
class process
{
public:
    process();
    ~process();
    int Start();
    int ProcessThread();
    ListBuf *m_RecvBuf;
private:
    pthread_t m_pid;
};

#endif // PROCESS_H
