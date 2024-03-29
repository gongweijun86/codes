/*
 * desc_network_name.h
 *
 *  Created on: Jun 23, 2011
 *      Author: orion
 */

#ifndef _DESC_NETWORK_NAME_H_
#define _DESC_NETWORK_NAME_H_

#include "ntypes.h"

struct _network_name_desc{
		uint8_t descriptor_tag;
		uint8_t descriptor_length;
		char* network_name;
};

typedef struct _network_name_desc NetworkNameDesc;

#define NETWORKNAME_DESC_TAG(b)			(b[0])
#define NETWORKNAME_DESC_LENGTH(b)		(b[1])

int decode_network_desc(byte* byteptr, int this_section_length,NetworkNameDesc* desc_network_name);

#endif /* _DESC_NETWORK_NAME_H_ */
