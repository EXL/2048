#include "2048.h"

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

#define RSRC_ID 128
#define MENU_APPLE 128
#define ROUND_RECT_RAD 20
#define TILE_SIZE 64
#define TILE_MARGIN 16
#define OFFSET_COORD(coord)  (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

class Window {
	WindowPtr mWinPtr;
	Rect mRectScr;
	Rect mRectWin;
public:
	Window(void) {
		// TODO: Check this shit.
		Rect lRectInit;
		mRectScr = qd.screenBits.bounds;
		SetRect(&lRectInit, 50, 50, 340 + 50, 400 + 50);
		SetRect(&mRectWin, 0, 0, 340, 400);
		mWinPtr = NewCWindow(nil, &lRectInit, "\p2048-D", true, documentProc, (WindowPtr) -1L, true, 0);
		//mWinPtr = GetNewCWindow(128, nil, (WindowPtr) -1L);
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
	
	Handle mMenuBar;
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
		InitGraf(&qd.thePort);
		InitFonts();
		InitWindows();
		InitMenus();
		TEInit();
		InitDialogs(nil);
		InitCursor();
		
		FlushEvents(nullEvent, everyEvent);
		SetEventMask(everyEvent);
		
	}
	void InitMenuBar(void) {
		mMenuBar = GetNewMBar(RSRC_ID);
		if (mMenuBar == nil) {
			SysBeep(60);
			ExitToShell();
		}
		SetMenuBar(mMenuBar);
		DisposeHandle(mMenuBar);
		AppendResMenu(GetMenuHandle(MENU_APPLE), 'DRVR');
		DrawMenuBar();
	}
	void InitWindow(void) {
		mWindow = new Window();
		mWindow->Activate();
		mWindow->SetFont();
	}
	void Run(void) {
		for (;;)
			HandleEvents();
	}
private:
	void HandleEvents(void) {
		EventRecord lEvent;
		if (WaitNextEvent(everyEvent, &lEvent, 0, nil)) {
			switch (lEvent.what) {
				case mouseDown:
					HandleMouse(&lEvent);
					break;
				case updateEvt:
					mWindow->Update();
					break;
				case keyDown:
				case autoKey:
					e_key(lEvent.message & charCodeMask);
					mWindow->Damage();
					break;
			}
		}	
	}
	void HandleMouse(const EventRecord *aEvent) {
		WindowPtr lWinPtr;
		const short lWhere = FindWindow(aEvent->where, &lWinPtr);
		switch (lWhere) {
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
