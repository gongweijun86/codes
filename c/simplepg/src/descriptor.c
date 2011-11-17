/*
 * descriptor.c
 *
 *  Created on: Jun 23, 2011
 *      Author: orion
 */

#include "../include/descriptor.h"

int decode_desc(byte* byteptr, int this_section_length) {
	byte* b = byteptr;
	int l = this_section_length;
	int desc_len;
	switch (b[0]) {
	case 0x40: // network_name_descriptor
		//maybe NetworkNameDesc will be globle var
	{
		NetworkNameDesc desc_network_name;
		desc_len = decode_network_desc(b, this_section_length,
				&desc_network_name);
	}
		break;
	case 0x41: {
		ServiceListDesc desc_service_list;
		desc_len = decode_servicelist_desc(b, this_section_length,
				&desc_service_list);
	}
		break;
	case 0x48: {
		ServiceDesc desc_service;
		desc_len = decode_service_desc(b, this_section_length, &desc_service);
	}
		break;
	case 0x4d: {
		ShortEventDesc desc_short_evt;
		desc_len = decode_short_evt_desc(b, this_section_length, &desc_short_evt);
	}
		break;
	default:
		desc_len = b[1] + 2 ;
	}

	return desc_len;
}
