/*
 * file_input - input function for signed integers
 *
 * chng: nov/2004 written [v1ctor]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fb.h"

/*:::::*/
FBCALL int fb_InputInt( int *dst )
{
    char buffer[FB_INPUT_MAXNUMERICLEN+1];
    int len, isfp;

	len = fb_FileInputNextToken( buffer, FB_INPUT_MAXNUMERICLEN, FB_FALSE, &isfp );

	if( isfp == FALSE )
		*dst = fb_hStr2Int( buffer, len );
	else
		*dst = (int)rint( fb_hStr2Double( buffer, len ) );

	return fb_ErrorSetNum( FB_RTERROR_OK );
}
