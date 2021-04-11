#include "2048.h"

#include <events.h>
#include <quickdraw.h>
#include <types.h>
#include <windows.h>

#include <stdio.h>

#define RSRC_ID              128
#define TILE_SIZE            64
#define TILE_MARGIN          16
#define ROUND_RECT_RAD       20
#define STRING_SCORE_LENGTH  16
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)
#define WW(rect)             (rect.right - rect.left)
#define HH(rect)             (rect.bottom - rect.top)

static void InitMac();
static void CreateWindow();
static void SetFont();
static Boolean CreateOffScreen();
static void DestroyOffscreen();
static void WinActivate();
static void WinFocus();
static void WinUpdate();
static void WinDamage();
static void WinDrag();
static void WinSelect();
static void WinClose();
static void OffScreenDraw();
static void InScreenDraw();
static void DrawTile();
static void DrawFinal();
static void DrawEnd();
static void GetRgbColor();
static void Run();
static void AdjustMenus();
static void HandleEvents();
static void HandleMouse();
static void HandleMenus();
static void HandleKeys();
static void DeInit();

static WindowPtr gWinPtr = nil;
static CGrafPtr gCGrafPtr = nil;
static Rect gRectScr;
static Rect gRectWin;

static Boolean gInBackground = false;
static Boolean gColorTiles = true;
static Boolean gRoundRect = true;

main() {
	e_init(27, 28, 29, 30, 31);
	//e_init(ESC, CLE, CRI, CUP, CDN);
	//e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	InitMac();
	CreateWindow();
	SetFont();
	if (!CreateOffScreen(&gCGrafPtr, &gRectWin)) {
		fprintf(stderr, "ERROR: Cannot create offscreen pixmap!\n");
		fprintf(stderr, "ERROR: Check memory limits in settings.\n");
		SysBeep(30);
		ExitToShell();
	}
	SetFont();
	Run();
	DeInit();
}

