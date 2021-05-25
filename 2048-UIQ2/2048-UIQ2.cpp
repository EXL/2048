// 2048-UIQ2.cpp
//
// Copyright (c) 2021 EXL. All rights reserved.
//

#include <eikchlst.h>
#include <eikenv.h>
#include <eikmenub.h>
#include <eiktbar.h>

#include <qikapplication.h>
#include <qikappui.h>
#include <qikdocument.h>

#include <quartzkeys.h>

#include <sys/reent.h>

#include <2048-UIQ2.rsg>    // Generated from RSS-resource.
#include "2048-UIQ2.hrh"
#include "2048.hpp"

#define TILE_SIZE           42
#define TILE_MARGIN         5
#define OFFSET_COORD(coord) (coord * (TILE_MARGIN + TILE_SIZE))

const TUid KUidExample = { 0x10009BBB };

// app view
class CGameAppView : public CCoeControl {
	CGameEngine *iGameEngine;
	TBool iRoundedTiles;

	CEikMenuBar *iMenuBar;
	CEikChoiceList *iChoiceList;
	const CFont *iFont;

	// from CCoeControl
	void DrawTile(CWindowGc &aGc, const TRect &aRectView, TInt aValue, TInt aX, TInt aY) const {
		const TInt lCenterTiles = (TILE_SIZE * 4 + TILE_MARGIN * 3) / 2;
		const TInt lX = aRectView.Width() / 2 - lCenterTiles + OFFSET_COORD(aX);
		const TInt lY = aRectView.Height() / 2 - lCenterTiles + OFFSET_COORD(aY) - TILE_MARGIN;
		const TRect lRectTile(lX, lY, lX + TILE_SIZE, lY + TILE_SIZE);
		aGc.SetPenStyle(CGraphicsContext::ENullPen);
		aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		aGc.SetBrushColor(TRgb::Color16M(iGameEngine->Background(aValue)));
		if (iRoundedTiles)
			aGc.DrawRoundRect(lRectTile, TSize(5, 5));
		else
			aGc.DrawRect(lRectTile);
		if (aValue) {
			TBuf<5> lStrValue;
			lStrValue.Num(aValue);
			aGc.UseFont(iFont); // TODO: Various font sizes.
			const TInt lBaseLine = lRectTile.Height() / 2 + iFont->AscentInPixels() / 2;
			aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
			aGc.SetPenStyle(CGraphicsContext::ESolidPen);
			aGc.SetPenColor(TRgb::Color16M(iGameEngine->Foreground(aValue)));
			aGc.DrawText(lStrValue, lRectTile, lBaseLine, CGraphicsContext::ECenter);
			aGc.DiscardFont();
		}
	}
	void Draw(const TRect &) const {
		CWindowGc &lGc = SystemGc();
		const TRect lRectView = Rect();
		lGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		lGc.SetBrushColor(TRgb::Color16M(COLOR_BOARD));
		lGc.DrawRect(lRectView);
		for (TInt y = 0; y < LINE_SIZE; ++y)
			for (TInt x = 0; x < LINE_SIZE; ++x)
				DrawTile(lGc, lRectView, iGameEngine->Board()[x + y * LINE_SIZE], x, y);
		// TODO: DrawFinal.
	}
	void HandlePointerEventL(const TPointerEvent& aPointerEvent) {
		if (aPointerEvent.iType == TPointerEvent::EButton1Down) {
			const TPoint click = aPointerEvent.iPosition;
			const TSize size = Size();
			const TInt w4 = size.iWidth / 4, h4 = size.iHeight / 4;
			const TRect up(w4, 0, w4 + w4 * 2, 0 + h4);
			const TRect down(w4, h4 * 3, w4 + w4 * 2, h4 * 3 + h4);
			const TRect left(0, h4, 0 + w4, h4 + h4 * 2);
			const TRect right(w4 * 3, h4, w4 * 3 + w4, h4 + h4 * 2);
			if (up.Contains(click))
				iGameEngine->Key(EQuartzKeyFourWayUp);
			else if (down.Contains(click))
				iGameEngine->Key(EQuartzKeyFourWayDown);
			else if (left.Contains(click))
				iGameEngine->Key(EQuartzKeyFourWayLeft);
			else if (right.Contains(click))
				iGameEngine->Key(EQuartzKeyFourWayRight);
			UpdateAll();
		}
	}
	TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType) {
		if (aType != EEventKey)
			return EKeyWasNotConsumed;
		switch (aKeyEvent.iCode) {
			case EKeyLeftArrow:
				iGameEngine->Key(EQuartzKeyFourWayLeft);
				break;
			case EKeyRightArrow:
				iGameEngine->Key(EQuartzKeyFourWayRight);
				break;
			case EKeyUpArrow:
			case EQuartzKeyTwoWayUp:
				iGameEngine->Key(EQuartzKeyFourWayUp);
				break;
			case EKeyDownArrow:
			case EQuartzKeyTwoWayDown:
				iGameEngine->Key(EQuartzKeyFourWayDown);
				break;
			case EKeyEscape:
			case EKeyBackspace:
			case EKeyApplicationA:
			case EKeyApplicationB:
				HandleReset();
				return EKeyWasConsumed;
			default:
				iGameEngine->Key(aKeyEvent.iCode);
				break;
		}
		UpdateAll();
		return EKeyWasConsumed;
	}

