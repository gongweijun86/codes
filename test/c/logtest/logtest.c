
#include	<stdio.h>

#include	<stdlib.h>

#include	<time.h>

#include	<stdarg.h>

#include	<unistd.h>

#include	<sys/types.h>

#include	<sys/stat.h>


#define	LOG_FILE_PATH	    "/home/orion/codes/c/etable/log/"			/*  */

#define	LOG_FILE_ABSOLUTE_PATH	    "/home/orion/codes/c/etable/log/log.log"			/*  */


void Log(const char* log, ...)
{
	va_list args;
	time_t t = time(0);
	char local_time[64];
	FILE *file = NULL;
#ifdef LOG_FILE_PATH 
#ifdef LOG_FILE_ABSOLUTE_PATH
	if(access(LOG_FILE_PATH,R_OK|W_OK) != -1)
	{
		file = fopen(LOG_FILE_ABSOLUTE_PATH, "a+");
	}
	else
	{
		mkdir(LOG_FILE_PATH, S_IRWXU);
		file = fopen(LOG_FILE_ABSOLUTE_PATH, "a+");
	}
#else
	file = fopen("LOG_FILE_ABSOLUTE_PATH","a+");
#endif
#else	
	file = fopen("LOG_FILE_ABSOLUTE_PATH","a+");
#endif
    {
	    va_start(args,log);
	    strftime(local_time, sizeof(local_time), "%Y-%m-%d %X",localtime(&t));
	    fprintf(file, "[%s]", local_time);
	    vfprintf(file, log, args);
	    fprintf(file,"\r\n");
	    va_end(args);
	    fclose(file);
	    file = NULL;
    }
}
int
main(int argc, char **argv)
{
	Log("hello");
	Log("hello %s","good night!");
	return 0;
}
