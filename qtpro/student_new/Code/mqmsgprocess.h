#ifndef MQMSGPROCESS_H
#define MQMSGPROCESS_H

#include <QObject>
#include <pthread.h>

class MqMsgProcess : public QObject
{
    Q_OBJECT
public:
    explicit MqMsgProcess(QObject *parent = 0);
signals:
public slots:
public:
    void _MqMsgProcess();
    void GetAddrMac();
    void start();
    void _abotThread();
public:
    char m_strVmID[50];
    char m_strMac[50];
    char m_strIP[20];
    pthread_t  m_pid;
};

#endif // MQMSGPROCESS_H
