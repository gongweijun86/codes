/*
 * structure.c
 *
 *  Created on: 2011-4-7
 *      Author: orion
 */

#include "../include/structure.h.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  put_in_new_stream
 *    Parameter:  
 *  Description:  
 * =====================================================================================
 */
int
put_in_new_stream(int fd, BYTE *dest, int buf_len, int *cur_pos)
{
	int read_len = TS_LENGTH;

	//	数据缓冲区中剩余的数据不足一个TS_LENGTH
	if ((buf_len - *cur_pos) < TS_LENGTH && (buf_len - *cur_pos) > 1) 
	{
		memcpy(dest, (BYTE *) (dest + *cur_pos), buf_len - *cur_pos);
		read_len = read(fd, dest + buf_len - *cur_pos, *cur_pos);
		if (read_len == -1){
			debuglog("readerror");
			return READ_FAILURE;
		}
		*cur_pos = 0;
	} else {
		read_len = read(fd, dest, buf_len);
		if (read_len == -1){
			debuglog("readerror");
			return READ_FAILURE;
		}
		*cur_pos = 0;
	}
	return read_len;
}

BOOL
read_next_ts_from_stream(BYTE *dest, BYTE *src, int src_len, int *cur_pos)
{
	if ((src_len - *cur_pos) < TS_LENGTH)
		return FALSE;
	memcpy(dest, (BYTE *) (src + *cur_pos), TS_LENGTH);
	*cur_pos += TS_LENGTH;
	return TRUE;
}

BOOL
parse_TS(BYTE *ts_stream)
{
	uint8_t tsph.sync = TS_SYNC_BYTE(ts_stream);
	if(tsph.sync != 0x47){
		debuglog("sync bytes missed!");
		return FALSE;
	}
	tsph.transport_error_indicator = TS_ERROR(ts_stream);
	tsph.payload_uint_start_indicator = TS_PAYLOAD_START(ts_stream);
	tsph.transport_priority = TS_PRIORITY(ts_stream);
	tsph.PID = TS_PID(ts_stream);
	tsph.transport_scrambling = TS_SCRAMBLING(ts_stream);
	tsph.adaptation_field_control = TS_ADAPT_CTL(ts_stream);
	tsph.continuity_counter = TS_CONT_COUNT(ts_stream);

	debuglog("ts:transport_error_indicator:%d\n
			payload_uint_start_indicator:%d\n
			transport_priority:%d\n
			PID:%d\n
			transport_scrambling:%d\n
			continuity_counter:%d\n",
			tsph.transport_error_indicator,
			tsph.payload_uint_start_indicator,
			tsph.transport_priority,
			tsph.PID,
			tsph.transport_scrambling,
			tsph.continuity_counter);

	if(!tsph.transport_error_indicator)
	{
		int len = 0;
		len += 4;

		if(is_psi(tsph.PID))
		{
			if(tsph.payload_uint_start_indicator == 1)
			{
				tsph.pointer_field = TS_POINTER_FIELD(ts_stream + len);
				len = len + tsph.pointer_field + 1;
			}
			else
			{
				/*TS包的净荷不带有PSI/SI包数据的第一个字节,没有pointer_field
				 *psi/si信息跨越两个ts包,不解析
				 */
				debuglog("此ts包是另一个psi/si表未完部分,暂为解析");
				return FALSE;
			}

			switch(tsph.adaptation_field_control)
			{
				case 0x03:
					/* 有adaptation,也有净荷 */
					tsph.adaptation_fields = (tsadaptation_filed *)malloc(sizeof(tsadaptation_filed));
					if(!tsph.adaptation_fields)
					{
						debuglog("malloc tsph.adaptation_field failed");
						return FALSE;
					}
					tsph.adaptation_fields->adapt_field_len = TS_ADAPT_LEN(ts_stream);
					len = len + tsph.adaptation_fields->adapt_field_len + 1; /* adapt_field_len表示在它后面的数据的长度 */
					break;
				case 0x01:/* 只有净荷数据 */
				case 0x02:/* 只有adaptation */
				case 0x00:/* 保留 */
				default:
					break;
			}

			BYTE* sec_start = ts_stream + len;	/* psi/si表起始位置 */

			switch(tsph.PID)
			{
				/* todo:对不同的错误可以给一个错误号 */
				case 0x0000:
					if(!parse_PAT(sec_start))
					{
						debuglog("parse pat failed!check log...");
						return FALSE;
					}
					break;
				case 0x0001:
					if(!parse_CAT(sec_start))
					{
						debuglog("parse cat failed!check log...");
						return FALSE;
					}
					break;
				case 0x0010:
					if(!parse_NIT(sec_start))
					{
						debuglog("parse nit failed!check log...");
						return FALSE;
					}
					break;
				case 0x0011:
					if(!parse_SDT(sec_start))
					{
						debuglog("parse sdt failed!check log...");
						return FALSE;
					}
					break;
				case 0x0012:
					if(!parse_EIT(sec_start))
					{
						debuglog("parse eit failed!check log...");
						return FALSE;
					}
					break;
				case 0x0014:
	//				parse_TDT();
	//				parse_TOD();
					break;
				default:
					if(is_pmt_pid(tsph.PID))
					{
						parse_PMT(sec_start);
					}
					break;
			}
		}
		else
		{
			if(is_es_pid(tsph.PID))
			{
				/*parse_ES()*/
			}
			else
			{
				/*parse_Others() */
			}
		}
		
	}
	else
	{
		debuglog("transport error!");
		return FALSE;
	}

	free(tsph.adaptation_fields);
	tsph.adaptation_fields = NULL;

	return TRUE;
}

