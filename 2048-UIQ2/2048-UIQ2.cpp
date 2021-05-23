// 2048-UIQ2.cpp
//
// Copyright (c) 2021 EXL. All rights reserved.
//

#include <coecntrl.h>

#include <eikapp.h>
#include <eikappui.h>
#include <eikdoc.h>
#include <eikenv.h>

#include <quartzkeys.h>

#include <sys/reent.h>

// #include <2048-UIQ2.rsg> // TODO: ??
#include "2048-UIQ2.hrh"
#include "2048.hpp"

#define TILE_SIZE 42
#define TILE_MARGIN 5
#define OFFSET_COORD(coord) (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2)

const TUid KUidExample = { 0x10009BBB };

// app view

class CGameAppView : public CCoeControl {
	Engine *iEngine;

	// from CCoeControl
	void Draw(const TRect &) const {
		CWindowGc &gc = SystemGc();
		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		gc.SetBrushColor(KRgbWhite);
		gc.DrawRect(Rect());

		const CFont *font = iCoeEnv->NormalFont();
		gc.UseFont(font);

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

				int xO = OFFSET_COORD(x) + 208 / 64;
				int yO = OFFSET_COORD(y) - TILE_MARGIN - 1;

				TRect rect(xO, yO, xO + TILE_SIZE, yO + TILE_SIZE);
				gc.SetBrushStyle(CGraphicsContext::ENullBrush);
				gc.DrawRect(rect);
				if (value) {
					TInt baseline = rect.Height() / 2 + font->AscentInPixels() / 2;
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
			DrawNow();
		}
	}
	TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType) {
		if (aType != EEventKey)
			return EKeyWasNotConsumed;
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
			case EKeyEnter:
				iEngine->Key(EQuartzKeyConfirm);
				break;
			default:
				iEngine->Key(aKeyEvent.iCode);
				break;
		}
		DrawNow();
		return EKeyWasConsumed;
	}

public:
	void ConstructL(const TRect& aRect) {
		iEngine = new(ELeave) Engine;
		iEngine->Init(EQuartzKeyConfirm,
			EQuartzKeyFourWayLeft, EQuartzKeyFourWayRight, EQuartzKeyFourWayUp, EQuartzKeyFourWayDown);
		CreateWindowL();
		SetRect(aRect);
		ActivateL();
	}
	void Reset() {
		iEngine->Key(EQuartzKeyConfirm);
		DrawNow();
	}
	~CGameAppView() {
		delete iEngine;
		CloseSTDLIB();
	}
};

// app UI

class CGameAppUi : public CEikAppUi {
	CGameAppView* iAppView;

	// from CEikAppUi
	void HandleCommandL(TInt aCommand) {
		switch (aCommand) {
			case EMenuItemReset:
				iAppView->Reset();
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

class CGameDocument : public CEikDocument {
	// from CEikDocument
	CEikAppUi* CreateAppUiL() { return new(ELeave) CGameAppUi; }

public:
	// construct/destruct
	CGameDocument(CEikApplication& aApp) : CEikDocument(aApp) { }
};

// application

class CGameApplication : public CEikApplication {
	// from CApaApplication
	CApaDocument* CreateDocumentL() { return new (ELeave) CGameDocument(*this); }
	TUid AppDllUid() const { return KUidExample; }
};

// DLL interface stuff

EXPORT_C CApaApplication* NewApplication() { return new CGameApplication; }
GLDEF_C TInt E32Dll(TDllReason) { return KErrNone; }
