/*
 * array_clear.c -- erase function for static arrays
 *
 * chng: jan/2005 written [v1ctor]
 *
 */

#include <stddef.h>
#include "fb.h"

/*:::::*/
FBCALL int fb_ArrayClear
	( 
		FBARRAY *array, 
		int isvarlen 
	)
{
    /* not an error, see fb_ArrayEraseObj() */
    if( array->ptr == NULL )
    	return fb_ErrorSetNum( FB_RTERROR_OK );
    
	if( isvarlen == FB_FALSE )
		memset( array->ptr, 0, array->size );
	else
    	fb_hArrayDtorStr( array, NULL, 0 );

   	return fb_ErrorSetNum( FB_RTERROR_OK );
}