BOOL
parse_PAT(BYTE *sec_start)
{
	BOOL flag = FALSE;
	pat.table_id = PAT_TABLE_ID(sec_start);
	pat.section_syntax_indicator = PAT_SECTION_SYNX(sec_start);
	pat.zero = PAT_ZERO(sec_start);
	pat.reserved1 = PAT_RESERVED1(sec_start);
	pat.section_length = PAT_SECTION_LENGTH(sec_start);
	pat.transport_stream_id = PAT_TRANSPORT_STREAM_ID(sec_start);
	pat.reserved2 = PAT_RESERVED2(sec_start);
	pat.version_number = PAT_VERSION(sec_start);
	pat.current_next_indicator = PAT_CURRENT_NEXT_IND(sec_start);
	pat.section_number = PAT_SECTION_NUMBER(sec_start);
	pat.last_section_number = PAT_LAST_SESSION_NUMBER(sec_start);
	pat.CRC_32 = PAT_CRC(sec_start);

	debuglog("pat.table_id:%d\n
			pat.section_syntax_indicator:%d\n
			pat.zero:%d\n
			pat.reserved1:%d\n
			pat.section_length:%l\n
			pat.transport_stream_id:%l\n
			pat.reserved2:%d\n
			pat.version_number:%d\n
			pat.current_next_indicator:%d\n
			pat.section_number:%d\n
			pat.last_section_number:%d\n
			pat.CRC_32:%l\n",
			pat.table_id,
			pat.section_syntax_indicator,
			pat.zero,
			pat.reserved1,
			pat.section_length,
			pat.transport_stream_id,
			pat.reserved2,
			pat.version_number,
			pat.current_next_indicator,
			pat.section_number,
			pat.last_section_number,
			pat.CRC_32);

	if(pat.table_id != 0x00)
	{
		debuglog("its not a pat");
		return FALSE;
	}
	

	int numbers_of_pmt = 0;
	numbers_of_pmt = (pat.section_length - 9) / 4;
	pat.pmap = (program_map *)malloc(sizeof(program_map) * numbers_of_pmt);
	if(!pat.pmap)
	{
		debuglog("malloc pat.pmap failed!");
		return FALSE;
	}

	int i = 0;
	BYTE* temp = sec_start;
	for(i = 0; i < numbers_of_pmt; i++)
	{
		pat.pmap->program_number = PAT_PROGRAM_NUMBER(temp);
		pat.pmap->reserved = PAT_MAP_RESERVED(temp);
		pat.pmap->PID = PAT_PMT_PID(temp);
		temp += 4; 
	}
	
	return TRUE;	
}

