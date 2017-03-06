#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
//#include <error.h> 
#include <errno.h> 

struct jpegheader //32 bytes
{
	char magic[4];
	unsigned short width;
	unsigned short height;
	unsigned int serial;
	unsigned int time_stamp;
	unsigned int size;
	unsigned int reserved[3];
}__attribute__((packed)); 

#define SOCKET_ERROR	-1
#define SOCKET_OK	1
#define JPEG_BUF_LEN	0x100000

void set_keepalive(int fd, int keep_alive, int keep_idle, int keep_interval, int keep_count)
{
	int opt = 1;
	if(keep_alive){
		if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE,(void*)&keep_alive, sizeof(keep_alive)) == -1){
			fprintf(stderr, "setsockopt SOL_SOCKET::SO_KEEPALIVE failed, %s\n",strerror(errno));
		}
		if(setsockopt(fd, SOL_TCP, TCP_KEEPIDLE,(void *)&keep_idle,sizeof(keep_idle)) == -1){
			fprintf(stderr,"setsockopt SOL_TCP::TCP_KEEPIDLE failed, %s\n", strerror(errno));
		}
		if(setsockopt(fd,SOL_TCP,TCP_KEEPINTVL,(void *)&keep_interval, sizeof(keep_interval)) == -1){
			fprintf(stderr,"setsockopt SOL_tcp::TCP_KEEPINTVL failed, %s\n", strerror(errno));
		}
		if(setsockopt(fd,SOL_TCP,TCP_KEEPCNT,(void *)&keep_count,sizeof(keep_count)) == -1){
			fprintf(stderr, "setsockopt SOL_TCP::TCP_KEEPCNT failed, %s\n", strerror(errno));
		}
	}
}

static void dump_data(uint32_t serial, uint8_t* data, int data_size)
{
	char file_str[200];
	DIR *dir=NULL;
	
	dir = opendir("/tmp/jpeg_dump");
	if(NULL == dir){
		printf("mkdir -p /tmp/jpeg_dump\n");
		system("mkdir -p /tmp/jpeg_dump");
	}else{
		closedir(dir);
	}
	sprintf(file_str, "/tmp/jpeg_dump/%d.jpg", serial);
	FILE *f = fopen(file_str, "wb");
	if (!f) {
		printf("open file error \n");
		return;
	}
	fwrite(data, 1, data_size, f);
	fclose(f);
}


int recv_data(int sock_fd, void *buffer, int len)
{

	int l, ret;
	void *d;
	static int err_count=0;

	d = buffer;
	l = len;

	while(l){
		ret = read(sock_fd, d, l);
		#if 0	
		if(ret ==-1 && errno==EAGAIN){
			printf("recv timeout\n");
		}
		#endif
		if( ret <= 0 ){
			perror("socket read");
			return SOCKET_ERROR;
		}
		l -= ret;
		d += ret;
	}
	return SOCKET_OK;
}

int data_process(int sockfd)
{
	uint8_t data_buf[JPEG_BUF_LEN];
	int i;
	char* magic = "SCDM";

	struct jpegheader header;
	memset(&header, 0, sizeof(struct jpegheader));
	if(SOCKET_ERROR == recv_data(sockfd, &header, sizeof(header))){
		return SOCKET_ERROR;
	}
	for( i=0; i<4; i++ ){
		if(header.magic[i] != *(magic+i)){
			printf("header.magic[%d]=%d\n", i, header.magic[i]);fflush(stdout);
			return SOCKET_OK;	
		}
	}

	for( i=0; i<4; i++ ){
		printf("%c\n", header.magic[i]);fflush(stdout);
	}
	printf("header.width=%d\n", header.width);fflush(stdout);
	printf("header.height=%d\n", header.height);fflush(stdout);
	printf("header.serial=%d\n", header.serial);fflush(stdout);
	printf("header.size=%d\n", header.size);fflush(stdout);


	memset(data_buf, 0, JPEG_BUF_LEN);
	if(SOCKET_ERROR == recv_data(sockfd, data_buf, header.size)){
		return SOCKET_ERROR;
	}
	printf("save jpeg data -> /tmp/jpeg_dump/%d.jpg\n", header.serial);
	dump_data(header.serial, data_buf, header.size);
	return SOCKET_OK;

}

static void handle_connection_client(int sockfd)
{
	fd_set  rset;
	struct timeval timeout={0,0};
	
	FD_ZERO(&rset);
    	for (; ;){
		//添加连接描述符
		FD_SET(sockfd,&rset);
		//printf("--select----");fflush(stdout);
		//进行轮询
		select(sockfd+1,&rset,NULL,NULL,NULL);
		//select(sockfd+1,&rset,NULL,NULL,&timeout);
		//printf("out----");fflush(stdout);
		//测试连接套接字是否准备好
		if (FD_ISSET(sockfd, &rset)){
			if( SOCKET_ERROR ==  data_process(sockfd)){
				close(sockfd);
				printf("socket error, reconnect\n");
				fflush(stdout);
				return;
			}
		}
      
    	}
}

int main(int argc, char *argv[])   
{   
	struct jpegheader jh;
	struct sockaddr_in servaddr;   
	int portnumber;
	int sockfd;
	
	if (argc != 3) {   
    		fprintf(stderr, "Usage:%s hostname portnumber \n\a", argv[0]);   
		exit(1);   
	}   

	if (inet_aton(argv[1], &servaddr.sin_addr) == 0) {   
    		fprintf(stderr, "the hostip is not right!");   
		exit(1);   
	}   
        
	if ((portnumber = atoi(argv[2])) < 0) {   
	    	fprintf(stderr, "Usage:%s hostname portnumber\n\a", argv[0]);   
		exit(1);   
	}   


	
	int ret;
		
	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portnumber);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret == -1){
		fprintf(stderr, "connect to %s:%s", argv[1], argv[2]);
		perror(" ");
		close(sockfd);
		return 0;
	}
	
	fprintf(stderr, "connect to %s:%s ok\n", argv[1], argv[2]);
	set_keepalive(sockfd, 1, 1, 1, 3);
	handle_connection_client(sockfd);		
}
