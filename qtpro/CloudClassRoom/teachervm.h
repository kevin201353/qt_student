#ifndef TEACHERVM_H
#define TEACHERVM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QFont>
#include "myhttp.h"
#include "myjson.h"
#include "log.h"

#define BACKGROUNDPNG  "/usr/local/shencloud/image/BackGround.png"
#define DESKTOPCLOSEPNG      "/usr/local/shencloud/image/Close.png"
#define DESKTOPRESTART      "/usr/local/shencloud/image/Restart.png"
#define DESKTOPUSING        "/usr/local/shencloud/image/Using.png"
#define DESKTOPERROR        "/usr/local/shencloud/image/Error.png"
#define DESKTOPWARNING      "/usr/local/shencloud/image/Warning.png"

#define STARTENABLE     "QPushButton{border-image: url(/usr/local/shencloud/image/StartEnable.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/StartEnablePress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/StartEnable.png)}"

#define STOPENABLE      "QPushButton{border-image: url(/usr/local/shencloud/image/StopEnable.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/StopEnablePress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/StopEnable.png)}"

#define RESTENABLE      "QPushButton{border-image: url(/usr/local/shencloud/image/ReastEnable.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/ReastEnablePress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/ReastEnable.png)}"


#define CONNECTENABLE   "QPushButton{border-image: url(/usr/local/shencloud/image/ConnectEnable.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/ConnectEnablePress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/ConnectEnable.png)}"

#define STARTDISABLE         "border-image: url(/usr/local/shencloud/image/StartDisable.png);"
#define STOPDISABLE         "border-image: url(/usr/local/shencloud/image/StopDisable.png);"
#define RESTDISABLE         "border-image: url(/usr/local/shencloud/image/ReastDisable.png);"
#define CONNECTDISABLE         "border-image: url(/usr/local/shencloud/image/ConnectDisable.png);"

#define CLOSE   0
#define RESTART 1
#define USING   2
#define ERROR   3
#define WARNING 4

struct VMConnectInfo
{
    char s_strVMID[50];

};
class TeacherVM:public QLabel
{
    Q_OBJECT
public:
    TeacherVM(QWidget *parent, const char *name, int status);
    void SetVMInfo(const char *VMid);
private:
    QLabel  *m_pVMNameQLabel;
    QLabel  *m_pDeskTopQLabel;
    QPushButton *m_pStartPushButton;
    QPushButton *m_pStopPushButton;
    QPushButton *m_pRestartPushButton;
    QPushButton *m_pConnectPushButton;
    QString     m_strTeachetVMName;
    int m_iStatus;
    QFont   m_Font;
    struct VMConnectInfo    m_VMInfo;
public:
    void SetStatus(int status);
    void CheckVMStatus();
private slots:
    void on_StartPushButton();

    void on_StopPushButton();

    void on_RestartPushButton();

    void on_ConnectPushButton();

    void ChangeStatus(int Status);

signals:
    void StatusChanged(int Status);
};

#endif // TEACHERVM_H
