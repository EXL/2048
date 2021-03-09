#include "2048.h"

#include <stdio.h>
#include <string.h>

#include <Types.h>
//#include <Memory.h>
#include <Quickdraw.h>
#include <Fonts.h>
#include <Events.h>
#include <Menus.h>
#include <Windows.h>
//#include <TextEdit.h>
#include <Dialogs.h>
//#include <OSUtils.h>
//#include <ToolUtils.h>
//#include <SegLoad.h>
//#include <Sound.h>
//#include <Processes.h>

#define	WIN_WIDTH      340
#define	WIN_HEIGHT     400
#define WIN_LEFT       (((qd.screenBits.bounds.right - qd.screenBits.bounds.left) - WIN_WIDTH) / 2)
#define WIN_TOP        (((qd.screenBits.bounds.bottom - qd.screenBits.bounds.top) - WIN_HEIGHT) / 2)
#define TILE_SIZE      64
#define TILE_MARGIN    16
#define OFFCOORD(coord) (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN) 
#define NUM_SIZE       5

void                   checkColorMac(void);
void                   initAll(void);
void                   createWindow(void);
void                   doEventLoop(void);
void                   drawAll(void);
void                   drawTile(int value, int x, int y);
void                   drawFinal(void);
const unsigned char *  c_string_to_pascal_string(char *c_string);

void main(void) {
	e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	
	checkColorMac();
	initAll();
	createWindow();
	doEventLoop();
}

void checkColorMac(void) {
	OSErr error;
	SysEnvRec theWorld;

	//
	//	Test the computer to be sure we can do color.  
	//	If not we would crash, which would be bad.  
	//	If we canÕt run, just beep and exit.
	//

	error = SysEnvirons(1, &theWorld);
	if (theWorld.hasColorQD == false) {
		SysBeep(50);
		ExitToShell();					/* If no color QD, we must leave. */
	}
}

void initAll(void) {
//	MaxApplZone(); // ?
	InitGraf(&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	//TEInit(); // ?
	InitDialogs(nil);
	InitCursor(); // ?
	FlushEvents(0, everyEvent);
	// InitRoutineDescriptors(); // ?
}

void createWindow(void) {
	Rect rect;
	WindowPtr window;
	
	SetRect(&rect, WIN_LEFT, WIN_TOP, WIN_LEFT + WIN_WIDTH, WIN_TOP + WIN_HEIGHT);
	window = NewCWindow(0L, &rect, "\p2048-Toolbox", true, documentProc, (WindowPtr)-1L, true, 0L);
	SetPort(window);
	
	/// ?
	TextFont(kFontIDGeneva);
	TextSize(20);
	TextMode(srcCopy);
}

void doEventLoop(void) {
	EventRecord event;
	WindowPtr window;
	short clickArea;
	Rect screenRect;
	
	for (;;) {
		if (WaitNextEvent(everyEvent, &event, 0, nil)) {
			switch (event.what) {
				case mouseDown: {
					clickArea = FindWindow(event.where, &window);
					if (clickArea == inDrag) {
						screenRect = (**GetGrayRgn()).rgnBBox;
						DragWindow(window, event.where, &screenRect);
					} else if (clickArea == inContent) {
						if (window != FrontWindow())
							SelectWindow(window);
					} else if (clickArea == inGoAway) {
						if (TrackGoAway(window, event.where))
							return;
					}
					break;
				}
				case updateEvt: {
					window = (WindowPtr)event.message;
					SetPort(window);
					BeginUpdate(window);
					drawAll();
					EndUpdate(window);
					break;
				}
				case keyDown:
				case autoKey: {
					e_key(event.message & charCodeMask);
					InvalRect(&window->portRect);
					break;
				}
			}
		}
	}
}

void drawAll(void) {
	int x, y;
	
	RGBColor background;
	background.red = 0xFFFF;
	
	RGBForeColor(&background);
	
	PaintRect(&qd.thePort->portRect);
	
	// Fill screen

	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			drawTile(e_board[x + y * LINE_SIZE], x, y);
	drawFinal();
}

void drawTile(int value, int x, int y) {
		RGBColor tileColor;
		Rect tileRect;
		char num[5];
		
		const int xOffset = OFFCOORD(x);
		const int yOffset = OFFCOORD(y);
		
		tileColor.red = Random();
		tileColor.blue = Random();
		tileColor.green = Random();
		
		RGBForeColor(&tileColor);
		
		SetRect(&tileRect, xOffset, yOffset, xOffset + TILE_SIZE, yOffset + TILE_SIZE);
		//MoveTo(xOffset, yOffset);
		PaintRoundRect(&tileRect, 20, 20);

		if (value) {		
			MoveTo(xOffset + 10, yOffset + 40);
			RGBBackColor(&tileColor);
			InvertColor(&tileColor);
			RGBForeColor(&tileColor);
			
			snprintf(num, 5, "%d", value);
			
			/* Use c2pstr function instead. */
			// DrawString(c_string_to_pascal_string(num));
			DrawString(c2pstr(num));
		}
}

void drawFinal(void) {
	//kDeleteCharCode;
}

// http://www6.uniovi.es/cscene/CS5/CS5-04.html
const unsigned char * c_string_to_pascal_string(char *c_string) {
	int i, length = strlen(c_string);
	if (length > 255)
		length = 255;
	for (i = 1; i <= length; ++i)
		c_string[i] = c_string[i - 1];
	c_string[0] = length;
	return (const unsigned char *) c_string;
}
