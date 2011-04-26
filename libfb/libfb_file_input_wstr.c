/*
 * file_input_wstr - input function for wstring's
 *
 * chng: nov/2005 written [v1ctor]
 *
 */

#include "fb.h"

/*:::::*/
FBCALL int fb_InputWstr( FB_WCHAR *dst, int dst_chars )
{
	fb_FileInputNextTokenWstr( dst, dst_chars, TRUE );

	return fb_ErrorSetNum( FB_RTERROR_OK );
}

