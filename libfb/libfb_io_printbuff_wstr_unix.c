/*
 * io_printbuff_wstr.c -- low-level print to console function for wstrings
 *
 * chng: nov/2005 written [v1ctor]
 *
 */

#include "fb.h"

#define ENTER_UTF8  "\e%G"
#define EXIT_UTF8   "\e%@"

/*:::::*/
void fb_ConsolePrintBufferWstrEx( const FB_WCHAR *buffer, size_t chars, int mask )
{
	size_t avail, avail_len;
	char *temp;

	if( !__fb_con.inited )
	{
		/* !!!FIXME!!! is this ok or should it be converted to UTF-8 too? */
		fwrite( buffer, sizeof( FB_WCHAR ), chars, stdout );
		fflush( stdout );
		return;
	}

	temp = alloca( chars * 4 + 1 );

	/* ToDo: handle scrolling for internal characters/attributes buffer? */
	avail = (__fb_con.w * __fb_con.h) - (((__fb_con.cur_y - 1) * __fb_con.w) + __fb_con.cur_x - 1);
	avail_len = chars;
	if (avail < avail_len)
		avail_len = avail;

	/* !!!FIXME!!! to support unicode the char_buffer would have to be a wchar_t,
				   slowing down non-unicode printing.. */
	fb_wstr_ConvToA( temp, buffer, avail_len );

	memcpy( __fb_con.char_buffer + ((__fb_con.cur_y - 1) * __fb_con.w) + __fb_con.cur_x - 1,
	        temp,
	        avail_len );

	memset( __fb_con.attr_buffer + ((__fb_con.cur_y - 1) * __fb_con.w) + __fb_con.cur_x - 1,
	        __fb_con.fg_color | (__fb_con.bg_color << 4),
	        avail_len );

	/* convert wchar_t to UTF-8 */
	int bytes;

	fb_WCharToUTF( FB_FILE_ENCOD_UTF8, buffer, chars, temp, &bytes );
	/* add null-term */
	temp[bytes] = '\0';

	fputs( ENTER_UTF8, __fb_con.f_out );

	fputs( temp, __fb_con.f_out );

	fputs( EXIT_UTF8, __fb_con.f_out );

	/* update x and y coordinates.. */
	for( ; chars; chars--, buffer++ )
	{
		++__fb_con.cur_x;
		if( (*buffer == _LC('\n')) || (__fb_con.cur_x >= __fb_con.w) )
		{
			__fb_con.cur_x = 1;
			++__fb_con.cur_y;
			if( __fb_con.cur_y > __fb_con.h )
				__fb_con.cur_y = __fb_con.h;
		}
	}

	fflush( __fb_con.f_out );
}

/*:::::*/
void fb_ConsolePrintBufferWstr( const FB_WCHAR *buffer, int mask )
{
	return fb_ConsolePrintBufferWstrEx( buffer, fb_wstr_Len( buffer ), mask );
}
