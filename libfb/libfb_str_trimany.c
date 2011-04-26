/*
 * str_trim.c -- trim$ ANY function
 *
 * chng: oct/2004 written [v1ctor]
 *
 */

#include "fb.h"


/*:::::*/
FBCALL FBSTRING *fb_TrimAny 
	( 
		FBSTRING *src, 
		FBSTRING *pattern 
	)
{
    const char *pachText = NULL;
	FBSTRING *dst;
	size_t len;

    if( src == NULL ) 
    {
        fb_hStrDelTemp( pattern );
        return &__fb_ctx.null_desc;
    }

   	FB_STRLOCK();

	len = 0;
	if( src->data != NULL )
    {
        size_t len_pattern = ((pattern != NULL) && (pattern->data != NULL)? FB_STRSIZE( pattern ) : 0);
        pachText = src->data;
        len = FB_STRSIZE( src );
		if( len_pattern != 0 )
		{
			while ( len != 0 )
	        {
	            size_t i;
	            for( i=0; i!=len_pattern; ++i ) 
	            {
	                if( FB_MEMCHR( pattern->data, *pachText, len_pattern )!=NULL )
	                    break;
	            }
	            
	            if( i==len_pattern )
	                break;

	            --len;
	            ++pachText;
			}
			while ( len != 0 )
	        {
	            size_t i;
	            --len;
	            for( i=0; i!=len_pattern; ++i ) 
	            {
	                if( FB_MEMCHR( pattern->data, pachText[len], len_pattern )!=NULL )
	                    break;
	            }
	            
	            if( i==len_pattern ) 
	            {
	                ++len;
	                break;
	            }
			}
		}
	}

	if( len > 0 )
	{
		/* alloc temp string */
        dst = fb_hStrAllocTemp_NoLock( NULL, len );
		if( dst != NULL )
		{
			/* simple copy */
			fb_hStrCopy( dst->data, pachText, len );
		}
		else
			dst = &__fb_ctx.null_desc;
    }
	else
		dst = &__fb_ctx.null_desc;

	/* del if temp */
	fb_hStrDelTemp_NoLock( src );
    fb_hStrDelTemp_NoLock( pattern );

   	FB_STRUNLOCK();

	return dst;
}
