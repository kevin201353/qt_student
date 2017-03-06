#ifndef PROCESS_H
#define PROCESS_H

#include <pthread.h>
#include "listbuf.h"
#include "loginwidget.h"
#define DATABUFLEN 10240
struct DataBuf
{
    bool s_IsArray;
    char Data[DATABUFLEN];
};
class process
{
public:
    process();
    ~process();
    int Start();
    int ProcessThread();
    ListBuf *m_RecvBuf;
    pid_t   m_SpicyPid;
    char m_strVmID[50];
    char m_strMac[50];
    char m_strIP[20];
    DataBuf m_data;
    void setEXIT(bool falg){IsBack = falg;}
    pthread_t m_pid;
private:
    bool IsBack;
    bool m_bExit;
    char m_strTerminalID[100];

};

#endif // PROCESS_H
