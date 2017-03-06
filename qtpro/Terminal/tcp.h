#ifndef TCP_H_
#define TCP_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/route.h>
#include <dirent.h>
#include "listbuf.h"

//#include <netinet/ether.h>

#define  SERVERPORT  5555
#define  READTIMEOUT (60*15)

typedef struct DataBuf
{
    int s_Size;
    char s_Buf[256];
}data;


class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    int InitTCP(int port);
    int Accept();
    int WriteTCP(const void *data, int size);
    int ReadTCP(void *data,int size);
    char *GetClientIP() const ;
    int TcpReadThread();
    int TcpWriteThread();
    int Connect(char const *ip,int port);
public:
    ListBuf *m_pRecvBuf;
    ListBuf *m_pSendBuf;
private:
    int m_iSocket;
    char m_cInitFlag;
    int m_iPort;
    struct sockaddr_in m_SockAddr;
    struct sockaddr m_ClientSocket;
    int m_iClientSocket;
    pthread_t m_ReadPid;
    pthread_t m_SendPid;
    pthread_mutex_t  m_Locak;
    int m_iSockOK;
private:
    int CreateSocket();
    int SetSocket();
    int Bind();
    int Listen();
    int InitBuf();
};

class TcpClient
{
private:
    int m_iPort;
    char m_strIP[20];
    int m_iSocket;
    struct addrinfo *m_addr;
    struct addrinfo *m_result;
    struct addrinfo m_hints;
    char m_cInitFlag;

private:
    int CreateSocket(const char *IP,const char *Port);

public:
    TcpClient();
    ~TcpClient();
    int Connect();
    int ReadTCP(void *data, int size);
    int WriteTCP(const void *data, int size);
};
#endif // TCP_H
