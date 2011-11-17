/*
 * pat.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/pat.h"

///////////////////////////
extern PIDList pidlist;///
//////////////////////////
byte* parse_PAT_program(byte* byteptr, int this_section_length) {
	byte* b = byteptr;
	int l = this_section_length;

	for(;b < b + l;){
		int pnum = PAT_PROGRAM_NUMBER(b);
		int re = PAT_PROGRAM_RESERVED(b);
		int pid = PAT_PMT_PID(b);
		printf("program number:%d\t", pnum);
		printf("reserved:%d\t",re);
		printf("pid:%x\n",pid);

		set_pmt(pid,pnum,&pidlist);
		b += 4;// set b to the next program,but after the last program,b will point to the end of the the section
		l -= 4;
	}

	b -= 4; // so here we reset it
	l += 4; // so does l

	return (b);
}

byte* parse_PAT(byte* byteptr, int this_section_length, PAT* pat) {
	byte* b = byteptr;

	pat->table_id = PAT_TABLE_ID(b);
	pat->section_syntax_indicator = PAT_SECTION_SYNX(b);
	pat->zero = PAT_ZERO(b);
	pat->reserved1 = PAT_RESERVED1(b);
	pat->section_length = PAT_SECTION_LENGTH(b);
	pat->transport_stream_id = PAT_TRANSPORT_STREAM_ID(b);
	pat->reserved2 = PAT_RESERVED2(b);
	pat->version_number = PAT_VERSION(b);
	pat->current_next_indicator = PAT_CURRENT_NEXT_IND(b);
	pat->section_number = PAT_SECTION_NUMBER(b);
	pat->last_section_number = PAT_LAST_SESSION_NUMBER(b);
	pat->CRC_32 = PAT_CRC(b);

	if (pat->section_length > 9) // 5 bytes past section_length for header, 4 bytes for CRC32
	{
		parse_PAT_program(b + 8, pat->section_length - 9);
	}

	b += pat->section_length + 3; //set b to the end of the section

	return b;
}
