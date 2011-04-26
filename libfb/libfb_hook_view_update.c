/*
 * hook_view_update.c -- call back function that gets called whenever VIEW PRINT
 *                       was called
 *
 * chng: sep/2005 written [mjs]
 *
 */

#include "fb.h"

/*:::::*/
FBCALL void fb_ViewUpdate( void )
{
    FB_LOCK();

    if( __fb_ctx.hooks.viewupdateproc ) {
        __fb_ctx.hooks.viewupdateproc( );
    } else {
        fb_ConsoleViewUpdate( );
    }

    FB_UNLOCK();
}
