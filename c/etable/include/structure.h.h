/*
 * structure.h
 *
 *  Created on: 2011-4-7
 *      Author: orion
 */

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#include	<string.h>
////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/*
 * Macros for type
 *
 */
#define BYTE unsigned char
#define BOOL		int
#define TRUE		1
#define FALSE		0

#define DATA_BUF_LENGTH 1024 * 64
#define TS_LENGTH 188
#define MAX_STREAM_NUMBER 6
#define MAX_PROGRAME_NUMBER 6
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#define ERROR_FILE 0
#define RTUN_READ_FAILURE ERROR_FILE-1
#define RTUN_UNEXPECTED_FILE_FORMAT ERROR_FILE-2
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//	PMT包的格式.
typedef struct _PMT_ITEM{
	u_int stream_number;		//	基本流编号
	u_int stream_pid;			//	包pid

	uint16_t pmt_sec_len;
	uint16_t p_info_len;
	uint16_t es_info_len;
	uint32_t crc;
	BYTE steam_type;			//	流的类型 audio video ...
}pmt_item;

//	PAT中包含很多PMT
typedef struct _PMT{
	int numbers_of_pmt_item;
	u_int pmt_pid;								//	pid
	pmt_item pmt_items[MAX_STREAM_NUMBER];			//	每一个节目源包含很多pmt_item
}pmt;

typedef struct _PAT_ITEM{
	u_int programe_number;
	u_int pmt_pid;
	uint32_t crc;
}pat_item;

typedef struct _PAT{
	int numbers_of_pat_item;
	pat_item pat_items[MAX_PROGRAME_NUMBER];
}pat;

///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/*
	Macros for accessing MPEG-2 TS packet headers

	Attention:
			b->TS_PACKET的首地址
*/
#define TS_PACKET_SYNC_BYTE(b)		(b[0])
#define TS_PACKET_TRANS_ERROR(b)	((b[1]&0x80)>>7)
#define TS_PACKET_PAYLOAD_START(b)	((b[1]&0x40)>>6)
#define TS_PACKET_PRIORITY(b)		((b[1]&0x20)>>5)
#define TS_PACKET_PID(b)			(((b[1]&0x1F)<<8) | b[2])

#define TS_PACKET_SCRAMBLING(b)		((b[3]&0xC0)>>6)
#define TS_PACKET_ADAPTATION(b)		((b[3]&0x30)>>4)
#define TS_PACKET_CONT_COUNT(b)		((b[3]&0x0F)>>0)
#define TS_PACKET_ADAPT_LEN(b)		(b[4])

/*
	Macros for PAT
	Attention:
			b->PAT的首地址
*/
#define PAT_TABLE_ID(b)					(b[0])
#define PAT_SECTION_SYNTAX(b)			((b[1] & 0x80)>>7)
#define PAT_SECTION_LENGTH(b)			((b[1] & 0x0f) <<8 | b[2])
#define PAT_TRANSPORT_STREAM_ID(b)		(b[3] | b[4])
#define PAT_VERSION(b)					((b[5] & 0x3e) >> 1)
#define PAT_CURRENT_NEXT(b)				(b[5] & 0x01)
#define PAT_SESSION_NUMBER(b)			(b[6])
#define PAT_LAST_SESSION_NUMBER			(b[7])
#define PAT_PROGRAME_NUMBER(b)			(b[8] | b[9])
#define PAT_PID(b)						((b[10] & 0x1f) << 8 | b[11])
/*#define PAT_CRC(b)						(b[12] | b[13] | b[14] | b[15])*/
#define PAT_CRC(b)				({ \
						    long len = PAT_SECTION_LENGTH(b); \
						    long n = len - 9; \
						    (b[7 + n + 1]<<24) | (b[7 + n + 2]<<16) | (b[7 + n + 3]<<8) | b[7 + n + 4]; \
						    }) 

/*
	Macros for PMT

	Attention:
			b->PMT的首地址
*/
#define PMT_TABLE_ID(b)					(b[0])
#define PMT_SECTION_SYNTAX(b)			((b[1] & 0x80)>>7)
#define PMT_SECTION_LENGTH(b)			((b[1] & 0x0f)<<8 | b[2])
#define PMT_PROGRAME_NUMBER(b)			(b[3] | b[4])
#define PMT_VERSION(b)					((b[5] & 0x3e) >> 1)
#define PMT_CURRENT_NEXT(b)				(b[5] & 0x01)
#define PMT_SESSION_NUMBER(b)			(b[6])
#define PMT_LAST_SESSION_NUMBER(b)		(b[7])
#define PMT_PCR_PID(b)					((b[8] & 0x1f) << 8 | b[9])
#define PMT_PROGRAME_INFO_LENGTH(b)		((b[10] & 0x0f) << 8 | b[11])

#define	PMT_ESINFO_LENGTH(b)			({ int n = PMT_PROGRAME_INFO_LENGTH(b); \
						    (b[10 + n + 5] & 0x0f) << 8 | b[10 + n + 6]; \
						    })/*  */

//#define	PMT_CRC(b)				({ int n = PMT_PROGRAME_INFO_LENGTH(b); \
//						   int m = PMT_SECTION_LENGTH(b); \
//						   int l = m - n - 4 - 9; \
//						    (b[10 + 2 + n + l] << 24) | (b[10 + 3 + n + l] << 16) | (b[10 + 4 + n + l] << 8) | b[10 + 5 + n  + l]; \
//						    })/*  */

#define	PMT_CRC(b)				({ \
						   int n = PMT_SECTION_LENGTH(b); \
						   int l = n - 4; \
						   int base = 3 + l; \
						    (b[base] << 24) | (b[base + 1] << 16) | (b[base + 2] << 8) | b[base + 3]; \
						    })/*  */

//////////something wrong/////////////////////////
//#define PMT_STREAM_TYPE(b)				(b[12])
//#define PMT_ELEMENTARY_ID(b)			((b[13] & 0x1f) << 8 | b[14])
//#define PMT_ES_INFO_LENGTH(b)			((b[15] & 0x0f) << 8 | b[16])
//#define PMT_CRC(b)						(b[17] | b[18] | b[19] | b[20])
///////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * functions
 */
int put_in_new_stream(int file_network_etc_handle,BYTE *stream_buf,int buff_len,int *current_pos);
BOOL read_next_ts_from_stream(BYTE *dest,BYTE *src,int src_len,int *current_pos);

BOOL process_pat(BYTE *ts_stream,pat *tpat);
BOOL process_pmt(BYTE *ts_stream,pmt *tpmt);

BOOL is_pat(BYTE *ts_stream);
BOOL is_pmt(BYTE *ts_stream,pat *tpat);

void copy_bytes(BYTE *dest,const BYTE *src, int len);
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
#endif /* _STRUCTURE_H_ */
