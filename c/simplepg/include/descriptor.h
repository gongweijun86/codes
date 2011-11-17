/*
 * descriptor.h
 *
 *  Created on: Jun 23, 2011
 *      Author: orion
 */

#ifndef _DESCRIPTOR_H_
#define _DESCRIPTOR_H_

#include "desc_network_name.h"
#include "desc_service_list.h"
#include "desc_service.h"
#include "desc_short_event.h"


int decode_desc(byte* byteptr, int this_section_length);

#endif /* _DESCRIPTOR_H_ */
