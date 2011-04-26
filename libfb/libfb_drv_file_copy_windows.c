/*
 * file_copy.c -- win32 file copy
 *
 * chng: dec/2005 written [DrV]
 *
 */

#include <windows.h>
#include "fb.h"

/*:::::*/
int fb_DrvFileCopy( const char *source, const char *destination )
{
	BOOL res;
	
	res = CopyFile( source, destination, FALSE );
	
	return fb_ErrorSetNum( res == FALSE ? FB_RTERROR_ILLEGALFUNCTIONCALL : FB_RTERROR_OK );
	
}
