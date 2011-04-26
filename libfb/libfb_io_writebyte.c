/*
 * io_write.c -- write [#] functions
 *
 * chng: nov/2004 written [v1ctor]
 *
 */

#include <stdio.h>
#include "fb.h"

/*:::::*/
FBCALL void fb_WriteByte ( int fnum, char val, int mask )
{
    FB_WRITENUM( fnum, val, mask, "%d" );
}

/*:::::*/
FBCALL void fb_WriteUByte ( int fnum, unsigned char val, int mask )
{
    FB_WRITENUM( fnum, val, mask, "%u" );
}
