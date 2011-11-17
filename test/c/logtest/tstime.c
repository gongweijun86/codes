#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include <stdint.h>
int
main ( int argc, char *argv[] )
{
	time_t t= time(NULL);
	char local_time[64];
	strftime(local_time, sizeof(local_time), "%Y-%m-%d %X",localtime(&t));
	printf ( "%s\n",local_time );
	return EXIT_SUCCESS;

//     time_t result = time(NULL);
//      result = time(NULL);
//      printf("%s%ju secs since the Epoch\n", asctime(localtime(&result)), (uintmax_t)result);
//      printf("%ju secs since the Epoch\n",  (uintmax_t)result);
//      return 0;
//char   str_time[32];
//char   str_date[32];
//_tzset();
//_strtime(str_time);
//_strdate(str_date);
//printf("%s\n",str_time);
//printf("%s\n",str_date);

}				/* ----------  end of function main  ---------- */



