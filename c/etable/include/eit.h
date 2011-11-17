/*
 * =====================================================================================
 *
 *       Filename:  eit.h
 *
 *    Description:  Event Information Table definition
 *
 *        Version:  1.0
 *        Created:  2011年06月03日 14时35分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orion
 *        Company:  
 *
 * =====================================================================================
 */

#include "../include/structure.h"


#ifndef  _EIT_H_
#define  _EIT_H_

struct _eit_short_event_desc{
	uint8_t desc_tag;
	uint8_t desc_len;
	uint32_t language;
	uint8_t event_name_len;
	char* event_name;
	uint8_t text_len;
	char* text;
};

typedef struct _eit_short_event_desc ESED;


struct _eit_desc {
	uint16_t event_id;
	uint64_t start_time;
	uint32_t duration;
	uint8_t running_status;
	uint8_t free_CA_mode;
	uint16_t descriptors_loop_length;
	void* descriptor;
};				/* ----------  end of struct _eit_desc  ---------- */

typedef struct _eit_desc EIT_DESC;

struct _event_information_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use1;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t service_id;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint16_t transport_stream_id;
	uint16_t original_network_id;
	uint8_t segment_last_section_number;
	uint8_t last_table_id;
	EIT_DESC* description;
	uint32_t CRC_32;
};				/* ----------  end of struct _event_information_table  ---------- */

typedef struct _event_information_table EIT;


#define	EIT_TABLE_ID(b)			(b[1])			/*  */

#define	EIT_SECTION_SYNX(b)		((b[2] & 0x80) >> 7)			/*  */

#define	EIT_RESERVED_FUTURE_USD1(b)	((b[2] & 0x40) >> 6)			/*  */

#define	EIT_RESERVED1(b)		((b[2] & 0x30) >> 4)			/*  */

#define	EIT_SECTION_LENGTH(b)		(((b[2] & 0x0f) << 8) | b[3])			/*  */

#define	EIT_SERVICE_ID(b)		((b[4] << 8) | b[5])			/*  */

#define	EIT_RESERVED2(b)		((b[6] & 0xc0) >> 6)	/*  */

#define	EIT_VERSION_NUM(b)		((b[6] & 0x3e) >> 1)			/*  */

#define	EIT_CURRENT_NEXT_IND(b)			(b[6] & 0x01)			/*  */

#define	EIT_SECTION_NUM(b)		(b[7])			/*  */

#define	EIT_LST_SECTION_NUM(b)		(b[8])			/*  */

#define	EIT_TS_ID(b)			((b[9] << 8) | b[10])			/*  */

#define	EIT_ORIGINAL_NETWORK_ID(b)	((b[11] << 8) | b[12])			/*  */

#define	EIT_SEG_LST_SECTION_NUM(b)	(b[13])			/*  */

#define	EIT_LST_TABLE_ID(b)		(b[14])			/*  */

#define	EIT_DESC_EVENT_ID(b)		((b[15] << 8) | b[16])			/*  */

#define	EIT_DESC_START_TIME(b)		((b[17] << 32) | (b[18] << 24) | (b[19] << 16) | (b[20] << 8) | b[21] )			/*  */

#define	EIT_DESC_DURATION(b)		((b[22] << 16) | (b[23] << 8) | b[24])			/*  */

#define	EIT_DESC_RUN_STATUS(b)		((b[25] & 0xe0) >> 5)			/*  */

#define	EIT_DESC_FREE_CA_MODE(b)	((b[25] & 0x10) >> 4)			/*  */

#define	EIT_DESC_LOOP_LENGTH(b)		(((b[25] & 0x0f) << 8) | b[26])			/*  */

#define	EIT_CRC(b)			({ \
					    int n = EIT_SECTION_LENGTH(b); \
					    int l = n -15; \
					    int base = 15; \
					    ((b[base + l] << 24) | (b[base + 1 + l] << 16) | (b[base + 2 + l] << 8) | b[base + 3 + l]); \
					    })			/*  */

#endif   /* ----- #ifndef _EIT_H_  ----- */

