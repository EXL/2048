#include "2048.h"

#include <events.h>
#include <quickdraw.h>
#include <types.h>
#include <windows.h>

#include <sys/crtctl.h>

#include <stdio.h>

#define RSRC_ID                 128

static void InitMac();
static void CreateWindow();
static void SetFont();
static Boolean CreateOffScreen();
static void WinActivate();
static void WinUpdate();
static void WinDamage();
static void WinDrag();
static void WinSelect();
static void WinClose();
static void OffScreenDraw();
static void InScreenDraw();
static void Run();
static void AdjustMenus();
static void HandleEvents();
static void HandleMouse();
static void HandleMenus();
static void HandleKeys();
static void DestroyOffscreen();
static void DeInit();

static WindowPtr gWinPtr = nil;
static CGrafPtr gCGrafPtr = nil;
static Rect gRectScr;
static Rect gRectWin;

main() {
	e_init(ESC, CLE, CRI, CUP, CDN);
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

	lOffBaseAddr = NewPtr((unsigned long) lBytesPerRow * (aRectWin->bottom - aRectWin->top + 1));
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

static void SetFont() {
	short lFontID;
	GetFNum("\pChicago", &lFontID);
	TextFont(lFontID);
}

static void WinActivate(aWinPtr) WindowPtr aWinPtr; {
	SetPort(aWinPtr);
}

static void WinUpdate(aWinPtr) WindowPtr aWinPtr; {
	BeginUpdate(gWinPtr);

	if (gWinPtr == FrontWindow())
		OffScreenDraw();
	else
		InScreenDraw();

	EndUpdate(gWinPtr);
}

static void WinDamage() {
	// TODO: Off
	// InvalRect(&gRectWin);
	OffScreenDraw();
}

static void WinDrag(aPoint, aWinPtr) Point aPoint; WindowPtr aWinPtr; {
	if (gWinPtr == aWinPtr)
		DragWindow(gWinPtr, aPoint, &gRectScr);
}

static void WinSelect(aWinPtr) WindowPtr aWinPtr; {
	if ((gWinPtr == aWinPtr) && ! (gWinPtr != FrontWindow()))
		SelectWindow(gWinPtr);
}

static void WinClose(aPoint, aWinPtr) Point aPoint; WindowPtr aWinPtr; {
	if ((gWinPtr == aWinPtr) && TrackGoAway(gWinPtr, aPoint))
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
	RGBColor color;
	color.red = 0xFFFF;
	color.green = 0x0000;
	color.blue = 0x0000;
	RGBBackColor(&color);
	EraseRect(&gRectWin);
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

}

static void DestroyOffscreen(aCGrafPtr) CGrafPtr aCGrafPtr; {
	DisposPtr((*aCGrafPtr->portPixMap)->baseAddr);
	DisposHandle((Handle) (*aCGrafPtr->portPixMap)->pmTable);
	CloseCPort(aCGrafPtr);
	DisposPtr((Ptr) aCGrafPtr);
}

static void DeInit() {
	DestroyOffscreen(gCGrafPtr);
	DisposeWindow(gWinPtr);
}
