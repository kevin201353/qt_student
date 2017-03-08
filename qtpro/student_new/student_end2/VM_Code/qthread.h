#ifndef SHQTHREAD_H
#define SHQTHREAD_H

#include <QThread>
#include <QObject>

class qthread: public QThread
{
    Q_OBJECT
public:
    qthread();
    ~qthread();
public:
    void stop();
protected:
    void run();
signals:
    void NoticeShow();
    void NoticeHide();
private:
    bool m_stop;
};

#endif // SHQTHREAD_H
