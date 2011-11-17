/*
 * =====================================================================================
 *
 *       Filename:  newletsgo.c
 *
 *    Description:  解析Transport Stream，包括：PAT，PMT，NIT，SDT，EIT，CAT，TOT，TDT
 *
 *        Version:  1.0
 *        Created:  2011年06月09日 15时14分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: orion 
 *        Company:  
 *
 * =====================================================================================
 */


#include	"../include/structure.h"


int
main(int argc, char *argv[])
{
	init_log(Log.logfile, "DEBUG");

	int fd;
	if((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf ( "error when open file:%s\n", argv[1] );
		exit(-1);
	}

	int cur_pos;
	BYTE *pbuf_for_stream = (BYTE *)malloc(DATA_BUF_LENGTH);
	BYTE *pbuf_for_ts = (BYTE *)malloc(TS_LENGTH);

	while(put_in_new_stream(fd, pbuf_for_stream, DATA_BUF_LENGTH, &cur_pos) > 0)
	{
		while(read_next_ts_from_stream(pbuf_for_ts, pbuf_for_stream, DATA_BUF_LENGTH, &cur_pos) == TRUE)
		{
			parse_TS(pbuf_for_ts);
		}
	}
}
