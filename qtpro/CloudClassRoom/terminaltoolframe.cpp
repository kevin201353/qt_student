#include "terminaltoolframe.h"
#include "ui_terminaltoolframe.h"
#include "include.h"

TerminalToolFrame::TerminalToolFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TerminalToolFrame)
{
    ui->setupUi(this);
    //this->setMinimumHeight(70);
    m_pCallNamePushButton = ui->CallNamepushButton;
    m_pHandUpPushButton = ui->NoHandUppushButton;
    m_pNetWorkPushButton = ui->NoNetworkpushButton;
    m_pUSBPushButton = ui->NoUSBpushButton;
    m_pFlusshPushButton = ui->DarkScreenpushButton;
    m_pVMTotail = ui->TerminNumberlabel;
    m_pDarkScreenPushButton = ui->DarkscreenpushButton;

    m_pDarkScreenPushButton->setMinimumSize(58,58);
    m_pDarkScreenPushButton->setStyleSheet(NOTDARKSCREEN);
    m_pDarkScreenPushButton->setToolTip("学生黑屏");

    m_pCallNamePushButton->setMinimumSize(58,58);
    m_pCallNamePushButton->setStyleSheet(CALLNAME);
    m_pCallNamePushButton->setToolTip("电子点名");

    m_pHandUpPushButton->setMinimumSize(58,58);
    m_pHandUpPushButton->setStyleSheet(HANDUP);
    m_pHandUpPushButton->setToolTip("禁止举手");

    m_pNetWorkPushButton->setMinimumSize(58,58);
    m_pNetWorkPushButton->setStyleSheet(ALLOWNETWORK);
    m_pNetWorkPushButton->setToolTip("禁止网络");

    m_pUSBPushButton->setMinimumSize(58,58);
    m_pUSBPushButton->setStyleSheet(ALLOWUSB);
    m_pUSBPushButton->setToolTip("禁止USB");

    m_pFlusshPushButton->setMinimumSize(58,58);
    m_pFlusshPushButton->setStyleSheet(FLUSSHPNG);
    m_pFlusshPushButton->setToolTip("刷新");

    m_Font.setPixelSize(25);
    m_pVMTotail->setFont(m_Font);
    m_pVMTotail->setStyleSheet("color: rgb(95,93,93)");
    m_bHandUPFlag = false;
    m_bUSBFlag = false;
    m_bNetWorkFlag = false;
    m_bDarkScreenFlag = false;
}

TerminalToolFrame::~TerminalToolFrame()
{
    delete ui;
}

