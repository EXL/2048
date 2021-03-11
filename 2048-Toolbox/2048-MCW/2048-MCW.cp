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
#include <QDOffscreen.h>
#include <Sound.h>
#include <TextEdit.h>
#include <ToolUtils.h>

#include <stdio.h>

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
#define STRING_SCORE_LENGTH  16
#define PATTERN_BACKGROUND   1
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

class Window {
	WindowPtr mWinPtr;
	GWorldPtr mOffScr;

	Rect mRectScr;
	Rect mRectWin;

	bool qRoundRect;
	bool qQdGxMode;

	Pattern mPattern;
public:
	Window(void) {
		qRoundRect = qQdGxMode = true;

		mWinPtr = GetNewCWindow(RSRC_ID, nil, (WindowPtr) -1L);
		mRectScr = qd.screenBits.bounds;
		mRectWin = mWinPtr->portRect;

		GetIndPattern(&mPattern, RSRC_ID, PATTERN_BACKGROUND);
	}
	~Window(void) {
		DisposeGWorld(mOffScr);
		DisposeWindow(mWinPtr);
	}

	void SetOffScreen(void) {
		OSErr lError = NewGWorld(&mOffScr, 0, &mRectWin, nil, nil, 0L);
		if (lError) {
			SysBeep(60);
			ExitToShell();
		}
		LockPixels(GetGWorldPixMap(mOffScr));
		SetGWorld((CGrafPtr) mOffScr, nil);
	}
	void SetFont(void) {
		short lFontID;
		GetFNum("\pCharcoal", &lFontID);
		TextFont(lFontID);
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

		SetGWorld((CGrafPtr) mOffScr, nil);

		Draw();

		SetGWorld((CGrafPtr) mWinPtr, GetMainDevice());

		CopyBits(
			&((GrafPtr) mOffScr)->portBits, &((GrafPtr) mWinPtr)->portBits,
			&mOffScr->portRect, &mWinPtr->portRect,
			srcCopy, nil
		);

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
		RGBBackColor(&GetRgbColor(COLOR_BOARD));
		EraseRect(&mRectWin);
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				DrawTile(e_board[x + y * LINE_SIZE], x, y);
		DrawFinal();
	}
	void DrawTile(int aVal, int aX, int aY) {
		const RGBColor lColorTile = GetRgbColor(e_background(aVal));
		RGBForeColor(&lColorTile);
		Rect lRectTile;
		const int lX = OFFSET_COORD(aX);
		const int lY = OFFSET_COORD(aY);
		SetRect(&lRectTile, lX, lY, lX + TILE_SIZE, lY + TILE_SIZE);

		if (qRoundRect)
			PaintRoundRect(&lRectTile, ROUND_RECT_RAD, ROUND_RECT_RAD);
		else
			PaintRect(&lRectTile);

		if (aVal) {
			const short size = (aVal < 10) ? 34 : (aVal < 100) ? 28 : (aVal < 1000) ? 26 : 22;
			TextFace(bold);
			TextSize(size);
			RGBBackColor(&lColorTile);
			RGBForeColor(&GetRgbColor(e_foreground(aVal)));
			Str15 lStrValue;
			NumToString(aVal, lStrValue);
			const int llX = StringWidth(lStrValue);
			const int llY = size - 4;
			MoveTo(lX + (TILE_SIZE - llX - 1) / 2, lY + TILE_SIZE - (TILE_SIZE - llY) / 2 - 2);
			DrawString(lStrValue);
		}
	}
	void DrawFinal(void) {
		const int lW = mRectWin.right - mRectWin.left;
		const int lH = mRectWin.bottom - mRectWin.top;

		if (e_win || e_lose)
			DrawEnd(lW, lH);
		else
			RGBForeColor(&GetRgbColor(COLOR_TEXT));

		TextFace(normal);
		TextSize(18);
		MoveTo(TILE_MARGIN, lH - TILE_MARGIN);
		DrawString("\pESC to Restart!");
		char strScore[STRING_SCORE_LENGTH];
		sprintf(strScore, "Score: %d", e_score);
		const int lX = StringWidth(c2pstr(strScore));
		MoveTo(lW - lX - TILE_MARGIN, lH - TILE_MARGIN);
		DrawString((const unsigned char *) strScore);
	}
	void DrawEnd(int aW, int aH) {
		RGBBackColor(&GetRgbColor(COLOR_OVERLAY));
		RGBForeColor(&GetRgbColor(COLOR_FINAL));
		PenState lPenState;
		GetPenState(&lPenState);
		PenPat(&mPattern);
		PenMode(patBic);
		PaintRect(&mRectWin);
		SetPenState(&lPenState);

		const unsigned char * lStrFinal = (e_win) ? "\pYou Won!" : "\pGame Over";
		TextSize(34);
		const int lX = StringWidth(lStrFinal);
		MoveTo(aW / 2 - lX / 2, aH / 2);
		DrawString(lStrFinal);
	}

	RGBColor GetRgbColor(unsigned BIG aRgb) const {
		// Not sure about the endianness (byte order). M68K and PPC are big-endian (BE).
		// Why colors use `short` in range 0x0000-0xFFFF? Is the last byte in 0xFF00 in use?
		RGBColor lColor;
		lColor.red   = ((aRgb >> 16) & 0xFF) << 8;
		lColor.green = ((aRgb >> 8)  & 0xFF) << 8;
		lColor.blue  = ((aRgb >> 0)  & 0xFF) << 8;
		return lColor;
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
		mWindow->SetOffScreen();
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
