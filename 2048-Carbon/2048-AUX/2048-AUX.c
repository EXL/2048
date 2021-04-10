#include "2048.h"

#include <events.h>
#include <types.h>
#include <windows.h>

#include <stdio.h>

#define RSRC_ID                 128

static void InitMac();
static void CreateWindow();
static void CreateOffScreen();
static void WinActivate();
static void WinUpdate();
static void WinDrag();
static void WinSelect();
static void WinClose();
static void Run();
static void AdjustMenus();
static void HandleEvents();
static void HandleMouse();
static void HandleMenus();
static void HandleKeys();
static void DeInit();

static WindowPtr gWinPtr = nil;
static Rect gRectScr;
static Rect gRectWin;

main() {
	// e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	InitMac();
	CreateWindow();
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

static void WinActivate(aWinPtr) WindowPtr aWinPtr; {
	SetPort(aWinPtr);
}

static void WinUpdate(aWinPtr) WindowPtr aWinPtr; {

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
				WinUpdate(gWinPtr);
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

static void DeInit() {
	DisposeWindow(gWinPtr);
}
