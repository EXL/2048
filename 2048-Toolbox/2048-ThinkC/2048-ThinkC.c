/*
 * Useful information and simple tutorial:
 * 	https://nondisplayable.ca/2018/05/23/what-think-c-doesnt-tell-you.html
 *
 * Offscreen drawing technique was copied from Flight Simulator demonstration program:
 * 	http://ftp.knoppix.nl/infomac/_Development/src/flight-simulator-20-c.hqx
 * 	Flight Simulator (c) Chris Moll, 1992, chris@carnival.lbl.gov
 */

#include "2048.h"

#include <MacHeaders>
#include <Constants.h>       /* For Macintosh keycodes. */

#include <stdio.h>           /* For sprintf() function. */

#define RSRC_ID              128
#define MENU_APPLE           128
#define MENU_GAME            129
#define MENU_TILE            130
#define MENU_ITEM_ABOUT      1
#define MENU_ITEM_RESET      1
#define MENU_ITEM_DRAWING    4
#define MENU_ITEM_QUIT       6
#define MENU_ITEM_ROUND      1
#define MENU_ITEM_RECT       2
#define TILE_SIZE            48
#define TILE_MARGIN          12
#define ROUND_RECT_RAD       20
#define OFFSET_SHADOW        2
#define STRING_SCORE_LENGTH  16
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

class Window : indirect {
	WindowPtr pWin;
	GrafPort  pOffScr;

	Rect rectScr;
	Rect rectWin;

	short qRoundRect;
	short qOffScreenDrawing;
public:
	Window(void);
	~Window(void);

	void SetFont(void);
	void InitOffScreenDrawing(void);

	void Drag(Point aPoint);
	void Select(void);
	void Close(Point aPoint);

	void Activate(void);
	void Update(void);
	void Damage(void);

	void OffScreenDraw(void);
	void InScreenDraw(void);

	void DrawTile(int aVal, int aX, int aY);
	void DrawFinal(void);
	void DrawEnd(int aW, int aH);

	short IsRoundRect(void);
	void SetRoundRect(short aRoundRect);
	short IsOffScreenDrawing(void);
	void SetOffScreenDrawing(short aOffScreenDrawing);
};

class Application : indirect {
	Window *pWindow;

	MenuHandle hAppleMenu;
	MenuHandle hGameMenu;
	MenuHandle hTileMenu;
public:
	Application(void);
	~Application(void);

	void InitMac(void);
	void SetUpMenus(void);
	void InitWindow(void);

	void Run(void);
	void AdjustMenus(void);

	void HandleEvents(void);
	void HandleMouse(EventRecord *aEvent);
	void HandleKeys(EventRecord *aEvent);
	void HandleMenus(long aSelect);
	void HandleAppleMenu(short aItem);
};

pascal void RestartProc(void) {
	SysBeep(60);
	ExitToShell();
}

Window::Window(void) {
	qRoundRect = qOffScreenDrawing = true;
	pWin = GetNewWindow(RSRC_ID, NULL, (void *) -1L);
	rectScr = screenBits.bounds;
	rectWin = pWin->portRect;
	SetPort(pWin);
	SetFont();
}

Window::~Window(void) {
	DisposeWindow(pWin);
}

void Window::SetFont(void) {
	int fontID;
	GetFNum("\pChicago", &fontID);
	TextFont(fontID);
}

void Window::InitOffScreenDrawing(void) {
	int bytes;
	Rect r;
	QDPtr space;

	r = pWin->portRect;
	r.bottom = r.bottom - r.top;
	r.top = 0;
	r.right = r.right - r.left;
	r.left = 0;

	OpenPort(&pOffScr);
	pOffScr.portRect = r;
	pOffScr.portBits.bounds = r;
	SetRectRgn(pOffScr.visRgn, 0, 0, r.right, r.bottom);
	SetRectRgn(pOffScr.clipRgn, 0, 0, r.right, r.bottom);

	bytes = ((r.right + 15) / 16) * 2;
	space = NewPtr((long) bytes * r.bottom);
	if (MemErr) {
		SysBeep(30);
		return;
	}

	pOffScr.portBits.rowBytes = bytes;
	pOffScr.portBits.baseAddr = space;
	SetPort(&pOffScr);
	EraseRect(&pOffScr.portRect);
}

void Window::Drag(Point aPoint) {
	DragWindow(pWin, aPoint, &rectScr);
}

void Window::Select(void) {
	SelectWindow(pWin);
}

void Window::Close(Point aPoint) {
	if (TrackGoAway(pWin, aPoint))
		ExitToShell();
}

void Window::Activate(void) {
	SetPort(pWin);
}

