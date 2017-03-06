#include "myhttp.h"

extern Log *g_pLog;
myHttp::myHttp()
{
    m_strIP = "http://";
    m_pNetManager = new QNetworkAccessManager();
    m_peventLoop = new QEventLoop();
    m_preply = NULL;
    QObject::connect(m_pNetManager, SIGNAL(finished(QNetworkReply*)),m_peventLoop, SLOT(quit()));
}
/*
void myHttp::ReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    m_JsonMessage.clear();
    m_JsonMessage = codec->toUnicode(reply->readAll());
    m_bReady = true;
    //g_pLog->WriteLog(0,"Recv:%s",m_JsonMessage.toStdString().c_str());
    qDebug("Recv:%s",m_JsonMessage.toStdString().c_str());
    reply->deleteLater();
}*/
myHttp::~myHttp()
{
    if(m_pNetManager)
        delete  m_pNetManager;
    if(m_peventLoop)
        delete m_peventLoop;
}
void myHttp::Post(QString url, const char *append)
{
    QUrl    Tempurl(m_strIP+url);
    qDebug("\nURL:%s\n",Tempurl.toString().toStdString().c_str());
    QByteArray  appen(append);
    m_preply = m_pNetManager->post(QNetworkRequest(Tempurl),appen);
}
void myHttp::Get(QString url)
{
    QUrl    Tempurl(m_strIP+url);
    qDebug("URL:%s",Tempurl.toString().toStdString().c_str());
    m_preply = m_pNetManager->get(QNetworkRequest(Tempurl));
}
void myHttp::GetData(char *Buf)
{
    if(Buf == NULL)
        return ;
    if(m_preply == NULL)
        return ;
    m_peventLoop->exec();
    m_JsonMessage.clear();
    m_JsonMessage = m_preply->readAll();
    strcpy(Buf,m_JsonMessage.toStdString().c_str());
    m_preply->deleteLater();
    m_preply = NULL;
}
