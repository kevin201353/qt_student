#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<linux/fb.h>

class SystemInfo
{
public:
    SystemInfo();
    int CoreNum();
    int Memory();
    char *Resol(char *param);
};

#endif // SYSTEMINFO_H
