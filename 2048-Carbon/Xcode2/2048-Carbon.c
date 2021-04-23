//
//  main.c
//  2048-Carbon
//
//  Created by EXL on 4/20/21.
//  Copyright © EXL, 2021. All rights reserved.
//

#include <Carbon/Carbon.h>

#include "2048.h"

#define MENU_ITEM_ROUND      1
#define MENU_ITEM_RECT       2
#define HIVIEW_ID            130
#define HIVIEW_SIGNATURE     'mVue'
#define TILE_SIZE            64
#define TILE_MARGIN          16
#define STR_VALUE_SIZE       5
#define STR_SCORE_SIZE       16
#define R(color)             (((color >> 16) & 0xFF) / 255.0)
#define G(color)             (((color >> 8)  & 0xFF) / 255.0)
#define B(color)             (((color >> 0)  & 0xFF) / 255.0)
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

static OSStatus AppEventHandler(EventHandlerCallRef inCaller, EventRef inEvent, void *inRefcon);
static OSStatus HandleNew();
static OSStatus WindowEventHandler(EventHandlerCallRef inCaller, EventRef inEvent, void *inRefcon);
static void MenuTilesUpdate(MenuRef menuRef);
static void HandleDraw(EventRef eventRef, void *userData);
static void HandleKeyboard(EventRef eventRef);
static void DrawTile(CGContextRef context, int value, int x, int y);
static void DrawFinal(CGContextRef context, const CGRect *bounds);
static float GetTextWidth(CGContextRef context, const char *str);

static IBNibRef sNibRef = NULL;
static HIViewRef sContentView = NULL;
static Boolean sRoundRectangle = true;

//--------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	OSStatus err;
	static const EventTypeSpec kAppEvents[] = { { kEventClassCommand, kEventCommandProcess } };

	e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);

	err = CreateNibReference(CFSTR("2048-Carbon"), &sNibRef);
	require_noerr(err, CantGetNibRef);

	err = SetMenuBarFromNib(sNibRef, CFSTR("MenuBar"));
	require_noerr(err, CantSetMenuBar);

	InstallApplicationEventHandler(NewEventHandlerUPP(AppEventHandler),
		GetEventTypeCount(kAppEvents), kAppEvents, 0, NULL);

	HandleNew();

	RunApplicationEventLoop();

CantSetMenuBar:
CantGetNibRef:
	return err;
}

//--------------------------------------------------------------------------------------------
static OSStatus AppEventHandler(EventHandlerCallRef inCaller, EventRef inEvent, void *inRefcon) {
	OSStatus result = eventNotHandledErr;
	switch (GetEventClass(inEvent)) {
		case kEventClassCommand: {
			HICommandExtended cmd;
			verify_noerr(GetEventParameter(inEvent, kEventParamDirectObject,
				typeHICommand, NULL, sizeof(cmd), NULL, &cmd));
			switch (GetEventKind(inEvent)) {
				case kEventCommandProcess:
					switch (cmd.commandID) {
						case kHICommandNew:
							result = HandleNew();
							break;
						case 'RSET': // Reset Menu Item.
							e_key(kEscapeCharCode);
							break;
						case 'ROND': // Rounded Menu Item.
							sRoundRectangle = true;
							MenuTilesUpdate(cmd.source.menu.menuRef);
							break;
						case 'RECT': // Rectangle Menu Item.
							sRoundRectangle = false;
							MenuTilesUpdate(cmd.source.menu.menuRef);
							break;
					}
					HIViewSetNeedsDisplay(sContentView, true);
					break;
			}
			break;
		}
	}
	return result;
}

//--------------------------------------------------------------------------------------------
DEFINE_ONE_SHOT_HANDLER_GETTER(WindowEventHandler)

