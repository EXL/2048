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

/* Global defines */
#define VALUE_MAX_SIZE 5   /* "2048\0" */
#define SCORE_MAX_SIZE 16 /* "Score: 999999..." */

/* Global variables */
int GmBackgroundShow = 1;
int GmTilesRound = 1;

/* Static variables */
static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

/* Inline functions */
static inline int
GmOffsetCoords( int coord, int size, int offset )

	{
	/* Offset Tile coordinates for proper Game Board rendering while window resizing. */
	const int start = ( size / 2 ) - ( ( ( TILE_SIZE * LINE_SIZE ) + ( TILE_MARGIN * ( LINE_SIZE - 1 ) ) ) / 2 );
	return coord * ( TILE_MARGIN + TILE_SIZE ) + start - offset;
	}

static inline int
GmColor( unsigned color )

	{
	/* Convert ARGB color to RGB color. */
	return (color & 0xFFFFFF);
	}

/* Static functions */
static void
GmDrawTile( const PhRect_t *GmCanvas, int value, int x, int y )

	{
	const int xOffset = GmOffsetCoords( x, GmCanvas->lr.x - GmCanvas->ul.x + 1, 0 ) + GmCanvas->ul.x;
	const int yOffset = GmOffsetCoords( y, GmCanvas->lr.y - GmCanvas->ul.y + 1, TILE_MARGIN * 2 ) + GmCanvas->ul.y;
	const PhRect_t GmTile = { { xOffset, yOffset }, { xOffset + TILE_SIZE, yOffset + TILE_SIZE } };

	/* Draw Tile background. */
	PgSetFillColor( GmColor( e_background( value ) ) );
	if( GmTilesRound )
		{
		const PhPoint_t GmRectRad = { 8, 8 };
		PgDrawRoundRect( &GmTile, &GmRectRad, Pg_DRAW_FILL );
		}
	else
		PgDrawRect( &GmTile, Pg_DRAW_FILL );

	/* Draw Tile value. */
	if( value )
		{
		const int size = ( value < 100 ) ? 24 : ( value < 1000 ) ? 18 : 14;
		const char *GmFont = ( value < 100 ) ? GmFontLarge : ( value < 1000 ) ? GmFontMiddle : GmFontSmall;
		PgSetFont( GmFont );
		PgSetTextColor( GmColor( e_foreground( value ) ) );
		char GmValue[ VALUE_MAX_SIZE ] = { '\0' };
		snprintf( GmValue, VALUE_MAX_SIZE, "%d", value );
		PhRect_t GmExtent;
		PgExtentText( &GmExtent, NULL, GmFont, GmValue, 0 );
		const int w = GmExtent.lr.x - GmExtent.ul.x + 1, h = size + 4;
		const PhPoint_t GmPos = { xOffset + ( TILE_SIZE - w ) / 2, yOffset + TILE_SIZE - ( TILE_SIZE - h ) / 2 - 2 };
		PgDrawText( GmValue, strlen(GmValue), &GmPos, 0 );
		}
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
			GmDrawTile( &GmCanvas, e_board[x + y * LINE_SIZE], x, y );

	/* Draw game score and final screen */
	// draw_final()

	PtClipRemove( );
	}
