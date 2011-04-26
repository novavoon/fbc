/*
 *	dev_file - file device
 *
 * chng: jul/2005 written [mjs]
 *
 */

#include "fb.h"

/*:::::*/
int fb_DevScrnReadLineWstr( struct _FB_FILE *handle, FB_WCHAR *dst, int dst_chars )
{
    int res;
    FBSTRING temp = { 0 };

    /* !!!FIXME!!! no unicode input supported */

    res = fb_LineInput( NULL, (void *)&temp, -1, FALSE, FALSE, TRUE );

    if( res == FB_RTERROR_OK )
    	fb_WstrAssignFromA( dst, dst_chars, (void *)&temp, -1 );

    fb_StrDelete( &temp );

    return res;
}

/*:::::*/
void fb_DevScrnInit_ReadLineWstr( void )
{
	fb_DevScrnInit_NoOpen( );

    if( FB_HANDLE_SCREEN->hooks->pfnReadLineWstr == NULL )
        FB_HANDLE_SCREEN->hooks->pfnReadLineWstr = fb_DevScrnReadLineWstr;
}
