#ifndef MYLABLE_H
#define MYLABLE_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QAction>
#include <pthread.h>
#include <unistd.h>
#include <QMouseEvent>

#define NORMALPIC           "/usr/local/shencloud/image/Using.png"
#define SOMEONEHANDUP       "/usr/local/shencloud/image/SomeOneHangUp.png"

#define DARKSCREENICON      "/usr/local/shencloud/image/StartIcon.png"
#define RESTARTICON         "/usr/local/shencloud/image/ShutDownIcon.png"
#define STUDENTSHOWICON     "/usr/local/shencloud/image/RestDeskTopIcon.png"
#define SENDFILEICON        "/usr/local/shencloud/image/RestVMIcon.png"
#define REMOTEACTIONICON    "/usr/local/shencloud/image/DesktopHelp.png"
#define IPLEN           20
#define NAMELEN         50
#define PORTLEN         10

struct jpegheader
{
    char magic[4];
    unsigned short width;
    unsigned short height;
    unsigned int serial;
    unsigned int time_stamp;
    unsigned int size;
    unsigned int reserved[3];
}__attribute__((packed));

void *ThreadFun(void *param);

class myLable:public QLabel
{
    Q_OBJECT

public:
    myLable(QWidget *parent = NULL);
    ~myLable();
    void ShowUpHand(bool flag);
    void Enable(bool flag);
    void SetIPPort(const char *ip, const int port);
    void SetName(const char *name,const char *seat,const char *ID);
    void SetSocket(int sock);
    void RemberPos(int x,int y);
private:
    QLabel *m_pFrontLabel;
    QLabel  *m_pNameLabel;
    QAction *m_pDarkScreenAction;
    QAction *m_pRestartAction;
    QAction *m_pStudentShowAction;
    QAction *m_pSendFileAction;
    QAction *m_pRemoteAction;
    bool m_bEnable;
    bool m_bFrontLableEnable;
    bool m_bDoubleCheckFlag;



    int m_iSocket;
    int m_OldPosX;
    int m_OldPosY;
    QFont   m_Font;

public:
    bool m_bThreadFlag;
    bool m_bExit;
    char m_strID[NAMELEN];
    bool m_bConnectFlag;
    char m_strIP[IPLEN];
    int m_iPort;
    bool m_bThreadEXIT;
    pthread_t m_pid;
private slots:
    void DarkScreenFun();
    void RestartFun();
    void StudentShowFun();
    void SendFileFun();
    void RemoteFun();
private:
    void mousePressEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);
};

#endif // MYLABLE_H
