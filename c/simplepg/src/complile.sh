#!/bin/bash

gcc -DDEBUG log.c desc_service_list.c newletsgo.c pmt.c desc_network_name.c desc_short_event.c nit.c sdt.c descriptor.c eit.c pat.c structure.c desc_service.c pidlist.c tsph.c -o ../simplepg
