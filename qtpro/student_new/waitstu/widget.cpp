#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QDesktopWidget>
#include <QDebug>
#include <QPalette>
#include <QFile>

#define DESKTOPMAP   ":/images/50_22.png"


int g_msgid = -1;
void create_msg_queue()
{
    g_msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (g_msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        //exit(EXIT_FAILURE);
    }
}

struct msg_t data;
void msg_recv(char* dataT)
{
    long int msgtype = 1;
    if ( msgrcv(g_msgid, (void*)&data, MAX_SIZE, msgtype, IPC_NOWAIT) == -1 )
    {
        fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
        //exit(EXIT_FAILURE);
    }
    strcpy(dataT, (char*)data.text);
}

void msg_queue_del()
{
    if (g_msgid != -1)
    {
        if (msgctl(g_msgid, IPC_RMID, 0) == -1)
        {
            fprintf(stderr, "msgctl(IPC_RMID) failed.\n");
            //exit(EXIT_FAILURE);
        }
    }
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setWindowFlags(this->windowFlags()& ~Qt::WindowMinMaxButtonsHint);
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect deskRect = desktopWidget->availableGeometry();
    this->setGeometry(QRect((deskRect.width() - width())/2, (deskRect.height() - this->height())/2, width(), height()));
    QPixmap pixmap(DESKTOPMAP);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    this->showFullScreen();
    m_pThread = NULL;
    m_pThread = new Thread();
    connect(m_pThread, SIGNAL(NoticeExit()), this, SLOT(NoticeWaitExit()));
    m_pThread->start();
    create_msg_queue();
}

Widget::~Widget()
{
    qDebug() << "main widget is exit, ~Widget()";
    mylog("main widget is exit, ~Widget()");
    delete ui;
    if (m_pThread)
    {
        m_pThread->stop();
        m_pThread->wait();
        delete m_pThread;
        m_pThread = NULL;
    }
    //msg_queue_del();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.drawPixmap(0,0,width(),height(),QPixmap(DESKTOPMAP));
}

void Widget::NoticeWaitExit()
{
    mylog("NoticeWaitExit !");
    this->close();
}
