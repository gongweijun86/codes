/*
 * structure.h
 *
 *  Created on: 2011-4-7
 *      Author: orion
 */

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_


#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<stdint.h>
#include	<stdarg.h>
#include	<string.h>
#include	<time.h>


/*-----------------------------------------------------------------------------
 *  常量定义
 *-----------------------------------------------------------------------------*/

#define	BYTE				unsigned char			/*  */
#define BOOL				int
#define TRUE				1
#define FALSE				0

#define DATA_BUF_LENGTH			1024 * 32
#define TS_LENGTH			188
#define MAX_STREAM_NUMBER		6
#define MAX_PROGRAME_NUMBER		20
#define	MAX_PMT_NUMBER			1024			/*max number of pmt_pid which the array can store  */
#define	MAX_PAT_NUMBER			1024			/*  */
#define	MAX_TDT_NUMBER			1024			/*  */
#define	MAX_TOT_NUMBER			1024			/*  */
#define	MAX_CAT_NUMBER			1024			/*  */
#define	MAX_NIT_NUMBER			1024			/*  */
#define	MAX_SDT_NUMBER			1024			/*  */
#define	MAX_EIT_NUMBER			1024			/*  */
#define	MAX_ES_NUMBER			16			/*how much pmt can store esinfo*/



#define ERROR_FILE			0
#define READ_FAILURE		ERROR_FILE-1
#define UNEXPECTED_FILE_FORMAT	ERROR_FILE-2


#include	"pat.h"
#include	"pmt.h"
#include	"nit.h"
#include	"sdt.h"
#include	"eit.h"
#include	"tot.h"
#include	"tdt.h"
#include	"cat.h"
#include	"tsph.h"
#include 	"log.h"
/*-----------------------------------------------------------------------------
 * 函数声明 
 *-----------------------------------------------------------------------------*/

int put_in_new_stream(int fd,BYTE *stream_buf,int buf_len,int *cur_pos);

BOOL read_next_ts_from_stream(BYTE *dest,BYTE *src,int src_len,int *cur_pos);

void copy_bytes(BYTE *dest,const BYTE *src, int len);

BOOL is_pmt_pid(uint16_t pid);

BOOL is_psi(uint16_t pid);

BOOL parse_TS(BYTE *sec_start);

BOOL parse_PAT(BYTE *sec_start);

BOOL parse_PMT(BYTE *sec_start);

BOOL parse_EIT(BYTE *sec_start);

BOOL parse_SDT(BYTE *sec_start);

BOOL parse_NIT(BYTE *sec_start);

BOOL parse_CAT(BYTE *sec_start);

BOOL parse_TDT(BYTE *sec_start);

BOOL parse_TOT(BYTE *sec_start);

/*-----------------------------------------------------------------------------
 *  全局变量
 *-----------------------------------------------------------------------------*/

uint16_t pmt_pid[MAX_PMT_NUMBER];
uint16_t es_pid[MAX_ES_NUMBER];

PMT pmt1[MAX_PMT_NUMBER];
PAT pat1[MAX_PAT_NUMBER];
SDT sdt1[MAX_SDT_NUMBER];
EIT eit1[MAX_EIT_NUMBER];
NIT nit1[MAX_NIT_NUMBER];
CAT cat1[MAX_CAT_NUMBER];
TOT tot1[MAX_TOT_NUMBER];
TDT tdt1[MAX_TDT_NUMBER];

TSPH tsph;
PMT pmt;
PAT pat;
SDT sdt;
EIT eit;
NIT nit;
CAT cat;
TOT tot;
TDT tdt;

NNND nnnd;
ESED esed;


#endif /* _STRUCTURE_H_ */