//--------------------------------------------------------------------------------------------
static OSStatus HandleNew() {
	OSStatus err;
	WindowRef windowRef;
	static const HIViewID viewID = { HIVIEW_SIGNATURE, HIVIEW_ID };
	static const EventTypeSpec kWindowEvents[] = {
		{ kEventClassKeyboard, kEventRawKeyDown },
		{ kEventClassKeyboard, kEventRawKeyRepeat },
		{ kEventClassWindow, kEventWindowClosed }
	};
	static const EventTypeSpec kControlEvents[] = { { kEventClassControl, kEventControlDraw } };

	err = CreateWindowFromNib(sNibRef, CFSTR("GameWindow"), &windowRef);
	require_noerr(err, CantCreateWindow);

	err = InstallWindowEventHandler(windowRef, GetWindowEventHandlerUPP(), GetEventTypeCount(kWindowEvents),
		kWindowEvents, windowRef, NULL);
	require_noerr(err, CantInstallWindowEventHandler);

	err = HIViewFindByID(HIViewGetRoot(windowRef), viewID, &sContentView);
	require_noerr(err, CantHIViewFindByID);

	err = InstallControlEventHandler(sContentView, GetWindowEventHandlerUPP(), GetEventTypeCount(kControlEvents),
		kControlEvents, sContentView, NULL);
	require_noerr(err, CantInstallControlEventHandler);

	ShowWindow(windowRef);

CantCreateWindow:
CantInstallWindowEventHandler:
CantHIViewFindByID:
CantInstallControlEventHandler:
	return err;
}

//--------------------------------------------------------------------------------------------
static OSStatus WindowEventHandler(EventHandlerCallRef inCaller, EventRef inEvent, void *inRefcon) {
	OSStatus err = eventNotHandledErr;
	switch (GetEventClass(inEvent)) {
		case kEventClassKeyboard:
			switch (GetEventKind(inEvent)) {
				case kEventRawKeyDown:
				case kEventRawKeyRepeat:
					HandleKeyboard(inEvent);
					HIViewSetNeedsDisplay(sContentView, true);
					break;
			}
			break;
		case kEventClassWindow:
			if (GetEventKind(inEvent) == kEventWindowClosed)
				QuitApplicationEventLoop();
			break;
		case kEventClassControl:
			if (GetEventKind(inEvent) == kEventControlDraw)
				HandleDraw(inEvent, inRefcon);
			break;
	}
	return err;
}

//--------------------------------------------------------------------------------------------
static void MenuTilesUpdate(MenuRef menuRef) {
	CheckMenuItem(menuRef, MENU_ITEM_ROUND, sRoundRectangle);
	CheckMenuItem(menuRef, MENU_ITEM_RECT, !sRoundRectangle);
}

//--------------------------------------------------------------------------------------------
static void HandleKeyboard(EventRef eventRef) {
	char keyCode;
	GetEventParameter(eventRef, kEventParamKeyMacCharCodes, typeChar, NULL, sizeof(char), NULL, &keyCode);
	switch (keyCode) {
		case 'w': e_key(kUpArrowCharCode);    break;
		case 's': e_key(kDownArrowCharCode);  break;
		case 'a': e_key(kLeftArrowCharCode);  break;
		case 'd': e_key(kRightArrowCharCode); break;
		case 'r': e_key(kEscapeCharCode);     break;
		default : e_key((int) keyCode);       break;
	}
}

//--------------------------------------------------------------------------------------------
static float GetTextWidth(CGContextRef context, const char *str) {
	// Q: How to measure CG text?
	// A: https://mirror.informatimago.com/next/developer.apple.com/qa/qa2001/qa1051.html
	CGContextSetTextDrawingMode(context, kCGTextInvisible);
	const CGPoint start = CGContextGetTextPosition(context);
	CGContextShowTextAtPoint(context, start.x, start.y, str, strlen(str));
	const CGPoint end = CGContextGetTextPosition(context);
	CGContextSetTextDrawingMode(context, kCGTextFill);
	return end.x - start.x;
}

//--------------------------------------------------------------------------------------------
static void HandleDraw(EventRef eventRef, void *userData) {
	int y, x;
	CGContextRef context;
	GetEventParameter(eventRef, kEventParamCGContextRef, typeCGContextRef, NULL, sizeof(context), NULL, &context);

	CGRect bounds;
	HIViewGetBounds((HIViewRef) userData, &bounds);

	CGContextSetRGBFillColor(context, R(COLOR_BOARD), G(COLOR_BOARD), B(COLOR_BOARD), 1.0f);
	CGContextFillRect(context, bounds);
	CGContextSetTextMatrix(context, CGAffineTransformMakeScale(1.0f, -1.0f));
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			DrawTile(context, e_board[x + y * LINE_SIZE], x, y);
	DrawFinal(context, &bounds);
}