void TerminalToolFrame::on_NoHandUppushButton_clicked()
{
    bool Recode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pHandUpPushButton->setEnabled(false);
    if(m_bHandUPFlag)
    {

        m_pHandUpPushButton->setStyleSheet(HANDUP);
        sprintf(TempBuf,"/service/classes/enable_handup?enableHand=true&name=%s",g_strRoomNum);

    }
    else
    {

        m_pHandUpPushButton->setStyleSheet(HANDDOWNPNG);
        sprintf(TempBuf,"/service/classes/enable_handup?enableHand=false&name=%s",g_strRoomNum);

    }
    m_bHandUPFlag = !m_bHandUPFlag;
    g_pLog->WriteLog(0,"Hand UP Set Get:%s",TempBuf);
    qDebug("Hand UP Set Get:%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);

    g_pLog->WriteLog(0,"HandUP Json:%s",JsonBuf);
    qDebug("HandUP Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&Recode,"success");
    if(Recode)
    {
        qDebug("HandUP OK");
    }
    else
    {

    }
    m_pHandUpPushButton->setEnabled(true);
}
void TerminalToolFrame::Reset()
{
    m_pDarkScreenPushButton->setStyleSheet(NOTDARKSCREEN);
    m_pCallNamePushButton->setStyleSheet(CALLNAME);
    m_pHandUpPushButton->setStyleSheet(HANDUP);
    m_pNetWorkPushButton->setStyleSheet(ALLOWNETWORK);
    m_pUSBPushButton->setStyleSheet(ALLOWUSB);
    m_pFlusshPushButton->setStyleSheet(FLUSSHPNG);
    m_bHandUPFlag = false;
    m_bUSBFlag = false;
    m_bNetWorkFlag = false;
    m_bDarkScreenFlag = false;

}
void TerminalToolFrame::on_NoNetworkpushButton_clicked()
{
    bool Recode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pNetWorkPushButton->setEnabled(false);
    if(m_bNetWorkFlag)
    {
        m_pNetWorkPushButton->setStyleSheet(ALLOWNETWORK);
        sprintf(TempBuf,"/service/classes/enable_net?enableNet=true&name=%s",g_strRoomNum);
    }
    else
    {
        m_pNetWorkPushButton->setStyleSheet(NOTALLOWNETWORK);
        sprintf(TempBuf,"/service/classes/enable_net?enableNet=false&name=%s",g_strRoomNum);
    }
    m_bNetWorkFlag = !m_bNetWorkFlag;
    g_pLog->WriteLog(0,"Network Set Get:%s",TempBuf);
    qDebug("%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Network Set Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&Recode,"success");
    if(Recode)
    {
        qDebug("NetWork OK");
    }
    else
    {

    }
    m_pNetWorkPushButton->setEnabled(true);
}

void TerminalToolFrame::on_NoUSBpushButton_clicked()
{
    bool Recode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pUSBPushButton->setEnabled(false);
    if(m_bUSBFlag)
    {
        m_pUSBPushButton->setStyleSheet(ALLOWUSB);
        sprintf(TempBuf,"/service/classes/enable_usb?enableUSB=true&name=%s",g_strRoomNum);
    }
    else
    {
        m_pUSBPushButton->setStyleSheet(NOTALLOWUSB);
         sprintf(TempBuf,"/service/classes/enable_usb?enableUSB=false&name=%s",g_strRoomNum);
    }
    m_bUSBFlag = !m_bUSBFlag;
    g_pLog->WriteLog(0,"USB Set Get:%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"USB Set Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&Recode,"success");
    if(Recode)
    {
        qDebug("USBOK");
    }
    else
    {

    }
    m_pUSBPushButton->setEnabled(true);
}
void TerminalToolFrame::SetTerminalNum(int i)
{
    char Buf[100];
    memset(Buf,0,100);
    sprintf(Buf,"共有%d台终端",i);
    m_pVMTotail->setText(Buf);
}
void TerminalToolFrame::on_DarkScreenpushButton_clicked()
{
    m_pFlusshPushButton->setEnabled(false);
    char TempBuf[100];
    char JsonBuf[102400];
    bool LoginFlag = false;
    char VMNameBuf[TERMINALMAX][100];
    memset(TempBuf,0,100);
    g_pMyHttp->Get("/service/aps/list?qp.filterWhere={\"type\":\"student\",\"status\":0}}");
    g_pLog->WriteLog(0,"Get Terminal:/service/aps/list?qp.filterWhere={\"type\":\"student\",\"status\":0}}");
    memset(JsonBuf,0,102400);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Get Terminal Recv Json:%s",JsonBuf);
    qDebug("Get Terminal Recv Json:%s",JsonBuf);
    LoginFlag = false;
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&LoginFlag,"success");
     if(LoginFlag)
    {
       char IDBuf[TERMINALMAX][100];
        char RoomNameBuf[TERMINALMAX][100];
        char HostAddr[TERMINALMAX][100];
        int Port[TERMINALMAX];
        memset(IDBuf,0,sizeof(IDBuf));
        memset(RoomNameBuf,0,sizeof(RoomNameBuf));
        memset(HostAddr,0,sizeof(HostAddr));
        memset(Port,0,sizeof(Port));
        memset(VMNameBuf,0,sizeof(VMNameBuf));
        memset(&g_pTeacherForm->m_TerminalSet,0,sizeof(g_pTeacherForm->m_TerminalSet));
        int iRecode = g_pMyJson->ReadJson(VMNameBuf,"data","list","id",TERMINALMAX);
        iRecode = g_pMyJson->ReadJson(IDBuf,"data","list","seat",TERMINALMAX);
        iRecode = g_pMyJson->ReadJson(RoomNameBuf,"data","list","stuName",TERMINALMAX);
        iRecode = g_pMyJson->ReadJson(HostAddr,"data","list","hostAddress",TERMINALMAX);
        iRecode = g_pMyJson->ReadJson(Port,"data","list","consolePort",TERMINALMAX);
        for(int i = 0; i < iRecode && i < TERMINALMAX;i++)
        {
            strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strName,RoomNameBuf[i]);
            strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strIP,VMNameBuf[i]);
            strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strSeat,IDBuf[i]);
            strcpy(g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_strHostIP,HostAddr[i]);
            g_pTeacherForm->m_TerminalSet.s_TerminalInfo[i].s_iPort = Port[i];

        }
        if(iRecode < TERMINALMAX)
            g_pTeacherForm->m_TerminalSet.s_TerminalNum = iRecode;
        else
            g_pTeacherForm->m_TerminalSet.s_TerminalNum = TERMINALMAX;
        g_pLog->WriteLog(0,"Get Terminal Num:%d",g_pTeacherForm->m_TerminalSet.s_TerminalNum);
        g_pTeacherForm->SetTerminal();
    }
    else
    {

    }
     m_pFlusshPushButton->setEnabled(true);
}

