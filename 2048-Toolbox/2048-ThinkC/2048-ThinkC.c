#include "2048.h"

#include <MacHeaders>
#include <Constants.h>

#include <stdio.h>

#define RSRC 128
#define KIND 'GW'
#define MENU_APPLE 128
#define MENU_GAME 129
#define MENU_TILE 130
#define TILE_SIZE 48
#define TILE_MARGIN 12
#define OFFCOORD(coord) (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

static MenuHandle appleMenu, gameMenu, tileMenu;

pascal void restartProc(void);
static void InitAll(void);
static void SetUpMenus(void);
static void HandleEvents(void);
static void AdjustMenus(void);
static void HandleMenus(long select);
static void HandleMouseDown(EventRecord *theEvent);
static void MakeOffScreen(void);

class GameWindow;

static GrafPtr wmPort;
static GameWindow *window;
static WindowPtr windowPtr;
static GrafPort offPort;

static int roundRect = 1;
static int offScreenDrawing = 1;

/* Make Offscreen drawing fucntion by Chris Moll: chris@carnival.lbl.gov */
/* Copied from Flight Simulator demonstration program: */
/* 	http://ftp.knoppix.nl/infomac/_Development/src/flight-simulator-20-c.hqx */
static void MakeOffScreen(void) {
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

class GameWindow : indirect {
	Rect drag;
	WindowPtr theWindow;

public:
	GameWindow(void);
	~GameWindow(void);

	short Activate(short active);
	short Select(void);
	short TrackClose(Point where);
	short Drag(Point where);
	short Update(EventRecord *event);
	short Draw(void);
	short DrawTile(int value, int x, int y);
	short DrawFinal(void);
	short Damage(void);
	short OffScreenDrawing(void);
};

GameWindow::GameWindow(void) {
	int fID;
	theWindow = GetNewWindow(RSRC, NULL, (void *) -1L);
	windowPtr = theWindow;
	drag = screenBits.bounds;
	((WindowPeek)theWindow)->windowKind = KIND;
	SetWRefCon(theWindow, (long)this);
	SetPort(theWindow);
	ShowWindow(theWindow);

	GetFNum("\pChicago", &fID);

	TextFont(fID);
//	TextFace(bold);
//	TextMode(NoSrcCopy);
}

GameWindow::~GameWindow(void) {
	DisposeWindow(theWindow);
}

short GameWindow::Activate(short active) {
	//DrawGrowIcon(theWindow);
	if (active)
		SetPort(theWindow);
	return 0;
}

short GameWindow::Select(void) {
	SelectWindow(theWindow);
	return 0;
}

short GameWindow::TrackClose(Point where) {
	if (TrackGoAway(theWindow, where))
		ExitToShell();
	return 0;
}

short GameWindow::Drag(Point where) {
	DragWindow(theWindow, where, &drag);
	return 0;
}

short GameWindow::Update(EventRecord *event) {
	GrafPtr savePort;
	WindowPtr whichWindow;
	whichWindow = (WindowPtr) event->message;
	BeginUpdate(whichWindow);
	GetPort(&savePort);
	SetPort(whichWindow);
	if (whichWindow == windowPtr) {
		EraseRect(&whichWindow->portRect);
		if (offScreenDrawing)
			OffScreenDrawing();
		else
			Draw();
	}
	EndUpdate(whichWindow);
	SetPort(savePort);
	return 0;
}

short GameWindow::Damage(void) {
	if (offScreenDrawing) {
		OffScreenDrawing();
	} else {
		InvalRect(&drag);
	}
	return 0;
}

short GameWindow::OffScreenDrawing(void) {
	SetPort(&offPort);
	EraseRect(&thePort->portRect);
	Draw();
	CopyBits(
		&offPort.portBits,
		&windowPtr->portBits,
		&offPort.portRect,
		&windowPtr->portRect,
		srcCopy,
		0L
	);
	SetPort(windowPtr);
}

short GameWindow::Draw(void) {
	int x, y;

	EraseRect(&thePort->portRect);

	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			DrawTile(e_board[x + y * LINE_SIZE], x, y);
	DrawFinal();

	return 0;
}

short GameWindow::DrawTile(int value, int x, int y) {
	Rect tileRect;
	Rect tileShadowRect;
	Str15 strNum;
	const int xOffset = OFFCOORD(x);
	const int yOffset = OFFCOORD(y);
	const int zOffset = 2;
	//RGBColor fgColor;

	SetRect(&tileRect, xOffset, yOffset, xOffset + TILE_SIZE, yOffset + TILE_SIZE);
	SetRect(&tileShadowRect, xOffset + zOffset,
	yOffset + zOffset, xOffset + TILE_SIZE + zOffset,
	yOffset + TILE_SIZE + zOffset);

	ForeColor(blackColor);

	PenSize(2, 2);

	EraseRect(&tileRect);
	EraseRect(&tileShadowRect);

	if (roundRect)
		PaintRoundRect(&tileShadowRect, 20, 20);
	else
		PaintRect(&tileShadowRect);

	if (value) {
		const short size =
			(value < 10) ? 30 : (value < 100) ? 24 : (value < 1000) ? 18 : 12;
		const short xO =
			(value < 10) ? 13 : (value < 100) ? 8 : (value < 1000) ? 7 : 8;
		const short yO =
			(value < 10) ? 34 : (value < 100) ? 33 : (value < 1000) ? 30 : 28;

		if (roundRect) {
			EraseRoundRect(&tileRect, 20, 20);
			FrameRoundRect(&tileRect, 20, 20);
		} else {
			EraseRect(&tileRect);
			FrameRect(&tileRect);
		}

		MoveTo(xOffset + xO, yOffset + yO);
		NumToString(value, strNum);

		TextSize(size);

		DrawString(strNum);
	}

	return 0;
}

short GameWindow::DrawFinal(void) {
	char strScore[16];
	const int height = theWindow->portRect.bottom - theWindow->portRect.top;
	const int width = theWindow->portRect.right - theWindow->portRect.left;
	const int w =
		(e_score < 10) ? 52 :
		(e_score < 100) ? 60 :
		(e_score < 1000) ? 67 :
		(e_score < 10000) ? 75 : 84;

	if (e_win || e_lose) {
		Rect text;
		Rect scoreRect;
		int i;
		SetRect(&text, 30, 100, 30 + 197, 100 + 50);
		SetRect(&scoreRect,
			TILE_MARGIN - 5,
			height - 10 - 13,
			width - TILE_MARGIN + 5, height - 5);
		EraseRect(&text);
		FrameRect(&text);
		PenSize(1, 1);
		for (i = 0; i < width; i += 2) {
			MoveTo(i, 0);
			LineTo(i, height);
		}
		TextSize(30);
		MoveTo((e_win) ? 52 : 34, 135);
		DrawString((e_win) ? "\pYou Won!" : "\pGame Over!");
		EraseRect(&scoreRect);
		PenSize(2, 2);
		FrameRect(&scoreRect);
	}

	sprintf(strScore, "Score: %d", e_score);

	TextSize(12);

	MoveTo(TILE_MARGIN, height - 10);
	DrawString("\pESC to Restart!");

	MoveTo(width - TILE_MARGIN - w, height - 10);

	DrawString(c2pstr(strScore));

	return 0;
}

pascal void restartProc(void) {
	ExitToShell();
}

static void InitAll(void) {
	MaxApplZone(); // ?

	InitGraf(&thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit(); // ?
	InitDialogs(restartProc);
	InitCursor();

	FlushEvents(everyEvent, 0);
	GetWMgrPort(&wmPort);
	SetPort(wmPort);
	SetEventMask(everyEvent);
}

static void SetUpMenus(void) {
	InsertMenu(appleMenu = GetMenu(MENU_APPLE), 0);
	AddResMenu(appleMenu, 'DRVR');
	InsertMenu(gameMenu = GetMenu(MENU_GAME), 0);
	InsertMenu(tileMenu = GetMenu(MENU_TILE), hierMenu);

	DrawMenuBar();
}

static void AdjustMenus(void) {
	// check mark here
	if (roundRect) {
		CheckItem(tileMenu, 1, true);
		CheckItem(tileMenu, 2, false);
	} else {
		CheckItem(tileMenu, 1, false);
		CheckItem(tileMenu, 2, true);
	}
	if (offScreenDrawing)
		CheckItem(gameMenu, 4, true);
	else
		CheckItem(gameMenu, 4, false);
}

static void HandleMenus(long select) {
	short menuId = HiWord(select);
	short menuItem = LoWord(select);
	Str255 menuName;
	GrafPtr savePort;

	switch (menuId) {
		case MENU_APPLE: {
			if (menuItem == 1) {
				Alert(128, 0L);
				break;
			}
			GetPort(&savePort);
			GetItem(appleMenu, menuItem, menuName);
			OpenDeskAcc(menuName);
			SetPort(savePort);
			break;
		}
		case MENU_GAME: {
			switch (menuItem) {
				case 1: {
					e_key(kEscapeOrClear);
					window->Damage();
					break;
				}
//				case 2: {
//					//InsertMenu(tileMenu = GetMenu(MENU_TILE), 0);
//					break;
//				}
				/* case 3: */ // Separator.
				case 4: {
					offScreenDrawing = !offScreenDrawing;
					window->Damage();
					break;
				}
				case 6: {
					ExitToShell();
					break;
				}
			}
			break;
		}
		case MENU_TILE: {
			switch (menuItem) {
				case 1: {
					roundRect = 1;
					break;
				}
				case 2: {
					roundRect = 0;
					break;
				}
			}
			window->Damage();
			break;
		}
	}
}

static void HandleMouseDown(EventRecord *theEvent) {
	WindowPeek wp;
	const short windowPart = FindWindow(theEvent->where, &wp);
	switch (windowPart) {
		case inSysWindow: {
			SystemClick(theEvent, wp);
			break;
		}
		case inMenuBar: {
			HandleMenus(MenuSelect(theEvent->where));
			break;
		}
		case inDrag: {
			if (wp->windowKind == KIND)
				((GameWindow *)(((WindowPeek)wp)->refCon))->Drag(theEvent->where);
			break;
		}
		case inContent: {
			if (wp->windowKind == KIND)
				if (wp != (WindowPeek)FrontWindow())
					((GameWindow *)(((WindowPeek)wp)->refCon))->Select();
				//else
				//	((GameWindow *)(((WindowPeek)wp)->refCon))->Update(theEvent);
			break;
		}
		case inGoAway: {
			if (wp->windowKind == KIND)
				((GameWindow *)(((WindowPeek)wp)->refCon))->TrackClose(theEvent->where);
			break;
		}
	}
}

static void HandleEvents(void) {
	EventRecord theEvent;

	HiliteMenu(0); // ?
	SystemTask(); // ?
	AdjustMenus();

	if (GetNextEvent(everyEvent, &theEvent)) {
		switch (theEvent.what) {
			case mouseDown: {
				HandleMouseDown(&theEvent);
				break;
			}
			case keyDown:
			case autoKey: {
				unsigned int theChar = theEvent.message & charCodeMask;
				if ((theEvent.modifiers & cmdKey) != 0)
					HandleMenus(MenuKey((char)(theEvent.message & charCodeMask)));
				else
					e_key(theChar);
				window->Damage();
				break;
			}
			case updateEvt: {
				if (((WindowPeek)theEvent.message)->windowKind == KIND)
					((GameWindow *)(((WindowPeek)theEvent.message)->refCon))->Update(&theEvent);
				break;
			}
			case activateEvt: {
				if (((WindowPeek)theEvent.message)->windowKind == KIND)
					((GameWindow *)(((WindowPeek)theEvent.message)->refCon))->Activate(theEvent.modifiers & 0x01);
				break;
			}
		}
	}
}


/* Tutorial:
 * https://nondisplayable.ca/2018/05/23/what-think-c-doesnt-tell-you.html */
int main(void) {
	e_init(kEscapeOrClear, kLeftCursor, kRightCursor, kUpCursor, kDownCursor);
	InitAll();
	SetUpMenus();
	window = new(GameWindow);
	MakeOffScreen();

	for (;;)
		HandleEvents();

	delete window;

	return 0;
}
