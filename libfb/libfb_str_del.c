/*
 * str_del.c -- string deletion function
 *
 * chng: oct/2004 written [v1ctor]
 *
 */

#include <stdlib.h>
#include <string.h>
#include "fb.h"

/*:::::*/
FBCALL void fb_StrDelete ( FBSTRING *str )
{
    if( (str == NULL) || (str->data == NULL) )
    	return;

    free( (void *)str->data );

	str->data = NULL;
	str->len  = 0;
	str->size = 0;
}