//--------------------------------------------------------------------------------------------
static void DrawTile(CGContextRef context, /*const CGRect *bounds,*/ int value, int x, int y) {
	const int lX = OFFSET_COORD(x), lY = OFFSET_COORD(y);
	const CGRect tile = CGRectMake(lX, lY, TILE_SIZE, TILE_SIZE);
	const unsigned int bkg = e_background(value), frg = e_foreground(value);
	CGContextSetRGBFillColor(context, R(bkg), G(bkg), B(bkg), 1.0f);
	// Q: How to draw a rounded rectangle in Core Graphics/Quartz 2D?
	// A: https://stackoverflow.com/a/2835659
	if (sRoundRectangle) {
		const float radius = 10.0f;
		const float minx = CGRectGetMinX(tile), midx = CGRectGetMidX(tile), maxx = CGRectGetMaxX(tile);
		const float miny = CGRectGetMinY(tile), midy = CGRectGetMidY(tile), maxy = CGRectGetMaxY(tile);
		CGContextMoveToPoint(context, minx, midy);
		CGContextAddArcToPoint(context, minx, miny, midx, miny, radius);
		CGContextAddArcToPoint(context, maxx, miny, maxx, midy, radius);
		CGContextAddArcToPoint(context, maxx, maxy, midx, maxy, radius);
		CGContextAddArcToPoint(context, minx, maxy, minx, midy, radius);
		CGContextClosePath(context);
		CGContextFillPath(context);
	}
	else
		CGContextFillRect(context, tile);

	if (value) {
		char strValue[STR_VALUE_SIZE] = { '\0' };
		snprintf(strValue, STR_VALUE_SIZE, "%d", value);
		const float size = (value < 10) ? 34.0f : (value < 100) ? 28.0f : (value < 1000) ? 26.0f : 22.0f;
		CGContextSetRGBFillColor(context, R(frg), G(frg), B(frg), 1.0f);
		CGContextSelectFont(context, "Helvetica Bold", size, kCGEncodingMacRoman);
		const float llX = GetTextWidth(context, strValue);
		const float llY = size - 4;
		CGContextShowTextAtPoint(context, lX + (TILE_SIZE - llX - 1) / 2, lY + TILE_SIZE - (TILE_SIZE - llY) / 2 - 3,
			strValue, strlen(strValue));
	}
}

//--------------------------------------------------------------------------------------------
static void DrawFinal(CGContextRef context, const CGRect *bounds) {
	if (e_win || e_lose) {
		const char *strFinal = (e_win) ? "You Won!" : "Game Over!";
		CGContextSetRGBFillColor(context, R(COLOR_OVERLAY), G(COLOR_OVERLAY), B(COLOR_OVERLAY), 0.5f);
		CGContextFillRect(context, *bounds);
		CGContextSetRGBFillColor(context, R(COLOR_FINAL), G(COLOR_FINAL), B(COLOR_FINAL), 1.0f);
		CGContextSelectFont(context, "Helvetica Bold", 34.0f, kCGEncodingMacRoman);
		const float lX = GetTextWidth(context, strFinal);
		CGContextShowTextAtPoint(context, bounds->size.width / 2 - lX / 2, bounds->size.height / 2,
			strFinal, strlen(strFinal));
	}
	char strScore[STR_SCORE_SIZE] = { '\0' };
	const char *strEscape = "ESC to Restart!";
	snprintf(strScore, STR_SCORE_SIZE, "Score: %d", e_score);
	CGContextSetRGBFillColor(context, R(COLOR_TEXT), G(COLOR_TEXT), B(COLOR_TEXT), 1.0f);
	CGContextSelectFont(context, "Helvetica", 18.0f, kCGEncodingMacRoman);
	const float lX = GetTextWidth(context, strScore);
	CGContextShowTextAtPoint(context, TILE_MARGIN, bounds->size.height - TILE_MARGIN, strEscape, strlen(strEscape));
	CGContextShowTextAtPoint(context, bounds->size.width - lX - TILE_MARGIN, bounds->size.height - TILE_MARGIN,
		strScore, strlen(strScore));
}
