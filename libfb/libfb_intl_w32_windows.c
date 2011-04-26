/*
 * intl_w32.c -- Core Win32 i18n functions
 *
 * chng: aug/2005 written [mjs]
 *
 */

#include "fb.h"
#include <stddef.h>
#include <stdlib.h>

char *fb_hGetLocaleInfo( LCID Locale,
                         LCTYPE LCType,
                         char *pszBuffer,
                         size_t uiSize )
{
    if( uiSize==0 ) {
        uiSize = 64;
        pszBuffer = NULL;
        for(;;) {
            pszBuffer = (char*) realloc( pszBuffer, uiSize <<= 1 );
            if( pszBuffer==NULL )
                break;
            if( GetLocaleInfo( Locale, LCType, pszBuffer, uiSize - 1 )!=0 ) {
                return pszBuffer;
            }
            if( GetLastError( ) != ERROR_INSUFFICIENT_BUFFER ) {
                free( pszBuffer );
                pszBuffer = NULL;
                break;
            }
        }
    } else {
        if( GetLocaleInfo( Locale, LCType, pszBuffer, uiSize )!=0 )
            return pszBuffer;
    }
    return NULL;
}