public:
	void ConstructL(const TRect& aRect) {
		iRoundedTiles = ETrue;

		iGameEngine = new(ELeave) CGameEngine(
			EKeyApplicationA,
			EQuartzKeyFourWayLeft,
			EQuartzKeyFourWayRight,
			EQuartzKeyFourWayUp,
			EQuartzKeyFourWayDown
		);

		CreateWindowL();
		SetRect(aRect);
		ActivateL();

		iMenuBar = iEikonEnv->AppUiFactory()->MenuBar();
		iChoiceList = STATIC_CAST(CEikChoiceList *,
			iEikonEnv->AppUiFactory()->ToolBar()->ControlOrNull(EToolBarCtrlChoice));
		iFont = iEikonEnv->TitleFont();
	}
	~CGameAppView() {
		delete iGameEngine;
		CloseSTDLIB();
	}

	TBool IsRoundedTiles() const { return iRoundedTiles; }
	void SetRoundedTiles(TBool aRoundedTiles) {
		iRoundedTiles = aRoundedTiles;
		if (iChoiceList) {
			iChoiceList->SetCurrentItem(!iRoundedTiles);
			iChoiceList->DrawNow();
		}
		DrawNow();
	}
	void UpdateAll() {
		TBuf<16> lStrValue;
		lStrValue.Format(_L("Score: %d"), *iGameEngine->Score());

		// Update MenuBar title.
		iMenuBar->SetTitleL(lStrValue, R_APP_SCORE_MENU);
		iMenuBar->DrawNow();

		// Update AppView screen.
		DrawNow();
	}
	void HandleReset() {
		iEikonEnv->InfoMsg(_L("Reset"));
		iGameEngine->Key(EKeyApplicationA);
		UpdateAll();
	}
	void HandleToolBarCommand() {
		if (iChoiceList)
			iRoundedTiles = !((TBool) iChoiceList->CurrentItem());
		DrawNow();
	}
};

// app UI
class CGameAppUi : public CQikAppUi {
	CGameAppView* iAppView;

	// from MEikMenuObserver
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane) {
		if (aResourceId == R_APP_TILES_MENU) {
			if (iAppView->IsRoundedTiles())
				aMenuPane->SetItemButtonState(EMenuItemRounded, EEikMenuItemSymbolOn);
			else
				aMenuPane->SetItemButtonState(EMenuItemRectangle, EEikMenuItemSymbolOn);
		}
	}

	// from CEikAppUi
	void HandleCommandL(TInt aCommand) {
		switch (aCommand) {
			case EMenuItemReset:
			case EToolBarButtonReset:
				iAppView->HandleReset();
				break;
			case EMenuItemRounded:
				iAppView->SetRoundedTiles(ETrue);
				break;
			case EMenuItemRectangle:
				iAppView->SetRoundedTiles(EFalse);
				break;
			case EToolBarCtrlChoice:
				iAppView->HandleToolBarCommand();
				break;
			case EEikCmdExit:
				Exit();
				break;
		}
	}

public:
	void ConstructL() {
		BaseConstructL();
		iAppView=new(ELeave) CGameAppView;
		iAppView->ConstructL(ClientRect());
		AddToStackL(iAppView);
	}
	~CGameAppUi() {
		RemoveFromStack(iAppView);
		delete iAppView;
	}
};

// document
class CGameDocument : public CQikDocument {
	// from CEikDocument
	CEikAppUi* CreateAppUiL() { return new(ELeave) CGameAppUi; }

public:
	// construct/destruct
	CGameDocument(CQikApplication& aApp) : CQikDocument(aApp) { }
};

// application
class CGameApplication : public CQikApplication {
	// from CApaApplication
	CApaDocument* CreateDocumentL() { return new(ELeave) CGameDocument(*this); }
	TUid AppDllUid() const { return KUidExample; }
};

// DLL interface stuff
EXPORT_C CApaApplication* NewApplication() { return new CGameApplication; }
GLDEF_C TInt E32Dll(TDllReason) { return KErrNone; }
