/*
 *  libfb - FreeBASIC's runtime library
 *	Copyright (C) 2004-2006 Andre V. T. Vicentini (av1ctor@yahoo.com.br) and
 *  the FreeBASIC development team.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  As a special exception, the copyright holders of this library give
 *  you permission to link this library with independent modules to
 *  produce an executable, regardless of the license terms of these
 *  independent modules, and to copy and distribute the resulting
 *  executable under terms of your choice, provided that you also meet,
 *  for each linked independent module, the terms and conditions of the
 *  license of that module. An independent module is a module which is
 *  not derived from or based on this library. If you modify this library,
 *  you may extend this exception to your version of the library, but
 *  you are not obligated to do so. If you do not wish to do so, delete
 *  this exception statement from your version.
 */

/*
 * file_open - open and core file functions
 *
 * chng: oct/2004 written [v1ctor]
 *       jul/2005 modified to use the VFS OPEN method
 *       aug/2005 added OPEN hook
 *
 */

#include <stdlib.h>
#include "fb.h"

/*:::::*/
int fb_FileOpenEx( FB_FILE *handle, FBSTRING *str_filename, unsigned int mode,
                   unsigned int access, unsigned int lock, int len )
{
    int res = 0;
    FBSTRING *filename, str_tmp = { 0 };
    FnFileOpen pfnFileOpen = NULL;

    if( __fb_ctx.pfnDevOpenHook != NULL )
    {
    	/*
     	 * We have to copy it here because the hook might modify this string
     	 * and FB assumes no var-len string arg will be changed by the rtlib
     	 */
    	filename = &str_tmp;
    	fb_StrAssign( (void *)filename, -1, (void *)str_filename, -1, FALSE );

        /* Call the OPEN hook */
        res = __fb_ctx.pfnDevOpenHook( filename,
                                 mode,
                                 access,
                                 lock,
                                 len,
                                 &pfnFileOpen );

    }
    else
    	filename = str_filename;

    if( res == 0 )
    {
        if( pfnFileOpen == NULL )
        {
            /* Defaults to "normal" FILE OPEN function */
            pfnFileOpen = fb_DevFileOpen;
        }

        res = fb_FileOpenVfsEx( handle,
        						filename,
                                mode,
                                access,
                                lock,
                                len,
                                FB_FILE_ENCOD_DEFAULT,
                                pfnFileOpen );
    }
    else
    {
        /* Set error to the error number previously returned by the open
         * hook */
        fb_ErrorSetNum( res );
    }

    if( __fb_ctx.pfnDevOpenHook != NULL )
    {
    	/* Release temporary string */
    	fb_StrDelete( &str_tmp );
    }

    return res;
}

/*:::::*/
FBCALL int fb_FileOpen( FBSTRING *str, unsigned int mode, unsigned int access,
						unsigned int lock, int fnum, int len )
{
	return fb_FileOpenEx( FB_FILE_TO_HANDLE(fnum), str, mode, access, lock, len );
}

