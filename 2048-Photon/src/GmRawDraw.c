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

/* Global variables */
int GmBackgroundShow = 1;
int GmTilesRound = 1;

/* Inline functions */
static inline int
GmColor( unsigned color )

	{
	/* Convert ARGB color to RGB color. */
	return (color & 0xFFFFFF);
	}

/* Callbacks */
void
GmRawDraw( PtWidget_t *widget, PhTile_t *damage )

	{
	PtSuperClassDraw( PtBasic, widget, damage );

	PhRect_t GmCanvas;
	PtCalcCanvas( widget, &GmCanvas );

	/* // Debug cavas sizes
	fprintf( stderr, "Canvas Size: %dx%d\n", GmCanvas.lr.x - GmCanvas.ul.x + 1, GmCanvas.lr.y - GmCanvas.ul.y + 1 );
	fprintf( stderr, "Canvas Rect: %dx%d %dx%d\n", GmCanvas.ul.x, GmCanvas.ul.y, GmCanvas.lr.x, GmCanvas.lr.y );
	*/

	PtClipAdd( widget, &GmCanvas );

	/* Draw background */
	if( GmBackgroundShow )
		{
		PgSetFillColor( GmColor( COLOR_BOARD ) );
		PgDrawRect( &GmCanvas, Pg_DRAW_FILL );
		}

	/* Draw tiles on game field */
	int x, y = 0;
	for( ; y < LINE_SIZE; ++y )
		for( x = 0; x < LINE_SIZE; ++x )
			// draw_tile()

	/* Draw game score and final screen */
	// draw_final()

	PtClipRemove( );
	}
