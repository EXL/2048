/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.03  */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Local headers */
#include "ablibs.h"
#include "GmGlobals.h"
#include "abimport.h"
#include "proto.h"

/* Game headers */
#include "2048.h"

/* Callbacks */
int
GmWindowKeyEventCb( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	if( cbinfo->event->type == Ph_EV_KEY )
		{
		const PhKeyEvent_t *GmKeyEvent = PhGetData( cbinfo->event );
		if( ( GmKeyEvent->key_flags & Pk_KF_Sym_Valid ) && ( PkIsKeyDown( GmKeyEvent->key_flags ) ) )
			{
			/* // Debug keyboard codes.
			fprintf( stderr, "GmKeyEvent->key_sym: %lu\n", GmKeyEvent->key_sym );
			*/

			/* Drop handling Escape key here because it's being handled in "GmMenuItemResetCallback.c" file. */
			if( GmKeyEvent->key_sym != Pk_Escape )
				{
				e_key( GmKeyEvent->key_sym );
				PtDamageWidget( GmRawWidget );
				}
			}
		}

	return( Pt_CONTINUE );
	}
