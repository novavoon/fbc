/*
 * dev_file_readling_wstr - wstring LINE INPUT for file devices
 *
 * chng: nov/2005 written [v1ctor]
 *
 */

#include "fb.h"

/*:::::*/
int fb_DevFileReadLineWstr( struct _FB_FILE *handle, FB_WCHAR *dst, int dst_chars )
{
    int res;
    FILE *fp;
    FBSTRING temp = { 0 };

	FB_LOCK();

    fp = (FILE *)handle->opaque;
    if( fp == stdout || fp == stderr )
        fp = stdin;

	if( fp == NULL )
	{
		FB_UNLOCK();
		return fb_ErrorSetNum( FB_RTERROR_ILLEGALFUNCTIONCALL );
	}

    res = fb_DevFileReadLineDumb( fp, &temp, NULL );

	/* convert to wchar, file should be opened with the ENCODING option
	   to allow UTF characters to be read */
	if( (res == FB_RTERROR_OK) || (res == FB_RTERROR_ENDOFFILE) )
    	fb_WstrAssignFromA( dst, dst_chars, (void *)&temp, -1 );

    fb_StrDelete( &temp );

	FB_UNLOCK();

	return res;
}
