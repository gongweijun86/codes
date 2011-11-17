/*
 * structure.c
 *
 *  Created on: 2011-4-7
 *      Author: orion
 */

#include "../include/structure.h"

extern PIDList pidlist;

long fpos_stream_start;
long total_offset;
extern int error;

bool iserror(FILE* f) {
	return (feof(f) || ferror(f));
}
long set_stream_to_packet(uint packet, uint offset, FILE *f) {
	long file_pos;
	file_pos = fpos_stream_start + (TSPACKETSIZE * packet) + offset;

	return (fseek(f, file_pos, SEEK_SET));
}

bool file_get_packet_start(FILE *f) {

	const int HEADERSTART = 0x47;
	const int TESTCOUNT = 15; // number of packets to check
	const int ALLOWEDTOFAIL = 1; // number of missing packet headers in above

	byte ch;
	long file_pos, temp_file_pos;
	int fail_count;

	do {
		do // look for an initial 0x47...
		{
			ch = fgetc(f);
			if (feof(f))
				return (false);

			if (ch == HEADERSTART)
				break;
		} while (true);

		// now we check to see if HEADERSTART occurs every PACKETSIZE bytes...

		file_pos = ftell(f);
		file_pos--;
		fail_count = 0;

		int i;
		for (i = 0; i < TESTCOUNT; i++) {
			temp_file_pos = ftell(f);
			temp_file_pos += (TSPACKETSIZE - 1);
			if (fseek(f, temp_file_pos, SEEK_SET)) {
				return (false);
			}

			if (feof(f) == 0) {
				ch = fgetc(f);
				if (ch != HEADERSTART)
					fail_count++; // Increment failCount - if more than ALLOWEDTOFAIL failure in TESTCOUNT, probably not correct header position.
			}
		}
		if (fail_count <= ALLOWEDTOFAIL) {
			fpos_stream_start = file_pos;
			fseek(f, file_pos, SEEK_SET);
			return (true);
		}
	} while (true);

	return (false);
}

int check_file(FILE *f) {
	if (!file_get_packet_start(f)) {
		printf("structure.c:Could not find start of Header - check stream!");
		fclose(f);
		return (false);
	}

	return (true);
}

