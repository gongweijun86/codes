/*
 * =====================================================================================
 *
 *       Filename:  tsph.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年06月01日 17时30分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _TSPH_H_
#define  _TSPH_H_

/*
 * adaption_field uncompleted
 */
struct _adaptation_field {
	uint8_t adapt_field_len;
	/*todo: other field*/
};				/* ----------  end of struct adaptation_filed  ---------- */

typedef struct _adaptation_field ADAPT_FILD;

struct _transport_stream_packet_head {
	uint8_t sync;
	uint8_t transport_error_indicator;
	uint8_t payload_unit_start_indicator;
	uint8_t transport_priority;
	uint16_t PID;
	uint8_t transport_scrambling;
	uint8_t adaptation_field_control;
	uint8_t continuity_counter;
	
	ADAPT_FILD *adaptation_fields; 
	
	uint8_t pointer_field;
};				/* ----------  end of struct transport_stream_packet_head  ---------- */

typedef struct _transport_stream_packet_head TSPH;

/*
 * macros for accessing mpeg-2 ts packets headers
 * b => ts packets' first address
 */

#define TS_SYNC_BYTE(b)		(b[0])
#define TS_ERROR(b)		((b[1] & 0x80) >> 7)
#define TS_PAYLOAD_START(b)	((b[1] & 0x40) >> 6)
#define TS_PRIORITY(b)		((b[1] & 0x20) >> 5)
#define TS_PID(b)		(((b[1] & 0x1f) << 8) | b[2])

#define TS_SCRAMBLING(b)	((b[3] & 0xc0) >> 6)
#define TS_ADAPT_CTL(b)		((b[3] & 0x30) >> 4)
#define TS_CONT_COUNT(b)	(b[3] & 0x0f)

/*
 * TS_ADAPT_* 不完整 未使用
 */
#define TS_ADAPT_LEN(b)		(b[4])
/*#define	TS_ADAPT_FIELD(b)	(b[5])*/
#define TS_POINTER_FIELD(b)	(b[4])			/*  */


#endif   /* ----- #ifndef _TSPH_H_  ----- */