static void InitMac() {
	InitGraf(&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();

	FlushEvents(everyEvent, 0);
	SetEventMask(everyEvent);
}

static void CreateWindow() {
	gWinPtr = GetNewCWindow(RSRC_ID, nil, (WindowPtr) -1L);
	gRectScr = qd.screenBits.bounds;
	gRectWin = gWinPtr->portRect;
	WinActivate(gWinPtr);
}

// Offscreen initialization and deinitialization functions were copied from Ravel FTN 2.0:
// https://github.com/mcyril/ravel-ftn/blob/master/Ravel%202.0%20%C6%92/RavelQUILL%202.0%20%C6%92/Source%20%C6%92/DialogLib.c
static Boolean CreateOffScreen(aCGrafPtr, aRectWin) CGrafPtr *aCGrafPtr; Rect *aRectWin; {
	GrafPtr lSavePort;
	CGrafPtr lNewPort;
	PixMapHandle lPixMap;
	Ptr lOffBaseAddr;
	unsigned short lBytesPerRow, lTemp;
	GDHandle lMainDevice;
	CTabHandle lCTable;
	short lDepth;

	GetPort(&lSavePort);
	lNewPort = (CGrafPtr) NewPtr(sizeof(CGrafPort));
	if (MemError() != noErr)
		return false;
	OpenCPort(lNewPort);
	lNewPort->portRect = *aRectWin;
	lPixMap = lNewPort->portPixMap;
	lMainDevice = GetMainDevice();
	lDepth = (**(**lMainDevice).gdPMap).pixelSize;
	lCTable = (**(**lMainDevice).gdPMap).pmTable;
	HandToHand((Handle *) &lCTable);
	lTemp = ((unsigned short) lDepth) * (aRectWin->right - aRectWin->left); // TODO: replace with macro?
	lTemp = (lTemp + 31) / 32;
	lBytesPerRow = lTemp * 4;
	(*lPixMap)->rowBytes = lBytesPerRow | 0x8000;
	(*lPixMap)->bounds = *aRectWin;
	(*lPixMap)->pmVersion = 0;
	(*lPixMap)->packType = 0;
	(*lPixMap)->packSize = 0;
	(*lPixMap)->hRes = 0x00480000;
	(*lPixMap)->vRes = 0x00480000;
	(*lPixMap)->pixelSize = lDepth;
	(*lPixMap)->planeBytes = 0;
	(*lPixMap)->pmReserved = 0;
	(*lPixMap)->pixelType = 0;
	(*lPixMap)->cmpCount = 1;
	(*lPixMap)->cmpSize = lDepth;
	(*lPixMap)->pmTable = lCTable;

	lOffBaseAddr = (Ptr) NewPtr((unsigned long) lBytesPerRow * (aRectWin->bottom - aRectWin->top + 1)); // TODO: replace with macro?
	(*lPixMap)->baseAddr = lOffBaseAddr;
	if (MemError() != noErr) {
		DisposHandle((Handle) (*lPixMap)->pmTable);
		SetPort(lSavePort);
		CloseCPort(lNewPort);
		DisposPtr((Ptr) lNewPort);
		return false;
	}
	RectRgn(lNewPort->clipRgn, aRectWin);
	RectRgn(lNewPort->visRgn, aRectWin);
	EraseRect(aRectWin);
	*aCGrafPtr = lNewPort;
	SetPort(lSavePort);
	return true;
}

static void DestroyOffscreen(aCGrafPtr) CGrafPtr aCGrafPtr; {
	DisposPtr((*aCGrafPtr->portPixMap)->baseAddr);
	DisposHandle((Handle) (*aCGrafPtr->portPixMap)->pmTable);
	CloseCPort(aCGrafPtr);
	DisposPtr((Ptr) aCGrafPtr);
}

static void SetFont() {
	short lFontID;
	GetFNum("\pChicago", &lFontID);
	TextFont(lFontID);
}

static void WinActivate(aWinPtr) WindowPtr aWinPtr; {
	SetPort(aWinPtr);
}

static void WinFocus(aMessage) long aMessage; {
	if (aMessage >> 24)
		gInBackground = !(aMessage & 0x01);
}

static void WinUpdate(aWinPtr) WindowPtr aWinPtr; {
	BeginUpdate(aWinPtr);

	if (!gInBackground)
		OffScreenDraw();
	else
		InScreenDraw();

	EndUpdate(aWinPtr);
}

static void WinDamage() {
	// OffScreenDraw();
	InvalRect(&gRectWin);
}

static void WinDrag(aPoint, aWinPtr) Point aPoint; WindowPtr aWinPtr; {
	if (gWinPtr == aWinPtr)
		DragWindow(aWinPtr, aPoint, &gRectScr);
}

static void WinSelect(aWinPtr) WindowPtr aWinPtr; {
	if ((gWinPtr == aWinPtr) && gInBackground)
		SelectWindow(aWinPtr);
}

static void WinClose(aPoint, aWinPtr) Point aPoint; WindowPtr aWinPtr; {
	if ((gWinPtr == aWinPtr) && TrackGoAway(aWinPtr, aPoint))
		ExitToShell();
}

static void OffScreenDraw() {
	SetPort((GrafPtr) gCGrafPtr);

	InScreenDraw();
	CopyBits(
		&((GrafPtr) gCGrafPtr)->portBits, &gWinPtr->portBits,
		&gRectWin, &gRectWin,
		srcCopy, nil
	);

	SetPort(gWinPtr);
}

static void InScreenDraw() {
	int y, x;
	RGBColor lColorBoard;
	GetRgbColor(COLOR_BOARD, &lColorBoard);
	RGBBackColor(&lColorBoard);
	EraseRect(&gRectWin);
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			DrawTile(e_board[x + y * LINE_SIZE], x, y);
	DrawFinal();
}

static void DrawTile(aVal, aX, aY) int aVal; int aX; int aY; {
	Rect lRectTile;
	RGBColor lColorTile, lColorText;
	int lX = OFFSET_COORD(aX);
	int lY = OFFSET_COORD(aY);
	GetRgbColor(e_background(aVal), &lColorTile);
	GetRgbColor(e_foreground(aVal), &lColorText);
	RGBForeColor(&lColorTile);
	SetRect(&lRectTile, lX, lY, lX + TILE_SIZE, lY + TILE_SIZE);

	if (gRoundRect)
		PaintRoundRect(&lRectTile, ROUND_RECT_RAD, ROUND_RECT_RAD);
	else
		PaintRect(&lRectTile);

	if (aVal) {
		int llX, llY;
		Str15 lStrValue;
		short lSize = (aVal < 10) ? 34 : (aVal < 100) ? 28 : (aVal < 1000) ? 26 : 22;
		TextFace(bold);
		TextSize(lSize);
		RGBBackColor(&lColorTile);
		RGBForeColor(&lColorText);
		NumToString(aVal, lStrValue);
		llX = StringWidth(lStrValue);
		llY = lSize - 4;
		MoveTo(lX + (TILE_SIZE - llX - 1) / 2, lY + TILE_SIZE - (TILE_SIZE - llY) / 2 - 2);
		DrawString(lStrValue);
	}
}

static void DrawFinal() {
	char lStrScore[STRING_SCORE_LENGTH];
	unsigned char *lStrScorePascal;
	int lX;
	RGBColor lColorText;
	GetRgbColor(COLOR_TEXT, &lColorText);

	if (e_win || e_lose)
		DrawEnd();
	else
		RGBForeColor(&lColorText);

	TextFace(normal);
	TextSize(18);
	MoveTo(TILE_MARGIN, HH(gRectWin) - TILE_MARGIN);
	DrawString("\pESC to Restart!");
	sprintf(lStrScore, "Score: %d", e_score);
	lStrScorePascal = (unsigned char *) c2pstr(lStrScore);
	lX = StringWidth(lStrScorePascal);
	MoveTo(WW(gRectWin) - lX - TILE_MARGIN, HH(gRectWin) - TILE_MARGIN);
	DrawString(lStrScorePascal);
}

static void DrawEnd() {
	int lX;
	RGBColor lColorOverlay, lColorFinal;
	PenState lPenState;
	unsigned char *lStrFinal = (unsigned char *) ((e_win) ? "\pYou Won!" : "\pGame Over!");
	GetRgbColor(COLOR_OVERLAY, &lColorOverlay);
	GetRgbColor(COLOR_FINAL, &lColorFinal);

	RGBBackColor(&lColorOverlay);
	RGBForeColor(&lColorFinal);
	GetPenState(&lPenState);
	PenPat(qd.gray);
	PenMode(patBic);
	PaintRect(&gRectWin);
	SetPenState(&lPenState);

	TextSize(34);
	lX = StringWidth(lStrFinal);
	MoveTo(WW(gRectWin) / 2 - lX / 2, HH(gRectWin) / 2);
	DrawString(lStrFinal);
}

static void GetRgbColor(aRgb, aColor) unsigned BIG aRgb; RGBColor *aColor; {
	// Not sure about the endianness (byte order). M68K and PPC are big-endian (BE).
	// Why colors use `short` in range 0x0000-0xFFFF? Is the last byte in 0xFF00 in use?
	// More information: https://stackoverflow.com/a/12043639
	RGBColor lColor;
	unsigned char red8   = (unsigned char) ((aRgb & 0xFF0000) >> 16);
	unsigned char green8 = (unsigned char) ((aRgb & 0x00FF00) >> 8);
	unsigned char blue8  = (unsigned char) ((aRgb & 0x0000FF) >> 0);
	lColor.red   = ((unsigned short) red8 << 8) | red8;
	lColor.green = ((unsigned short) green8 << 8) | green8;
	lColor.blue  = ((unsigned short) blue8 << 8) | blue8;
	*aColor = lColor;
}

static void Run() {
	for (;;) {
		AdjustMenus();
		HandleEvents();
	}
}

static void AdjustMenus() {

}

static void HandleEvents() {
	EventRecord lEvent;
	if (WaitNextEvent(everyEvent, &lEvent, 0, nil)) {
		switch (lEvent.what) {
			case mouseDown:
				HandleMouse(&lEvent);
				break;
			case keyDown:
			case autoKey:
				HandleKeys(&lEvent);
				WinDamage();
				break;
			case updateEvt:
				WinUpdate(gWinPtr);
				break;
			case activateEvt:
				WinActivate(gWinPtr);
				break;
			case app4Evt:
				WinFocus(lEvent.message);
				break;
		}
	}
}

static void HandleMouse(aEvent) EventRecord *aEvent; {
	WindowPtr lWinPtr;
	short lWinPart = FindWindow(aEvent->where, &lWinPtr);
	switch (lWinPart) {
		case inSysWindow:
			SystemClick(aEvent, lWinPtr);
			break;
		case inMenuBar:
			HandleMenus(MenuSelect(aEvent->where));
			break;
		case inDrag:
			WinDrag(aEvent->where, lWinPtr);
			break;
		case inContent:
			WinSelect(lWinPtr);
			break;
		case inGoAway:
			WinClose(aEvent->where, lWinPtr);
			break;
	}
}

static void HandleMenus(aSelect) long aSelect; {

}

static void HandleKeys(aEvent) EventRecord *aEvent; {
	char lKey = aEvent->message & charCodeMask;
	if ((aEvent->modifiers & cmdKey) != 0)
		HandleMenus(MenuKey(lKey));
	else
		e_key((int) lKey);
}

static void DeInit() {
	DestroyOffscreen(gCGrafPtr);
	DisposeWindow(gWinPtr);
}
