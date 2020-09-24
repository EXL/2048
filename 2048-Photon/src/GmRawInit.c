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
PtWidget_t *GmRawWidget = NULL;

char *GmFontNormal = NULL;
char *GmFontSmall = NULL;
char *GmFontMiddle = NULL;
char *GmFontLarge = NULL;

/* Static variables */
static char Helvetica14N[MAX_FONT_TAG];
static char Helvetica14B[MAX_FONT_TAG];
static char Helvetica18B[MAX_FONT_TAG];
static char Helvetica24B[MAX_FONT_TAG];
static char Helvetica14NA[MAX_FONT_TAG];
static char Helvetica14BA[MAX_FONT_TAG];
static char Helvetica18BA[MAX_FONT_TAG];
static char Helvetica24BA[MAX_FONT_TAG];

/* Static functions */
static void
GmFontsInit( void )

	{
	if( !PfGenerateFontName( "Helvetica", 0, 14, Helvetica14N ) )
		perror( "Unable to generate Helvectica 14, Normal font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_BOLD, 14, Helvetica14B ) )
		perror( "Unable to generate Helvectica 14, Bold font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_BOLD, 18, Helvetica18B ) )
		perror( "Unable to generate Helvectica 18, Bold font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_BOLD, 24, Helvetica24B ) )
		perror( "Unable to generate Helvectica 24, Bold font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_ANTIALIAS, 14, Helvetica14NA ) )
		perror( "Unable to generate Helvectica 14, Normal, Anti-aliased font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_BOLD | PF_STYLE_ANTIALIAS, 14, Helvetica14BA ) )
		perror( "Unable to generate Helvectica 14, Bold, Anti-aliased font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_BOLD | PF_STYLE_ANTIALIAS, 18, Helvetica18BA ) )
		perror( "Unable to generate Helvectica 18, Bold, Anti-aliased font!" );
	if( !PfGenerateFontName( "Helvetica", PF_STYLE_BOLD | PF_STYLE_ANTIALIAS, 24, Helvetica24BA ) )
		perror( "Unable to generate Helvectica 24, Bold, Anti-aliased font!" );
	}

/* Global functions */
void
GmFontsSetAntialias( int antialias )

	{
	if( antialias )
		{
		GmFontNormal = Helvetica14NA;
		GmFontSmall = Helvetica14BA;
		GmFontMiddle = Helvetica18BA;
		GmFontLarge = Helvetica24BA;
		}
	else
		{
		GmFontNormal = Helvetica14N;
		GmFontSmall = Helvetica14B;
		GmFontMiddle = Helvetica18B;
		GmFontLarge = Helvetica24B;
		}
	}

/* Callbacks */
int
GmRawInit( PtWidget_t *widget )

	{
	/* Save global Game Raw Widget pointer. */
	GmRawWidget = widget;

	/* Init Game Engine with Control Keys. */
	e_init( Pk_Escape, Pk_Left, Pk_Right, Pk_Up, Pk_Down );

	/* Init Game Fonts and enable anti-aliasing by default. */
	GmFontsInit( );
	GmFontsSetAntialias( 1 );

	return PtSuperClassInit( PtBasic, widget );
	}
