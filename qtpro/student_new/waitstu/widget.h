#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "thread.h"
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>

#define MAX_SIZE  100
struct msg_t
{
    long int msg_type;
    char text[MAX_SIZE];
};

extern void create_msg_queue();
extern void msg_recv(char* dataT);
extern void msg_queue_del();

namespace Ui {
class Widget;
}

#define mylog(x) ({ FILE *fp = fopen("/usr/local/shencloud/waitstu.log", "a+"); \
    if (fp != NULL){ \
        fwrite(x, 1, strlen(x), fp);\
        fclose(fp); \
    }})

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void NoticeWaitExit();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    Thread  *m_pThread;
};

#endif // WIDGET_H
