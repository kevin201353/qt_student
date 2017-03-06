#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    ~Thread();
    void stop();
protected:
    void run();
signals:
    void NoticeExit();
private:
    volatile bool m_stopped;
};

#endif // THREAD_H
