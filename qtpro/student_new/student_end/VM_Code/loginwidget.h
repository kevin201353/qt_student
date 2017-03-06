#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QLineEdit>
#include <QKeyEvent>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QFont>
#include <QPalette>
#include <QGroupBox>
#include "setform.h"
#include "classmould.h"
#include "classnameconfig.h"
#include "netconfig.h"
#include "setroomseatdialog.h"
#include "mydialog.h"
//linux
#include <sys/types.h>
#include <sys/stat.h>

#define LOGOPNG      "/usr/local/shencloud/image1/Logo_Student.png"
#define DESKTOPMAP  "/usr/local/shencloud/image1/Top_Student1.png"
//#define USRLOGO      "/usr/local/shencloud/pengjian/QtProject/CloudClassRoom/image/Username.png"
//#define PASSWDLOGO  "/usr/local/shencloud/pengjian/QtProject/CloudClassRoom/image/Userpasswd.png"

#define SETLOGO         "QPushButton{border-image: url(/usr/local/shencloud/image/Set.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/SetPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Set.png)}"

#define INFORMATIONLOGO     "QPushButton{border-image: url(/usr/local/shencloud/image/Information.png);}"\
                            "QPushButton:hover{border-image: url(/usr/local/shencloud/image/InformationPress.png);}"\
                            "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Information.png)}"

#define SERVERMANLOGO   "QPushButton{border-image: url(/usr/local/shencloud/image/ServerMan.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/ServerManPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/ServerMan.png)}"

#define LOGINLOGO       "QPushButton{border-image: url(/usr/local/shencloud/image/Login.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/LoginPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Login.png)}"

#define SHUTDOWNLOGO    "QPushButton{border-image: url(/usr/local/shencloud/image/Shutdown.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/ShutdownPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Shutdown.png)}"

#define RIGHTPNG        "QPushButton{border-image: url(/usr/local/shencloud/image/Right.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/RightPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Right.png)}"

#define LEFTPNG         "QPushButton{border-image: url(/usr/local/shencloud/image/Left.png);}" \
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/LeftPress.png);}" \
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Left.png)}"

#define ENTER           "QPushButton{border-image: url(/usr/local/shencloud/image1/Enter.png);}" \
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image1/EnterPress.png);}" \
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image1/Enter.png)}"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    ClassNameConfig *m_pClassNameConfig;
    QGroupBox   *m_pGroupWigdet;
    void Thread();
    void SetChecked();
    void createPipe();
private slots:

    void OnTimeOut();
    void on_SetpushButton_clicked();

    void on_ShutdownpushButton_clicked();

    void on_InformationpushButton_clicked();

    void on_LeftPushButton();

    void on_RightPushButton();

private slots:
    void on_LabelChecked();

    void on_EnterPushButton();
private:
    Ui::LoginWidget *ui;
    QLabel *m_pLogoQLable;
    QLCDNumber *m_pTimeLCDNumber;
    QLabel  *m_pSoftInforLabel;
    QPushButton *m_pInformationPushButton;
    QPushButton *m_pSetPushButton;
    QPushButton *m_pServerManPushButton;
    QPushButton *m_pShutdownPushButton;
    QTimer      *m_pTimer;
    QDateTime       *m_pTime;
    SetForm     *m_pSetForm;
    QFont       m_Font;

    QPushButton *m_pLeftPushButton;
    QPushButton *m_pRightPushButton;
    QPushButton *m_pEnterPushButton;

    ClassMould *m_pClassName1;
    ClassMould *m_pClassName2;
    ClassMould *m_pClassName3;
    SetRoomSeatDialog *m_pSetRoomSeat;
    MyDialog    *m_pMyDialog;
    bool m_bExitThread;
    LoadingFrame * g_Loadingwnd;
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent  *event);
};

#endif // LOGINWIDGET_H
