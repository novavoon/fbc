/*
 * sys_ports.c -- ports I/O for Linux
 *
 * chng: aug/2005 written [lillo]
 *
 */

#include "fb.h"
#include "fb_linux.h"

/*:::::*/
int fb_hIn( unsigned short port )
{
	unsigned char value;
	
	if (!__fb_con.has_perm)
		return -fb_ErrorSetNum( FB_RTERROR_NOPRIVILEDGES );
	__asm__ volatile ("inb %1, %0" : "=a" (value) : "d" (port));
	
	return (int)value;
}

/*:::::*/
int fb_hOut( unsigned short port, unsigned char value )
{
	if (!__fb_con.has_perm)
		return fb_ErrorSetNum( FB_RTERROR_NOPRIVILEDGES );
	__asm__ volatile ("outb %0, %1" : : "a" (value), "d" (port));
	
	return FB_RTERROR_OK;
}

