/*
 * =====================================================================================
 *
 *       Filename:  test_macros.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年06月06日 23时30分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
 
#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

#define	_OFFSET(b) b[0]>>1			/*  */

#define OFFSET(b) ({ \
		int a=_OFFSET(b);\
		int c; \
		if(a>0) c=b[0]+b[1]; \
		else c=b[1]-b[0]; \
		c;\
		})				/*  */
	int
main ( int argc, char *argv[] )
{

	int t[] = {1,2};
	printf("%d",OFFSET(t));
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