BOOL
parse_PMT(BYTE* sec_start)
{
	pmt.table_id = PMT_TABLE_ID(sec_start);
	pmt.section_syntax_indicator = PMT_SECTION_SYNX(sec_start);
	pmt.zero = PMT_ZERO(sec_start);
	pmt.reserved1 = PMT_RESERVED1(sec_start);
	pmt.section_length = PMT_SECTION_LENGTH(sec_start);
	pmt.program_number = PMT_PROGRAM_NUMBER(sec_start);
	pmt.reserved2 = PMT_RESERVED2(sec_start);
	pmt.version_number = PMT_VERSION(sec_start);
	pmt.current_next_indicator = PMT_CURRENT_NEXT_IND(sec_start);
	pmt.section_number = PMT_SECTION_NUMBER(sec_start);
	pmt.last_section_number = PMT_LAST_SECTION_NUMBER(sec_start);
	pmt.reserved3 = PMT_RESERVED3(sec_start);
	pmt.PCR_PID = PMT_PCR_PID(sec_start);
	pmt.reserved4 = PMT_RESERVED4(sec_start);
	pmt.program_info_length = PMT_PROGRAM_INFO_LENGTH(sec_start);

	debuglog("pmt.table_id:%d\n	
		pmt.section_syntax_indicator:%d\n	
		pmt.zero:%d\n	
		pmt.reserved1:%d\n	
		pmt.section_length:%l\n	
		pmt.program_number:%l\n	
		pmt.reserved2:%d\n	
		pmt.version_number:%d\n	
		pmt.current_next_indicator:%d\n	
		pmt.section_number:%d\n	
		pmt.last_section_number:%d\n	
		pmt.reserved3:%d\n	
		pmt.PCR_PID:%l\n	
		pmt.reserved4:%d\n	
		pmt.program_info_length:%l\n	
		pmt.CRC_32:%l\n",	
		pmt.table_id,
		pmt.section_syntax_indicator,
		pmt.zero,
		pmt.reserved1,
		pmt.section_length,
		pmt.program_number,
		pmt.reserved2,
		pmt.version_number,
		pmt.current_next_indicator,
		pmt.section_number,
		pmt.last_section_number,
		pmt.reserved3,
		pmt.PCR_PID,
		pmt.reserved4,
		pmt.program_info_length,
		pmt.CRC_32);

	if(pmt.table_id != 0x02)
	{
		debuglog("its not a pmt");
		return FALSE;
	}


	int all_es_len = 0;
	all_es_len = pmt.section_length - pmt.program_info_length - 9 - 4;
	int sin_es_len = 0;

	pmt.esinfo = (ESINFO *)malloc(sizeof(ESINFO) * MAX_ES_NUMBER);
	if(!pmt.es_info_len)
	{
		debuglog("malloc to pmt.esinfo failed");
		return FALSE;
	}
	BYTE* temp = sec_start;
	for(;sin_es_len < all_es_len;)
	{
		pmt.esinfo->stream_type = PMT_ESINFO_STREAM_TYPE(temp);
		pmt.esinfo->reserved1 = PMT_ESINFO_RESERVED1(temp);
		pmt.esinfo->elementary_PID = PMT_ESINFO_ELEPID(temp);
		pmt.reserved2 = PMT_ESINFO_RESERVED2(temp);
		pmt.ES_info_length = PMT_ESINFO_LENGTH(temp);

		sin_es_len = 5 + pmt.ES_info_length;
		temp = temp + sin_es_len; 
	}
	free(pmt.esinfo);
	pmt.esinfo = NULL;

	return TRUE;
}

BOOL
parse_CAT(BYTE* sec_start)
{

}

