/*
 * tsph.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/tsph.h"


extern PIDList pidlist;

byte* parse_TS(byte *byteptr,int this_section_length, TSPH *tsph) {
	byte *b = byteptr;
	int l = this_section_length;

	tsph->sync = TS_SYNC_BYTE(b);
	tsph->transport_error_indicator = TS_ERROR(b);
	tsph->payload_unit_start_indicator = TS_PAYLOAD_START(b);
	tsph->transport_priority = TS_PRIORITY(b);
	tsph->PID = TS_PID(b);
	tsph->transport_scrambling = TS_SCRAMBLING(b);
	tsph->adaptation_field_control = TS_ADAPT_CTL(b);
	tsph->continuity_counter = TS_CONT_COUNT(b);

	printf("tsph->sync:%d\t",tsph->sync);
	printf("tsph->transport_error_indicator:%d\t",tsph->transport_error_indicator);
	printf("tsph->payload_unit_start_indicator:%d\t",tsph->payload_unit_start_indicator);
	printf("tsph->transport_priority:%d\t",tsph->transport_priority);
	printf("tsph->PID:%d\t",tsph->PID);
	printf("tsph->continuity_counter:%d\n",tsph->continuity_counter);

	b += 4;
	l -= 4;

	return (b);
}
