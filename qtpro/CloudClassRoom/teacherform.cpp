#include "teacherform.h"
#include "myui_teacherform.h"
#include "include.h"
extern TerminalConfig *g_pTerminalConfig;
extern myHttp   *g_pMyHttp;
extern myJson   *g_pMyJson;
extern Log      *g_pLog;
bool LoadFrame =false;
TeacherForm::TeacherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherForm)
{
    ///////////////////////Set UI//////////////////////////////////////////
    this->resize(g_ScreenWidth,g_ScreenHeight);
    ui->setupUi(this);
    this->setMouseTracking(true);
    m_Font.setPixelSize(20);
    m_pLogoLabel = ui->Logolabel;
    m_pLogoLabel->setAlignment(Qt::AlignCenter);
    m_pLogoLabel->setPixmap(QPixmap(LOGOPNG1));

    m_pTeacherNameLogoTabel = ui->TeacherNameLogolabel;
    //m_pTeacherNameLogoTabel->setText("教师名称");
    m_pTeacherNameLogoTabel->setPixmap(QPixmap(TEACHERNAMEPNG));


    m_pBackPushButton = ui->BackpushButton;
 //   m_pBackPushButton->setText("后退");
    m_pBackPushButton->setStyleSheet(QStringLiteral(EXITPNG));
    m_pBackPushButton->setMinimumSize(26,27);

    m_pTeachetVMStatusTabel = ui->TeacherVMStatuslabel;
    m_pTeachetVMStatusTabel->setFont(m_Font);
    m_pTeachetVMStatusTabel->setAlignment(Qt::AlignCenter);


    m_pClassNamelTitletabel = ui->ClassNamelTitletabel;
    m_pClassNamelTitletabel->setFont(m_Font);
    m_pClassNamelTitletabel->setStyleSheet("color: rgb(95,93,93)");
    m_pClassNamelTitletabel->setText("当前课程: ");

    m_pClassNameLogoLabel = ui->ClassNameLogolabel;
    m_pClassNameLogoLabel->setPixmap(QPixmap(CLASSNAMEPNG));

    m_pClassNameLabel = ui->ClassNamelabel;
    m_pClassNameLabel->setFont(m_Font);
    m_pClassNameLabel->setStyleSheet("color: rgb(95,93,93)");
    m_pClassNameLabel->setText("请选择课程");

//    m_pClassStatusLogoLabel = ui->ClassStatusLogolabel;
//    m_pClassStatusLogoLabel->setPixmap(QPixmap(ClASSSTATUSPNG));

//    m_pClassStatusLabel = ui->ClassStatuslabel;
//    m_pClassStatusLabel->setFont(ftClassName);
//    m_pClassStatusLabel->setText("自习课");



    m_pStartSelpPushButton = ui->StartSelfpushButton;
    m_pStartSelpPushButton->setFlat(false);
    //m_pStartSelpPushButton->setText("自习");
    m_pStartSelpPushButton->setStyleSheet(QStringLiteral(STUDYSELFPNG));
    m_pStartSelpPushButton->setMinimumSize(113,40);

    m_pClassOverPushButton = ui->ClassOverpushButton;
    m_pClassOverPushButton->setFlat(false);
    //m_pClassOverPushButton->setText("下课");
    m_pClassOverPushButton->setStyleSheet(QStringLiteral(CLASSOVER));
    m_pClassOverPushButton->setMinimumSize(113,40);
    m_pClassOverPushButton->setEnabled(false);

    m_pGrandName = ui->SetClassNamelabel;
    m_pGrandName->setFont(m_Font);
    m_pGrandName->setText("当前班级:");

    m_pTeacherName = ui->TeacherNamelabel;
    m_pClassRoomNum = ui->RoomNumberlabel;
    m_Font.setPointSize(15);
    m_pTeacherName->setFont(m_Font);
    m_pClassRoomNum->setFont(m_Font);

    m_pTeacherName->setText(m_strTeacherName);
    m_pClassRoomNum->setText(m_strClassRoomNum);
    //m_pClassRoomNum->setStyleSheet("color:rgb()");
    m_pTimeLCDNumber = ui->TimelcdNumber;
    m_pTimeLCDNumber->setDigitCount(25);
    m_pTimeLCDNumber->setMode(QLCDNumber::Dec);
    m_pTimeLCDNumber->setSegmentStyle(QLCDNumber::Flat);
    m_pTimeLCDNumber->setFrameShape(QLCDNumber::NoFrame);
    m_pTimeLCDNumber->setMinimumSize(50,20);
    m_pComboxGrand = ui->ClsaaNamecomboBox;
    m_pComboxGrand->setEditable(false);
    m_pComboxGrand->setMinimumWidth(150);
    m_pComboxGrand->setMinimumHeight(30);
    m_pComboxGrand->setFont(m_Font);
    m_pClassTabWidget = ui->ClasstabWidget;
    m_Font.setPixelSize(19);
    m_pClassTabWidget->setFont(m_Font);
    m_pClassTabWidget->setStyleSheet("color: rgb(55,144,240)");
    m_pClassTabWidget->setTabText(0,"    课程    ");
    m_pClassTabWidget->setTabText(1,"学生终端");
    m_pClassTabWidget->setCurrentIndex(0);

    m_pRightPushButton = ui->RightpushButton;
    m_pRightPushButton->setMinimumSize(43,169);
    m_pRightPushButton->setFlat(false);
   // m_pRightPushButton->setStyleSheet(QStringLiteral(RIGHTPNG));
    m_pRightPushButton->setStyleSheet(RIGHTPNG);
    //m_pRightPushButton->setText("右翻");
    m_pLeftPushButton = ui->LeftpushButton;
    m_pLeftPushButton->setMinimumSize(43,169);
    m_pLeftPushButton->setFlat(false);
    //m_pLeftPushButton->setStyleSheet(QStringLiteral(LEFTPNG));
    m_pLeftPushButton->setStyleSheet(LEFTPNG);
    // m_pLeftPushButton->setText("左翻");

    m_pClassStartPushButton = ui->ClassBeginpushButton;
    m_pClassStartPushButton->setMinimumSize(282,65);
    m_pClassStartPushButton->setFlat(false);
    m_pClassStartPushButton->setStyleSheet(QStringLiteral(STARTCLASS));
    m_pClassStartPushButton->setEnabled(true);
    //m_pClassStartPushButton->setText("上课");

    m_pTeacherVMScrollArea = ui->TeacherscrollArea;
    m_pStudentLabelContent = ui->Student_scrollAreaWidgetContents;
    m_pStudentLabelContent->setMinimumSize(1200,750);
    //qDebug("===========%dx%d",m_pTeacherVMScrollArea->geometry().width(),m_pTeacherVMScrollArea->geometry().height());
    //m_pStudentLabelContent->setStyleSheet("background:rgba(255,0,0,0)");
//    m_pMyLable[0] = new myLable(m_pStudentLabelContent);
//    m_pMyLable[0]->move(100,200);
//    m_pMyLable[0]->RemberPos(100,200);
//    m_pMyLable[0]->Enable(true);

//    m_pMyLable[1] = new myLable(m_pStudentLabelContent);
//    m_pMyLable[1]->move(500,200);
//    m_pMyLable[1]->RemberPos(500,200);
//    m_pMyLable[1]->Enable(true);

//    m_pMyLable[2] = new myLable(m_pStudentLabelContent);
//    m_pMyLable[2]->move(100,600);
//    m_pMyLable[2]->RemberPos(100,600);
//    m_pMyLable[2]->Enable(false);

//    m_pMyLable[3] = new myLable(m_pStudentLabelContent);
//    m_pMyLable[3]->move(500,600);
//    m_pMyLable[3]->RemberPos(500,600);
//    m_pMyLable[3]->Enable(false);

    m_pTeachetVMQWidget = ui->Teacher_scrollAreaWidgetContents;
    m_pClassWidget = ui->tab;
    m_pClassNameLabel_1 = ui->ClassNamelabel_1;
    m_pClassNameLabel_2 = ui->ClassNamelabel_2;  
    m_pClassNameLabel_3 = ui->ClassNamelabel_3;

    m_pClassNameConfig = new ClassNameConfig();

    m_pClassNameConfig->AddLabel(m_pClassNameLabel_1);
    m_pClassNameConfig->AddLabel(m_pClassNameLabel_2);
    m_pClassNameConfig->AddLabel(m_pClassNameLabel_3);
    m_pClassNameLabel_1->SetCheckedFlag(true);

    connect(m_pLeftPushButton,SIGNAL(clicked()),this,SLOT(on_LeftPushButton()));
    connect(m_pRightPushButton,SIGNAL(clicked()),this,SLOT(on_RightPushButton()));
    connect(m_pClassNameLabel_1,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassNameLabel_2,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassNameLabel_3,SIGNAL(LabelChecked()),this,SLOT(on_LabelChecked()));
    connect(m_pClassStartPushButton,SIGNAL(clicked()),this,SLOT(on_ClassStartPushButton()));
    connect(m_pClassOverPushButton,SIGNAL(clicked()),this,SLOT(on_ClassOverPushButton()));
    connect(m_pStartSelpPushButton,SIGNAL(clicked()),this,SLOT(on_StudySelfPushButton()));
/////////////////////////new Class///////////////////////////////////////////////////
    m_pTerminalToolFrame = new TerminalToolFrame(m_pStudentLabelContent);
    m_pTerminalToolFrame->resize(1300,100);
    memset(&g_TeacherVMSet,0,sizeof(g_TeacherVMSet));
    m_bFlag =false;
    m_pLoadingFrame = new LoadingFrame(this);
    m_pLoadingFrame->hide();
    pthread_mutex_init(&m_Locak,NULL);
    m_bBackThreadExit = true;
    for(int i = 0;i < TERMINALMAX;i++)
    {
        m_pMyLable[i] = NULL;
    }
    m_pDialog = new MyDialog(this);
    connect(m_pDialog,SIGNAL(ClassStart),this,SLOT(ClassStart()));
}

