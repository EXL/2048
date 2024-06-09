#include <AEEAppGen.h>
#include <AEEStdLib.h>
#include <AEEGraphics.h>

#include "2048.h"

#include "2048-BREW.bid"

#define SCORE_VALUE_MAX_LENGTH           (16)
#define TILE_VALUE_MAX_LENGTH             (5)

typedef enum {
	R,
	G,
	B,
	A
} APP_COLOR_COMPONENT_T;

typedef struct {
	AEEApplet pMe;

	IGraphics *pIGraphics;
} APP_INSTANCE_T;

static boolean APP_InitAppData(AEEApplet *pMe);
static boolean APP_FreeAppData(AEEApplet *pMe);
static boolean APP_HandleEvent(AEEApplet *pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam);

static boolean GFX_PaintBoard(AEEApplet *pMe);
static boolean GFX_PaintBackgroud(AEEApplet *pMe);
static boolean GFX_PaintTile(AEEApplet *pMe, uint32 value, uint8 x, uint8 y);
static boolean GFX_PaintFinal(AEEApplet *pMe);

static inline RGBVAL GFX_ConvertColor(uint32 color) {
	uint32 a = (color >> 24) & 0xFF;
	uint32 r = (color >> 16) & 0xFF;
	uint32 g = (color >>  8) & 0xFF;
	uint32 b = (color >>  0) & 0xFF;
	return MAKE_RGBA(r, g, b, a);
}

static inline uint8 GFX_RGBA(uint32 color, APP_COLOR_COMPONENT_T component) {
	switch (component) {
		case A: return (color >> 24) & 0xFF;
		case R: return (color >> 16) & 0xFF;
		case G: return (color >>  8) & 0xFF;
		default:
		case B: return (color >>  0) & 0xFF;
	}
}

static inline uint32 GFX_OffsetCoord(uint8 coord, uint16 tile_size, uint16 offset) {
	return (coord * (tile_size + offset) + offset);
}

AEEResult AEEClsCreateInstance(AEECLSID ClsId, IShell *pIShell, IModule *pMod, void **ppObj) {
	*ppObj = NULL;

	if (ClsId == AEECLSID_2048_BREW) {
		if(
			AEEApplet_New(
				sizeof(APP_INSTANCE_T),                     // Size of our private class.
				ClsId,                                      // Our class ID.
				pIShell,                                    // Shell interface.
				pMod,                                       // Module instance.
				(IApplet **) ppObj,                         // Return object.
				(AEEHANDLER) APP_HandleEvent,               // Our event handler.
				(PFNFREEAPPDATA) APP_FreeAppData            // Special "cleanup" function.
			)
		) {
			if (APP_InitAppData((AEEApplet *) *ppObj)) {
				return AEE_SUCCESS;
			} else {
				IAPPLET_Release((IApplet *) *ppObj);
				return AEE_EFAILED;
			}

		}
	}
	return AEE_EFAILED;
}

static boolean APP_InitAppData(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	e_init(AVK_0, AVK_LEFT, AVK_RIGHT, AVK_UP, AVK_DOWN);

	if (ISHELL_CreateInstance(app->pMe.m_pIShell, AEECLSID_GRAPHICS, (void **) &app->pIGraphics) == AEE_SUCCESS) {
		return TRUE;
	}

	return FALSE;
}

static boolean APP_FreeAppData(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	IGRAPHICS_Release(app->pIGraphics);

	return TRUE;
}

