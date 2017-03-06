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

#define LOGOPNG      "/home/pengjian/QtProject/CloudClassRoom_student/image/Logo_Student.png"
#define DESKTOPMAP  "/home/pengjian/QtProject/CloudClassRoom_student/image/Top_Student1.png"
#define USRLOGO      "/home/pengjian/QtProject/CloudClassRoom/image/Username.png"
#define PASSWDLOGO  "/home/pengjian/QtProject/CloudClassRoom/image/Userpasswd.png"

#define SETLOGO         "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Set.png);}"\
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/SetPress.png);}"\
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Set.png)}"

#define INFORMATIONLOGO     "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Information.png);}"\
                            "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/InformationPress.png);}"\
                            "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Information.png)}"

#define SERVERMANLOGO   "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/ServerMan.png);}"\
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/ServerManPress.png);}"\
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/ServerMan.png)}"

#define LOGINLOGO       "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Login.png);}"\
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/LoginPress.png);}"\
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Login.png)}"

#define SHUTDOWNLOGO    "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Shutdown.png);}"\
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/ShutdownPress.png);}"\
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Shutdown.png)}"

#define RIGHTPNG        "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Right.png);}"\
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/RightPress.png);}"\
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Right.png)}"

#define LEFTPNG         "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Left.png);}" \
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/LeftPress.png);}" \
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom/image/Left.png)}"

#define ENTER           "QPushButton{border-image: url(/home/pengjian/QtProject/CloudClassRoom_student/image/Enter.png);}" \
                        "QPushButton:hover{border-image: url(/home/pengjian/QtProject/CloudClassRoom_student/image/EnterPress.png);}" \
                        "QPushButton:pressed{border-image: url(/home/pengjian/QtProject/CloudClassRoom_student/image/Enter.png)}"

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

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent  *event);
};

#endif // LOGINWIDGET_H
