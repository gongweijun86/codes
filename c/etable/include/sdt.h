/*
 * =====================================================================================
 *
 *       Filename:  sdt.h
 *
 *    Description:  Service Description Table difinition
 *
 *        Version:  1.0
 *        Created:  2011年06月03日 14时23分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orion 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _SDT_H_
#define  _SDT_H_
struct _sdt_desc {
	uint16_t service_id;
	uint8_t reserved_future_use;
	uint8_t EIT_schedule_flag;
	uint8_t EIT_present_following_flag;
	uint8_t running_status;
	uint8_t free_CA_mode;
	uint16_t descriptors_loop_length;
	char* descriptor;
};				/* ----------  end of struct _sdt_desc  ---------- */

typedef struct _sdt_desc SDT_DESC;

struct _service_description_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved_future_use1;
	uint8_t reserved1;
	uint16_t section_length;
	uint16_t transport_stream_id;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint16_t original_network_id;
	uint8_t reserved_future_use2;
	SDT_DESC* description;
	uint32_t CRC_32;
};				/* ----------  end of struct _service_description_table  ---------- */

typedef struct _service_description_table SDT;



#define	SDT_TABLE_ID(b)				    (b[0])			/*  */

#define SDT_SECTION_SYNX(b)			    ((b[1] & 0x80) >> 7)				/*  */

#define	SDT_RESERVED_FUTURE_USD1(b)		    ((b[1] & 0x40) >> 6)			/*  */

#define	SDT_RESERVED1(b)			    ((b[1] & 0x30) >> 4)			/*  */

#define	SDT_SECTION_LENGTH(b)			    (((b[1] & 0x0f) << 8) | b[2])			/*  */

#define	SDT_TS_ID(b)				    ((b[3] << 8) | b[4])			/*  */

#define	SDT_RESERVED2(b)			    ((b[5] & 0xc0) >> 6)			/*  */

#define	SDT_VERSION_NUM(b)			    ((b[5] & 0x3e) >> 1)			/*  */

#define	SDT_CURRENT_NEXT_IND(b)			    (b[5] & 0x01)			/*  */

#define	SDT_SECTION_NUM(b)			    (b[6])		/*  */

#define	SDT_LST_SECTION_NUM(b)			    (b[7])			/*  */

#define	SDT_ORIGINAL_NETWORK_ID(b)		    ((b[8] << 8) | b[9])			/*  */

#define	SDT_RESERVED_FUTURE_USD2(b)		    (b[10])			/*  */

#define	SDT_DESC_SERVICE_ID(b)			    ((b[11] << 8) | b[12])			/*  */

#define	SDT_DESC_RESERVED_USD(b)		    ((b[13] & 0xfc) >> 2)			/*  */

#define	SDT_DESC_EIT_SCHEDULE_FLAG(b)		    ((b[13] & 0x02) >> 1)			/*  */

#define	SDT_DESC_EIT_PRESENT_FOLLOWING_FLAG(b)	    (b[13] & 0x01)			/*  */

#define	SDT_DESC_RUN_STATUS(b)			    ((b[14] & 0xe0) >> 5)			/*  */

#define	SDT_DESC_FREE_CA_MODE(b)		    ((b[14] & 0x10) >> 4)			/*  */

#define	SDT_DESC_LOOP_LENGTH(b)			    (((b[14] & 0x0f) << 8) | b[15])			/*  */

#define	SDT_CRC(b)				    ({ \
							int n = SDT_SECTION_LENGTH(b); \
							int l = n - 4; \
							int base = 3 + l; \
							((b[base] << 24) | (b[base + 1] << 16) | (b[base + 2] << 8) | b[base + 3]); \
							})			/*  */
#endif   /* ----- #ifndef _SDT_H_  ----- */