static boolean APP_HandleEvent(AEEApplet *pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	switch (eCode) {
		case EVT_APP_START:
			GFX_PaintBoard(pMe);
			return TRUE;
			break;
		case EVT_APP_STOP:
			return TRUE;
			break;
		case EVT_KEY:
			switch (wParam) {
				case AVK_0:
				case AVK_LEFT:
				case AVK_RIGHT:
				case AVK_UP:
				case AVK_DOWN:
					e_key(wParam); GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_4:
					e_key(AVK_LEFT); GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_6:
					e_key(AVK_RIGHT); GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_2:
					e_key(AVK_UP); GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_8:
					e_key(AVK_DOWN); GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_SOFT2:
					e_key(AVK_0); GFX_PaintBoard(pMe); return TRUE;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return FALSE;
}

static boolean GFX_PaintBoard(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	uint8 x;
	uint8 y;

	GFX_PaintBackgroud(pMe);
	for (y = 0; y < LINE_SIZE; ++y) {
		for (x = 0; x < LINE_SIZE; ++x) {
			GFX_PaintTile(pMe, e_board[x + y * LINE_SIZE], x, y);
		}
	}
	GFX_PaintFinal(pMe);

	IDISPLAY_Update(app->pMe.m_pIDisplay);

	return TRUE;
}

static boolean GFX_PaintBackgroud(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	IDISPLAY_FillRect(app->pMe.m_pIDisplay, NULL, GFX_ConvertColor(COLOR_BOARD));

	return TRUE;
}

static boolean GFX_PaintTile(AEEApplet *pMe, uint32 value, uint8 x, uint8 y) {
	APP_INSTANCE_T *app;
	AEERect tile_rect;

	uint32 coord_x;
	uint32 coord_y;
	uint16 tile_size;
	uint16 offset_x;
	uint16 offset_y;
	uint16 offset_w;
	uint16 offset_h;
	uint16 radius;
	uint32 fc;
	uint32 bc;


	app = (APP_INSTANCE_T *) pMe;

	// TODO: Hacks.
	tile_size = 48;
	offset_x = offset_y = 6;
	offset_w = 10;
	offset_h = 6;
	radius = 14;

	coord_x = GFX_OffsetCoord(x, tile_size, offset_x) + offset_w;
	coord_y = GFX_OffsetCoord(y, tile_size, offset_y) + offset_h;

	SETAEERECT(&tile_rect, coord_x, coord_y, tile_size, tile_size);

	fc = e_foreground(2);
	bc = e_background(value);

	// TODO: Switch here!
	if (1) {
		IGRAPHICS_SetColor(app->pIGraphics, GFX_RGBA(fc, R), GFX_RGBA(fc, G), GFX_RGBA(fc, B), GFX_RGBA(fc, A));
		IGRAPHICS_SetFillColor(app->pIGraphics, GFX_RGBA(bc, R), GFX_RGBA(bc, G), GFX_RGBA(bc, B), GFX_RGBA(bc, A));
		IGRAPHICS_SetFillMode(app->pIGraphics, TRUE);
		IGRAPHICS_DrawRoundRectangle(app->pIGraphics, &tile_rect, radius, radius);
	} else {
		IDISPLAY_SetColor(app->pMe.m_pIDisplay, CLR_USER_LINE, GFX_ConvertColor(fc));
		IDISPLAY_SetColor(app->pMe.m_pIDisplay, CLR_USER_BACKGROUND, GFX_ConvertColor(bc));
		IDisplay_FrameSolidRect(app->pMe.m_pIDisplay, &tile_rect);
	}

	if (value) {
		AEEFont font;
		AECHAR w_tile_value[TILE_VALUE_MAX_LENGTH];
		int pnAscent;
		int pnDescent;
		uint32 point_x;
		uint32 point_y;
		uint32 text_w;
		uint32 text_h;

		WSPRINTF(w_tile_value, sizeof(AECHAR) * TILE_VALUE_MAX_LENGTH, L"%d", value);

		if (value < 10) {
			font = AEE_FONT_LARGE;
		} else if (value < 100) {
			font = AEE_FONT_LARGE;
		} else if (value < 1000) {
			font = AEE_FONT_BOLD;
		} else {
			font = AEE_FONT_NORMAL;
		}

		IDISPLAY_GetFontMetrics(app->pMe.m_pIDisplay, font, &pnAscent, &pnDescent);
		text_h = pnAscent + pnDescent;
		text_w = IDISPLAY_MeasureText(app->pMe.m_pIDisplay, font, w_tile_value);

		point_x = coord_x + ((tile_size - text_w) / 2);
		point_y = coord_y + ((tile_size - text_h) / 2);

		if (value < 64) {
			IDISPLAY_SetColor(app->pMe.m_pIDisplay, CLR_USER_TEXT, GFX_ConvertColor(e_foreground(value)));
		} else {
			IDISPLAY_SetColor(app->pMe.m_pIDisplay, CLR_USER_TEXT, GFX_ConvertColor(e_foreground(2)));
		}

		IDISPLAY_DrawText(app->pMe.m_pIDisplay, font, w_tile_value, -1, point_x, point_y, NULL, IDF_TEXT_TRANSPARENT);
	}

	return TRUE;
}

static boolean GFX_PaintFinal(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	AECHAR w_score[SCORE_VALUE_MAX_LENGTH];
	const AECHAR *w_press = L"\"0\" to Reset!";
	const AECHAR *w_win = L"You Won!";
	const AECHAR *w_over = L"Game Over!";

	int width;

	WSPRINTF(w_score, sizeof(AECHAR) * SCORE_VALUE_MAX_LENGTH, L"Score: %d", e_score);
	IDISPLAY_SetColor(app->pMe.m_pIDisplay, CLR_USER_TEXT, GFX_ConvertColor(COLOR_TEXT));

	width = IDISPLAY_MeasureText(app->pMe.m_pIDisplay, AEE_FONT_NORMAL, w_score);

	IDISPLAY_DrawText(app->pMe.m_pIDisplay, AEE_FONT_NORMAL, w_press, -1,
		10 /* offset_w */, 280 - 10, NULL, IDF_TEXT_TRANSPARENT);
	IDISPLAY_DrawText(app->pMe.m_pIDisplay, AEE_FONT_NORMAL, w_score, -1,
		240 - width - 10 /* offset_w */, 280 - 10, NULL, IDF_TEXT_TRANSPARENT);

	if (e_win || e_lose) {
		if (e_win) {
			IDISPLAY_DrawText(app->pMe.m_pIDisplay, AEE_FONT_LARGE, w_win, -1,
				10 /* offset_w */, 260 - 10, NULL, IDF_TEXT_TRANSPARENT);
		} else {
			IDISPLAY_DrawText(app->pMe.m_pIDisplay, AEE_FONT_LARGE, w_over, -1,
				10 /* offset_w */, 260 - 10, NULL, IDF_TEXT_TRANSPARENT);
		}
	}

	return TRUE;
}