BOOL
parse_NIT(BYTE* sec_start)
{
	pat.table_id = NIT_TABLE_ID(sec_start);
	pat.section_syntax_indicator = NIT_SECTION_SYNX(sec_start);
	pat.reserved_future_use1 = NIT_RESERVED_FUTURE_USD1(sec_start);
	pat.reserved1 = NIT_RESERVED1(sec_start);
	pat.section_length = NIT_SECTION_LENGTH(sec_start);
	pat.network_id = NIT_NETWORK_ID(sec_start);
	pat.reserved2 = NIT_RESERVED2(sec_start);
	pat.version_number = NIT_VERSION_NUM(sec_start);
	pat.current_next_indicator = NIT_CURRENT_NEXT_IND(sec_start);
	pat.section_number = NIT_SECTION_NUM(sec_start);
	pat.last_section_number = NIT_LST_SECTION_NUM(sec_start);
	pat.reserved_future_use2 = NIT_RESERVED_FUTURE_USD2(sec_start);
	pat.network_descriptor_length = NIT_NETWORK_DESC_LENGTH(sec_start);
	pat.reserved_future_use3 = NIT_RESERVED_FUTURE_USD3(sec_start);
	pat.transport_stream_loop_length = NIT_TS_LOOP_LENGTH(sec_start);
	pat.CRC = NIT_CRC(sec_start);

	debuglog("nit.table_id:%d\n	
		nit.section_syntax_indicator:%d\n	
		nit.reserved_future_use1:%d\n	
		nit.reserved1:%d\n	
		nit.section_length:%l\n	
		nit.network_id:%l\n	
		nit.reserved2:%d\n	
		nit.version_number:%d\n	
		nit.current_next_indicator:%d\n	
		nit.section_number:%d\n	
		nit.last_section_number:%d\n	
		nit.reserved_future_use2:%d\n	
		nit.network_descriptor_length:%l\n	
		nit.reserved_future_use3:%d\n	
		nit.transport_stream_loop_length:%l\n	
		nit.CRC:%l\n",	
		nit.table_id,
		nit.section_syntax_indicator,
		nit.reserved_future_use1,
		nit.reserved1,
		nit.section_length,
		nit.network_id,
		nit.reserved2,
		nit.version_number,
		nit.current_next_indicator,
		nit.section_number,
		nit.last_section_number,
		nit.reserved_future_use2,
		nit.network_descriptor_length,
		nit.reserved_future_use3,
		nit.transport_stream_loop_length,
		nit.CRC);

	if(nit.table_id != 0x40 || nit.table_id != 0x41)
	{
		debuglog("its not a nit");
		return FALSE;
	}
//	network_name_desc 测试－－begin
	BYTE* start = sec_start + 11;
	BYTE* end = sec_start + nit.network_descriptor_length;
	for(;start < end;)
	{
		int tag = *(start);
		int len = *(++start);
		if(*(start) == 0x40)
		{
			printf("network_name_descriptor");
			nnnd->desc_tag = tag;
			nndd->desc_length = len;
			nnnd->desc = (BYTE *)malloc(sizeof(BYTE) * nnnd->desc_length);
			nnnd->desc = ++start;
			printf("network_name_descriptor:%s",nnnd->desc);
		}
		free(nnnd->desc);
		nnnd->desc = NULL;
		start = start - 2 + len;
	}
//	network_name_desc 测试－－结束
	/*
	 * todo:parse TSL
	 */
}

BOOL
parse_EIT(BYTE* sec_start)
{
	pat.table_id = EIT_TABLE_ID(sec_start);
pat.section_syntax_indicator = EIT_SECTION_SYNX(sec_start);
pat.reserved_future_use1 = EIT_RESERVED_FUTURE_USD1(sec_start);
pat.reserved1 = EIT_RESERVED1(sec_start);
pat.section_length = EIT_SECTION_LENGTH(sec_start);
pat.service_id = EIT_SERVICE_ID(sec_start);
pat.reserved2 = EIT_RESERVED2(sec_start);
pat.version_number = EIT_VERSION_NUM(sec_start);
pat.current_next_indicator = EIT_CURRENT_NEXT_IND(sec_start);
pat.section_number = EIT_SECTION_NUM(sec_start);
pat.last_section_number = EIT_LST_SECTION_NUM(sec_start);
pat.transport_stream_id = EIT_TS_ID(sec_start);
pat.original_network_id = EIT_ORIGINAL_NETWORK_ID(sec_start);
pat.segment_last_section_number = EIT_SEG_LST_SECTION_NUM(sec_start);
pat.last_table_id = EIT_LST_TABLE_ID(sec_start);
pat.description = EIT_DESC_EVENT_ID(sec_start);
pat.CRC_32 = EIT_DESC_START_TIME(sec_start);

nit.table_id:%d\n	
nit.section_syntax_indicator:%d\n	
nit.reserved_future_use1:%d\n	
nit.reserved1:%d\n	
nit.section_length:%d\n	
nit.service_id:%d\n	
nit.reserved2:%d\n	
nit.version_number:%d\n	
nit.current_next_indicator:%d\n	
nit.section_number:%d\n	
nit.last_section_number:%d\n	
nit.transport_stream_id:%d\n	
nit.original_network_id:%d\n	
nit.segment_last_section_number:%d\n	
nit.last_table_id:%d\n	
nit.description:%d\n	
nit.CRC_32:%d\n	
nit.table_id,
nit.section_syntax_indicator,
nit.reserved_future_use1,
nit.reserved1,
nit.section_length,
nit.service_id,
nit.reserved2,
nit.version_number,
nit.current_next_indicator,
nit.section_number,
nit.last_section_number,
nit.transport_stream_id,
nit.original_network_id,
nit.segment_last_section_number,
nit.last_table_id,
nit.description,
nit.CRC_32,	
}

BOOL
parse_SDT(BYTE* sec_start)
{

}
