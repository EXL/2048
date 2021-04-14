#include "2048.h"

#include <events.h>
#include <quickdraw.h>
#include <menus.h>
#include <types.h>
#include <windows.h>

#include <stdio.h>

#define K_ESCAPE             0x1B
#define K_LEFT               0x1C
#define K_RIGHT              0x1D
#define K_UP                 0x1E
#define K_DOWN               0x1F

#define MAIN_WINDOW          128
#define MENU_APPLE           128
#define MENU_GAME            129
#define MENU_TILES           130
#define MENU_COLOR           131
#define MENU_ITEM_ABOUT      1
#define MENU_ITEM_RESET      1
#define MENU_ITEM_ROUND      1
#define MENU_ITEM_RECT       2
#define MENU_ITEM_BW         1
#define MENU_ITEM_COLORS     2
#define MENU_ITEM_QUIT       5
#define TILE_SIZE            64
#define TILE_MARGIN          16
#define ROUND_RECT_RAD       20
#define STRING_SCORE_LENGTH  16
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)
#define WW(rect)             (rect.right - rect.left)
#define HH(rect)             (rect.bottom - rect.top)

static void InitMac();
static void SetUpMenus();
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
static void HandleAppleMenu();
static void HandleKeys();
static void DeInit();

static WindowPtr gWinPtr = nil;
static CGrafPtr gCGrafPtr = nil;
static Rect gRectScr;
static Rect gRectWin;

static Boolean gInBackground = false;
static Boolean gColorTiles = true;
static Boolean gRoundRect = true;
static Boolean gRunning = true;

static MenuHandle gMenuApple;
static MenuHandle gMenuGame;
static MenuHandle gMenuTiles;
static MenuHandle gMenuColor;

main() {
	e_init(K_ESCAPE, K_LEFT, K_RIGHT, K_UP, K_DOWN);
	InitMac();
	SetUpMenus();
	CreateWindow();
	if (!CreateOffScreen(&gCGrafPtr, &gRectWin)) {
		fprintf(stderr, "ERROR: Cannot create offscreen pixmap!\n");
		fprintf(stderr, "ERROR: Check memory limits in settings.\n");
		SysBeep(30);
		ExitToShell();
	}
	WinActivate(gWinPtr);
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

static void SetUpMenus() {
	InsertMenu(gMenuApple = GetMenu(MENU_APPLE), 0);
	AddResMenu(gMenuApple, 'DRVR');
	InsertMenu(gMenuGame = GetMenu(MENU_GAME), 0);
	InsertMenu(gMenuTiles = GetMenu(MENU_TILES), hierMenu);
	InsertMenu(gMenuColor = GetMenu(MENU_COLOR), hierMenu);

	DrawMenuBar();
}

static void CreateWindow() {
	gWinPtr = GetNewCWindow(MAIN_WINDOW, nil, (WindowPtr) -1L);
	gRectScr = qd.screenBits.bounds;
	gRectWin = gWinPtr->portRect;
}

/* Offscreen initialization function was copied from GlyphaIVOld project: */
/* https://github.com/fruitsamples/GlyphaIVOld/blob/master/G4Utilities.c  */
static Boolean CreateOffScreen(aCGrafPtr, aRectWin) CGrafPtr *aCGrafPtr; Rect *aRectWin; {
	CTabHandle lColorTable;
	GDHandle lOldGDevice, lGDevice;
	Ptr lBits;
	long lSizeOfOff, lOffRowBytes;
	OSErr lErr;
	short lDepth;
	CGrafPtr lNewCGrafPtr = 0L;
	Rect lRectWin;

	lRectWin = *aRectWin;
	lOldGDevice = GetGDevice();
	lGDevice = (GDHandle) GetMainDevice();
	SetGDevice(lGDevice);
	lNewCGrafPtr = (CGrafPtr) NewPtr(sizeof(CGrafPort));
	if (lNewCGrafPtr != 0L) {
		OpenCPort(lNewCGrafPtr);
		lDepth = (**(*lNewCGrafPtr).portPixMap).pixelSize;
		lOffRowBytes = ((((long) lDepth * (long) WW(lRectWin)) + 15L) >> 4L) << 1L;
		lSizeOfOff = (long) HH(lRectWin) * lOffRowBytes;
		OffsetRect(&lRectWin, -(lRectWin.left), -(lRectWin.top));
		lBits = (Ptr) NewPtr(lSizeOfOff);
		if (lBits != 0L) {
			(**(*lNewCGrafPtr).portPixMap).baseAddr = lBits;
			(**(*lNewCGrafPtr).portPixMap).rowBytes = (short) lOffRowBytes + 0x8000;
			(**(*lNewCGrafPtr).portPixMap).bounds = lRectWin;
			lColorTable = (**(**lGDevice).gdPMap).pmTable;
			lErr = HandToHand((Handle *) &lColorTable);
			(**(*lNewCGrafPtr).portPixMap).pmTable = lColorTable;
			ClipRect(&lRectWin);
			RectRgn(lNewCGrafPtr->visRgn, &lRectWin);
			ForeColor(blackColor);
			BackColor(whiteColor);
			EraseRect(&lRectWin);
		} else {
			CloseCPort(lNewCGrafPtr);
			DisposPtr((Ptr) lNewCGrafPtr);
			lNewCGrafPtr = 0L;
			return false;
		}
	}
	else
		return false;

	if (lDepth < 8)
		gColorTiles = false;

	*aCGrafPtr = lNewCGrafPtr;
	SetGDevice(lOldGDevice);
	return true;
}

/* Offscreen deinitialization function was copied from Ravel FTN 2.0: */
/* https://github.com/mcyril/ravel-ftn/blob/master/Ravel%202.0%20%C6%92/RavelQUILL%202.0%20%C6%92/Source%20%C6%92/DialogLib.c */
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

	OffScreenDraw();

	EndUpdate(aWinPtr);
}

