#ifndef MQMSGPROCESS_H
#define MQMSGPROCESS_H

#include <QObject>
#include <pthread.h>

class MqMsgProcess : public QObject
{
    Q_OBJECT
public:
    explicit MqMsgProcess(QObject *parent = 0);
    ~MqMsgProcess();
signals:
public slots:
public:
    void _MqMsgProcess();
    void GetAddrMac();
    void start();
    void _abotThread();
    void strart_spicyThrd();
    void _spicyProcess();
public:
    char m_strVmID[50];
    char m_strMac[50];
    char m_strIP[20];
    pthread_t  m_pid;
    pthread_t  m_pidsp;
};

#endif // MQMSGPROCESS_H
