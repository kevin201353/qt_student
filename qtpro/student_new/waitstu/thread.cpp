#include "thread.h"
#include <QDebug>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "widget.h"
#include <QDateTime>
#include <QByteArray>

#define MAX_BUFF_SIZE   10
#define FIFO_WRITE  "/usr/local/shencloud/student_fifo"
Thread::Thread()
{
    m_stopped = false;
}


Thread::~Thread()
{

}

void Thread::stop()
{
    m_stopped = true;
}

void Thread::run()
{
//    char buf[MAX_BUFF_SIZE] = {0};
//    char szTmp[MAX_BUFF_SIZE] = {0};
//    int readfifo;
//    readfifo = open(FIFO_WRITE, O_RDONLY);
    char data[MAX_SIZE] = {0};
    char szTmp[MAX_SIZE] = {0};
    while(!m_stopped)
    {
//        FILE *fp = fopen(FIFO_WRITE, "r");
//        if (fp != NULL)
//        {
//            while(fgets(buf, MAX_BUFF_SIZE, fp) > 0)
//            {
//                if (m_stopped)
//                    break;
//                sprintf(szTmp, "Thread::run() read student_fifo buf=%s.\n", buf);
//                //buf[strlen(buf) - 1] = '\0';
//                qDebug() << QString(szTmp);
//                qDebug() << QString(buf);
//                if (strcmp(buf, "1") == 0)
//                {
//                    emit NoticeExit();
//                }
//                sleep(1);
//            }//while
//        }//if
//        qDebug() << "Thread::run() running ... ";
//        if (fp)
//        {
//            fclose(fp);
//            fp = NULL;
//        }
//        if (readfifo != -1)
//        {
//            while (read(readfifo, buf, MAX_BUFF_SIZE) > 0)
//            {
//                if (m_stopped)
//                    break;
//                sprintf(szTmp, "Thread::run() read student_fifo buf=%s.\n", buf);
//                qDebug() << QString(szTmp);
//                qDebug() << QString(buf);
//                mylog(buf);
//                if (strcmp(buf, "1") == 0)
//                {
//                    if (readfifo != -1)
//                    {
//                        close(readfifo);
//                        readfifo = -1;
//                    }
//                    emit NoticeExit();
//                }
//            }
//        }
        memset(data, 0, MAX_SIZE);
        msg_recv(data);
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
        QByteArray ba = str.toLatin1();
        strcpy(szTmp, ba.data());
        strcat(szTmp, " ----- ");
        strcat(szTmp, data);
        strcat(szTmp, "\r\n");
        mylog(szTmp);
        qDebug() << "Thread::run() running ... ";
        if (strncmp(data, "1", strlen("1")) == 0)
        {
            emit NoticeExit();
        }
        sleep(1);
    }
}
