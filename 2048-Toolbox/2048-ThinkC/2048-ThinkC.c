#include "2048.h"

#include <MacHeaders>
#include <Constants.h>
#include <QDOffscreen.h>

#define RSRC 128
#define KIND 'GW'
#define MENU_APPLE 128
#define MENU_GAME 129
#define MENU_TILE 130
#define TILE_SIZE 48
#define TILE_MARGIN 12
#define OFFCOORD(coord) (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

static MenuHandle appleMenu, gameMenu, tileMenu;

static void InitAll(void);
static void SetUpMenus(void);
static void HandleEvents(void);
static void AdjustMenus(void);
static void HandleMenus(long select);
static void HandleMouseDown(EventRecord *theEvent);

class GameWindow;

static GameWindow *window;

static int roundRect = 1;

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
	short Update(void);
	short Draw(void);
	short DrawTile(int value, int x, int y);
	short DrawFinal(void);
	short Damage(void);
};

GameWindow::GameWindow(void) {
	int fID;
	theWindow = GetNewWindow(RSRC, NULL, (void *) -1L);
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
	delete this;
}

short GameWindow::Activate(short active) {
	DrawGrowIcon(theWindow);
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

short GameWindow::Update(void) {
	WindowPtr savePort;
	GetPort(&savePort);
	SetPort(theWindow);
	BeginUpdate(theWindow);
	Draw();
	EndUpdate(theWindow);
	SetPort(savePort);
	return 0;
}

short GameWindow::Damage(void) {
	InvalRect(&drag);
	return 0;
}

short GameWindow::Draw(void) {
	int x, y;
	
	// EraseRect(&drag);
	
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
	const int zOffset = 4;
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
		const short size = (value < 100) ? 20 : (value < 1000) ? 16 : 14;
	//	ForeColor(whiteColor);
			
		
		if (roundRect) {
			EraseRoundRect(&tileRect, 20, 20);
			FrameRoundRect(&tileRect, 20, 20);
		} else {
			EraseRect(&tileRect);
			FrameRect(&tileRect);
		}
	
		MoveTo(xOffset + 10, yOffset + 40);
		NumToString(value, strNum);
		
		TextSize(size);
		
		DrawString(strNum);
	}
	
	return 0;
}

short GameWindow::DrawFinal(void) {
	// Draw
	return 0;
}

static void InitAll(void) {
	MaxApplZone(); // ?
	
	InitGraf(&thePort);
	InitFonts();
	FlushEvents(everyEvent, 0);
	InitWindows();
	InitMenus();
	TEInit(); // ?
	InitDialogs(0L);
	InitCursor();
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
				else
					((GameWindow *)(((WindowPeek)wp)->refCon))->Update();
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
					((GameWindow *)(((WindowPeek)theEvent.message)->refCon))->Update();
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

int main(void) {
	e_init(kEscapeOrClear, kLeftCursor, kRightCursor, kUpCursor, kDownCursor);
	InitAll();
	SetUpMenus();
	window = new(GameWindow);

	for (;;)
		HandleEvents();
	
	return 0;
}
