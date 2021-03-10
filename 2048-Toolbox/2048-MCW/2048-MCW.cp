#include "2048.h"

#include <Devices.h>
#include <Dialogs.h>
#include <Events.h>
#include <Fonts.h>
#include <MacTypes.h>
#include <MacWindows.h>
#include <Menus.h>
#include <NumberFormatting.h>
#include <OSUtils.h>
#include <Processes.h>
#include <Quickdraw.h>
#include <QuickdrawText.h>
#include <Sound.h>
#include <TextEdit.h>
#include <ToolUtils.h>

#define RSRC_ID              128
#define MENU_APPLE           128
#define MENU_GAME            129
#define MENU_TILES           130
#define MENU_ITEM_ABOUT      1
#define MENU_ITEM_ROUND      1
#define MENU_ITEM_QD_GX      4
#define MENU_ITEM_QUIT       6
#define MENU_ITEM_RECT       2
#define MENU_ITEM_RESET      1
#define TILE_SIZE            64
#define TILE_MARGIN          16
#define ROUND_RECT_RAD       20
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

class Window {
	WindowPtr mWinPtr;

	Rect mRectScr;
	Rect mRectWin;

	bool qRoundRect;
	bool qQdGxMode;
public:
	Window(void) {
		qRoundRect = qQdGxMode = true;
		mWinPtr = GetNewCWindow(RSRC_ID, nil, (WindowPtr) -1L);
		mRectScr = qd.screenBits.bounds;
		mRectWin = mWinPtr->portRect;
	}
	~Window(void) {
		DisposeWindow(mWinPtr);
	}

	void SetFont(void) {
		// TODO: Chicago font here.
		TextFont(kFontIDGeneva);
		TextSize(20);
		TextMode(srcCopy);
	}

	void Drag(Point aPoint, WindowPtr aWinPtr) {
		if (mWinPtr == aWinPtr)
			DragWindow(mWinPtr, aPoint, &mRectScr);
	}
	void Select(WindowPtr aWinPtr) {
		if ((mWinPtr == aWinPtr) && (mWinPtr != FrontWindow()))
			SelectWindow(mWinPtr);
	}
	void Close(Point aPoint, WindowPtr aWinPtr) {
		if ((mWinPtr == aWinPtr) && TrackGoAway(mWinPtr, aPoint))
			ExitToShell();
	}

	void Activate(void) {
		SetPort(mWinPtr);
	}
	void Update(void) {
		BeginUpdate(mWinPtr);
		Draw();
		EndUpdate(mWinPtr);
	}
	void Damage(void) {
		InvalRect(&mRectWin);
	}

	void SetRoundRect(bool aRoundRect) {
		qRoundRect = aRoundRect;
	}
	bool IsRoundRect(void) const {
		return qRoundRect;
	}
	void SetQdGxMode(bool aQdGxMode) {
		qQdGxMode = aQdGxMode;
	}
	bool IsQdGxMode(void) const {
		return qQdGxMode;
	}

private:
	void Draw(void) {
		RGBColor lBackground;
		lBackground.red = 0xFFFF;
		RGBForeColor(&lBackground);

		PaintRect(&mRectWin);

		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				DrawTile(e_board[x + y * LINE_SIZE], x, y);
		DrawFinal();
	}
	void DrawTile(int aVal, int aX, int aY) {
		RGBColor lColorTile;
		Rect lRectTile;
		Str15 lStrValue;

		const int lX = OFFSET_COORD(aX);
		const int lY = OFFSET_COORD(aY);

		lColorTile.red = Random();
		lColorTile.blue = Random();
		lColorTile.green = Random();

		RGBForeColor(&lColorTile);

		SetRect(&lRectTile, lX, lY, lX + TILE_SIZE, lY + TILE_SIZE);
		PaintRoundRect(&lRectTile, ROUND_RECT_RAD, ROUND_RECT_RAD);

		if (aVal) {
			MoveTo(lX + 20, lY + 40);
			RGBBackColor(&lColorTile);
			InvertColor(&lColorTile);
			RGBForeColor(&lColorTile);

			NumToString(aVal, lStrValue);

			DrawString(lStrValue);
		}
	}
	void DrawFinal(void) {

	}
};

class Application {
	Window *mWindow;

	MenuHandle mMenuApple;
	MenuHandle mMenuGame;
	MenuHandle mMenuTiles;
public:
	Application(void) {
		e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	}
	~Application(void) {
		delete mWindow;
	}