void Window::Update(void) {
	BeginUpdate(pWin);
	EraseRect(&rectWin);
	if (qOffScreenDrawing)
		OffScreenDraw();
	else
		InScreenDraw();
	EndUpdate(pWin);
}

void Window::Damage(void) {
	if (qOffScreenDrawing)
		OffScreenDraw();
	else
		InvalRect(&rectWin);
}

void Window::OffScreenDraw(void) {
	SetPort(&pOffScr);
	EraseRect(&rectWin);
	InScreenDraw();
	CopyBits(
		&pOffScr.portBits, &pWin->portBits,
		&pOffScr.portRect, &pWin->portRect,
		srcCopy, NULL
	);
	SetPort(pWin);
}

void Window::InScreenDraw(void) {
	int x, y;
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			DrawTile(e_board[x + y * LINE_SIZE], x, y);
	DrawFinal();
}

void Window::DrawTile(int aVal, int aX, int aY) {
	Rect rectTile;
	Rect rectShadow;
	Str15 strValue;
	const int i = OFFSET_COORD(aX);
	const int j = OFFSET_COORD(aY);

	SetRect(&rectTile, i, j, i + TILE_SIZE, j + TILE_SIZE);
	SetRect(
		&rectShadow,
		i + OFFSET_SHADOW, j + OFFSET_SHADOW,
		i + TILE_SIZE + OFFSET_SHADOW, j + TILE_SIZE + OFFSET_SHADOW
	);
	ForeColor(blackColor);
	PenSize(2, 2);
	EraseRect(&rectTile);
	EraseRect(&rectShadow);
	if (qRoundRect)
		PaintRoundRect(&rectShadow, ROUND_RECT_RAD, ROUND_RECT_RAD);
	else
		PaintRect(&rectShadow);

	if (aVal) {
		const short size =
			(aVal < 10) ? 30 : (aVal < 100) ? 24 : (aVal < 1000) ? 18 : 12;
		const short ii =
			(aVal < 10) ? 13 : (aVal < 100) ?  9 : (aVal < 1000) ?  7 :  8;
		const short jj =
			(aVal < 10) ? 34 : (aVal < 100) ? 33 : (aVal < 1000) ? 30 : 28;

		if (qRoundRect) {
			EraseRoundRect(&rectTile, ROUND_RECT_RAD, ROUND_RECT_RAD);
			FrameRoundRect(&rectTile, ROUND_RECT_RAD, ROUND_RECT_RAD);
		} else {
			EraseRect(&rectTile);
			FrameRect(&rectTile);
		}
		MoveTo(i + ii, j + jj);
		NumToString(aVal, strValue);
		TextSize(size);
		DrawString(strValue);
	}
}

void Window::DrawFinal(void) {
	char strScore[STRING_SCORE_LENGTH];
	const int w = rectWin.right - rectWin.left;
	const int h = rectWin.bottom - rectWin.top;
	const int o =
		(e_score < 10)    ? 52 :
		(e_score < 100)   ? 60 :
		(e_score < 1000)  ? 67 :
		(e_score < 10000) ? 75 :
		/* else */          84 ;

	if (e_win || e_lose)
		DrawEnd(w, h);
	sprintf(strScore, "Score: %d", e_score);
	TextSize(12);
	MoveTo(TILE_MARGIN, h - 10);
	DrawString("\pESC to Restart!");
	MoveTo(w - TILE_MARGIN - o, h - 10);
	DrawString(c2pstr(strScore)); /* C string to Pascal string. */
}

void Window::DrawEnd(int aW, int aH) {
	int i;
	Rect rectText;
	Rect rectStatus;

	SetRect(&rectText, 30, 100, 30 + 197, 100 + 50);
	SetRect(
		&rectStatus,
		TILE_MARGIN - 5, aH - 10 - 13,
		aW - TILE_MARGIN + 5, aH - 5
	);
	EraseRect(&rectText);
	FrameRect(&rectText);
	PenSize(1, 1);
	for (i = 0; i < aW; i += 2) {
		MoveTo(i, 0);
		LineTo(i, aH);
	}
	TextSize(30);
	MoveTo((e_win) ? 52 : 34, 135);
	DrawString((e_win) ? "\pYou Won!" : "\pGame Over!");
	PenSize(2, 2);
	EraseRect(&rectStatus);
	FrameRect(&rectStatus);
}

short Window::IsRoundRect(void) {
	return qRoundRect;
}

short Window::IsOffScreenDrawing(void) {
	return qOffScreenDrawing;
}

void Window::SetRoundRect(short aRoundRect) {
	qRoundRect = aRoundRect;
}

void Window::SetOffScreenDrawing(short aOffScreenDrawing) {
	qOffScreenDrawing = aOffScreenDrawing;
}