void TerminalToolFrame::on_CallNamepushButton_clicked()
{
    char JsonBuf[1024];
    bool Recode = false;
    memset(JsonBuf,0,1024);
    m_pCallNamePushButton->setEnabled(false);
    sprintf(JsonBuf,"/service/classes/enable_signin?enableCallroll=true&name=%s",g_strRoomNum);
    g_pMyHttp->Get(JsonBuf);
    memset(JsonBuf,0,1024);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"CallName Recv Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&Recode,"success");
    if(Recode)
    {
        qDebug("CallNameOK");
    }
    else
    {

    }
    m_pCallNamePushButton->setEnabled(true);
}

void TerminalToolFrame::on_DarkscreenpushButton_clicked()
{
    bool Recode = false;
    char TempBuf[100];
    char JsonBuf[1024];
    memset(JsonBuf,0,1024);
    memset(TempBuf,0,100);
    m_pDarkScreenPushButton->setEnabled(false);
    if(m_bDarkScreenFlag)
    {
        m_pDarkScreenPushButton->setStyleSheet(NOTDARKSCREEN);
        sprintf(TempBuf,"/service/classes/enable_blackscreen?enableBlack=false&name=%s",g_strRoomNum);
    }
    else
    {
        m_pDarkScreenPushButton->setStyleSheet(DARKSCREEN);
        sprintf(TempBuf,"/service/classes/enable_blackscreen?enableBlack=true&name=%s",g_strRoomNum);
    }
    m_bDarkScreenFlag = !m_bDarkScreenFlag;
    g_pLog->WriteLog(0,"Dark Screen Get:%s",TempBuf);
    g_pMyHttp->Get(TempBuf);
    g_pMyHttp->GetData(JsonBuf);
    g_pLog->WriteLog(0,"Dark Screen Json:%s",JsonBuf);
    qDebug("Dark Screen Json:%s",JsonBuf);
    g_pMyJson->Parse(JsonBuf);
    g_pMyJson->ReadJson(&Recode,"success");
    if(Recode)
    {
        qDebug("Dark Screen OK");
    }
    else
    {

    }
    m_pDarkScreenPushButton->setEnabled(true);
}
