/*
 * sdt.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include	"../include/sdt.h"


int decode_sdt_service(byte* byteptr, int this_section_length, SDT_SERVICE* sdt_service){
	byte* b = byteptr;

	sdt_service->service_id = SDT_SERVICE_ID(b);
	sdt_service->reserved_future_use = SDT_SERVICE_RESERVED_USD(b);
	sdt_service->EIT_schedule_flag = SDT_SERVICE_EIT_SCHEDULE_FLAG(b);
	sdt_service->EIT_present_following_flag = SDT_SERVICE_EIT_PRESENT_FOLLOWING_FLAG(b);
	sdt_service->running_status = SDT_SERVICE_RUN_STATUS(b);
	sdt_service->free_CA_mode = SDT_SERVICE_FREE_CA_MODE(b);
	sdt_service->descriptors_loop_length = SDT_SERVICE_LOOP_LENGTH(b);

	printf("sdt_service->service_id:%d\t",sdt_service->service_id);
	printf("sdt_service->EIT_schedule_flag:%d\t",sdt_service->EIT_schedule_flag);
	printf("sdt_service->EIT_present_following_flag:%d\t",sdt_service->EIT_present_following_flag);
	printf("sdt_service->running_status:%d\t",sdt_service->running_status);
	printf("sdt_service->descriptors_loop_length:%d\n",sdt_service->descriptors_loop_length);

	int len = sdt_service->descriptors_loop_length;
	byte* serv_start = &b[5];
	while(len > 0){
		int desc_len;
		desc_len = decode_desc(serv_start, len);// here we can handle several descriptor,but we only handle one type.
		serv_start += desc_len;
		len -= desc_len;
	}

	return (sdt_service->descriptors_loop_length + 5);
}

byte*
parse_SDT(byte* byteptr, int this_section_length, SDT* sdt)
{
	byte* b = byteptr;

	sdt->table_id = SDT_TABLE_ID(b);
	sdt->section_syntax_indicator = SDT_SECTION_SYNX(b);
	sdt->reserved_future_use1 = SDT_RESERVED_FUTURE_USD1(b);
	sdt->reserved1 = SDT_RESERVED1(b);
	sdt->section_length = SDT_SECTION_LENGTH(b);
	sdt->transport_stream_id = SDT_TS_ID(b);
	sdt->reserved2 = SDT_RESERVED2(b);
	sdt->version_number = SDT_VERSION_NUM(b);
	sdt->current_next_indicator = SDT_CURRENT_NEXT_IND(b);
	sdt->section_number = SDT_SECTION_NUM(b);
	sdt->last_section_number = SDT_LST_SECTION_NUM(b);
	sdt->original_network_id = SDT_ORIGINAL_NETWORK_ID(b);
	sdt->reserved_future_use2 = SDT_RESERVED_FUTURE_USD2(b);


	printf("sdt->table_id:%d\t",sdt->table_id);
	printf("sdt->section_length:%d\t",sdt->section_length);
	printf("sdt->transport_stream_id:%d\t",sdt->transport_stream_id);
	printf("sdt->section_number:%d\t",sdt->section_number);
	printf("sdt->original_network_id:%d\n",sdt->original_network_id);

	int len = sdt->section_length;
	byte* serv_start = &b[11];
	while(len > 12){
		SDT_SERVICE sdt_service;
		int serv_len = decode_sdt_service(serv_start, len-12, &sdt_service);
		serv_start += serv_len;
		len -= serv_len;
	}

	b += (sdt->section_length + 3);
	return b;
}
