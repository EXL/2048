#include <MacHeaders>
#include <Constants.h>

static GrafPtr wmPort;
static GrafPort offPort;
static WindowPtr windowPtr;
static WindowRecord windowRec;

void MakeOffScreen() {
	Rect windRect;
	QDPtr newSpace;
	int rwBytes;

	windRect = windowPtr->portRect;
	windRect.bottom = windRect.bottom - windRect.top;
	windRect.top = 0;
	windRect.right = windRect.right - windRect.left;
	windRect.left = 0;

	OpenPort(&offPort);
	offPort.portRect = windRect;
	offPort.portBits.bounds = windRect;
	SetRectRgn(offPort.visRgn, 0, 0, windRect.right, windRect.bottom);
	SetRectRgn(offPort.clipRgn, 0, 0, windRect.right, windRect.bottom);

	rwBytes = ((windRect.right + 15) / 16) * 2;
	newSpace = NewPtr((long) rwBytes * windRect.bottom);
	if (MemErr)
		return;

	offPort.portBits.rowBytes = rwBytes;
	offPort.portBits.baseAddr = newSpace;
	SetPort(&offPort);
	EraseRect(&offPort.portRect);
}

void HandleMouseMove(Point *click) {
	while (StillDown()) {
		SetPort(&offPort);

		/* Drawing here! */
		EraseRect(&thePort->portRect); /* Comment this line just for fun. */
		MoveTo(click->h, click->v);
		LineTo(120, 120);

		CopyBits(
			&offPort.portBits,
			&windowPtr->portBits,
			&offPort.portRect,
			&windowPtr->portRect,
			srcCopy,
			0L
		);

		SetPort(windowPtr);
		GetMouse(click);
	}
}

void HandleContent(EventRecord *event, WindowPtr whichWindow) {
	Point localPt;
	if (whichWindow != FrontWindow())
		SelectWindow(whichWindow);
	else {
		localPt = event->where;
		GlobalToLocal(&localPt);
		HandleMouseMove(&localPt);
	}
}

void HandleMouseDown(EventRecord *event) {
	int thePart;
	WindowPtr whichWindow;
	thePart = FindWindow(event->where, &whichWindow);
	switch (thePart) {
		case inContent:
			HandleContent(event, whichWindow);
			break;
	}
}

void DoFirstDraw(void) {
	EraseRect(&thePort->portRect);
	MoveTo(20, 20);
	LineTo(120, 120);
}

void HandleUpdate(EventRecord *event) {
	GrafPtr savePort;
	WindowPtr whichWindow;
	whichWindow = (WindowPtr) event->message;

	BeginUpdate(whichWindow);
	GetPort(&savePort);
	SetPort(whichWindow);
	if (whichWindow == windowPtr) {
		EraseRect(&whichWindow->portRect);
		DoFirstDraw();
	}
	EndUpdate(whichWindow);
	SetPort(savePort);
}

void HandleActivate(EventRecord *event) {
	WindowPtr whichWindow;
	whichWindow = (WindowPtr) event->message;
	if (whichWindow == windowPtr)
		if (event->modifiers & activeFlag)
			SetPort(whichWindow);
}

void HandleEvent() {
	EventRecord event;
	if (GetNextEvent(everyEvent, &event)) {
		switch (event.what) {
			case mouseDown:
				HandleMouseDown(&event);
				break;
			case updateEvt:
				HandleUpdate(&event);
				break;
			case keyDown:
			case autoKey:
				if ((event.message & charCodeMask) == kEscapeOrClear)
					Alert(128, 0L);
				else
					ExitToShell();
				break;
			case activateEvt:
				HandleActivate(&event);
				break;
		}
	}
}

pascal void restartProc(void) {
	ExitToShell();
}

void InitAll(void) {
	InitGraf(&thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(restartProc);
	InitCursor();

	FlushEvents(everyEvent, 0);
	GetWMgrPort(&wmPort); /* Whole screen port that window manager uses. */
	SetPort(wmPort);
	SetEventMask(everyEvent);

	windowPtr = GetNewWindow(128, &windowRec, (WindowPtr) -1L);
	MakeOffScreen();
}

int main(void) {
	InitAll();
	for (;;) {
		SystemTask();
		HandleEvent();
	}
	return 0;
}
