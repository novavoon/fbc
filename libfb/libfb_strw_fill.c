/*
 * strw_fill.c -- stringw$ function
 *
 * chng: ago/2005 written [v1ctor]
 *
 */

#include "fb.h"

/*:::::*/
FBCALL FB_WCHAR *fb_WstrFill1 ( int chars, FB_WCHAR c )
{
	FB_WCHAR *dst;

	if( chars <= 0 )
		return NULL;

	/* alloc temp string */
    dst = fb_wstr_AllocTemp( chars );
	if( dst != NULL )
	{
		/* fill it */
		fb_wstr_Fill( dst, c, chars );
	}

	return dst;
}


/*:::::*/
FBCALL FB_WCHAR *fb_WstrFill2 ( int chars, const FB_WCHAR *src )
{
	FB_WCHAR *dst;

	if( (chars > 0) && (src != NULL) && (fb_wstr_Len( src ) > 0) )
	{
		dst = fb_WstrFill1( chars, src[0] );
	}
	else
		dst = NULL;

	return dst;
}