Application::Application(void) {
	e_init(kEscapeOrClear, kLeftCursor, kRightCursor, kUpCursor, kDownCursor);
	InitMac();
	SetUpMenus();
	InitWindow();
}

Application::~Application(void) {
	delete pWindow;
}

void Application::InitMac(void) {
	MaxApplZone();

	InitGraf(&thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(RestartProc);
	InitCursor();

	FlushEvents(everyEvent, 0);
	SetEventMask(everyEvent);
}

void Application::SetUpMenus(void) {
	InsertMenu(hAppleMenu = GetMenu(MENU_APPLE), 0);
	AddResMenu(hAppleMenu, 'DRVR');
	InsertMenu(hGameMenu = GetMenu(MENU_GAME), 0);
	InsertMenu(hTileMenu = GetMenu(MENU_TILE), hierMenu);

	DrawMenuBar();
}

void Application::InitWindow(void) {
	pWindow = new(Window);
	pWindow->InitOffScreenDrawing();
}

void Application::Run(void) {
	for (;;) {
		SystemTask();
		HiliteMenu(0);
		AdjustMenus();
		HandleEvents();
	}
}

void Application::AdjustMenus(void) {
	CheckItem(hTileMenu, MENU_ITEM_ROUND, pWindow->IsRoundRect());
	CheckItem(hTileMenu, MENU_ITEM_RECT, !pWindow->IsRoundRect());
	CheckItem(hGameMenu, MENU_ITEM_DRAWING, pWindow->IsOffScreenDrawing());
}

void Application::HandleEvents(void) {
	EventRecord event;
	if (GetNextEvent(everyEvent, &event)) {
		switch (event.what) {
			case mouseDown: {
				HandleMouse(&event);
				break;
			}
			case keyDown:
			case autoKey: {
				HandleKeys(&event);
				break;
			}
			case updateEvt: {
				pWindow->Update();
				break;
			}
			case activateEvt: {
				pWindow->Activate();
				break;
			}
		}
	}
}

void Application::HandleMouse(EventRecord *aEvent) {
	WindowPeek peek;
	const short where = FindWindow(aEvent->where, &peek);
	switch (where) {
		case inSysWindow: {
			SystemClick(aEvent, peek);
			break;
		}
		case inMenuBar: {
			HandleMenus(MenuSelect(aEvent->where));
			break;
		}
		case inDrag: {
			pWindow->Drag(aEvent->where);
			break;
		}
		case inContent: {
			pWindow->Select();
			break;
		}
		case inGoAway: {
			pWindow->Close(aEvent->where);
			break;
		}
	}
}

void Application::HandleKeys(EventRecord *aEvent) {
	const char key = aEvent->message & charCodeMask;
	if ((aEvent->modifiers & cmdKey) != 0)
		HandleMenus(MenuKey(key));
	else
		switch (key) {
			case 'r': { e_key(kEscapeOrClear); break; }
			case 'w': { e_key(kUpCursor); break; }
			case 'a': { e_key(kLeftCursor); break; }
			case 's': { e_key(kDownCursor); break; }
			case 'd': { e_key(kRightCursor); break; }
			default: { e_key((unsigned int) key); break; }
		}
	pWindow->Damage();
}

void Application::HandleMenus(long aSelect) {
	const short menu = HiWord(aSelect);
	const short item = LoWord(aSelect);
	switch (menu) {
		case MENU_APPLE: {
			if (item == MENU_ITEM_ABOUT) {
				Alert(RSRC_ID, NULL);
				break;
			}
			HandleAppleMenu(item);
			break;
		}
		case MENU_GAME: {
			switch (item) {
				case MENU_ITEM_RESET: {
					e_key(kEscapeOrClear);
					pWindow->Damage();
					break;
				}
				case MENU_ITEM_DRAWING: {
					pWindow->SetOffScreenDrawing(!pWindow->IsOffScreenDrawing());
					pWindow->Damage();
					break;
				}
				case MENU_ITEM_QUIT: {
					ExitToShell();
					break;
				}
			}
			break;
		}
		case MENU_TILE: {
			switch (item) {
				case MENU_ITEM_ROUND: {
					pWindow->SetRoundRect(true);
					break;
				}
				case MENU_ITEM_RECT: {
					pWindow->SetRoundRect(false);
					break;
				}
			}
			pWindow->Damage();
			break;
		}
	}
}

void Application::HandleAppleMenu(short aItem) {
	Str255 menuName;
	GrafPtr savePort;

	GetPort(&savePort);
	GetItem(hAppleMenu, aItem, menuName);
	OpenDeskAcc(menuName);
	SetPort(savePort);
}

int main(void) {
	Application *pApp = new(Application);
	pApp->Run();
	delete pApp;
	return 0;
}
