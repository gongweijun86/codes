/*
 * =====================================================================================
 *
 *       Filename:  cat.h
 *
 *    Description:  Conditional Access Table definition
 *
 *        Version:  1.0
 *        Created:  2011年06月03日 14时57分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orion
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _CAT_H_
#define  _CAT_H_

struct _CA_identifier_descriptor {
	uint8_t descriptor_tag;
	uint8_t descriptor_length;
	uint16_t* CA_system_id;
};				/* ----------  end of struct _CA_identifier_descriptor  ---------- */

typedef struct _CA_identifier_descriptor CAID;

struct _conditional_access_table {
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t zero;
	uint8_t reserved1;
	uint16_t section_length;
	uint32_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_nubmer;
	CAID* caid;
	uint32_t CRC_32;
};				/* ----------  end of struct _conditional_access_table  ---------- */

typedef struct _conditional_access_table CAT;


#define	CAT_TABLE_ID(b)			(b[0])			/*  */

#define	CAT_SECTION_SYNX(b)		((b[1] & 0x80) >> 7)			/*  */

#define	CAT_ZERO(b)			((b[1] & 0x40) >> 6)			/*  */

#define	CAT_RESERVED1(b)		((b[1] & 0x30) >> 4)			/*  */

#define	CAT_SECTION_LENGTH(b)		((b[1] & 0x0f) << 8 | b[2])			/*  */

#define	CAT_RESERVED2(b)		((b[2] << 10) | (b[3] << 2) | (b[4] & 0xc0))			/*  */

#define	CAT_VERSION_NUM(b)		((b[4] & 0x3e) >> 1)	/*  */

#define	CAT_CURRENT_NEXT_IND(b)		(b[4] & 0x01)	/*  */

#define	CAT_SECTION_NUM(b)		(b[5])	/*  */

#define	CAT_LST_SECTION_NUMBER(b)	(b[6])		/*  */

#define	CAT_CRC(b)			({ \
					    int n = CAT_SECTION_LENGTH(b); \
					    int l = n - 9; \
					    (b[7 + l] << 24) | (b[8 + l] << 16) | (b[9 + l] << 8) | b[10 + l]; \
					    })	/*  */
#endif   /* ----- #ifndef _CAT_H_  ----- */

