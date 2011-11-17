/*
 * =====================================================================================
 *
 *       Filename:  debuglog.c
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  2011年06月09日 22时42分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  orion (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifdef DEBUG
#define DEBUGCODE(a) a
#define DPRINTF(a) printf("[%s:%d]", __FILE__, __LINE__);printf("%s\n", a);      
#else
#define DEBUGCODE(a)
#define DPRINTF(a) 
#endif
//#ifdef _DEBUG
//  #define dbg_msg printf
//#else
//  #define dbg_msg()
//#endif
#include	<stdlib.h>
#include <stdio.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
//	dbg_msg("%s","msgmsgmsgmsgmsg");
	DPRINTF("aaaaaaaaaaaaaaa");	
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
