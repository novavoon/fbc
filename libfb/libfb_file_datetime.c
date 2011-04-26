/*
 * file_datetime.c -- get file date/time by filename
 *
 * chng: jul/2006 written [v1ctor]
 *
 */

#include "fb.h"

#include <time.h>
#include <sys/stat.h>

#ifdef TARGET_WIN32
#define stat _stat
#endif

/*:::::*/
FBCALL double fb_FileDateTime 
	( 
		const char *filename 
	)
{
	struct stat buf;
	struct tm *tm;
	
	if( stat( filename, &buf ) != 0 )
		return 0.0;
		
	tm = localtime( &buf.st_mtime );
	
	return fb_DateSerial( 1900 + tm->tm_year, 1+tm->tm_mon, tm->tm_mday ) +
		   fb_TimeSerial( tm->tm_hour, tm->tm_min, tm->tm_sec );
}
