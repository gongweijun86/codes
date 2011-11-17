/*
 * eit.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include 	"../include/eit.h"

int decode_eit_desc(byte* byteptr, int this_section_length, EIT_DESC* desc_eit){
	byte* b = byteptr;

	desc_eit->event_id = EIT_DESC_EVENT_ID(b);
	desc_eit->start_date = EIT_DESC_START_DATE(b);
	desc_eit->start_time = EIT_DESC_START_TIME(b);
	desc_eit->duration = EIT_DESC_DURATION(b);
	desc_eit->running_status = EIT_DESC_RUN_STATUS(b);
	desc_eit->free_CA_mode = EIT_DESC_FREE_CA_MODE(b);
	desc_eit->descriptors_loop_length = EIT_DESC_LOOP_LENGTH(b);

	printf("desc_eit->event_id:%d\t",desc_eit->event_id);
	printf("desc_eit->start_date:%d\t",desc_eit->start_date);
	printf("desc_eit->start_time:%d\t",desc_eit->start_time);
	printf("desc_eit->duration:%d\t",desc_eit->duration);
	printf("desc_eit->running_status:%d\t",desc_eit->running_status);
	printf("desc_eit->free_CA_mode:%d\t",desc_eit->free_CA_mode);
	printf("desc_eit->descriptors_loop_length:%d\n",desc_eit->descriptors_loop_length);

	int len = desc_eit->descriptors_loop_length;
	byte* desc_start = &b[12];
	while (len > 0) {
		int desc_len;
		desc_len = decode_desc(desc_start, len);// here we can handle several descriptor,but we only handle one type.
		desc_start += desc_len;
		len -= desc_len;
	}

	return (desc_eit->descriptors_loop_length + 12);
}

byte*
parse_EIT(byte* byteptr, int this_section_length, EIT* eit)
{
	byte* b = byteptr;

	eit->table_id = EIT_TABLE_ID(b);
	eit->section_syntax_indicator = EIT_SECTION_SYNX(b);
	eit->reserved_future_use1 = EIT_RESERVED_FUTURE_USD1(b);
	eit->reserved1 = EIT_RESERVED1(b);
	eit->section_length = EIT_SECTION_LENGTH(b);
	eit->service_id = EIT_SERVICE_ID(b);
	eit->reserved2 = EIT_RESERVED2(b);
	eit->version_number = EIT_VERSION_NUM(b);
	eit->current_next_indicator = EIT_CURRENT_NEXT_IND(b);
	eit->section_number = EIT_SECTION_NUM(b);
	eit->last_section_number = EIT_LST_SECTION_NUM(b);
	eit->transport_stream_id = EIT_TS_ID(b);
	eit->original_network_id = EIT_ORIGINAL_NETWORK_ID(b);
	eit->segment_last_section_number = EIT_SEG_LST_SECTION_NUM(b);
	eit->last_table_id = EIT_LST_TABLE_ID(b);
	eit->CRC_32 = EIT_CRC(b);

	printf("eit->table_id:%d\t",eit->table_id);
	printf("eit->section_length:%d\t",eit->section_length);
	printf("eit->version_number:%d\t",eit->version_number);
	printf("eit->section_number:%d\t",eit->section_number);
	printf("eit->transport_stream_id:%d\t",eit->transport_stream_id);
	printf("eit->original_network_id:%d\t",eit->original_network_id);
	printf("eit->segment_last_section_number:%d\t",eit->segment_last_section_number);
	printf("eit->last_table_id:%d\n",eit->last_table_id);

	int len = eit->section_length;
	byte* evt_start = &b[14];
	while (len > 15) {
		EIT_DESC desc_eit;
		int evtlen;
		evtlen = decode_eit_desc(evt_start, evtlen, &desc_eit);
		evt_start += evtlen;
		len -= evtlen;
	}

	b += (eit->section_length + 3);

	return b;
}
