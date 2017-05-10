#include "myhttp.h"

extern Log *g_pLog;
myHttp::myHttp()
{
    m_strIP = "http://";
    m_pNetManager = new QNetworkAccessManager();
    m_peventLoop = new QEventLoop();
    m_preply = NULL;
    pthread_mutex_init(&m_Locak,NULL);
    m_Qtimer.setInterval(TIMEOUT);
    m_Qtimer.setSingleShot(true);
    QObject::connect(&m_Qtimer,SIGNAL(timeout()),m_peventLoop,SLOT(quit()));
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
    g_pLog->WriteLog(0,"\nURL:%s, %s \n",Tempurl.toString().toStdString().c_str(), append);
    m_preply = m_pNetManager->post(QNetworkRequest(Tempurl),appen);
}
void myHttp::Get(QString url)
{
    QUrl    Tempurl(m_strIP+url);
    qDebug("URL:%s",Tempurl.toString().toStdString().c_str());
    g_pLog->WriteLog(0,"\nURL: %s \n",Tempurl.toString().toStdString().c_str());
    m_preply = m_pNetManager->get(QNetworkRequest(Tempurl));
}

void myHttp::Get2(QString url)
{
    QUrl    Tempurl(url);
    qDebug("URL:%s",Tempurl.toString().toStdString().c_str());
    g_pLog->WriteLog(0,"\nURL: %s \n",Tempurl.toString().toStdString().c_str());
    m_preply = m_pNetManager->get(QNetworkRequest(Tempurl));
}

void myHttp::GetData(char *Buf)
{
    if(Buf == NULL)
        return ;
    if(m_preply == NULL)
        return ;
    m_Qtimer.start();
    pthread_mutex_lock(&m_Locak);
    m_peventLoop->exec();
    pthread_mutex_unlock(&m_Locak);
    if(m_Qtimer.isActive())
    {
        m_Qtimer.stop();
        m_JsonMessage.clear();
        m_JsonMessage = m_preply->readAll();
        if(m_JsonMessage.size())
        {
            strcpy(Buf,m_JsonMessage.toStdString().c_str());
        }
        g_pLog->WriteLog(0,"zhaosenhua ProcessThread http receive msg len: %d.\n", m_JsonMessage.size());
        m_preply->deleteLater();
        m_preply = NULL;
    }
    else
    {
        qDebug("Time Out");
        g_pLog->WriteLog(0,"zhaosenhua ProcessThread http receive msg time out.\n");
    }
    if(m_preply)
    {
        m_preply->deleteLater();
        m_preply = NULL;
    }
}
