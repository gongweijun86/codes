/*
 * pmt.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/pmt.h"

byte*
parse_PMT(byte* byteptr, int this_section_length,PMT* pmt)
{
	byte* b = byteptr;

	pmt->table_id = PMT_TABLE_ID(b);
	pmt->section_syntax_indicator = PMT_SECTION_SYNX(b);
	pmt->zero = PMT_ZERO(b);
	pmt->reserved1 = PMT_RESERVED1(b);
	pmt->section_length = PMT_SECTION_LENGTH(b);
	pmt->program_number = PMT_PROGRAM_NUMBER(b);
	pmt->reserved2 = PMT_RESERVED2(b);
	pmt->version_number = PMT_VERSION(b);
	pmt->current_next_indicator = PMT_CURRENT_NEXT_IND(b);
	pmt->section_number = PMT_SECTION_NUMBER(b);
	pmt->last_section_number = PMT_LAST_SECTION_NUMBER(b);
	pmt->reserved3 = PMT_RESERVED3(b);
	pmt->PCR_PID = PMT_PCR_PID(b);
	pmt->reserved4 = PMT_RESERVED4(b);
	pmt->program_info_length = PMT_PROGRAM_INFO_LENGTH(b);


	return b;
}
