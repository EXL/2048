#include "2048.h"

#if defined(__MACH__)        // Mac OS X
#include <Carbon/Carbon.h>
#else
#include <Carbon.h>
#endif

#include <stdio.h>

#define RSRC_ID              128
#define ALERT_ERR_BUFFER     130
#define MENU_APPLE           128
#define MENU_GAME            129
#define MENU_TILES           130
#define MENU_GAME_OS_X       131
#define MENU_ITEM_ABOUT      1
#define MENU_ITEM_RESET      1
#define MENU_ITEM_QUIT       4
#define MENU_ITEM_ROUND      1
#define MENU_ITEM_RECT       2
#define TILE_SIZE            64
#define TILE_MARGIN          16
#define ROUND_RECT_RAD       20
#define STRING_SCORE_LENGTH  16
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)
#define WW(rect)             (rect.right - rect.left)
#define HH(rect)             (rect.bottom - rect.top)

static pascal OSErr QuitAppleEventHandler(const AppleEvent *, AppleEvent *, UInt32) {
	ExitToShell();
	return noErr;
}

class Window {
	WindowPtr mWinPtr;
	GWorldPtr mOffScr;

	Rect mRectScr;
	Rect mRectWin;

	bool qRoundRect;
	bool qIsMacOS_X;

public:
	Window(bool aIsMacOS_X) {
		qRoundRect = true;
		qIsMacOS_X = aIsMacOS_X;

		mWinPtr = GetNewCWindow(RSRC_ID, nil, (WindowPtr) -1);
		BitMap lBitMapScr;
		GetQDGlobalsScreenBits(&lBitMapScr);
		mRectScr = lBitMapScr.bounds;
		GetPortBounds(GetWindowPort(mWinPtr), &mRectWin);
	}
	~Window(void) {
		DisposeGWorld(mOffScr);
		DisposeWindow(mWinPtr);
	}

	bool SetOffScreen(void) {
		OSErr lError = NewGWorld(&mOffScr, 0, &mRectWin, nil, nil, 0);
		if (lError) {
			Alert(ALERT_ERR_BUFFER, nil);
			return false;
		}
		LockPixels(GetGWorldPixMap(mOffScr));
		SetGWorld((CGrafPtr) mOffScr, nil);
		return true;
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
		SetPortWindowPort(mWinPtr);
	}
	void Update(void) {
		BeginUpdate(mWinPtr);

		SetGWorld(mOffScr, nil);

		Draw();

		SetGWorld(GetWindowPort(mWinPtr), GetMainDevice());
		Rect lRectOffScr;
		GetPortBounds(mOffScr, &lRectOffScr);
		CopyBits(
			GetPortBitMapForCopyBits(mOffScr), GetPortBitMapForCopyBits(GetWindowPort(mWinPtr)),
			&lRectOffScr, &mRectWin,
			srcCopy, nil
		);

		QDFlushPortBuffer(GetQDGlobalsThePort(), nil); // TODO: check this.

		EndUpdate(mWinPtr);
	}
	void Damage(void) {
		InvalWindowRect(mWinPtr, &mRectWin);
	}

	void SetRoundRect(bool aRoundRect) {
		qRoundRect = aRoundRect;
	}
	bool IsRoundRect(void) const {
		return qRoundRect;
	}

	Rect *GetRectScreen(void) {
		return &mRectScr;
	}

private:
	void Draw(void) {
		const RGBColor lColorBoard = GetRgbColor(COLOR_BOARD);
		RGBBackColor(&lColorBoard);
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
			const short lSize = (aVal < 10) ? 34 : (aVal < 100) ? 28 : (aVal < 1000) ? 26 : 22;
			TextFace(bold);
			TextSize(lSize);
			RGBBackColor(&lColorTile);
			const RGBColor lColorValue = GetRgbColor(e_foreground(aVal));
			RGBForeColor(&lColorValue);
			Str15 lStrValue;
			NumToString(aVal, lStrValue);
			const int llX = StringWidth(lStrValue);
			const int llY = lSize - 4;
			MoveTo(lX + (TILE_SIZE - llX - 1) / 2, lY + TILE_SIZE - (TILE_SIZE - llY) / 2 - 2);
			DrawString(lStrValue);
		}
	}
	void DrawFinal(void) {
		const RGBColor lColorText = GetRgbColor(COLOR_TEXT);
		if (e_win || e_lose)
			DrawEnd();
		else
			RGBForeColor(&lColorText);

		if (!qIsMacOS_X)
			TextFace(normal);
		TextSize(18);
		MoveTo(TILE_MARGIN, HH(mRectWin) - TILE_MARGIN);
		DrawString("\pESC to Restart!");
		char lStrScore[STRING_SCORE_LENGTH];
		sprintf(lStrScore, "Score: %d", e_score);
		Str15 lStrScorePascal;
		CopyCStringToPascal(lStrScore, lStrScorePascal);
		const int lX = StringWidth(lStrScorePascal);
		MoveTo(WW(mRectWin) - lX - TILE_MARGIN, HH(mRectWin) - TILE_MARGIN);
		DrawString(lStrScorePascal);
	}
	void DrawEnd(void) {
		const RGBColor lColorOverlay = GetRgbColor(COLOR_OVERLAY);
		const RGBColor lColorFinal = GetRgbColor(COLOR_FINAL);
		RGBBackColor(&lColorOverlay);
		RGBForeColor(&lColorFinal);
		PenState lPenState;
		GetPenState(&lPenState);
		Pattern gray;
		GetQDGlobalsGray(&gray);
		PenPat(&gray);
		PenMode(patBic);
		PaintRect(&mRectWin);
		SetPenState(&lPenState);

		const unsigned char *lStrFinal = (e_win) ? "\pYou Won!" : "\pGame Over!";
		TextSize(34);
		const int lX = StringWidth(lStrFinal);
		MoveTo(WW(mRectWin) / 2 - lX / 2, HH(mRectWin) / 2);
		DrawString(lStrFinal);
	}

	RGBColor GetRgbColor(unsigned BIG aRgb) const {
		// Not sure about the endianness (byte order). M68K and PPC are big-endian (BE).
		// Why colors use `short` in range 0x0000-0xFFFF? Is the last byte in 0xFF00 in use?
		// More information: https://stackoverflow.com/a/12043639
		const unsigned char red8   = (unsigned char) ((aRgb & 0xFF0000) >> 16);
		const unsigned char green8 = (unsigned char) ((aRgb & 0x00FF00) >> 8);
		const unsigned char blue8  = (unsigned char) ((aRgb & 0x0000FF) >> 0);
		RGBColor lColor;
		lColor.red   = ((unsigned short) red8 << 8) | red8;
		lColor.green = ((unsigned short) green8 << 8) | green8;
		lColor.blue  = ((unsigned short) blue8 << 8) | blue8;
		return lColor;
	}
};

