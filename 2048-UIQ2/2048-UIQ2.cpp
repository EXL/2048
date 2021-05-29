// 2048-UIQ2.cpp
//
// Copyright (c) 2021 EXL. All rights reserved.
//

#include <eikchlst.h>
#include <eikdialg.h>
#include <eikenv.h>
#include <eikmenub.h>
#include <eiktbar.h>

#include <qikapplication.h>
#include <qikappui.h>
#include <qikdocument.h>

#include <quartzkeys.h>

#include <s32file.h>

#include <sys/reent.h>

#include <2048-UIQ2.rsg>    // Generated from RSS-resource.
#include "2048-UIQ2.hrh"
#include "2048.h"

#define TILE_SIZE           42
#define TILE_MARGIN         5
#define OFFSET_COORD(coord) (coord * (TILE_MARGIN + TILE_SIZE))

const TUid KUidGameApplication = { 0x10009BBB };

// app view
class CGameAppView : public CCoeControl {
	Engine iEngine;
	TBool iRoundedTiles;

	CEikMenuBar *iMenuBar;
	CEikChoiceList *iChoiceList;
	CWsScreenDevice *iScreenDevice;
	CFont *iFontLarge;
	CFont *iFontNormal;
	CFont *iFontSmall;
	TRect iRectView;

	CFbsBitmap *iBmp;
	CFbsBitmapDevice *iBmpDevice;
	CFbsBitGc *iBmpGc;

	// from CCoeControl
	void DrawFinal() const {
		if (iEngine.e_win || iEngine.e_lose) {
			iBmpGc->SetBrushStyle(CGraphicsContext::ESquareCrossHatchBrush);
			iBmpGc->SetDrawMode(CGraphicsContext::EDrawModeNOTSCREEN);
			iBmpGc->DrawRect(iRectView);
			iBmpGc->SetDrawMode(CGraphicsContext::EDrawModePEN);
			iBmpGc->UseFont(iFontLarge);
			const TInt lBaseLine = iRectView.Height() / 2 + iFontLarge->AscentInPixels() / 2;
			iBmpGc->SetBrushStyle(CGraphicsContext::ENullBrush);
			iBmpGc->SetPenColor(TRgb::Color16M(COLOR_FINAL));
			iBmpGc->DrawText((iEngine.e_win) ? _L("You Won!") : _L("Game Over!"),
				iRectView, lBaseLine, CGraphicsContext::ECenter);
			iBmpGc->DiscardFont();
		}
	}
	void DrawTile(TInt aValue, TInt aX, TInt aY) const {
		const TInt lCenterTiles = (TILE_SIZE * 4 + TILE_MARGIN * 3) / 2;
		const TInt lX = iRectView.Width() / 2 - lCenterTiles + OFFSET_COORD(aX);
		const TInt lY = iRectView.Height() / 2 - lCenterTiles + OFFSET_COORD(aY) - TILE_MARGIN;
		const TRect lRectTile(lX, lY, lX + TILE_SIZE, lY + TILE_SIZE);
		iBmpGc->SetPenStyle(CGraphicsContext::ENullPen);
		iBmpGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
		iBmpGc->SetBrushColor(TRgb::Color16M(e_background(aValue)));
		if (iRoundedTiles)
			iBmpGc->DrawRoundRect(lRectTile, TSize(5, 5));
		else
			iBmpGc->DrawRect(lRectTile);
		if (aValue) {
			TBuf<5> lStrValue;
			lStrValue.Num(aValue);
			CFont *lFont = (aValue < 100) ? iFontLarge : (aValue < 1000) ? iFontNormal : iFontSmall;
			iBmpGc->UseFont(lFont);
			const TInt lBaseLine = lRectTile.Height() / 2 + lFont->AscentInPixels() / 2;
			iBmpGc->SetBrushStyle(CGraphicsContext::ENullBrush);
			iBmpGc->SetPenStyle(CGraphicsContext::ESolidPen);
			iBmpGc->SetPenColor(TRgb::Color16M(e_foreground(aValue)));
			iBmpGc->DrawText(lStrValue, lRectTile, lBaseLine, CGraphicsContext::ECenter);
			iBmpGc->DiscardFont();
		}
	}
	void Draw(const TRect &) const {
		CWindowGc &lGc = SystemGc();
		iBmpGc->SetPenStyle(CGraphicsContext::ENullPen);
		iBmpGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
		iBmpGc->SetBrushColor(TRgb::Color16M(COLOR_BOARD));
		iBmpGc->DrawRect(iRectView);
		for (TInt y = 0; y < LINE_SIZE; ++y)
			for (TInt x = 0; x < LINE_SIZE; ++x)
				DrawTile(iEngine.e_board[x + y * LINE_SIZE], x, y);
		DrawFinal();
		lGc.BitBlt(TPoint(0, 0), iBmp);
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
				e_key(&iEngine, EQuartzKeyFourWayUp);
			else if (down.Contains(click))
				e_key(&iEngine, EQuartzKeyFourWayDown);
			else if (left.Contains(click))
				e_key(&iEngine, EQuartzKeyFourWayLeft);
			else if (right.Contains(click))
				e_key(&iEngine, EQuartzKeyFourWayRight);
			UpdateAll();
		}
	}
	TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType) {
		if (aType != EEventKey)
			return EKeyWasNotConsumed;
		switch (aKeyEvent.iCode) {
			case EKeyLeftArrow:
				e_key(&iEngine, EQuartzKeyFourWayLeft);
				break;
			case EKeyRightArrow:
				e_key(&iEngine, EQuartzKeyFourWayRight);
				break;
			case EKeyUpArrow:
			case EQuartzKeyTwoWayUp:
				e_key(&iEngine, EQuartzKeyFourWayUp);
				break;
			case EKeyDownArrow:
			case EQuartzKeyTwoWayDown:
				e_key(&iEngine, EQuartzKeyFourWayDown);
				break;
			case EKeyEscape:
			case EKeyBackspace:
			case EKeyApplicationA:
			case EKeyApplicationB:
				HandleReset();
				return EKeyWasConsumed;
			default:
				e_key(&iEngine, aKeyEvent.iCode);
				break;
		}
		UpdateAll();
		return EKeyWasConsumed;
	}

