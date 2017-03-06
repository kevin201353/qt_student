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
#include "setform.h"
#include <QPainter>
#include <QFont>
#include <QPalette>
#include "loadingframe.h"
#include <QTextCodec>
#include <QNetworkReply>




#define LOGOPNG      "/usr/local/shencloud/image/Logo1.png"
#define DESKTOPMAP  "/usr/local/shencloud/image/Top.png"
#define USRLOGO      "/usr/local/shencloud/image/Username.png"
#define PASSWDLOGO  "/usr/local/shencloud/image/Userpasswd.png"

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

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    const char *GetUserName();
    const char *GetPasswd();
private slots:
    void on_LoginpushButton_clicked();

    void OnTimeOut();
    void on_SetpushButton_clicked();

    void on_ShutdownpushButton_clicked();

    void on_InformationpushButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::LoginWidget *ui;
    QLabel *m_pLogoQLable;
    QLCDNumber *m_pTimeLCDNumber;
    QLineEdit   *m_pUserNameLineEdit;
    QLineEdit   *m_pPasswdLineEdit;
    QPushButton *m_pLoginPushButton;
    QLabel  *m_pSoftInforLabel;
    QPushButton *m_pInformationPushButton;
    QPushButton *m_pSetPushButton;
    QPushButton *m_pServerManPushButton;
    QPushButton *m_pShutdownPushButton;
    QString      m_UserName;
    QString      m_Passwd;
    QTimer      *m_pTimer;
    QDateTime       *m_pTime;
    SetForm     *m_pSetForm;
    LoadingFrame    *m_pLoadingFrame;
    QLabel      *m_pUserNameLogo;
    QLabel      *m_pPasswdLogo;
    QLabel      *m_pShencloudNamelabel;
    QFont       m_Font;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // LOGINWIDGET_H
