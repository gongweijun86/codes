/*
 * desc_service.c
 *
 *  Created on: Jun 24, 2011
 *      Author: orion
 */

#include "../include/desc_service.h"

int decode_service_desc(byte* byteptr, int this_section_length,ServiceDesc* desc_service){
	byte* b = byteptr;
	int l = this_section_length;

	desc_service->descriptor_tag = SERV_DESC_TAG(b);
	desc_service->descriptor_length = SERV_DESC_LENGTH(b);
	desc_service->service_type = SERV_DESC_SERV_TYPE(b);
	desc_service->service_provider_name_length = SERV_DESC_SERV_PRO_NAME_LENGTH(b);
	desc_service->provider_name = (char *)calloc(desc_service->service_provider_name_length + 1,sizeof(char));
	strncpy(desc_service->provider_name,(char *)&b[4],desc_service->service_provider_name_length);
	desc_service->service_name_length = SERV_DESC_SERV_NAME_LENGTH(b);
	desc_service->service_name = (char*)calloc(desc_service->service_name_length + 1, sizeof(char));
	strncpy(desc_service->service_name, (char*)&b[desc_service->service_provider_name_length + 5], desc_service->service_name_length);

	printf("desc_service->descriptor_tag:%d\t",desc_service->descriptor_tag);
	printf("desc_service->descriptor_length:%d\t",desc_service->descriptor_length);
	printf("desc_service->service_type:%d\t",desc_service->service_type);
	printf("desc_service->service_provider_name_length:%d\t",desc_service->service_provider_name_length);
	printf("desc_service->provider_name:%s\t",desc_service->provider_name);
	printf("desc_service->service_name_length:%d\t",desc_service->service_name_length);
	printf("desc_service->service_name:%s\n",desc_service->service_name);

	return (desc_service->descriptor_length + 2);

}
