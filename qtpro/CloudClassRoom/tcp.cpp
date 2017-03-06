#include "tcp.h"
void *ReadThread(void *param);
void *WriteThread(void *param);

TcpServer::TcpServer()
{
    m_iSocket = 0;
    m_cInitFlag = 0;
    memset(&m_SockAddr,0,sizeof(m_SockAddr));
    memset(&m_ClientSocket,0,sizeof(m_ClientSocket));
    m_iClientSocket = 0;
    m_iPort = 0;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
    m_SendPid = 0;
    m_ReadPid = 0;
    pthread_mutex_init(&m_Locak,NULL);
    m_iSockOK = 0;
}

TcpServer::~TcpServer()
{
    if(m_iSocket)
        close(m_iSocket);
    if(m_iClientSocket)
    {
        close(m_iClientSocket);
    }
    if(m_pRecvBuf)
        delete m_pRecvBuf;
    if(m_pSendBuf)
        delete m_pSendBuf;
    m_iClientSocket = 0;
    m_iSocket = 0;
    m_cInitFlag = 0;
    m_iPort = 0;
    m_SendPid = 0;
    m_ReadPid = 0;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
    pthread_mutex_destroy(&m_Locak);
    m_iSockOK = 0;
}

int TcpServer::CreateSocket()
{
    if(m_iSocket)
    {
        close(m_iSocket);
    }
    m_iSocket = socket(AF_INET,SOCK_STREAM,0);
    if(m_iSocket < 0)
    {
        printf("Create socket Error[%d]:%s",errno,strerror(errno));
        return -1;
    }
    return m_iSocket;
}

int TcpServer::Bind()
{
    int iRecode = 0;
    if(m_iSocket <= 0)
    {
        return -1;
    }

    iRecode = bind(m_iSocket,(const struct sockaddr*)&m_SockAddr,sizeof(m_SockAddr));
    if(iRecode < 0)
    {
        return -2;
    }
    return 0;
}

int TcpServer::InitBuf()
{
    if(!m_pRecvBuf)
    {
        m_pRecvBuf = new ListBuf();
    }
    else
    {
        printf("m_pRecvBuf is not NULL\n");
        return -1;
    }
    m_pRecvBuf->InitBuf(sizeof(data),1024,EXPANDMODE);
    if(!m_pSendBuf)
    {
        m_pSendBuf = new ListBuf();
    }
    else
    {
        printf("m_pSendBuf is not NULL\n");
        return -2;
    }
    m_pSendBuf->InitBuf(sizeof(data),1024,EXPANDMODE);
    return 0;
}
int TcpServer::InitTCP(int port)
{
    int iRecode = 0;
    if(port < 0)
    {
        printf("Port Error[%d]\n",port);
        return -1;
    }
    iRecode = CreateSocket();
    if(iRecode < 0)
    {
        printf("CreateSocket Error\n");
        return -2;
    }
    iRecode = SetSocket();
    if(iRecode < 0)
    {
        printf("Set Socket Error\n");
        return -3;
    }
    iRecode = InitBuf();
    if(iRecode < 0)
    {
        printf("Init TCP Recv Buf Error!\n");
        return -6;
    }
    m_SockAddr.sin_family = AF_INET;
    m_SockAddr.sin_addr.s_addr = INADDR_ANY;
    m_SockAddr.sin_port = htons(port);
    m_iPort = port;

    iRecode = Bind();
    if(iRecode < 0)
    {
        printf("Bind Error!\n");
        return -4;
    }
    iRecode = Listen();
    if(iRecode < 0)
    {
        printf("Listen Error!\n");
        return -5;
    }
    pthread_create(&m_ReadPid,NULL,ReadThread,this);
    pthread_create(&m_SendPid,NULL,WriteThread,this);
    return 0;
}
void *ReadThread(void *param)
{
    TcpServer *Tmp = (TcpServer*)param;
    Tmp->TcpReadThread();
    return NULL;
}
void *WriteThread(void *param)
{
    TcpServer *Tmp = (TcpServer*)param;
    Tmp->TcpWriteThread();
    return NULL;
}
int TcpServer::TcpWriteThread()
{
    data Tempdata;
    while(/*!cMainExitFlag*/1)
    {
        if(!m_iSockOK)
        {
            sleep(2);
            continue;
        }
        memset(&Tempdata,0,sizeof(data));
        if(m_pSendBuf->Get((char *)&Tempdata,1) < 0)
        {
            continue;
        }
        if(WriteTCP(Tempdata.s_Buf,Tempdata.s_Size) < 0)
        {
            continue;
        }
        sleep(1);
    }
    return 0;
}
int TcpServer::TcpReadThread()
{
    int iLen = 0;
    char TempBuf[1024];
    data Tempdata;
    while(/*!cMainExitFlag*/1)
    {
        if(!m_iSockOK)
        {
            sleep(2);
            continue;
        }
        memset(TempBuf,0,1024);
        memset(&Tempdata,0,sizeof(data));
        if(ReadTCP(&iLen,4) <= 0)
        {
            continue;
        }
        if(iLen > 0)
        {
            if(ReadTCP(TempBuf,iLen) <= 0)
            {
                continue;
            }
        }
        Tempdata.s_Size = iLen;
        strcpy(Tempdata.s_Buf,TempBuf);
        m_pRecvBuf->Put((char *)&Tempdata,1);
 //       g_pLog->WriteLog(0,"Recv:%s",Tempdata.s_Buf);
        sleep(1);
    }
    return 0;
}
int TcpServer::Listen()
{
    int iRecode = 0;
    if(m_iSocket <= 0)
    {
        printf("m_iSocket Error\n");
        return -1;
    }
    iRecode = listen(m_iSocket,5);
    if(iRecode < 0)
    {
        printf("Function listen Error!");
        return -2;
    }
    return 0;
}
int TcpServer::Accept()
{
    socklen_t sockAddrLen = 0;
    int iTempSocket = 0;
    sockAddrLen = sizeof(m_ClientSocket);
    if(m_iSocket <= 0)
    {
        printf("Accept Error\n");
        return -1;
    }

    iTempSocket = accept(m_iSocket,&m_ClientSocket,&sockAddrLen);
    if(m_iClientSocket < 0)
    {
        printf("Server accept Error[%d]!\n",m_iClientSocket);
        return -2;
    }
    //lock
    pthread_mutex_lock(&m_Locak);
    m_iSockOK = 1;
    m_iClientSocket = iTempSocket;
    pthread_mutex_unlock(&m_Locak);
    //unlock
    return m_iClientSocket;
}