class Application {
	Window *mWindow;

	MenuHandle mMenuApple;
	MenuHandle mMenuGame;
	MenuHandle mMenuTiles;

	bool qIsMacOS_X;

public:
	Application(void) {
		mWindow = nil;
		qIsMacOS_X = false;
		e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	}
	~Application(void) {
		if (mWindow)
			delete mWindow;
	}

	bool InitMac(void) {
		InitCursor();

		FlushEvents(everyEvent, 0);
		SetEventMask(everyEvent);

		OSErr lErr = AEInstallEventHandler(
			kCoreEventClass, kAEQuitApplication,
			NewAEEventHandlerUPP((AEEventHandlerProcPtr) QuitAppleEventHandler),
			0, false
		);
		return lErr == noErr;
	}
	void InitMenuBar(void) {
		Handle lMenuBar = GetNewMBar(RSRC_ID);
		SetMenuBar(lMenuBar);
		DisposeHandle(lMenuBar);

		SetUpMenus();

		if (qIsMacOS_X)
			DeleteMenu(MENU_GAME);
		else
			DeleteMenu(MENU_GAME_OS_X);

		DrawMenuBar();
	}
	bool InitWindow(void) {
		mWindow = new Window(qIsMacOS_X);
		mWindow->Activate();

		if (!mWindow->SetOffScreen())
			return false;

		mWindow->SetFont();
		return true;
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
		long lRes;
		OSErr lErr = Gestalt(gestaltMenuMgrAttr, &lRes);
		if (!lErr && (lRes & gestaltMenuMgrAquaLayoutMask)) {
			qIsMacOS_X = true;
			InsertMenu(mMenuGame = GetMenu(MENU_GAME_OS_X), 0);
		} else
			InsertMenu(mMenuGame = GetMenu(MENU_GAME), 0);
		InsertMenu(mMenuTiles = GetMenu(MENU_TILES), hierMenu);
	}
	void AdjustMenus(void) {
		HiliteMenu(0);

		CheckMenuItem(mMenuTiles, MENU_ITEM_ROUND, mWindow->IsRoundRect());
		CheckMenuItem(mMenuTiles, MENU_ITEM_RECT, !mWindow->IsRoundRect());
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
					ShowAboutModalDialog();
				break;
			case MENU_GAME:
			case MENU_GAME_OS_X:
				switch (lItem) {
					case MENU_ITEM_RESET:
						e_key(kEscapeCharCode);
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
	void ShowAboutModalDialog(void) {
		DialogPtr lDialogPtr = GetNewDialog(RSRC_ID, nil, (WindowPtr) -1);
		SetDialogDefaultItem(lDialogPtr, 1); // "OK" button.

		// This piece of code was inherited from "MoreIsBetter" example:
		// http://mirror.informatimago.com/next/developer.apple.com/samplecode/MoreIsBetter/index.html
		EventRecord lEvent;
		DialogItemIndex lItemIndex = -1;
		DialogRef lDialogRef = GetDialogFromWindow(FrontWindow());
		do {
			WaitNextEvent(everyEvent & ~highLevelEventMask, &lEvent, 0, nil);
			switch (lEvent.what) {
				case mouseDown: {
					WindowPtr lWinPtr;
					const WindowPartCode lWinPart = FindWindow(lEvent.where, &lWinPtr);
					if (lWinPtr != GetDialogWindow(lDialogRef)) {
						SysBeep(30);
						break;
					}
					if (inDrag == lWinPart) {
						DragWindow(GetDialogWindow(lDialogRef), lEvent.where, mWindow->GetRectScreen());
						break;
					}
				}
				// Fallthrough.
				default:
					if (IsDialogEvent(&lEvent))
						DialogSelect(&lEvent, &lDialogRef, &lItemIndex);
					mWindow->Update();
					break;
			}
		} while (lItemIndex == -1);

		DisposeDialog(lDialogPtr);
	}
};

int main(void) {
	Application lApp;
	if (lApp.InitMac()) {
		lApp.InitMenuBar();
		if (lApp.InitWindow())
			lApp.Run();
	}
	return 0;
}
