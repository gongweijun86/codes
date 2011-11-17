/*
 * desc_network_name.c
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */
#include "../include/desc_network_name.h"

int decode_network_desc(byte* byteptr, int this_section_length,NetworkNameDesc* desc_network_name){
	byte* b = byteptr;
	int l = this_section_length;

	desc_network_name->descriptor_tag = NETWORKNAME_DESC_TAG(b);
	desc_network_name->descriptor_length = NETWORKNAME_DESC_LENGTH(b);

	desc_network_name->network_name = (char*)calloc(desc_network_name->descriptor_length + 1, sizeof(char));
	strncpy(desc_network_name->network_name, (char*)&b[2], desc_network_name->descriptor_length);

	printf("descriptor_tag:%d:\t",desc_network_name->descriptor_tag);
	printf("descriptor_length:%d\t",desc_network_name->descriptor_length);
	printf("network_name:%s\n",desc_network_name->network_name);

	return (desc_network_name->descriptor_length + 2);
}
