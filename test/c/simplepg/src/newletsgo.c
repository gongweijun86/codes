#include	"../include/newletsgo.h"
#include 	"../include/pidlist.h"

#include 	<signal.h>

extern PIDList pidlist;

bool error = false;
void sig_usr(int signo){
	printf("segment fault!\n");
}


int main(int argc, char *argv[]) {

	if(signal(SIGSEGV,sig_usr) == SIG_ERR){
		printf("sig_err!");
	}

	init_log(Log.logfile, "DEBUG");
	init_pidlist(&pidlist);

	FILE *f;
	char *filepath = "/home/orion/Development/file/resource_for_test/ts/20100709_SVN_MUX_A.ts";

	if (!(f = fopen(filepath, "rb"))) {
		printf("Failure to open stream!");
		exit(1);
	}
	if(!check_file(f)){
		printf("Could not find start of Header - check stream!");
		exit(1);
	}
	//static char buf[BUF_SIZE];
	//setbuf(f,buf);
	int packet = 0;
	int total = get_total_packet(f);
	printf("totalpackets:%d\n",total);
	while(!feof(f) && !error){
		handle_packet(packet++,f);
		printf("\n=======%d:%d========\n",total,packet);
	}

	fclose(f);
	return 0;
}
