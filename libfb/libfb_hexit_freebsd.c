/*
 * exit.c -- end helper for FreeBSD
 *
 * chng: sep/2007 written [DrV]
 *
 */

#include "fb.h"

/*:::::*/
void fb_hEnd ( int unused )
{
	fb_unix_hEnd( unused );
}