char* TcpServer::GetClientIP() const
{
    sockaddr_in Temp = *((sockaddr_in *)&m_ClientSocket);
    return inet_ntoa(Temp.sin_addr);
}

int TcpServer::WriteTCP(const void *data, int size)
{
    int iTemp = 0;
    char *pTemp = NULL;
    int iRecode = 0;
    if(data == NULL)
    {
        return -1;
    }
    if(m_iClientSocket <= 0)
    {
        return -2;
    }
    pTemp = (char *)data;
    while(iTemp < size)
    {
        iRecode = write(m_iClientSocket,pTemp,size-iTemp);
        if(iRecode <= 0)
        {
            m_iSockOK = 0;
            return iTemp;
        }
        iTemp += iRecode;
        pTemp += iTemp;
    }
    return iTemp;
}
int TcpServer::ReadTCP(void *data, int size)
{
    char *pData = NULL;
    int  iTemp = 0;
    int iRecode = 0;
    struct timeval tv;
    fd_set fds;
    if(data == NULL)
    {
        return -1;
    }
    if(m_iClientSocket <= 0)
    {
        return -2;
    }
    pData = (char*)data;
    while(iTemp < size)
    {
        tv.tv_sec = READTIMEOUT;
        tv.tv_usec = 0;

        FD_ZERO(&fds);
        if(m_iClientSocket > 0)
        {
            FD_SET(m_iClientSocket,&fds);
        }
        else
        {
            //g_pLog->WriteLog(0,"m_iClient[%d] Connect Close",m_iClientSocket);
            return -4;
        }
        iRecode = select(m_iClientSocket+1,&fds,NULL,NULL,&tv);
        if(iRecode < 0)
        {
          //  g_pLog->WriteLog(0,"select Error[%d]:%s",errno,strerror(errno));
            return -3;
        }else if(iRecode == 0)
        {
         //   g_pLog->WriteLog(0,"select Time Out");
            close(m_iClientSocket);
            return 0;
        }
        else
        {
            iRecode = read(m_iClientSocket,pData,size-iTemp);
            if(iRecode <= 0)
            {
                m_iSockOK = 0;
            //    g_pLog->WriteLog(0,"TCP Read Error:[%d] %s",iRecode,strerror(errno));
                return iTemp;
            }
            iTemp += iRecode;
            pData += iTemp;
        }
    }
    return iTemp;
}
int TcpServer::SetSocket()
{
    int iRecode = 0;
    struct linger sLin;
    int iTemp;
    if(m_iSocket <= 0)
    {
        printf("m_iSkcoet Error!\n");
        return -1;
    }
    sLin.l_onoff = 1;
    sLin.l_linger = 5;
    iRecode = setsockopt(m_iSocket,SOL_SOCKET,SO_LINGER,&sLin,sizeof(sLin));
    if(iRecode < 0)
    {
        printf("Set SO_LINGER Error:%s\n",strerror(errno));
        return iRecode;
    }

    iTemp = 1;
    iRecode = setsockopt(m_iSocket,SOL_SOCKET,SO_REUSEADDR,&iTemp,sizeof(iTemp));
    if(iRecode < 0)
    {
        printf("Set SO_REUSEADDR Error:%s\n",strerror(errno));
        return iRecode;
    }
    iTemp = 0;
    iRecode = setsockopt(m_iSocket,SOL_SOCKET,SO_RCVBUF,&iTemp,sizeof(iTemp));
    if(iRecode < 0)
    {
        printf("Set SO_RCVBUF Error:%s\n",strerror(errno));
        return iRecode;
    }
    iRecode = setsockopt(m_iSocket,SOL_SOCKET,SO_SNDBUF,&iTemp,sizeof(iTemp));
    if(iRecode < 0)
    {
        printf("Set SO_SNDBUF Error:%s\n",strerror(errno));
        return iRecode;
    }

    // 接收缓冲区
    iTemp =32*1024;//设置为32K
    iRecode = setsockopt (m_iSocket,SOL_SOCKET,SO_RCVBUF,(const char*)&iTemp,sizeof(iTemp));
    if(iRecode < 0)
    {
        printf("Set SO_RCVBUF Error:%s\n",strerror(errno));
        return iRecode;
    }
    //发送缓冲区

    iRecode = setsockopt (m_iSocket,SOL_SOCKET,SO_SNDBUF,(const char*)&iTemp,sizeof(iTemp));
    if(iRecode < 0)
    {
        printf("Set SO_SNDBUF Error:%s\n",strerror(errno));
        return iRecode;
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
TcpClient::TcpClient()
{
    m_iPort = 0;
    m_iSocket = 0;
    memset(m_strIP,0,20);
    m_cInitFlag = 0;
    m_addr = NULL;
    m_result = NULL;
    memset(&m_cInitFlag,0,sizeof(m_cInitFlag));
}

TcpClient::~TcpClient()
{
    m_iPort = 0;
    if(m_iSocket > 0)
        close(m_iSocket);
    m_iSocket = 0;
}
int TcpClient::CreateSocket(const char *IP,const char *Port)
{
    int iFcnl = -1;
    int istatus = 0;
    if(m_iSocket < 0)
        return 0;
    if(IP == NULL || Port == NULL)
        return -1;
    memset(&m_hints,0,sizeof(m_hints));
    m_hints.ai_family = AF_UNSPEC;
    m_hints.ai_socktype = SOCK_STREAM;
    istatus = getaddrinfo(IP,Port,&m_hints,&m_result);
    if(istatus)
    {
        printf("Getaddrinfo:%s\n",gai_strerror(istatus));
        return -1;
    }
    m_addr = m_result;
    if((m_addr->ai_family == AF_INET6) && (m_addr->ai_next != 0))
    {
        while((m_addr=m_addr->ai_next))
        {
            if(m_addr->ai_family == AF_INET)
                break;
        }
        if(m_addr == NULL)
            m_addr = m_result;
    }
    if(m_iSocket > 0)
        close(m_iSocket);
    m_iSocket = 0;
    m_iSocket = socket(m_addr->ai_family,m_addr->ai_socktype,m_addr->ai_protocol);
    if(m_iSocket < 0)
    {
        freeaddrinfo(m_result);
        printf("Create socket Error[%d]:%s\n",errno,strerror(errno));
        return -2;
    }
    m_cInitFlag = 1;

//    iFcnl = fcntl(m_iSocket,F_GETFL);
//    if(iFcnl < 0)
//    {
//        return -3;
//    }
//    fcntl(m_iSocket,F_SETFL,O_NONBLOCK|iFcnl);
    return m_iSocket;
}
int TcpClient::Connect()
{
    if(m_cInitFlag)
    {
        //Connect .........
        if(connect(m_iSocket,m_addr->ai_addr,m_addr->ai_addrlen))
        {
            printf("Connect Error!\n");
            return -1;
        }
    }
    else
    {
        printf("Not Init\n");
    }
    return 0;
}

int TcpClient::WriteTCP(const void *data, int size)
{
    int iTemp = 0;
    char *pTemp = NULL;
    int iRecode = 0;
    if(data == NULL)
    {
        return -1;
    }
    if(m_iSocket <= 0)
    {
        return -2;
    }
    pTemp = (char *)data;
    while(iTemp < size)
    {
        if(pTemp == NULL)
            break;
        iRecode = write(m_iSocket,pTemp,size-iTemp);
        if(iRecode <= 0)
        {
            return iTemp;
        }
        iTemp += iRecode;
        pTemp += iTemp;
    }
    return iTemp;
}
int TcpClient::ReadTCP(void *data, int size)
{
    char *pData = NULL;
    int  iTemp = 0;
    int iRecode = 0;
    struct timeval tv;
    fd_set fds;
    if(data == NULL)
    {
        return -1;
    }
    if(m_iSocket <= 0)
    {
        return -2;
    }
    pData = (char*)data;
    while(iTemp < size)
    {
        tv.tv_sec = READTIMEOUT;
        tv.tv_usec = 0;

        FD_ZERO(&fds);
        if(m_iSocket > 0)
        {
            FD_SET(m_iSocket,&fds);
        }
        else
        {
         //   printf("m_iClient[%d] Connect Close",m_iSocket);
   //         g_pLog->WriteLog(0,"m_iClient[%d] Connect Close",m_iSocket);
            return -4;
        }
        iRecode = select(m_iSocket+1,&fds,NULL,NULL,&tv);
        if(iRecode < 0)
        {
        //    printf("select Error[%d]:%s",errno,strerror(errno));
 //           g_pLog->WriteLog(0,"select Error[%d]:%s",errno,strerror(errno));
            return -3;
        }else if(iRecode == 0)
        {
       //     printf("select Time Out");
 //           g_pLog->WriteLog(0,"select Time Out");
            close(m_iSocket);
            return 0;
        }
        else if(FD_ISSET(m_iSocket, &fds))
        {
            iRecode = read(m_iSocket,pData,size-iTemp);
            if(iRecode <= 0)
            {
          //      printf("TCP Read Socket[%d] Error:[%d] %s",m_iSocket,iRecode,strerror(errno));

 //               g_pLog->WriteLog(0,"TCP Read Error:[%d] %s",iRecode,strerror(errno));
                return iTemp;
            }
            iTemp += iRecode;
            pData += iRecode;
        }
    }
    return iTemp;
}
void TcpClient::set_keepalive(int keep_alive, int keep_idle, int keep_interval, int keep_count)
{
    int opt = 1;
    if(keep_alive){
        if(setsockopt(m_iSocket, SOL_SOCKET, SO_KEEPALIVE,(void*)&keep_alive, sizeof(keep_alive)) == -1){
            fprintf(stderr, "setsockopt SOL_SOCKET::SO_KEEPALIVE failed, %s\n",strerror(errno));
        }
        if(setsockopt(m_iSocket, SOL_TCP, TCP_KEEPIDLE,(void *)&keep_idle,sizeof(keep_idle)) == -1){
            fprintf(stderr,"setsockopt SOL_TCP::TCP_KEEPIDLE failed, %s\n", strerror(errno));
        }
        if(setsockopt(m_iSocket,SOL_TCP,TCP_KEEPINTVL,(void *)&keep_interval, sizeof(keep_interval)) == -1){
            fprintf(stderr,"setsockopt SOL_tcp::TCP_KEEPINTVL failed, %s\n", strerror(errno));
        }
        if(setsockopt(m_iSocket,SOL_TCP,TCP_KEEPCNT,(void *)&keep_count,sizeof(keep_count)) == -1){
            fprintf(stderr, "setsockopt SOL_TCP::TCP_KEEPCNT failed, %s\n", strerror(errno));
        }
    }
}
