#include "2048.h"

#include <Devices.h>
#include <Dialogs.h>
#include <Events.h>
#include <Fonts.h>
#include <Gestalt.h>
#include <MacMemory.h>
#include <MacTypes.h>
#include <MacWindows.h>
#include <Menus.h>
#include <NumberFormatting.h>
#include <OSUtils.h>
#include <Processes.h>
#include <Quickdraw.h>
#include <QuickdrawText.h>
#include <QDOffscreen.h>
#include <TextEdit.h>
#include <ToolUtils.h>

#include <GXEnvironment.h>
#include <GXGraphics.h>
#include <GXMath.h>
#include <GXTypes.h>
#include <FontLibrary.h>
#include <GraphicsLibraries.h>
#include <OffscreenLibrary.h>
#include <QDLibrary.h>

#include <stdio.h>

#define RSRC_ID              128
#define ALERT_ERR_COLOR      129
#define ALERT_ERR_BUFFER     130
#define ALERT_WARN_QD_GX     131
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
#define WW(rect)             (rect.right - rect.left)
#define HH(rect)             (rect.bottom - rect.top)

class Window {
	WindowPtr mWinPtr;
	GWorldPtr mOffScr;

	offscreen mOffScrGx;
	gxShape mShapeBkgGx;
	gxShape mShapeSignGx;
	gxShape mShapeOverlayGx;
	gxShape mShapeRestartGx;

	Rect mRectScr;
	Rect mRectWin;

	bool qRoundRect;
	bool qQdGxMode;
	bool qQdGxAvailable;

	Pattern mPattern;

public:
	Window(bool aUseQuickDrawGx) {
		qRoundRect = true;
		qQdGxAvailable = qQdGxMode = aUseQuickDrawGx;

		mWinPtr = GetNewCWindow(RSRC_ID, nil, (WindowPtr) -1L);
		mRectScr = qd.screenBits.bounds;
		mRectWin = mWinPtr->portRect;

		GetIndPattern(&mPattern, RSRC_ID, PATTERN_BACKGROUND);
	}
	~Window(void) {
		DisposeGWorld(mOffScr);
		if (qQdGxAvailable) {
			GXDisposeShape(mShapeRestartGx);
			GXDisposeShape(mShapeOverlayGx);
			GXDisposeShape(mShapeSignGx);
			GXDisposeShape(mShapeBkgGx);
			DisposeOffscreen(&mOffScrGx);
		}
		DisposeWindow(mWinPtr);
	}

