#include "stdio.h"
#include "stdarg.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define  UINT32 unsigned int
#define  UINT16 unsigned short
#define  UINT8   unsigned char
#define  LOG_FILE_PATH "/home/orion/test"
#define  LOG_FILE_ABSOLUTE_PATH "/home/orion/test/log.log"

#ifdef DEBUG
#define DPRINTF LOG("[%s:%d]", __FILE__, __LINE__);LOG          
#else
#define DPRINTF 
#endif

typedef  FILE* HANDLE;
typedef struct
{
    HANDLE hLOG;
    UINT16 fsize;
    UINT16 status;
} FILEHAND_T;
 
FILEHAND_T gFileHanle;
UINT32 INITLOG(FILEHAND_T *pHandle, UINT8 pLog[])
{
    UINT8 LOGPATH[96]  = {0};
    UINT16 len_logDirectory;
    UINT16 len_logName;
    //TODO:LOG文件初始化
    if( access(LOG_FILE_PATH, R_OK) != -1)//路径存在
    {
        len_logDirectory = strlen(LOG_FILE_PATH);
        len_logName      = strlen(pLog);
        memcpy(LOGPATH, LOG_FILE_PATH, len_logDirectory);
        LOGPATH[len_logDirectory] = '/';
        memcpy(LOGPATH + len_logDirectory + 1,  pLog, len_logName);
        memcpy(LOGPATH + len_logDirectory + 1 + len_logName, ".log", 4);
        pHandle->hLOG = fopen(LOGPATH, "a+");
    }
    else
    {
#ifdef LOG_FILE_PATH
#ifdef LOG_FILE_ABSOLUTE_PATH
        mkdir(LOG_FILE_PATH,S_IRWXU);
        pHandle->hLOG = fopen(LOG_FILE_ABSOLUTE_PATH, "a+");
#else
        pHandle->hLOG = fopen("\\debug.log", "a+");
#endif
#else
        pHandle->hLOG = fopen("\\debug.log", "a+");
#endif
    }
    if (NULL == pHandle->hLOG)
    {
        return 1;
    }
    return 0;
}
 
void LOG(const char *log, ...)
{
    va_list args;
    time_t t = time(0);
    char local_time[64];
    va_start(args,log);
    strftime(local_time, sizeof(local_time), "%Y-%m-%d %X",localtime(&t));
    fprintf( gFileHanle.hLOG, "[%s] ", local_time);
    vfprintf(gFileHanle.hLOG, log, args);
    fprintf( gFileHanle.hLOG, "\r\n");
    va_end(args);
}
 
int main(int argc,char **argv)
{
    INITLOG(&gFileHanle,"hello.txt");
    DPRINTF("hello,world!");
    DPRINTF("hellohellohello world! %s", "good night!");
    return 0;
}