public:
	void ConstructL(const TRect& aRect) {
		iRoundedTiles = ETrue;

		iEngine.K_ESCAPE = EKeyApplicationA;
		iEngine.K_LEFT = EQuartzKeyFourWayLeft;
		iEngine.K_RIGHT = EQuartzKeyFourWayRight;
		iEngine.K_UP = EQuartzKeyFourWayUp;
		iEngine.K_DOWN = EQuartzKeyFourWayDown;
		e_init(&iEngine);

		CreateWindowL();
		SetRect(aRect);
		ActivateL();

		iScreenDevice = iEikonEnv->ScreenDevice();
		iRectView = Rect();
		iBmp = new(ELeave) CFbsBitmap();
		iBmp->Create(iRectView.Size(), iScreenDevice->DisplayMode());
		iBmpDevice = CFbsBitmapDevice::NewL(iBmp);
		iBmpDevice->CreateContext(iBmpGc);

		iMenuBar = iEikonEnv->AppUiFactory()->MenuBar();
		iChoiceList = STATIC_CAST(CEikChoiceList *,
			iEikonEnv->AppUiFactory()->ToolBar()->ControlOrNull(EToolBarCtrlChoice));
		iScreenDevice->GetNearestFontInTwips(iFontLarge, GetFontSpec(_L("Dialer"), 20));
		iScreenDevice->GetNearestFontInTwips(iFontNormal, GetFontSpec(_L("HGGothicB"), 16));
		iScreenDevice->GetNearestFontInTwips(iFontSmall, GetFontSpec(_L("HGGothicB"), 14));
	}
	~CGameAppView() {
		iScreenDevice->ReleaseFont(iFontSmall);
		iScreenDevice->ReleaseFont(iFontNormal);
		iScreenDevice->ReleaseFont(iFontLarge);
		delete iBmpGc;
		delete iBmpDevice;
		delete iBmp;
		CloseSTDLIB();
	}

	TFontSpec GetFontSpec(const TDesC &aTypefaceName, TInt aHeight) const {
		TFontSpec lFontSpec(aTypefaceName, aHeight * 20);
		lFontSpec.iTypeface.SetIsProportional(ETrue);
		lFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
		return lFontSpec;
	}

	TBool IsRoundedTiles() const { return iRoundedTiles; }
	void SetRoundedTiles(TBool aRoundedTiles) {
		iRoundedTiles = aRoundedTiles;
		if (iChoiceList) {
			iChoiceList->SetCurrentItem(!iRoundedTiles);
			iChoiceList->DrawNow();
		}
		iEikonEnv->InfoMsg((iRoundedTiles) ? _L("Rounded Tiles") : _L("Rectangle Tiles"));
		DrawNow();
	}
	void UpdateAll() {
		TBuf<16> lStrValue;
		lStrValue.Format(_L("Score: %d"), iEngine.e_score);

		// Update MenuBar title.
		iMenuBar->SetTitleL(lStrValue, R_APP_SCORE_MENU);
		iMenuBar->DrawNow();

		// Update AppView screen.
		DrawNow();

		if (iEngine.e_win || iEngine.e_lose)
			iEikonEnv->InfoMsg((iEngine.e_win) ? _L("You Won!") : _L("Game Over!"));
	}
	void HandleReset() {
		iEikonEnv->InfoMsg(_L("Reset Game"));
		e_key(&iEngine, EKeyApplicationA);
		UpdateAll();
	}
	void HandleToolBarCommand() {
		if (iChoiceList)
			iRoundedTiles = !((TBool) iChoiceList->CurrentItem());
		iEikonEnv->InfoMsg((iRoundedTiles) ? _L("Rounded Tiles") : _L("Rectangle Tiles"));
		DrawNow();
	}
	void SaveGameL() {
		TRAPD(lErr, WriteFileL());
		if (lErr) {
			TBuf<64> lStr;
			lStr.Format(_L("Cannot save \"2048-UIQ2.sav\" file, error code: 0x%X"), lErr);
			iEikonEnv->InfoWinL(_L("Error!"), lStr);
			User::Leave(lErr);
		}
	}
	void WriteFileL() {
		RFileWriteStream lWriter;
		lWriter.PushL();
		User::LeaveIfError(lWriter.Replace(iEikonEnv->FsSession(), _L("2048-UIQ2.sav"), EFileWrite));
		lWriter.WriteL((const TUint8 *) &iEngine, sizeof(Engine));
		TTime lTime;
		lTime.HomeTime();
		lWriter.WriteL((const TUint8 *) &lTime.Int64(), sizeof(TInt64));
		TBuf<64> lStr;
		TBuf<32> lStrDateTime;
		lTime.FormatL(lStrDateTime, _L("%D%*N%Y%1-%2-%3%, %H:%T:%S")); // 30-May-2021, 03:19:54
		lStr.Append(_L("Save file is \"2048-UIQ2.sav\", date:\n"));
		lStr.Append(lStrDateTime);
		iEikonEnv->InfoWinL(_L("Game Saved!"), lStr);
		lWriter.CommitL();
		CleanupStack::PopAndDestroy();
	}
	void LoadGameL() {
		TRAPD(lErr, ReadFileL());
		if (lErr) {
			TBuf<64> lStr;
			lStr.Format(_L("Cannot load \"2048-UIQ2.sav\" file, error code: 0x%X"), lErr);
			iEikonEnv->InfoWinL(_L("Error!"), lStr);
			User::Leave(lErr);
		}
	}
	void ReadFileL() {
		RFileReadStream lReader;
		lReader.PushL();
		User::LeaveIfError(lReader.Open(iEikonEnv->FsSession(), _L("2048-UIQ2.sav"), EFileRead));
		lReader.ReadL((TUint8 *) &iEngine, sizeof(Engine));
		TInt64 lTimeStamp;
		lReader.ReadL((TUint8 *) &lTimeStamp, sizeof(TInt64));
		TBuf<64> lStr;
		TBuf<32> lStrDateTime;
		TTime lTime(lTimeStamp);
		lTime.FormatL(lStrDateTime, _L("%D%*N%Y%1-%2-%3%, %H:%T:%S")); // 30-May-2021, 03:19:54
		lStr.Append(_L("Save file is \"2048-UIQ2.sav\", date:\n"));
		lStr.Append(lStrDateTime);
		UpdateAll();
		iEikonEnv->InfoWinL(_L("Game Loaded!"), lStr);
		CleanupStack::PopAndDestroy();
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
			case EMenuItemSave:
				iAppView->SaveGameL();
				break;
			case EMenuItemLoad:
				iAppView->LoadGameL();
				break;
			case EEikCmdExit:
				Exit();
				break;
			case EMenuItemAbout: {
				// iEikonEnv->InfoWinL(_L("About"), _L("About Dialog"));
				CEikDialog *lAboutDialog = new(ELeave) CEikDialog();
				lAboutDialog->SetHelpContext(TCoeHelpContext(KUidGameApplication, _L("This is about dialog.")));
				lAboutDialog->ExecuteLD(R_APP_ABOUT_DIALOG);
				}
				break;
			case EToolBarCtrlChoice:
				iAppView->HandleToolBarCommand();
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
	TUid AppDllUid() const { return KUidGameApplication; }
};

// DLL interface stuff
EXPORT_C CApaApplication* NewApplication() { return new CGameApplication; }
GLDEF_C TInt E32Dll(TDllReason) { return KErrNone; }
