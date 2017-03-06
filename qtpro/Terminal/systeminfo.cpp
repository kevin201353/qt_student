#include "systeminfo.h"

SystemInfo::SystemInfo()
{

}
int SystemInfo::CoreNum()
{
    char TempBuf[1024];
    int iNum = -1;
    memset(TempBuf,0,1024);
    system("cat /proc/cpuinfo| grep \"processor\"| wc -l >> temp");
    FILE *pf = fopen("temp","r");
    if(pf == NULL)
    {
        printf("Fopen Error");
    }
    else
    {
        fread(TempBuf,1024,1,pf);
    }
    fclose(pf);
    system("rm -rf temp");
    if(strlen(TempBuf))
        iNum = atoi(TempBuf);
    return iNum;
}

int SystemInfo::Memory()
{
    char TempBuf[1024];
    int iNum = -1;
    memset(TempBuf,0,1024);
    system("cat /proc/meminfo | grep MemTotal >> temp");
    FILE *pf = fopen("temp","r");
    if(pf == NULL)
    {
        printf("Fopen Error");
    }
    else
    {
        fread(TempBuf,1024,1,pf);
        printf("\n%s\n",TempBuf);
        char *p = strstr(TempBuf,"MemTotal:");
        if(p == NULL)
        {

        }
        else
        {
            p += 9;
            while(*p == ' ')
                p++;
            char NUm[10];
            memset(NUm,0,10);
            sscanf(p,"%s",NUm);
            if(strlen(NUm))
            {
                iNum = atoi(NUm);
            }
        }
    }
    fclose(pf);
    system("rm -rf temp");
    return iNum;
}
char *SystemInfo::Resol(char *param)
{
    int fd;
    struct fb_var_screeninfo screen_info;
    fd = open("/dev/fb0",O_RDWR);
    ioctl(fd,FBIOGET_VSCREENINFO,&screen_info);
    printf("%d*%d\n",screen_info.xres,screen_info.yres);
    close(fd);
    sprintf(param,"%d*%d",screen_info.xres,screen_info.yres);
    return param;
}