void TeacherForm::SetTerminal()
{
    int y = m_TerminalSet.s_TerminalNum/3;
    int x = m_TerminalSet.s_TerminalNum%3;

    for(int i = 0;i < y;i++)
    {
        if(m_pMyLable[3*i] == NULL)
        {
            m_pMyLable[3*i] = new myLable(m_pStudentLabelContent);
            m_pMyLable[3*i]->SetName(m_TerminalSet.s_TerminalInfo[i*3].s_strName,m_TerminalSet.s_TerminalInfo[i*3].s_strSeat\
                                        ,m_TerminalSet.s_TerminalInfo[i*3].s_strIP);
            m_pMyLable[3*i]->SetIPPort(m_TerminalSet.s_TerminalInfo[i*3].s_strHostIP,m_TerminalSet.s_TerminalInfo[i*3].s_iPort);
            m_pMyLable[3*i]->move(100,150+(100+200)*i);
            m_pMyLable[3*i]->RemberPos(100,150+(100+200)*i);

            m_pMyLable[3*i]->Enable(true);
            m_pMyLable[3*i]->show();

        }
        else
        {
            int j = 0;
            for(j = 0;j < m_TerminalSet.s_TerminalNum;j++)
            {
                if(strcmp(m_pMyLable[3*i]->m_strID,m_TerminalSet.s_TerminalInfo[j].s_strIP) == 0)
                    break;
            }
            if(j == m_TerminalSet.s_TerminalNum)
            {
                m_pMyLable[3*i]->m_bExit = true;
                pthread_join(m_pMyLable[3*i]->m_pid,NULL);
                delete m_pMyLable[3*i];
                m_pMyLable[3*i] = NULL;

            }
            else
            {
                m_pMyLable[3*i]->SetName(m_TerminalSet.s_TerminalInfo[j].s_strName,m_TerminalSet.s_TerminalInfo[j].s_strSeat\
                                        ,m_TerminalSet.s_TerminalInfo[j].s_strIP);
                m_pMyLable[3*i]->SetIPPort(m_TerminalSet.s_TerminalInfo[j].s_strHostIP,m_TerminalSet.s_TerminalInfo[j].s_iPort);
//                m_pMyLable[3*i]->Enable(true);
            }
        }


        if(m_pMyLable[3*i+1] == NULL)
        {
            m_pMyLable[3*i+1] = new myLable(m_pStudentLabelContent);
            m_pMyLable[3*i+1]->SetName(m_TerminalSet.s_TerminalInfo[3*i+1].s_strName,m_TerminalSet.s_TerminalInfo[3*i+1].s_strSeat\
                                            ,m_TerminalSet.s_TerminalInfo[i*3+1].s_strIP);
            m_pMyLable[3*i+1]->SetIPPort(m_TerminalSet.s_TerminalInfo[i*3+1].s_strHostIP,m_TerminalSet.s_TerminalInfo[i*3+1].s_iPort);
            m_pMyLable[3*i+1]->move(500,150+(100+200)*i);
            m_pMyLable[3*i+1]->RemberPos(500,150+(100+200)*i);
            m_pMyLable[3*i+1]->Enable(true);
            m_pMyLable[3*i+1]->show();
        }
        else
        {
            int j = 0;
            for(j = 0;j < m_TerminalSet.s_TerminalNum;j++)
            {
                if(strcmp(m_pMyLable[3*i+1]->m_strID,m_TerminalSet.s_TerminalInfo[j].s_strIP) == 0)
                    break;
            }
            if(j == m_TerminalSet.s_TerminalNum)
            {
                m_pMyLable[3*i+1]->m_bExit = true;
                pthread_join(m_pMyLable[3*i+1]->m_pid,NULL);
                delete m_pMyLable[3*i+1];
                m_pMyLable[3*i+1] = NULL;

            }
            else
            {
                m_pMyLable[3*i+1]->SetName(m_TerminalSet.s_TerminalInfo[j].s_strName,m_TerminalSet.s_TerminalInfo[j].s_strSeat\
                                        ,m_TerminalSet.s_TerminalInfo[j].s_strIP);
                m_pMyLable[3*i+1]->SetIPPort(m_TerminalSet.s_TerminalInfo[j].s_strHostIP,m_TerminalSet.s_TerminalInfo[j].s_iPort);
            }
        }


        if(m_pMyLable[3*i+2] == NULL)
        {
            m_pMyLable[3*i+2] = new myLable(m_pStudentLabelContent);
            m_pMyLable[3*i+2]->SetName(m_TerminalSet.s_TerminalInfo[3*i+2].s_strName,m_TerminalSet.s_TerminalInfo[3*i+2].s_strSeat\
                    ,m_TerminalSet.s_TerminalInfo[i*3+2].s_strIP);
            m_pMyLable[3*i+2]->SetIPPort(m_TerminalSet.s_TerminalInfo[i*3+2].s_strHostIP,m_TerminalSet.s_TerminalInfo[i*3+2].s_iPort);
            m_pMyLable[3*i+2]->move(900,150+(100+200)*i);
            m_pMyLable[3*i+2]->RemberPos(900,150+(100+200)*i);
            m_pMyLable[3*i+2]->Enable(true);
            m_pMyLable[3*i+2]->show();
        }
        else
        {
            int j = 0;
            for(j = 0;j < m_TerminalSet.s_TerminalNum;j++)
            {
                if(strcmp(m_pMyLable[3*i+2]->m_strID,m_TerminalSet.s_TerminalInfo[j].s_strIP) == 0)
                    break;
            }
            if(j == m_TerminalSet.s_TerminalNum)
            {
                m_pMyLable[3*i+2]->m_bExit = true;
                pthread_join(m_pMyLable[3*i+2]->m_pid,NULL);
                delete m_pMyLable[3*i+2];
                m_pMyLable[3*i+2] = NULL;
            }
            else
            {
                m_pMyLable[3*i+2]->SetName(m_TerminalSet.s_TerminalInfo[j].s_strName,m_TerminalSet.s_TerminalInfo[j].s_strSeat\
                                        ,m_TerminalSet.s_TerminalInfo[j].s_strIP);
                m_pMyLable[3*i+2]->SetIPPort(m_TerminalSet.s_TerminalInfo[j].s_strHostIP,m_TerminalSet.s_TerminalInfo[j].s_iPort);
            }
        }
    }//for
    for(int i = 0;i < x;i++)
    {
        if(m_pMyLable[3*y+i] == NULL)
        {
            m_pMyLable[3*y+i] = new myLable(m_pStudentLabelContent);
            m_pMyLable[3*y+i]->SetName(m_TerminalSet.s_TerminalInfo[3*y+i].s_strName,m_TerminalSet.s_TerminalInfo[3*y+i].s_strSeat\
                                ,m_TerminalSet.s_TerminalInfo[3*y+i].s_strIP);
            m_pMyLable[3*y+i]->SetIPPort(m_TerminalSet.s_TerminalInfo[3*y+i].s_strHostIP,m_TerminalSet.s_TerminalInfo[3*y+i].s_iPort);
            m_pMyLable[3*y+i]->move(100+400*i,150+(100+200)*y);
            m_pMyLable[3*y+i]->RemberPos(100+400*i,150+(100+200)*y);
            m_pMyLable[3*y+i]->Enable(true);
            m_pMyLable[3*y+i]->show();
        }
        else
        {
            int j = 0;
            for(j = 0;j < m_TerminalSet.s_TerminalNum;j++)
            {
                if(strcmp(m_pMyLable[3*y+i]->m_strID,m_TerminalSet.s_TerminalInfo[j].s_strIP) == 0)
                    break;
            }
            if(j == m_TerminalSet.s_TerminalNum)
            {
                m_pMyLable[3*y+i]->m_bExit = true;
                pthread_join(m_pMyLable[3*y+i]->m_pid,NULL);
                delete m_pMyLable[3*y+i];
                m_pMyLable[3*y+i] = NULL;
            }
            else
            {
                m_pMyLable[3*y+i]->SetName(m_TerminalSet.s_TerminalInfo[j].s_strName,m_TerminalSet.s_TerminalInfo[j].s_strSeat\
                                        ,m_TerminalSet.s_TerminalInfo[j].s_strIP);
                m_pMyLable[3*y+i]->SetIPPort(m_TerminalSet.s_TerminalInfo[j].s_strHostIP,m_TerminalSet.s_TerminalInfo[j].s_iPort);

            }
        }
    }
    int j  = 0;
    for(int iNode = 0;iNode < TERMINALMAX;iNode++)
    {
        if(m_pMyLable[iNode] == NULL)
            continue;
        for(j = 0;j < m_TerminalSet.s_TerminalNum;j++)
        {
            if(strcmp(m_pMyLable[iNode]->m_strID,m_TerminalSet.s_TerminalInfo[j].s_strIP) == 0)
                break;
        }
        if(j == m_TerminalSet.s_TerminalNum)
        {
            m_pMyLable[iNode]->m_bExit = true;
            pthread_join(m_pMyLable[iNode]->m_pid,NULL);
            delete m_pMyLable[iNode];
            m_pMyLable[iNode] = NULL;
        }
    }
    m_pStudentLabelContent->setMinimumSize(1300,150+(100+200)*(y+1));
    m_pTerminalToolFrame->SetTerminalNum(m_TerminalSet.s_TerminalNum);
}

