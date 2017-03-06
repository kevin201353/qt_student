#ifndef TERMINALTOOLFRAME_H
#define TERMINALTOOLFRAME_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QFont>

#define CALLNAME    "QPushButton{border-image: url(/usr/local/shencloud/image/CallNamePress.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/CallName.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/CallNamePress.png)}"


#define HANDUP      "QPushButton{border-image: url(/usr/local/shencloud/image/HandUP.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/HandUPPress.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/HandUP.png)}"

#define HANDDOWNPNG "QPushButton{border-image: url(/usr/local/shencloud/image/HandDown.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/HandDown.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/HandDown.png)}"


#define ALLOWNETWORK    "QPushButton{border-image: url(/usr/local/shencloud/image/AllowNetWork.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/AllowNetWorkPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/AllowNetWork.png)}"

#define NOTALLOWNETWORK "QPushButton{border-image: url(/usr/local/shencloud/image/NotAllowNetWork.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/NotAllowNetWork.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/NotAllowNetWork.png)}"

#define ALLOWUSB    "QPushButton{border-image: url(/usr/local/shencloud/image/USB.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/USBPress.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/USB.png)}"

#define NOTALLOWUSB "QPushButton{border-image: url(/usr/local/shencloud/image/NotUSB.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/NotUSB.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/NotUSB.png)}"


#define FLUSSHPNG   "QPushButton{border-image: url(/usr/local/shencloud/image/Flussh.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/FlusshPress.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Flussh.png)}"

#define DARKSCREEN   "QPushButton{border-image: url(/usr/local/shencloud/image/DarkScreen.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/DarkScreenPress.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/DarkScreen.png)}"

#define NOTDARKSCREEN   "QPushButton{border-image: url(/usr/local/shencloud/image/NotDarkScreen.png);}"\
                    "QPushButton:hover{border-image: url(/usr/local/shencloud/image/NotDarkScreen.png);}"\
                    "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/NotDarkScreen.png)}"
namespace Ui {
class TerminalToolFrame;
}
class TerminalToolFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TerminalToolFrame(QWidget *parent = 0);
    ~TerminalToolFrame();
    void SetTerminalNum(int i);
    void Reset();
private slots:
    void on_NoHandUppushButton_clicked();

    void on_NoNetworkpushButton_clicked();

    void on_NoUSBpushButton_clicked();

    void on_DarkScreenpushButton_clicked();

    void on_CallNamepushButton_clicked();

    void on_DarkscreenpushButton_clicked();

private:
    Ui::TerminalToolFrame *ui;
    QPushButton *m_pCallNamePushButton;
    QPushButton *m_pHandUpPushButton;
    QPushButton *m_pNetWorkPushButton;
    QPushButton *m_pUSBPushButton;
    QPushButton *m_pFlusshPushButton;
    QPushButton *m_pDarkScreenPushButton;
    QLabel      *m_pVMTotail;
    QFont       m_Font;
    bool    m_bHandUPFlag;
    bool    m_bUSBFlag;
    bool    m_bNetWorkFlag;
    bool    m_bDarkScreenFlag;
};

#endif // TERMINALTOOLFRAME_H
