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

/* Global variables */
static int GmFontsAntialiased = 1;

/* Callbacks */
int
GmMenuItemBackgroundCb( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	GmBackgroundShow = !GmBackgroundShow;
	ApModifyItemState( &GmMenuView, ( GmBackgroundShow ) ? AB_ITEM_SET : AB_ITEM_NORMAL, 
		ABN_GmMenuItemBackground, NULL );
	PtDamageWidget( GmRawWidget );

	return( Pt_CONTINUE );
	}

int
GmMenuItemTilesCb( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;

	GmTilesRound = !GmTilesRound;
	ApModifyItemState( &GmMenuView, ( GmTilesRound ) ? AB_ITEM_SET : AB_ITEM_NORMAL, 
		ABN_GmMenuItemTiles, NULL );
	PtDamageWidget( GmRawWidget );

	return( Pt_CONTINUE );
	}

int
GmMenuItemFontsCb( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )

	{
	/* eliminate 'unreferenced' warnings */
	widget = widget, apinfo = apinfo, cbinfo = cbinfo;
	
	GmFontsAntialiased = !GmFontsAntialiased;
	ApModifyItemState( &GmMenuView, ( GmFontsAntialiased ) ? AB_ITEM_SET : AB_ITEM_NORMAL, 
		ABN_GmMenuItemFonts, NULL );
	GmFontsSetAntialias( GmFontsAntialiased );
	PtDamageWidget( GmRawWidget );

	return( Pt_CONTINUE );
	}
