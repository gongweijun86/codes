/*
 * nit.c
 *
 *  Created on: Jun 21, 2011
 *      Author: orion
 */

#include "../include/nit.h"


int decode_transport_stream_loop(byte* byteptr, int this_section_length,TSL* tsl) {
	byte* b = byteptr;
//	int l = this_section_length;

	tsl->transport_stream_id = NIT_TSL_TSID(b);
	tsl->original_network_id = NIT_TSL_ORIGINAL_NETWORK_ID(b);
	tsl->reserved_future_use = NIT_TSL_RESERVED_FUTURE_USD(b);
	tsl->transport_descriptors_length = NIT_TSL_TRANS_DESC_LENGTH(b);

	printf("transport_stream_id:%d\t", tsl->transport_stream_id);
	printf("original_network_id:%d\t", tsl->original_network_id);
	printf("reserved_future_use:%d\t", tsl->reserved_future_use);
	printf("transport_descriptors_length:%d\n",	tsl->transport_descriptors_length);

	int len = tsl->transport_descriptors_length;
	byte* desc_start = &b[6];
	while (len > 0) {
		int desc_len;
		desc_len = decode_desc(desc_start, len);// here we can handle several descriptor,but we only handle one type.
		desc_start += desc_len;
		len -= desc_len;
	}

	return (tsl->transport_descriptors_length + 6);
}

byte* parse_NIT(byte* byteptr, int this_section_length, NIT* nit) {
	byte* b = byteptr;
//	int l = this_section_length;

	nit->table_id = NIT_TABLE_ID(b);
	nit->section_syntax_indicator = NIT_SECTION_SYNX(b);
	nit->reserved_future_use1 = NIT_RESERVED_FUTURE_USD1(b);
	nit->reserved1 = NIT_RESERVED1(b);
	nit->section_length = NIT_SECTION_LENGTH(b);
	nit->network_id = NIT_NETWORK_ID(b);
	nit->reserved2 = NIT_RESERVED2(b);
	nit->version_number = NIT_VERSION_NUM(b);
	nit->current_next_indicator = NIT_CURRENT_NEXT_IND(b);
	nit->section_number = NIT_SECTION_NUM(b);
	nit->last_section_number = NIT_LST_SECTION_NUM(b);
	nit->reserved_future_use2 = NIT_RESERVED_FUTURE_USD2(b);
	nit->network_descriptor_length = NIT_NETWORK_DESC_LENGTH(b);
	nit->reserved_future_use3 = NIT_RESERVED_FUTURE_USD3(b);
	nit->transport_stream_loop_length = NIT_TS_LOOP_LENGTH(b);
	nit->CRC = NIT_CRC(b);

	printf("nit->table_id:%d\t",nit->table_id);
	printf("nit->section_length:%d\t",nit->section_length);
	printf("nit->version_number:%d\t",nit->version_number);
	printf("nit->section_number:%d\t",nit->section_number);
	printf("nit->network_descriptor_length:%d\t",nit->network_descriptor_length);
	printf("nit->reserved_future_use3:%d\t",nit->reserved_future_use3);
	printf("nit->transport_stream_loop_length:%d\t",nit->transport_stream_loop_length);
	printf("nit->CRC:%d\n",nit->CRC);

	int len = nit->network_descriptor_length;
	byte* desc_start = &b[10];
	while (len > 0) {
		int desc_len;
		desc_len = decode_desc(desc_start, len);// here we can handle several descriptor,but we only handle one type.
		desc_start += desc_len;
		len -= desc_len;
	}

	len = nit->network_descriptor_length;
	int loop_len = nit->transport_stream_loop_length;
	byte* tsl_start = &b[12 + len];
	while (loop_len > 0) {
		TSL tsl;
		int tslen;
		tslen = decode_transport_stream_loop(tsl_start, loop_len, &tsl);
		tsl_start += tslen;
		loop_len -= tslen;
	}

	b += (nit->section_length + 3);//set b to the end ot the section

	return (b);
}