void TeacherForm::on_ClassOverPushButton()
{
    m_pClassOverPushButton->setEnabled(false);
    char Append[102400];
    bool ReturnCode = false;
    memset(Append,0,102400);
    QString RoomID = m_pClassNameConfig->GetRoomID();
    Q_ASSERT(RoomID.isEmpty());
    sprintf(Append,"roomName=%s",RoomID.toStdString().c_str());
    g_pLog->WriteLog(0,"Class Over Post:%s",Append);
    g_pMyHttp->Post("/service/classes/over",Append);
    memset(Append,0,102400);
    g_pMyHttp->GetData(Append);
    g_pLog->WriteLog(0,"Class Over Recv:%s",Append);
    g_pMyJson->Parse(Append);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        m_pStartSelpPushButton->setEnabled(true);
        m_pClassStartPushButton->setEnabled(true);
        m_pClassWidget->setEnabled(true);
        m_pBackPushButton->setEnabled(true);
        m_pComboxGrand->setEnabled(true);
        m_pClassOverPushButton->setEnabled(false);
        m_pTerminalToolFrame->Reset();
        m_pClassNameLabel->setText("请选择课程");
    }
    else
    {
        m_pClassOverPushButton->setEnabled(true);
    }
}
void TeacherForm::on_StudySelfPushButton()
{
    m_pStartSelpPushButton->setEnabled(false);
    char Append[102400];
    bool ReturnCode = false;
    memset(Append,0,102400);
    QString RoomID = m_pClassNameConfig->GetRoomID();
    Q_ASSERT(RoomID.isEmpty());
    sprintf(Append,"roomName=%s",RoomID.toStdString().c_str());
    g_pLog->WriteLog(0,"Study Self Post:%s",Append);
    g_pMyHttp->Post("/service/classes/freeStudy",Append);
    memset(Append,0,102400);
    g_pMyHttp->GetData(Append);
   g_pLog->WriteLog(0,"Study Self Recv:%s",Append);
    g_pMyJson->Parse(Append);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    if(ReturnCode)
    {
        m_pStartSelpPushButton->setEnabled(false);
        m_pClassStartPushButton->setEnabled(false);
        m_pClassWidget->setEnabled(false);
        m_pClassNameLabel->setText("自习课");
        m_pBackPushButton->setEnabled(false);
        m_pComboxGrand->setEnabled(false);
        m_pClassOverPushButton->setEnabled(true);
    }
    else
    {
        m_pStartSelpPushButton->setEnabled(true);
    }
}
void TeacherForm::SetClass()
{
    char JsonBuf[10240];
    bool Recode = false;
    char ClassName[GRANDNAMEMAX][100];
    memset(JsonBuf,0,10240);
    g_pMyHttp->Get("/service/classes/list?name=");
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Get Grand Name List:%s",JsonBuf);
    qDebug("Grand Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&Recode,"success");
    if(Recode)
    {
        memset(ClassName,0,sizeof(ClassName));
        int iRecode = g_pMyJson->ReadJson(ClassName,"data","name",GRANDNAMEMAX);
        for(int i = 0;i < iRecode && i < GRANDNAMEMAX;i++)
        {
            strcpy(m_ClassNameSet.s_ClassNameInfo[i].s_strClassName,ClassName[i]);
            qDebug("Class Name:%s",ClassName[i]);
        }
        memset(ClassName,0,sizeof(ClassName));
        iRecode = g_pMyJson->ReadJson(ClassName,"data","id",GRANDNAMEMAX);
        for(int i = 0;i < iRecode && i < GRANDNAMEMAX;i++)
        {
            strcpy(m_ClassNameSet.s_ClassNameInfo[i].s_strClassID,ClassName[i]);
            qDebug("Class ID:%s",ClassName[i]);
        }
        g_pLog->WriteLog(0,"Grand Num:%d",iRecode);
        if(iRecode < GRANDNAMEMAX)
            m_ClassNameSet.s_ClassNum = iRecode;
        else
            m_ClassNameSet.s_ClassNum = GRANDNAMEMAX;
    }
    else
    {

    }
    for(int i = 0; i < m_ClassNameSet.s_ClassNum;i++)
    {
        qDebug("Class[%d]:%s",i,m_ClassNameSet.s_ClassNameInfo[i].s_strClassName);
         m_pComboxGrand->addItem(m_ClassNameSet.s_ClassNameInfo[i].s_strClassName);
    }
}
void TeacherForm::SetTeacherVM()
{
    char Text[50];
    memset(Text,0,50);
    int iVMNum = 0;
    int i = 0;
    iVMNum = g_TeacherVMSet.s_VMNum;
    sprintf(Text,"教师虚拟机:%d台     可用:%d台",iVMNum,GetUsrVMNum());
    m_pTeachetVMStatusTabel->setText(Text);
    for(i = 0;i < iVMNum && i < TEACHERVMNUM;i++)
    {
        if(m_pTeacherVM[i] == NULL)
        {
            m_pTeacherVM[i] = new TeacherVM(m_pTeachetVMQWidget,g_TeacherVMSet.s_pVMInfo[i].s_strName,g_TeacherVMSet.s_pVMInfo[i].s_VMStatus);
            m_pTeacherVM[i]->SetVMInfo(g_TeacherVMSet.s_pVMInfo[i].s_strVMID);
            m_pTeacherVM[i]->move(90,(256+20)*i + 20);
        }
        //m_pTeacherVM[i]->SetStatus(m_TeacherVMSet.s_pVMInfo[i].s_VMStatus);
    }
    m_pTeachetVMQWidget->setMinimumSize(300,(256+20)*i + 20);
}
void TeacherForm::CleanTeacherVM()
{
    int iVMNum = 0;
    iVMNum = g_TeacherVMSet.s_VMNum;
    for(int i = 0;i < iVMNum && i < TEACHERVMNUM;i++)
    {
        if(m_pTeacherVM[i])
            delete m_pTeacherVM[i];
        m_pTeacherVM[i] = NULL;
    }
    memset(&g_TeacherVMSet,0,sizeof(g_TeacherVMSet));
}
void TeacherForm::CleanClassName()
{
    m_pClassNameConfig->m_iClassNum = 0;
    m_pClassNameLabel_1->SetCheckedFlag(true);
    m_pClassNameLabel_1->setEnabled(true);
    m_pClassNameLabel_2->setEnabled(true);
    m_pClassNameLabel_3->setEnabled(true);
}
void TeacherForm::on_LeftPushButton()
{
    m_pClassNameConfig->MinusInode();
    m_pClassNameConfig->SetLabelName();
}
void TeacherForm::on_RightPushButton()
{
    m_pClassNameConfig->AddInode();
    m_pClassNameConfig->SetLabelName();
}
void TeacherForm::on_LabelChecked()
{
    m_pClassNameConfig->ChooseOne();
    m_pClassNameConfig->SetLabelName();
}
void TeacherForm::on_ClassStartPushButton()
{
    qDebug() << "xxxxxxxxxxxxxxxxxxxxxxxxddddddddddddddddddddddddd." ;
    m_pClassStartPushButton->setEnabled(false);
    char Append[102400];
    memset(Append,0,102400);
    bool ReturnCode = false;
    QString name = m_pClassNameConfig->GetClassName();
    QString ID = m_pClassNameConfig->GetID();
    QString RoomID = m_pClassNameConfig->GetRoomID();
    QString GrandName = m_pComboxGrand->currentText();
    g_pLog->WriteLog(0,"Name :%s GrandName:%s",name.toStdString().c_str(),GrandName.toStdString().c_str());
    m_pClassNameLabel->setText(name);
    sprintf(Append,"desktop_pool_id=%s&roomName=%s&className=%s",ID.toStdString().c_str()\
            ,RoomID.toStdString().c_str(),GrandName.toStdString().c_str());
    g_pLog->WriteLog(0,"Class Begin Post:%s",Append);
    g_pMyHttp->Post("/service/classes/begin",Append);
    memset(Append,0,102400);
    g_pMyHttp->GetData(Append);
    g_pLog->WriteLog(0,"Class Begin Recv:%s",Append);
    g_pMyJson->Parse(Append);
    g_pMyJson->ReadJson(&ReturnCode,"success");
    qDebug("Start Button:%d",ReturnCode);
    if(ReturnCode)
    {
        m_pStartSelpPushButton->setEnabled(false);
        m_pClassWidget->setEnabled(false);
        m_pBackPushButton->setEnabled(false);
        m_pComboxGrand->setEnabled(false);
        m_pClassOverPushButton->setEnabled(true);
    }
    else
    {
        m_pClassStartPushButton->setEnabled(true);
    }
}
void TeacherForm::ClassStart()
{
}
TeacherForm::~TeacherForm()
{
    delete m_pClassNameConfig;
    delete ui;
}
void TeacherForm::CleanGrandName()
{
    m_pComboxGrand->clear();
}
void TeacherForm::CleanTermin()
{
    int iNum = m_TerminalSet.s_TerminalNum;
    for(int i = 0;i < TERMINALMAX;i++)
    {
        if(m_pMyLable[i])
        {
            m_pMyLable[i]->m_bExit = true;
            pthread_join(m_pMyLable[i]->m_pid,NULL);
            qDebug("While Thread Over");
            delete m_pMyLable[i];
            m_pMyLable[i] = NULL;
        }
    }
    for(int i = 0;i < TERMINALMAX;i++)
    {
        m_pMyLable[i] = NULL;
    }
    memset(&m_TerminalSet,0,sizeof(m_TerminalSet));
}
void *BackThreads(void *param)
{
    TeacherForm *p = (TeacherForm *)param;
        p->BackThread();
}
void TeacherForm::on_BackpushButton_clicked()
{
//    LoadFrame = false;
    m_pLoadingFrame->show();
    this->setEnabled(false);
    m_bFlag = true;
    g_pProcess->setEXIT(true);
    pthread_join(m_pid,NULL);
    //pthread_join(g_pProcess->m_pid,NULL);
    CleanTeacherVM();
    CleanClassName();
    CleanGrandName();
    CleanTermin();
    this->hide();
    m_pTerminalToolFrame->Reset();
    m_pClassStartPushButton->setEnabled(true);
    m_pLoadingFrame->hide();

}
void TeacherForm::BackThread()
{

}
void TeacherForm::SetTeachetName(QString Name)
{
    m_strTeacherName = Name;
    m_pTeacherName->setText(m_strTeacherName);
    m_pTeacherName->setStyleSheet("color:rgb(95,93,93)");
}
void TeacherForm::SetClassRoom(QString number)
{
    m_strClassRoomNum = number;
    m_pClassRoomNum->setText(m_strClassRoomNum);
}

void TeacherForm::ThreadFunWhile()
{
    char Append[100];
    char JsonBuf[102400];
    char TerminID[TERMINALMAX][100];
    bool TerminStatus[TERMINALMAX];
    int iTerminNum = 0;
    int iWhileNum = 0;
    bool Recode = false;
    myHttp http;
    http.SetUrlIP(g_strServerIP);
    m_pid = pthread_self();
    while(!m_bFlag)
    {
       // qDebug("While Fun Thread");
        sleep(2);
        memset(Append,0,100);
        memset(JsonBuf,0,102400);
        memset(TerminID,0,sizeof(TerminID));
        memset(TerminStatus,0,sizeof(TerminStatus));
        sprintf(Append,"roomname=%s",g_strRoomNum);
        http.Post("/service/classes/list_handupstubyap",Append);
        iWhileNum++;
        http.GetData(JsonBuf);
        qDebug("Get HandUPStatus:%s",JsonBuf);
        if(iWhileNum == 10)
        {
            g_pLog->WriteLog(0,"While:%s",JsonBuf);
            iWhileNum = 0;
        }
        g_pMyJson->Parse(JsonBuf);
        g_pMyJson->ReadJson(&Recode,"success");
        if(Recode)
        {
            iTerminNum = g_pMyJson->ReadJson(TerminID,"data","studentHandUpStatus","apId",TERMINALMAX);
            iTerminNum = g_pMyJson->ReadJson(TerminStatus,"data","studentHandUpStatus","enableHandUp",TERMINALMAX);
            if(iTerminNum == 0)
            {
                for(int j = 0;j < m_TerminalSet.s_TerminalNum;j++)
                {
                    if(m_pMyLable[j])
                        m_pMyLable[j]->ShowUpHand(false);
                }
            }
            for(int i = 0;i < iTerminNum;i++)
            {
              //  qDebug("TerminID[%s]",TerminID[i]);
                for(int j = 0;j < m_TerminalSet.s_TerminalNum;j++)
                {
                   // qDebug("Terminal ID[%s]",m_pMyLable[j]->m_strID);
                    if(m_pMyLable[j])
                    {
                        if(strlen(m_pMyLable[j]->m_strID))
                        {
                            if(strcmp(m_pMyLable[j]->m_strID,TerminID[i]) == 0)
                            {
                                //qDebug("Terminal Status[%d]:%d",j,TerminStatus[i]);
                                m_pMyLable[j]->ShowUpHand(TerminStatus[i]);
                                break;
                            }
                        }
                    }
                }
            }
        }
        else
        {

        }
//        http.Get("/service/desktops/list");
//        memset(JsonBuf,0,102400);
//        http.GetData(JsonBuf);
//        Recode = false;
//        g_pMyJson->Parse(JsonBuf);
//        g_pMyJson->ReadJson(&Recode,"success");
//        if(Recode)
//        {
//            memset(VMNameBuf,0,sizeof(VMNameBuf));
//            int iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","name",TEACHERVMNUM);
//            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
//            {
//                strcpy(m_TeacherVMSet.s_pVMInfo[i].s_strName,VMNameBuf[i]);
//            }
//            iRecode = g_pMyJson->ReadJson(VMStatus,"data","status",TEACHERVMNUM);
//            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
//            {
//                switch(VMStatus[i])
//                {
//                case 2:m_TeacherVMSet.s_pVMInfo[i].s_VMStatus = USING;
//                    break;
//                case 1:m_TeacherVMSet.s_pVMInfo[i].s_VMStatus = CLOSE;
//                    break;
//                case 3:m_TeacherVMSet.s_pVMInfo[i].s_VMStatus = RESTART;
//                    break;
//                case 8:m_TeacherVMSet.s_pVMInfo[i].s_VMStatus = WARNING;
//                    break;
//                default:m_TeacherVMSet.s_pVMInfo[i].s_VMStatus = ERROR;
//                    break;
//                }
//            }
//            memset(VMNameBuf,0,sizeof(VMNameBuf));
//            iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","id",TEACHERVMNUM);
//            for(int i = 0; i < iRecode && i < TEACHERVMNUM;i++)
//            {
//                strcpy(m_TeacherVMSet.s_pVMInfo[i].s_strVMID,VMNameBuf[i]);
//            }
//            if(iRecode < TEACHERVMNUM)
//                m_TeacherVMSet.s_VMNum =    iRecode;
//            else
//                m_TeacherVMSet.s_VMNum = TEACHERVMNUM;
//            SetTeacherVM();
//        }
    }
    m_bFlag = false;
}
void TeacherForm::SetClock(QDateTime *time)
{
    char Text[50];
    memset(Text,0,50);
    sprintf(Text,"教师虚拟机:%d台     可用:%d台",g_TeacherVMSet.s_VMNum,GetUsrVMNum());
    m_pTeachetVMStatusTabel->setText(Text);
    m_pTimeLCDNumber->display(time->toString("yyyy-MM-dd HH:mm:ss"));
}
int TeacherForm::GetUsrVMNum()
{
    int iNum = 0;
    for(int i = 0;i < g_TeacherVMSet.s_VMNum;i++)
     {
        if(g_TeacherVMSet.s_pVMInfo[i].s_VMStatus == USING)
            iNum++;

     }
    return iNum;
}
void TeacherForm::SetStartClassPushButton(bool flag)
{
    if(m_pClassStartPushButton)
    {
        m_pClassStartPushButton->setEnabled(flag);
    }
}
