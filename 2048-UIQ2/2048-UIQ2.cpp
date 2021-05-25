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
	Engine *iEngine;
	TBool iRoundedTiles;

	CEikMenuBar *iMenuBar;
	CEikChoiceList *iChoiceList;
	const CFont *iFont;

	// from CCoeControl
	void Draw(const TRect &) const {
		TRect lRectScr = Rect();
		TInt lWidthScr = lRectScr.Width();
		TInt lHeightScr = lRectScr.Height();
		TInt lBoardSize = TILE_SIZE * 4 + TILE_MARGIN * 3;
		CWindowGc &gc = SystemGc();
		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		gc.SetBrushColor(KRgbWhite);
		gc.Clear(Rect());

		gc.UseFont(iFont);

		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x) {
				int *board = iEngine->GetBoard();
				int value = board[x + y * LINE_SIZE];
				if (value)
					gc.SetPenColor(KRgbGreen);
				else
					gc.SetPenColor(KRgbRed);

				TBuf<5> strValue;
				strValue.Num(value);

				int xO = lWidthScr / 2 - lBoardSize / 2 + OFFSET_COORD(x);
				int yO = lHeightScr / 2 - lBoardSize / 2 + OFFSET_COORD(y);

				TRect rect(xO, yO, xO + TILE_SIZE, yO + TILE_SIZE);
				gc.SetBrushStyle(CGraphicsContext::ENullBrush);
				if (iRoundedTiles)
					gc.DrawRoundRect(rect, TSize(8, 8));
				else
					gc.DrawRect(rect);
				if (value) {
					TInt baseline = rect.Height() / 2 + iFont->AscentInPixels() / 2;
					gc.DrawText(strValue, rect, baseline, CGraphicsContext::ECenter);
				}
			}

		gc.DiscardFont();
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
				iEngine->Key(EQuartzKeyFourWayUp);
			else if (down.Contains(click))
				iEngine->Key(EQuartzKeyFourWayDown);
			else if (left.Contains(click))
				iEngine->Key(EQuartzKeyFourWayLeft);
			else if (right.Contains(click))
				iEngine->Key(EQuartzKeyFourWayRight);
			UpdateAll();
		}
	}
	TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType) {
		if (aType != EEventKey)
			return EKeyWasNotConsumed;

		// TODO: Debug keys.
		TBuf<16> lStrValue;
		lStrValue.Format(_L("0x%X"), aKeyEvent.iCode);
		iEikonEnv->InfoMsg(lStrValue);

		switch (aKeyEvent.iCode) {
			case EKeyLeftArrow:
				iEngine->Key(EQuartzKeyFourWayLeft);
				break;
			case EKeyRightArrow:
				iEngine->Key(EQuartzKeyFourWayRight);
				break;
			case EKeyUpArrow:
			case EQuartzKeyTwoWayUp:
				iEngine->Key(EQuartzKeyFourWayUp);
				break;
			case EKeyDownArrow:
			case EQuartzKeyTwoWayDown:
				iEngine->Key(EQuartzKeyFourWayDown);
				break;
			case EKeyEscape:
			case EKeyBackspace:
			case EKeyApplicationB:
				iEngine->Key(EKeyApplicationA);
				break;
			default:
				iEngine->Key(aKeyEvent.iCode);
				break;
		}
		UpdateAll();
		return EKeyWasConsumed;
	}

public:
	void ConstructL(const TRect& aRect) {
		iRoundedTiles = ETrue;

		iEngine = new(ELeave) Engine;
		iEngine->Init(
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
		iChoiceList = STATIC_CAST(CEikChoiceList *, iEikonEnv->AppUiFactory()->ToolBar()->ControlOrNull(EToolBarCtrlChoice));
		iFont = iEikonEnv->TitleFont();
	}
	~CGameAppView() {
		delete iEngine;
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
		lStrValue.Format(_L("Score: %d"), iEngine->GetScore());

		/*
		// Update ToolBar label.
		CEikLabel *lLabel =
			STATIC_CAST(CEikLabel *, iEikonEnv->AppUiFactory()->ToolBar()->ControlOrNull(EToolBarCtrlLabel));
		if (iLabel) {
			lLabel->SetTextL(lStrValue);
			lLabel->DrawNow();
		}
		*/

		// Update MenuBar title.
		iMenuBar->SetTitleL(lStrValue, R_APP_SCORE_MENU);
		iMenuBar->DrawNow();

		// Update AppView screen.
		DrawNow();
	}
	void HandleReset() {
		iEikonEnv->InfoMsg(_L("Reset"));
		iEngine->Key(EKeyApplicationA);
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
