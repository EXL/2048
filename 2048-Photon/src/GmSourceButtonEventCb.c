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


/* Callbacks */
int
GmSourceButtonEventCb( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	if( cbinfo->event->type == Ph_EV_BUT_PRESS )
		{
		system( "firefox \"https://github.com/EXL/2048/\"" );
		}

	return( Pt_CONTINUE );
	}