	void SetWindowDefaultViewPort(void) {
		SetDefaultViewPort(GXNewWindowViewPort(mWinPtr));
	}
	void SetFont(void) {
		short lFontID;
		GetFNum("\pCharcoal", &lFontID);
		TextFont(lFontID);
	}
	void SetOffScreen(void) {
		OSErr lError = NewGWorld(&mOffScr, 0, &mRectWin, nil, nil, 0L);
		if (lError) {
			Alert(ALERT_ERR_BUFFER, nil);
			ExitToShell();
		}
		LockPixels(GetGWorldPixMap(mOffScr));
		if (!qQdGxAvailable)
			SetGWorld((CGrafPtr) mOffScr, nil);
	}
	void SetOffScreenGx(void) {
		gxBitmap lGxBitmap;
		lGxBitmap.width = WW(mRectWin);
		lGxBitmap.height = HH(mRectWin);
		lGxBitmap.pixelSize = 8 * 4;
		lGxBitmap.space = gxRGB32Space;
		lGxBitmap.set = CTableToColorSet(GetCTable(8));
		lGxBitmap.profile = nil;
		lGxBitmap.image = nil;

		gxShape lGxShapeOffScr;
		lGxShapeOffScr = GXNewBitmap(&lGxBitmap, nil);
		CreateOffscreen(&mOffScrGx, lGxShapeOffScr);
		GXDisposeShape(lGxShapeOffScr);
	}
	void InitStaticShapesGx(void) {
		mShapeBkgGx = GXNewRectangle(&GetGxRectangle(&mRectWin));
		RGBColor lColorBkg = GetRgbColor(COLOR_BOARD);
		SetShapeRGB(mShapeBkgGx, lColorBkg.red, lColorBkg.green, lColorBkg.blue);
		GXSetShapeTransform(mShapeBkgGx, mOffScrGx.xform);

		mShapeSignGx = NewCString("GX", nil);
		SetShapeCommonFont(mShapeSignGx, timesFont);
		SetShapeCommonFace(mShapeSignGx, gxBold);
		GXSetShapeTextSize(mShapeSignGx, ff(200));
		RGBColor lColorSign = GetRgbColor(COLOR_TILE_0);
		SetShapeRGB(mShapeSignGx, lColorSign.red, lColorSign.green, lColorSign.blue);
		SetShapeCommonTransfer(mShapeSignGx, gxBlendMode);
		gxRectangle lRectSign;
		GXGetShapeBounds(mShapeSignGx, 0L, &lRectSign);
		GXRotateShape(mShapeSignGx, ff(45), WW(lRectSign), HH(lRectSign));
		GXMoveShapeTo(mShapeSignGx, ff(WW(mRectWin) / 2) - WW(lRectSign) / 2, ff(HH(mRectWin) / 2) - HH(lRectSign) / 2);
		GXSetShapeTransform(mShapeSignGx, mOffScrGx.xform);

		mShapeOverlayGx = GXNewRectangle(&GetGxRectangle(&mRectWin));
		RGBColor lColorOverlay = GetRgbColor(COLOR_OVERLAY);
		SetShapeRGB(mShapeOverlayGx, lColorOverlay.red, lColorOverlay.green, lColorOverlay.blue);
		SetShapeCommonTransfer(mShapeOverlayGx, gxBlendMode);
		GXSetShapeTransform(mShapeOverlayGx, mOffScrGx.xform);

		gxPoint lPointRestart;
		lPointRestart.x = ff(TILE_MARGIN);
		lPointRestart.y = ff(HH(mRectWin) - TILE_MARGIN);
		mShapeRestartGx = NewCString("ESC to Restart!", &lPointRestart);
		SetShapeCommonFont(mShapeRestartGx, genevaFont);
		GXSetShapeTextSize(mShapeRestartGx, ff(18));
		RGBColor lColorText = GetRgbColor(COLOR_TEXT);
		SetShapeRGB(mShapeRestartGx, lColorText.red, lColorText.green, lColorText.blue);
		GXSetShapeTransform(mShapeRestartGx, mOffScrGx.xform);
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
		if (qQdGxMode)
			UpdateQuickDrawGx();
		else
			UpdateQuickDraw();
		EndUpdate(mWinPtr);
	}
	void Damage(void) {
		if (qQdGxMode)
			DrawGx();
		else
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
	void UpdateQuickDraw(void) {
		SetGWorld((CGrafPtr) mOffScr, nil);

		Draw();

		SetGWorld((CGrafPtr) mWinPtr, GetMainDevice());

		CopyBits(
			&((GrafPtr) mOffScr)->portBits, &((GrafPtr) mWinPtr)->portBits,
			&mOffScr->portRect, &mWinPtr->portRect,
			srcCopy, nil
		);
	}
	void UpdateQuickDrawGx(void) {
		SetPort(mWinPtr);
		DrawGx();
	}
	void Draw(void) {
		RGBBackColor(&GetRgbColor(COLOR_BOARD));
		EraseRect(&mRectWin);
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				DrawTile(e_board[x + y * LINE_SIZE], x, y);
		DrawFinal();
	}
	void DrawGx(void) {
		GXDrawShape(mShapeBkgGx);
		GXDrawShape(mShapeSignGx);
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				DrawTileGx(e_board[x + y * LINE_SIZE], x, y);
		DrawFinalGx();
		GXDrawShape(mOffScrGx.draw);
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
	void DrawTileGx(int aVal, int aX, int aY) {
		const int lX = OFFSET_COORD(aX);
		const int lY = OFFSET_COORD(aY);
		gxShape lShapeTile;
		if (qRoundRect) {
			const int lR = 10;                               // Rounded rectangle corner radius.
			const long lPathGeometry[] = {
				1,                                           // Number of contours.
				12,                                          // Number of points.
				0x24900000,                                  // Points mask, hex(0b001001001001).
				ff(lX + lR), ff(lY),                         // On, simple point.
				ff(lX + TILE_SIZE - lR), ff(lY),             // On, simple point.                      12  1      2  3
				ff(lX + TILE_SIZE), ff(lY),                  // Off, quadratic bezier control point.    .  .      .  .
				ff(lX + TILE_SIZE), ff(lY + lR),             // On, simple point.
				ff(lX + TILE_SIZE), ff(lY + TILE_SIZE - lR), // On, simple point.                    11 .            . 4
				ff(lX + TILE_SIZE), ff(lY + TILE_SIZE),      // Off, quadratic bezier control point.
				ff(lX + TILE_SIZE - lR), ff(lY + TILE_SIZE), // On, simple point.
				ff(lX + lR), ff(lY + TILE_SIZE),             // On, simple point.                    10 .            . 5
				ff(lX), ff(lY + TILE_SIZE),                  // Off, quadratic bezier control point.
				ff(lX), ff(lY + TILE_SIZE - lR),             // On, simple point.                     9 .  .      .  . 6
				ff(lX), ff(lY + lR),                         // On, simple point.
				ff(lX), ff(lY)                               // Off, quadratic bezier control point.       8      7
			};
			lShapeTile = GXNewPaths((gxPaths *) lPathGeometry);
		} else
			lShapeTile = GXNewRectangle(&GetGxRectangle(lX, lX + TILE_SIZE, lY, lY + TILE_SIZE));
		RGBColor lColorTile = GetRgbColor(e_background(aVal));
		SetShapeRGB(lShapeTile, lColorTile.red, lColorTile.green, lColorTile.blue);
		GXSetShapeTransform(lShapeTile, mOffScrGx.xform);
		GXDrawShape(lShapeTile);

		if (aVal) {
			Str15 lStrValue;
			NumToString(aVal, lStrValue);
			gxShape lShapeText = NewPString((const char *) lStrValue, nil);
			SetShapeCommonFont(lShapeText, newyorkFont);
			SetShapeCommonFace(lShapeText, gxBold);
			GXSetShapeTextSize(lShapeText,
				(aVal < 10)   ? ff(32) :
				(aVal < 100)  ? ff(26) :
				(aVal < 1000) ? ff(24) :
				/* else */      ff(20)
			);
			RGBColor lColorText = GetRgbColor(e_foreground(aVal));
			SetShapeRGB(lShapeText, lColorText.red, lColorText.green, lColorText.blue);
			gxRectangle lRectBounds;
			GXGetShapeBounds(lShapeText, 0L, &lRectBounds);
			gxPoint lPos;
			GXGetShapeCenter(lShapeTile, 0L, &lPos);
			const Fixed lP = ff(2);
			GXMoveShapeTo(lShapeText, lPos.x - WW(lRectBounds) / 2 - lP, lPos.y + HH(lRectBounds) / 2 - lP);
			GXSetShapeTransform(lShapeText, mOffScrGx.xform);
			GXDrawShape(lShapeText);
			GXDisposeShape(lShapeText);
		}
		GXDisposeShape(lShapeTile);
	}
	void DrawFinal(void) {
		if (e_win || e_lose)
			DrawEnd();
		else
			RGBForeColor(&GetRgbColor(COLOR_TEXT));

		TextFace(normal);
		TextSize(18);
		MoveTo(TILE_MARGIN, HH(mRectWin) - TILE_MARGIN);
		DrawString("\pESC to Restart!");
		char lStrScore[STRING_SCORE_LENGTH];
		sprintf(lStrScore, "Score: %d", e_score);
		const unsigned char * lStrScorePascal = c2pstr(lStrScore);
		const int lX = StringWidth(lStrScorePascal);
		MoveTo(WW(mRectWin) - lX - TILE_MARGIN, HH(mRectWin) - TILE_MARGIN);
		DrawString(lStrScorePascal);
	}
	void DrawFinalGx(void) {
		if (e_win || e_lose)
			DrawEndGx();

		GXDrawShape(mShapeRestartGx);

		char lStrScore[STRING_SCORE_LENGTH];
		sprintf(lStrScore, "Score: %d", e_score);
		gxShape lShapeScore = NewCString(lStrScore, nil);
		SetShapeCommonFont(lShapeScore, genevaFont);
		GXSetShapeTextSize(lShapeScore, ff(18));
		RGBColor lColorText = GetRgbColor(COLOR_TEXT);
		SetShapeRGB(lShapeScore, lColorText.red, lColorText.green, lColorText.blue);
		gxRectangle lRectScore;
		GXGetShapeBounds(lShapeScore, 0L, &lRectScore);
		GXMoveShapeTo(lShapeScore, ff(WW(mRectWin) - TILE_MARGIN) - WW(lRectScore), ff(HH(mRectWin) - TILE_MARGIN));
		GXSetShapeTransform(lShapeScore, mOffScrGx.xform);
		GXDrawShape(lShapeScore);
		GXDisposeShape(lShapeScore);
	}
	void DrawEnd(void) {
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
		MoveTo(WW(mRectWin) / 2 - lX / 2, HH(mRectWin) / 2);
		DrawString(lStrFinal);
	}
	void DrawEndGx(void) {
		GXDrawShape(mShapeOverlayGx);

		gxShape lShapeFinal = NewCString((e_win) ? "You Won!" : "Game Over!", nil);
		SetShapeCommonFont(lShapeFinal, newyorkFont);
		SetShapeCommonFace(lShapeFinal, gxBold);
		GXSetShapeTextSize(lShapeFinal, ff(36));
		RGBColor lColorFinal = GetRgbColor(COLOR_FINAL);
		SetShapeRGB(lShapeFinal, lColorFinal.red, lColorFinal.green, lColorFinal.blue);
		gxRectangle lRectFinal;
		GXGetShapeBounds(lShapeFinal, 0L, &lRectFinal);
		GXMoveShapeTo(lShapeFinal, ff(WW(mRectWin) / 2) - WW(lRectFinal) / 2, ff(HH(mRectWin) / 2) - HH(lRectFinal) / 2);
		GXSetShapeTransform(lShapeFinal, mOffScrGx.xform);
		GXDrawShape(lShapeFinal);
		GXDisposeShape(lShapeFinal);
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

	gxRectangle GetGxRectangle(const Rect *aRect) const {
		return GetGxRectangle(aRect->left, aRect->right, aRect->top, aRect->bottom);
	}

	gxRectangle GetGxRectangle(register short aL, register short aR, register short aT, register short aB) const {
		gxRectangle lRectangle;
		lRectangle.left = ff(aL);
		lRectangle.right = ff(aR);
		lRectangle.top = ff(aT);
		lRectangle.bottom = ff(aB);
		return lRectangle;
	}
};

class Application {
	Window *mWindow;

	MenuHandle mMenuApple;
	MenuHandle mMenuGame;
	MenuHandle mMenuTiles;

	bool qUseQuickDrawGx;
	gxGraphicsClient mGxGraphicsClient;

public:
	Application(void) {
		mWindow = nil;
		qUseQuickDrawGx = false;
		e_init(kEscapeCharCode, kLeftArrowCharCode, kRightArrowCharCode, kUpArrowCharCode, kDownArrowCharCode);
	}
	~Application(void) {
		if (qUseQuickDrawGx)
			GXDisposeGraphicsClient(mGxGraphicsClient);
		if (mWindow)
			delete mWindow;
	}

	bool CheckColorMac(void) {
		SysEnvRec lEnvWorld;
		SysEnvirons(curSysEnvVers, &lEnvWorld);
		if (!lEnvWorld.hasColorQD) {
			Alert(ALERT_ERR_COLOR, nil);
			return false;
		}
		return true;
	}
	void InitMac(void) {
		MaxApplZone();
		MoreMasters(); MoreMasters(); MoreMasters();
		MoreMasters(); MoreMasters(); MoreMasters();

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
	void InitQuickDrawGx(void) {
		CheckQuickDrawGx();
		if (qUseQuickDrawGx)
			mGxGraphicsClient = GXNewGraphicsClient(nil, 2000L * 1024L, 0L);
	}
	void InitMenuBar(void) {
		Handle lMenuBar = GetNewMBar(RSRC_ID);
		SetMenuBar(lMenuBar);
		DisposeHandle(lMenuBar);

		SetUpMenus();

		DrawMenuBar();
	}
	void InitWindow(void) {
		mWindow = new Window(qUseQuickDrawGx);
		mWindow->Activate();
		mWindow->SetOffScreen();
		mWindow->SetFont();
		if (qUseQuickDrawGx) {
			mWindow->SetWindowDefaultViewPort();
			mWindow->SetOffScreenGx();
			mWindow->InitStaticShapesGx();
		}
	}
	void Run(void) {
		for (;;) {
			AdjustMenus();
			HandleEvents();
		}
	}

private:
	void CheckQuickDrawGx(void) {
		qUseQuickDrawGx = (Gestalt(gestaltGraphicsVersion, nil) == noErr);
		if (!qUseQuickDrawGx)
			Alert(ALERT_WARN_QD_GX, nil);
	}
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

		if (!qUseQuickDrawGx)
			DisableItem(mMenuGame, MENU_ITEM_QD_GX);
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
					ShowAboutModalDialog();
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
	void ShowAboutModalDialog(void) {
		DialogPtr lDialogAbout = GetNewDialog(RSRC_ID, nil, (WindowPtr) -1L);
		SetDialogDefaultItem(lDialogAbout, 1); // "OK" button.
		short lAnswer = 0;
		do
			ModalDialog(nil, &lAnswer);
		while (lAnswer == 0);
		DisposeDialog(lDialogAbout);
	}
};

int main(void) {
	Application lApp;
	lApp.InitMac();
	if (lApp.CheckColorMac()) {
		lApp.InitQuickDrawGx();
		lApp.InitMenuBar();
		lApp.InitWindow();
		lApp.Run();
	}
	return 0;
}