void handle_packet(long packet, FILE *f) {
	byte ch;
	uint offset = 0;
	byte bytes[4096];
	int sect_length, table_id;

	TSPH header;
	//	PMT pmt;
	PAT pat;
	SDT sdt;
	EIT eit;
	NIT nit;

	/**
	 * 判断一个包是否是si包，是则继续1.2.3....,否则读取新包
	 * 1.从buf_ts中读取一个包到bytes中
	 * 2.如果包中数据分好几包发过来了，就从文件中直接查找然后读进bytes中
	 * 3.经过1.2.，bytes中就有了一个完整的section
	 * 4.根据pid判断是什么section，然后分别解包
	 */

	set_stream_to_packet(packet, offset, f);
	fread(bytes, sizeof(byte), 4, f);// just get the header (4 bytes) for now...

	if (iserror(f)) {
		//do {
		//	packet--;
		//	set_stream_to_packet(packet, offset, f);
		//	fread(bytes, sizeof(byte), 4, f);
			error = true;
			printf("-----------------error---------------");
			return;
		//} while (iserror(f));
	}

	parse_TS(bytes, 4, &header);
	//here could print header;
	offset = 4; // get past the header...

	if (!header.transport_error_indicator && (header.sync == 0x47)) {
		if (header.adaptation_field_control >= 2){ // adaptation field exists
			// do the adaptation field first...
			set_stream_to_packet(packet, offset, f);
			memset(bytes, 0xFF, sizeof(bytes));

			fread(&ch, sizeof(byte), 1, f); // this is the length of the adaptation field - we'll assume it will be less than a packet?

			set_stream_to_packet(packet, offset, f);
			fread(bytes, sizeof(byte), (int) ch, f);

			offset += ch + 1;
		}

		if ((header.adaptation_field_control == 1)
				|| (header.adaptation_field_control == 3)) {
			// Do we attempt to decode this?
			if (header.payload_unit_start_indicator && is_si(header.PID,
					&pidlist)) {
				set_stream_to_packet(packet, offset, f);
				memset(bytes, 0xFF, sizeof(bytes));

				byte startpoint;
				fread(&startpoint, sizeof(byte), 1, f);

				//jump of the pointer_field
				if (startpoint > 0x00) {
					byte b;
					int i;
					for (i = 0; i < startpoint; i++)
						fread(&b, sizeof(byte), 1, f);
				}
				//now read the actural data,183 is at the condition of adaptation_field_ctl == 1
				// but anyway adapt to it is 3
				fread(bytes, sizeof(byte), 183, f);

				sect_length = (0x100 * (bytes[1] & 0x0F)) + bytes[2];
				table_id = bytes[0];
				int bytes_remain_to_be_read = sect_length - (188 - 8
						- startpoint);

				int next_packet = packet;
				// do we need more packets? maybe one packet is not enough HAHHAAHHA
				while (bytes_remain_to_be_read > 0) {
					bool found = false;
					uint thisPID;
					bool payload_unit_start_indicator;

					do {
						byte tempread[4];
						set_stream_to_packet(++next_packet, 0, f);

						//file_stream->Read(tempread, sizeof(tempread));
						fread(tempread, sizeof(byte), sizeof(tempread), f);

						payload_unit_start_indicator = (((tempread[1] & 0x40)
								>> 6) == 1);
						thisPID = (256 * (tempread[1] & 0x1F)) + tempread[2];

						if (thisPID == header.PID) // found it!
							found = true;
					} while (!found);

					set_stream_to_packet(next_packet,
							(payload_unit_start_indicator) ? 5 : 4, f);
					int a = sect_length - bytes_remain_to_be_read + 3; // read into bytes[] from here
					//we find the rest data, read them into bytes just after front data.
					fread(&bytes[a], sizeof(byte),
							(payload_unit_start_indicator) ? 183 : 184, f);

					bytes_remain_to_be_read
							-= ((payload_unit_start_indicator) ? 183 : 184);
				};

				byte *b = bytes;

				bool flag = true;
				// now we got a complete "packet"(>=188 byte) in "bytes",so we parse it step by step.
				do {
					switch (header.PID) {
					case 0x0000: // Program Association Table
						b = parse_PAT(b, sect_length + 3, &pat);
						break;
					case 0x0001: // Conditional Access Table
						//pass it
						break;

					case 0x0010: // Network Information Table
						b = parse_NIT(b, sect_length + 3, &nit);
						break;

					case 0x0011: // Service Description Table
						b = parse_SDT(b, sect_length + 3, &sdt);
						break;

					case 0x0012: // Event Information Table
						b = parse_EIT(b, sect_length + 3, &eit);
						break;

					case 0x0013: // Running Status Table
						//pass it
						break;

					case 0x0014: // Time Date Table / Time Offset Table
						// pass it
						break;

					default:
						//if (pid_list->IsPMT(header.PID))
						//							if(is_pmt(header.PID,&pidlist))
						//							{
						//								b = psi_pmt->Decode(b, sect_length + 3, dataptr);
						//								// OK, let's add the PIDs into the list...
						//								pid_list->SetKnownPID(psi_pmt->PCR_PID, 0x100);
						//								if (psi_pmt->first_program_info_loop)
						//								{
						//									PSI_PMT_Program_Info_Loop* thisProgramInfo = psi_pmt->first_program_info_loop;
						//									while (thisProgramInfo)
						//									{
						//										pid_list->SetKnownPID(thisProgramInfo->elementary_PID, thisProgramInfo->stream_type);
						//										if (thisProgramInfo->stream_type == 0x06)	// Either Teletext or AC3
						//										{
						//											void *testDescriptor = thisProgramInfo->first_descriptor;
						//											// we make the (possibly wrong) assumption that the AC3 / Teletext
						//											// descriptor will be the first descriptor, hence the loop commented out
						//	//										while (testDescriptor)
						//	//										{
						//												switch (((Descriptor*)testDescriptor)->descriptor_tag)
						//												{
						//												case 0x56:
						//													pid_list->SetPIDAC3Teletext(thisProgramInfo->elementary_PID, PID_TELETEXT);
						//													break;
						//												case 0x6A:
						//													pid_list->SetPIDAC3Teletext(thisProgramInfo->elementary_PID, PID_AC3);
						//													break;
						//												default:
						//													break;
						//												}
						//	//										}
						//										}
						//										thisProgramInfo = thisProgramInfo->next_program_info_loop;
						//									}
						//								}
						//								break;
						//							}

						if (is_known_pid(header.PID, &pidlist)) {
							flag = false; // no decode, so avoid an endless loop
							break;
						}

						flag = false; // no decode, so avoid an endless loop
						break;
					}

					if (b[0] == 0xFF)
						break;

					// there may be a case where corrupt data causes the returned b value to be past the end of bytes[4096].
					// check this here...
					if (b > (bytes + 4096))
						break;

					// b is not 0xFF, so we may have a new table starting here.  Is this legal?  Anyway...
					// header.PID will stay the same, but table_id will change, as will sect_length.

					//table_id = b[0];
					//sect_length = (0x100 * (b[1] & 0x0F)) + b[2];
					flag = false;
				} while (flag);
			}
		}
	}

}

int get_total_packet(FILE* f) {
	fseek(f, 0, SEEK_END);
	int filelength = ftell(f);

	return ((int) (filelength / 188));
}