	bool CheckColorMac(void) {
		SysEnvRec lEnvWorld;
		SysEnvirons(curSysEnvVers, &lEnvWorld);
		if (!lEnvWorld.hasColorQD) {
			SysBeep(30);
			return false;
		}
		return true;
	}
	void InitMac(void) {
		MaxApplZone();

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
	void InitMenuBar(void) {
		Handle lMenuBar = GetNewMBar(RSRC_ID);
		SetMenuBar(lMenuBar);
		DisposeHandle(lMenuBar);

		SetUpMenus();

		DrawMenuBar();
	}
	void InitWindow(void) {
		mWindow = new Window();
		mWindow->Activate();
		mWindow->SetFont();
	}
	void Run(void) {
		for (;;) {
			AdjustMenus();
			HandleEvents();
		}
	}
private:
	void SetUpMenus(void) {
		InsertMenu(mMenuApple = GetMenu(MENU_APPLE), 0);
		AppendResMenu(mMenuApple, 'DRVR');
		InsertMenu(mMenuGame = GetMenu(MENU_GAME), 0);
		InsertMenu(mMenuTiles = GetMenu(MENU_TILES), hierMenu);
	}
	void AdjustMenus(void) {
		HiliteMenu(0);

		CheckItem(mMenuTiles, MENU_ITEM_ROUND, mWindow->IsRoundRect());
		CheckItem(mMenuTiles, MENU_ITEM_RECT, !mWindow->IsRoundRect());
		CheckItem(mMenuGame, MENU_ITEM_QD_GX, mWindow->IsQdGxMode());
	}
	void HandleEvents(void) {
		EventRecord lEvent;
		if (WaitNextEvent(everyEvent, &lEvent, 0, nil)) {
			switch (lEvent.what) {
				case mouseDown:
					HandleMouse(&lEvent);
					break;
				case keyDown:
				case autoKey:
					HandleKeys(&lEvent);
					mWindow->Damage();
					break;
				case updateEvt:
					mWindow->Update();
					break;
				case activateEvt:
					mWindow->Activate();
					break;
			}
		}
	}
	void HandleMouse(const EventRecord *aEvent) {
		WindowPtr lWinPtr;
		const short lWhere = FindWindow(aEvent->where, &lWinPtr);
		switch (lWhere) {
			case inSysWindow:
				SystemClick(aEvent, lWinPtr);
				break;
			case inMenuBar:
				HandleMenus(MenuSelect(aEvent->where));
				break;
			case inDrag:
				mWindow->Drag(aEvent->where, lWinPtr);
				break;
			case inContent:
				mWindow->Select(lWinPtr);
				break;
			case inGoAway:
				mWindow->Close(aEvent->where, lWinPtr);
				break;
		}
	}
	void HandleKeys(const EventRecord *aEvent) {
		const char lKey = aEvent->message & charCodeMask;
		if ((aEvent->modifiers & cmdKey) != 0)
			HandleMenus(MenuKey(lKey));
		else
			switch (lKey) {
				case 'r': e_key(kEscapeCharCode);     break;
				case 'w': e_key(kUpArrowCharCode);    break;
				case 'a': e_key(kLeftArrowCharCode);  break;
				case 's': e_key(kDownArrowCharCode);  break;
				case 'd': e_key(kRightArrowCharCode); break;
				default : e_key((unsigned int) lKey); break;
			}
	}
	void HandleMenus(long aSelect) {
		const short lMenu = HiWord(aSelect);
		const short lItem = LoWord(aSelect);
		switch (lMenu) {
			case MENU_APPLE:
				if (lItem == MENU_ITEM_ABOUT)
					Alert(RSRC_ID, nil);
				else
					HandleAppleMenu(lItem);
				break;
			case MENU_GAME:
				switch (lItem) {
					case MENU_ITEM_RESET:
						e_key(kEscapeCharCode);
						mWindow->Damage();
						break;
					case MENU_ITEM_QD_GX:
						mWindow->SetQdGxMode(!mWindow->IsQdGxMode());
						mWindow->Damage();
						break;
					case MENU_ITEM_QUIT:
						ExitToShell();
						break;
				}
				break;
			case MENU_TILES:
				switch (lItem) {
					case MENU_ITEM_ROUND:
						mWindow->SetRoundRect(true);
						break;
					case MENU_ITEM_RECT:
						mWindow->SetRoundRect(false);
						break;
				}
				mWindow->Damage();
				break;
		}
	}
	void HandleAppleMenu(long aItem) {
		Str255 lMenuItemName;
		GetMenuItemText(mMenuApple, aItem, lMenuItemName);
		OpenDeskAcc(lMenuItemName);
	}
};

int main(void) {
	Application *app = new Application();
	if (app->CheckColorMac()) {
		app->InitMac();
		app->InitMenuBar();
		app->InitWindow();
		app->Run();
	}
	delete app;
	ExitToShell();
	return 0;
}
