#ifndef TEACHERFORM_H
#define TEACHERFORM_H

#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QScrollArea>
#include "teachervm.h"
#include <QFont>
#include <QBoxLayout>
#include "classnameconfig.h"
#include "terminaltoolframe.h"
#include "terminalconfig.h"
#include "classmould.h"
#include <QDateTime>
#include "loadingframe.h"
#include "mydialog.h"

#define TEACHERVMNUM    100
#define CLASSNAMEMAX    10
#define TERMINALMAX     100
#define GRANDNAMEMAX    30

#define LOGOPNG1        "/usr/local/shencloud/image/Logo2.png"
#define TEACHERNAMEPNG "/usr/local/shencloud/image/TeacherName.png"
#define CLASSNAMEPNG    "/usr/local/shencloud/image/ClassName.png"
#define ClASSSTATUSPNG  "/usr/local/shencloud/image/ClassStatus.png"

#define STUDYSELFPNG    "QPushButton{border-image: url(/usr/local/shencloud/image/StudySelp.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/StudySelpPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/StudySelp.png)}"

#define CLASSOVER       "QPushButton{border-image: url(/usr/local/shencloud/image/ClassOver.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/ClassOverPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/ClassOver.png)}"

#define STARTCLASS      "QPushButton{border-image: url(/usr/local/shencloud/image/StartClass.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/StartClassPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/StartClass.png)}"

#define EXITPNG         "QPushButton{border-image: url(/usr/local/shencloud/image/Exit.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/ExitPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Exit.png)}"

#define RIGHTPNG        "QPushButton{border-image: url(/usr/local/shencloud/image/Right.png);}"\
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/RightPress.png);}"\
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Right.png)}"

#define LEFTPNG         "QPushButton{border-image: url(/usr/local/shencloud/image/Left.png);}" \
                        "QPushButton:hover{border-image: url(/usr/local/shencloud/image/LeftPress.png);}" \
                        "QPushButton:pressed{border-image: url(/usr/local/shencloud/image/Left.png)}"
#define CLASSNAME1      "/usr/local/shencloud/image/ClassName1.png"
#define CLASSNAME2      "/usr/local/shencloud/image/ClassName2.png"


struct TeacherVMInfo
{
    int s_VMStatus;
    char s_strName[100];
    char s_strVMID[100];
};
struct ClassNameInfo
{
  char s_strClassID[100];
    char s_strClassName[100];
};
struct ClassNameSet
{
    int s_ClassNum;
    struct ClassNameInfo s_ClassNameInfo[GRANDNAMEMAX];
};
struct TeacherVMSet
{
    int s_VMNum;
    struct TeacherVMInfo s_pVMInfo[TEACHERVMNUM];
};

struct TerminalInfo
{
    char s_strName[100];
    char s_strIP[100];
    char s_strSeat[100];
    char s_strHostIP[100];
    int s_iPort;
};
struct TerminalSet
{
  int s_TerminalNum;
  struct TerminalInfo s_TerminalInfo[TERMINALMAX];
};
namespace Ui {
class TeacherForm;
}

class TeacherForm : public QWidget
{
    Q_OBJECT

public:
    struct TerminalSet      m_TerminalSet;
    ClassNameConfig *m_pClassNameConfig;
public:
    explicit TeacherForm(QWidget *parent = 0);
    ~TeacherForm();
    void SetTeachetName(QString Name);
    void SetClassRoom(QString number);
    void SetTeacherVM();
    void SetClass();
    void SetTerminal();
    void ThreadFunWhile();
    void SetClock(QDateTime *time);
    void SetStartClassPushButton(bool flag);
    void BackThread();
private slots:
    void on_BackpushButton_clicked();

    void on_LeftPushButton();

    void on_RightPushButton();

    void on_LabelChecked();

    void on_ClassStartPushButton();

    void on_ClassOverPushButton();

    void on_StudySelfPushButton();
private:
    Ui::TeacherForm *ui;
    QLabel  *m_pTeacherName;
    QLabel  *m_pClassRoomNum;
    QLabel  *m_pLogoLabel;
    QLabel  *m_pTeacherNameLogoTabel;
    QPushButton     *m_pBackPushButton;
    QLabel  *m_pTeachetVMStatusTabel;

    QLabel  *m_pClassNameLabel;
    QLabel  *m_pClassNameLogoLabel;
    QLabel  *m_pClassNamelTitletabel;

    QLCDNumber *m_pTimeLCDNumber;

    QPushButton *m_pStartSelpPushButton;
    QPushButton *m_pClassOverPushButton;
    QLabel      *m_pGrandName;
    QString m_strTeacherName;
    QString m_strClassRoomNum;
    myLable *m_pMyLable[TERMINALMAX];
    QWidget     *m_pStudentLabelContent;
    QComboBox   *m_pComboxGrand;
    QTabWidget   *m_pClassTabWidget;
    QPushButton     *m_pRightPushButton;
    QPushButton     *m_pLeftPushButton;
    ClassMould          *m_pClassNameLabel_1;
    ClassMould          *m_pClassNameLabel_2;
    ClassMould          *m_pClassNameLabel_3;
    QPushButton     *m_pClassStartPushButton;
    QScrollArea     *m_pTeacherVMScrollArea;
    QWidget     *m_pTeachetVMQWidget;
    TeacherVM   *m_pTeacherVM[TEACHERVMNUM];
    QFont       m_Font;
    QWidget     *m_pClassWidget;
    TerminalToolFrame *m_pTerminalToolFrame;
    LoadingFrame *m_pLoadingFrame;
    struct ClassNameSet m_ClassNameSet;
    pthread_mutex_t  m_Locak;
//    QVBoxLayout *m_pTeacherVMLayOut;
//    QGridLayout *m_pTeacherVMGridLayOut;
    bool m_bFlag;
    pthread_t m_pid;
    bool m_bBackThreadExit;
    MyDialog    *m_pDialog;
private:
    void CleanTeacherVM();
    void CleanClassName();
    void CleanGrandName();
    void CleanTermin();
    int GetUsrVMNum();
private slots:
    void ClassStart(void);
};

#endif // TEACHERFORM_H
