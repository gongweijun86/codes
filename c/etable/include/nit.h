/*
 * =====================================================================================
 *
 *       Filename:  nit.h
 *
 *    Description:  Network Information Table definition
 *
 *        Version:  1.0
 *        Created:  2011年06月03日 11时29分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: orion 
 *        Company:  
 *
 * =====================================================================================
 */

#include "../include/structure.h"

#ifndef  _NIT_H_
#define  _NIT_H_

struct _nit_network_name_desc{
	uint8_t desc_tag;
	uint8_t desc_length;
	BYTE* desc;
};

typedef struct _nit_network_name_desc NNND;

struct _transport_stream_loop {
	uint16_t transport_stream_id;
	uint16_t original_network_id;
	uint8_t reserved_future_use;
	uint16_t transport_descriptors_length;
	BYTE* descriptor;
};				/* ----------  end of struct _transport_stream_loop  ---------- */

typedef struct _transport_stream_loop TSL;

struct _network_information_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use1;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t network_id;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint8_t reserved_future_use2;
	uint16_t network_descriptor_length;
	BYTE* descriptor;
	uint8_t reserved_future_use3;
	uint16_t transport_stream_loop_length;
	TSL* transport_stream;
	uint32_t CRC;
};				/* ----------  end of struct _network_information_table  ---------- */

typedef struct _network_information_table NIT;


#define	NIT_TABLE_ID(b)			(b[0])			/*  */

#define	NIT_SECTION_SYNX(b)		((b[1] & 0x80) >> 7)			/*  */

#define	NIT_RESERVED_FUTURE_USD1(b)	((b[1] & 0x40) >> 6)			/*  */

#define	NIT_RESERVED1(b)		((b[1] & 0x30) >> 4)		    	/*  */

#define	NIT_SECTION_LENGTH(b)		(((b[2] & 0x0f) << 8) | b[3])			/*  */

#define	NIT_NETWORK_ID(b)		((b[4] << 8) | b[5])			/*  */

#define	NIT_RESERVED2(b)		((b[6] & 0xc0) >> 6)			/*  */

#define	NIT_VERSION_NUM(b)		((b[6] & 0x3e) >> 1)			/*  */

#define	NIT_CURRENT_NEXT_IND(b)			(b[6] & 0x01)			/*  */

#define	NIT_SECTION_NUM(b)		(b[7])			/*  */

#define	NIT_LST_SECTION_NUM(b)		(b[8])			/*  */

#define	NIT_RESERVED_FUTURE_USD2(b)	((b[9] & 0xf0) >> 4)			/*  */

#define	NIT_NETWORK_DESC_LENGTH(b)	(((b[9] & 0x0f) << 8)| b[10])		/*  */

#define	NIT_RESERVED_FUTURE_USD3(b)	({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 11 + l; \
					    ((b[base] & 0xf0) >> 4); \
					    })			/*  */

#define	NIT_TS_LOOP_LENGTH(b)		({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 11 + l; \
					    (((b[base] & 0x0f) << 8) | b[base + 1]); \
					    })			/*  */

#define	NIT_TSL_TSID(b)			({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 13 + l; \
					    ((b[base] << 8) | b[base + 1]); \
					    })			/*  */

#define	NIT_TSL_ORIGINAL_NETWORK_ID(b)	({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 15 + l; \
					    ((b[base] << 8) | b[base + 1]); \
					    })			/*  */

#define	NIT_TSL_RESERVED_FUTURE_USD(b)	({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 17 + l; \
					    ((b[base] & 0xf0) >> 4); \
					    })			/*  */

#define	NIT_TSL_TRANS_DESC_LENGTH(b)	({ \
					    int l = NIT_NETWORK_DESC_LENGTH(b); \
					    int base = 17 + l; \
					    (((b[base] & 0x0f) << 8) | b[base + 1]); \
					    })			/*  */

#define	NIT_CRC(b)			({ \
					    int n = NIT_SECTION_LENGTH(b); \
					    int l = n - 4; \
					    int base = 4; \
					    ((b[base + l] << 24) | (b[base + l + 1] << 16)| (b[base + l + 2] << 8) | b[base + l + 3]); \
					    })			/*  */
#endif   /* ----- #ifndef _NIT_H_  ----- */

