#include "2048.h"

#include <MacHeaders>

#define RSRC 128
#define KIND 'GW'
#define MENU_APPLE 128
#define MENU_GAME 129
#define MENU_TILE 130

static MenuHandle appleMenu, gameMenu, tileMenu;

static void InitAll(void);
static void SetUpMenus(void);
static void HandleEvents(void);
static void AdjustMenus(void);
static void HandleMenus(long select);
static void HandleMouseDown(EventRecord *theEvent);

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
};

GameWindow::GameWindow(void) {
	theWindow = GetNewWindow(RSRC, NULL, (void *) -1L);
	drag = screenBits.bounds;
	((WindowPeek)theWindow)->windowKind = KIND;
	SetWRefCon(theWindow, (long)this);
	SetPort(theWindow);
	ShowWindow(theWindow);
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

short GameWindow::Draw(void) {
	EraseRect(&drag);
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
	
	DrawMenuBar();
}

static void AdjustMenus(void) {
	// check mark here	
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
					// e_key(reset);
					break;
				}
				case 2: {
					InsertMenu(tileMenu = GetMenu(MENU_TILE), 0);
					break;
				}
				/* case 3: */ // Separator.
				case 4: {
					ExitToShell();
					break;
				}
			}
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
	// AdjustMenus();
	
	if (GetNextEvent(everyEvent, &theEvent)) {
		switch (theEvent.what) {
			case mouseDown: {
				HandleMouseDown(&theEvent);
				break;
			}
			case keyDown:
			case autoKey: {
				if ((theEvent.modifiers & cmdKey) != 0)
					HandleMenus(MenuKey((char)(theEvent.message & charCodeMask)));
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
	// e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	InitAll();
	SetUpMenus();
	
	new(GameWindow);

	for (;;)
		HandleEvents();
	
	return 0;
}