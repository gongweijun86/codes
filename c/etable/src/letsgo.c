/*
 * letsgo.c
 *
 *  Created on: 2011-4-7
 *      Author: orion
 */

#include "../include/structure.h"

#include "stdint.h"	
void print_pat(pat *tpat){
	int i;
	printf("PAT-TABLE\n");
	for(i =0;i < tpat->numbers_of_pat_item;i++){
		printf("序号：%d\n",i + 1);
		printf("pmt_pid:%x\n",tpat->pat_items[i].pmt_pid);
		printf("programe_number:%x\n",tpat->pat_items[i].programe_number);
		printf("crc:%d",tpat->pat_items[i].crc);
	}
}
void print_pmt(pmt *tpmt){
	int i;
	printf("PMT-TABLE\n");
	printf("pmt_pid:%x\n",tpmt->pmt_pid);
	for(i = 0;i < tpmt->numbers_of_pmt_item;i++){
		printf("序号：%d\n",i + 1);
		printf("stream_type:%x\n",tpmt->pmt_items[i].steam_type);
		printf("stream_pid:%x\n",tpmt->pmt_items[i].stream_pid);
		printf("stream_nubmer:%x\n",tpmt->pmt_items[i].stream_number);
		printf("crc:%d",tpmt->pmt_items[i].crc);
		printf("plen:%d",tpmt->pmt_items[i].p_info_len);
		printf("pseclen:%d",tpmt->pmt_items[i].pmt_sec_len);
		printf("eslen:%d",tpmt->pmt_items[i].es_info_len);
	}

}

int main(int argc, char **argv) {
	int stream_file;

	if ((stream_file = open(argv[1], O_RDONLY)) == -1) {
		printf("error when open the file %s\n", argv[1]);
		exit(-1);
	}

	int current_pos;

	BYTE *p_buffer_for_stream = (BYTE *) malloc(DATA_BUF_LENGTH);
	BYTE *p_buffer_for_ts = (BYTE *) malloc(TS_LENGTH);

	pat tpat;
	pmt tpmt;

	while (put_in_new_stream(stream_file, p_buffer_for_stream, DATA_BUF_LENGTH, &current_pos) > 0) {
		while (read_next_ts_from_stream(p_buffer_for_ts, p_buffer_for_stream, DATA_BUF_LENGTH, &current_pos) == TRUE) {
			if (is_pat(p_buffer_for_ts) == TRUE) {
				process_pat(p_buffer_for_ts,&tpat);
			}
			if (is_pmt(p_buffer_for_ts,&tpat) == TRUE) {
				process_pmt(p_buffer_for_ts,&tpmt);
			}
		}
	}
	print_pat(&tpat);
	print_pmt(&tpmt);
	
	
	return 0;
}