static void WinDamage() {
	OffScreenDraw();
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
		gRunning = false;
}

static void OffScreenDraw() {
	SetPort((GrafPtr) gCGrafPtr);

	InScreenDraw();

	SetPort(gWinPtr);

	CopyBits(
		&((GrafPtr) gCGrafPtr)->portBits, &gWinPtr->portBits,
		&gRectWin, &gRectWin,
		srcCopy, nil
	);
}

static void InScreenDraw() {
	int y, x;
	RGBColor lColorBoard;
	GetRgbColor(COLOR_BOARD, &lColorBoard);
	if (gColorTiles)
		RGBBackColor(&lColorBoard);
	else
		BackColor((e_win || e_lose) ? blackColor : whiteColor);
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
	if (gColorTiles)
		RGBForeColor(&lColorTile);
	else
		ForeColor((e_win || e_lose) ? whiteColor : blackColor);
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
		if (gColorTiles)
			RGBForeColor(&lColorText);
		else
			ForeColor((e_win || e_lose) ? blackColor : whiteColor);
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
		if (gColorTiles)
			RGBForeColor(&lColorText);
		else
			ForeColor((e_win || e_lose) ? whiteColor : blackColor);

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

	if (gColorTiles) {
		RGBBackColor(&lColorOverlay);
		RGBForeColor(&lColorFinal);
	} else {
		BackColor(blackColor);
		ForeColor(whiteColor);
	}

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
	/* Not sure about the endianness (byte order). M68K and PPC are big-endian (BE).     */
	/* Why colors use `short` in range 0x0000-0xFFFF? Is the last byte in 0xFF00 in use? */
	/* More information: https://stackoverflow.com/a/12043639                            */
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
	for (;gRunning;) {
		AdjustMenus();
		HandleEvents();
	}
}

static void AdjustMenus() {
	HiliteMenu(0);

	CheckItem(gMenuTiles, MENU_ITEM_ROUND, gRoundRect);
	CheckItem(gMenuTiles, MENU_ITEM_RECT, !gRoundRect);
	CheckItem(gMenuColor, MENU_ITEM_BW, !gColorTiles);
	CheckItem(gMenuColor, MENU_ITEM_COLORS, gColorTiles);
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
	short lMenu = HiWord(aSelect);
	short lItem = LoWord(aSelect);
	switch (lMenu) {
		case MENU_APPLE:
			if (lItem == MENU_ITEM_ABOUT)
				NoteAlert(128, nil);
			else
				HandleAppleMenu(lItem);
			break;
		case MENU_GAME:
			switch (lItem) {
				case MENU_ITEM_RESET:
					e_key(K_ESCAPE);
					break;
				case MENU_ITEM_QUIT:
					gRunning = false;
					break;
			}
			break;
		case MENU_TILES:
			switch (lItem) {
				case MENU_ITEM_ROUND:
					gRoundRect = true;
					break;
				case MENU_ITEM_RECT:
					gRoundRect = false;
					break;
			}
			break;
		case MENU_COLOR:
			switch (lItem) {
				case MENU_ITEM_BW:
					gColorTiles = false;
					break;
				case MENU_ITEM_COLORS:
					gColorTiles = true;
					break;
			}
			break;
	}
	WinDamage(gWinPtr);
}

static void HandleAppleMenu(aItem) long aItem; {
	Str255 lMenuItemName;
	GetItem(gMenuApple, aItem, lMenuItemName);
	OpenDeskAcc(lMenuItemName);
}

static void HandleKeys(aEvent) EventRecord *aEvent; {
	char lKey = aEvent->message & charCodeMask;
	if ((aEvent->modifiers & cmdKey) != 0)
		HandleMenus(MenuKey(lKey));
	else
		switch (lKey) {
			case 'r': e_key(K_ESCAPE);          break;
			case 'w': e_key(K_UP);              break;
			case 'a': e_key(K_LEFT);            break;
			case 's': e_key(K_DOWN);            break;
			case 'd': e_key(K_RIGHT);           break;
			default : e_key((int) lKey);        break;
		}
}

static void DeInit() {
	DestroyOffscreen(gCGrafPtr);
	DisposeWindow(gWinPtr);
}
