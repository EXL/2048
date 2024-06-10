#include <AEEAppGen.h>
#include <AEEStdLib.h>
#include <AEEGraphics.h>

#include "2048-BREW.bid"

#include "2048.h"

#define SCORE_VALUE_MAX_LENGTH           (16)
#define TILE_VALUE_MAX_LENGTH             (5)

typedef enum { R, G, B, A } APP_COLOR_COMPONENT_T;

typedef struct {
	AEERect m_RectScreen;

	int16 m_ScreenW;
	int16 m_ScreenH;

	uint16 m_TileSize;
	uint16 m_OffsetX;
	uint16 m_OffsetY;
	uint16 m_OffsetW;
	uint16 m_OffsetH;
	uint16 m_Radius;
	int16 m_GapX;
	int16 m_GapY;
	uint16 m_ZoomFactor;

	AEEFont m_FontX;       /* Large Size Font. */
	AEEFont m_FontXX;      /* Big Size Font. */
	AEEFont m_FontXXX;     /* Meduim/Regular Size Font. */
	AEEFont m_FontXXXX;    /* Small Size Font. */

	const AECHAR *m_wstr_title;
} APP_DEVICE_T;

typedef struct {
	boolean m_RoundedRectangle;
} APP_SETTINGS_T;

typedef struct {
	AEEApplet m_App;
	APP_DEVICE_T m_AppDevice;
	APP_SETTINGS_T m_AppSettings;

	IGraphics *m_pIGraphics;

	boolean is_softkey_menu_pushed;
	boolean is_softkey_reset_pushed;
} APP_INSTANCE_T;

static boolean APP_InitAppData(AEEApplet *pMe);
static boolean APP_FreeAppData(AEEApplet *pMe);
static boolean APP_HandleEvent(AEEApplet *pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam);
static boolean APP_DeviceFill(AEEApplet *pMe);

static boolean GFX_PaintBoard(AEEApplet *pMe);
static boolean GFX_PaintBackgroud(AEEApplet *pMe);
static boolean GFX_PaintTile(AEEApplet *pMe, uint32 value, uint8 x, uint8 y);
static boolean GFX_PaintFinal(AEEApplet *pMe);

const AECHAR *wstr_lbl_title = L"2048-BREW";
const AECHAR *wstr_lbl_title_small = L"2048";
const AECHAR *wstr_game_win = L"You Won!";
const AECHAR *wstr_game_over = L"Game Over!";
const AECHAR *wstr_lbl_score = L"Score: %d";
const AECHAR *wstr_soft_menu = L"Menu";
const AECHAR *wstr_soft_reset = L"Reset";

static inline RGBVAL COL_ARGB_BGRA(uint32 color) {
	uint32 A = (color >> 24) & 0xFF;
	uint32 R = (color >> 16) & 0xFF;
	uint32 G = (color >>  8) & 0xFF;
	uint32 B = (color >>  0) & 0xFF;
	return MAKE_RGBA(R, G, B, A);
}

static inline byte COL_BGRA(RGBVAL color, APP_COLOR_COMPONENT_T component) {
	switch (component) {
		case B:  return (color >> 24) & 0xFF;
		case G:  return (color >> 16) & 0xFF;
		case R:  return (color >>  8) & 0xFF;
		default:
		case A:  return (color >>  0) & 0xFF;
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

	APP_DeviceFill(pMe);
	app->m_AppSettings.m_RoundedRectangle = TRUE;

	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_GRAPHICS, (void **) &app->m_pIGraphics) == AEE_SUCCESS) {
		return TRUE;
	}

	return FALSE;
}

static boolean APP_FreeAppData(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	IGRAPHICS_Release(app->m_pIGraphics);

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
		case EVT_KEY_PRESS:
			switch (wParam) {
				case AVK_SOFT1:
					app->is_softkey_menu_pushed = TRUE; GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_SOFT2:
					app->is_softkey_reset_pushed = TRUE; GFX_PaintBoard(pMe); return TRUE;
					break;
				default:
					break;
			}
			break;
		case EVT_KEY_RELEASE:
			switch (wParam) {
				case AVK_SOFT1:
					app->is_softkey_menu_pushed = FALSE; GFX_PaintBoard(pMe); return TRUE;
					break;
				case AVK_SOFT2:
					app->is_softkey_reset_pushed = FALSE; GFX_PaintBoard(pMe); return TRUE;
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

static boolean APP_DeviceFill(AEEApplet *pMe) {
	AEEDeviceInfo device_info;
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	device_info.wStructSize = sizeof(AEEDeviceInfo);
	ISHELL_GetDeviceInfo(app->m_App.m_pIShell, &device_info);

	app->m_AppDevice.m_ScreenW = device_info.cxScreen;
	app->m_AppDevice.m_ScreenH = device_info.cyScreen;

	SETAEERECT(&app->m_AppDevice.m_RectScreen, 0, 0, app->m_AppDevice.m_ScreenW, app->m_AppDevice.m_ScreenH);

	switch (app->m_AppDevice.m_ScreenW) {
		default:
		case 240: /* 240x320 */
			app->m_AppDevice.m_TileSize = 48;
			app->m_AppDevice.m_OffsetX = 6;
			app->m_AppDevice.m_OffsetY = 6;
			app->m_AppDevice.m_OffsetW = 10;
			app->m_AppDevice.m_OffsetH = 6;
			app->m_AppDevice.m_Radius = 14;
			app->m_AppDevice.m_GapX = 0;
			app->m_AppDevice.m_GapY = 0;
			app->m_AppDevice.m_ZoomFactor = 3;
			app->m_AppDevice.m_FontX = AEE_FONT_LARGE;
			app->m_AppDevice.m_FontXX = AEE_FONT_LARGE;
			app->m_AppDevice.m_FontXXX = AEE_FONT_BOLD;
			app->m_AppDevice.m_FontXXXX = AEE_FONT_NORMAL;
			app->m_AppDevice.m_wstr_title = wstr_lbl_title;
			break;
		case 176: /* 176x220 */
			app->m_AppDevice.m_TileSize = 34;
			app->m_AppDevice.m_OffsetX = 4;
			app->m_AppDevice.m_OffsetY = 4;
			app->m_AppDevice.m_OffsetW = 10;
			app->m_AppDevice.m_OffsetH = 4;
			app->m_AppDevice.m_Radius = 10;
			app->m_AppDevice.m_GapX = 0;
			app->m_AppDevice.m_GapY = 0;
			app->m_AppDevice.m_ZoomFactor = 2;
			app->m_AppDevice.m_FontX = AEE_FONT_LARGE;
			app->m_AppDevice.m_FontXX = AEE_FONT_BOLD;
			app->m_AppDevice.m_FontXXX = AEE_FONT_BOLD;
			app->m_AppDevice.m_FontXXXX = AEE_FONT_NORMAL;
			app->m_AppDevice.m_wstr_title = wstr_lbl_title_small;
			break;
	}

	return TRUE;
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

	IDISPLAY_Update(app->m_App.m_pIDisplay);

	return TRUE;
}

static boolean GFX_PaintBackgroud(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	IDISPLAY_FillRect(app->m_App.m_pIDisplay, &app->m_AppDevice.m_RectScreen, COL_ARGB_BGRA(COLOR_BOARD));

	return TRUE;
}

static boolean GFX_PaintTile(AEEApplet *pMe, uint32 value, uint8 x, uint8 y) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	RGBVAL fc;
	RGBVAL bc;
	uint32 coord_x;
	uint32 coord_y;
	AEERect tile_r;

	coord_x = GFX_OffsetCoord(x, app->m_AppDevice.m_TileSize, app->m_AppDevice.m_OffsetX) + app->m_AppDevice.m_OffsetW;
	coord_y = GFX_OffsetCoord(y, app->m_AppDevice.m_TileSize, app->m_AppDevice.m_OffsetY) + app->m_AppDevice.m_OffsetH;
	SETAEERECT(&tile_r, coord_x, coord_y, app->m_AppDevice.m_TileSize, app->m_AppDevice.m_TileSize);

	fc = COL_ARGB_BGRA(COLOR_TEXT);
	bc = COL_ARGB_BGRA(e_background(value));

	if (app->m_AppSettings.m_RoundedRectangle) {
		IGRAPHICS_SetColor(app->m_pIGraphics, COL_BGRA(fc, R), COL_BGRA(fc, G), COL_BGRA(fc, B), COL_BGRA(fc, A));
		IGRAPHICS_SetFillColor(app->m_pIGraphics, COL_BGRA(bc, R), COL_BGRA(bc, G), COL_BGRA(bc, B), COL_BGRA(bc, A));
		IGRAPHICS_SetFillMode(app->m_pIGraphics, TRUE);
		IGRAPHICS_DrawRoundRectangle(app->m_pIGraphics, &tile_r, app->m_AppDevice.m_Radius, app->m_AppDevice.m_Radius);
	} else {
		IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_LINE, fc);
		IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, bc);
		IDisplay_FrameSolidRect(app->m_App.m_pIDisplay, &tile_r);
	}

	if (value) {
		AEEFont font;
		int nAscent;
		int nDescent;
		uint32 point_x;
		uint32 point_y;
		uint32 text_w;
		uint32 text_h;
		AECHAR wstr_value[TILE_VALUE_MAX_LENGTH];

		WSPRINTF(wstr_value, sizeof(AECHAR) * TILE_VALUE_MAX_LENGTH, L"%d", value);

		if (value < 10) {
			font = app->m_AppDevice.m_FontX;
		} else if (value < 100) {
			font = app->m_AppDevice.m_FontXX;
		} else if (value < 1000) {
			font = app->m_AppDevice.m_FontXXX;
		} else {
			font = app->m_AppDevice.m_FontXXXX;
		}

		IDISPLAY_GetFontMetrics(app->m_App.m_pIDisplay, font, &nAscent, &nDescent);
		text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, font, wstr_value);
		text_h = nAscent + nDescent;

		point_x = coord_x + ((app->m_AppDevice.m_TileSize - text_w) / 2) + app->m_AppDevice.m_GapX;
		point_y = coord_y + ((app->m_AppDevice.m_TileSize - text_h) / 2) + app->m_AppDevice.m_GapY;

		if (value < 64) {
			fc = COL_ARGB_BGRA(e_foreground(value));
		}

		IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_TEXT, fc);

		IDISPLAY_DrawText(app->m_App.m_pIDisplay, font, wstr_value, -1, point_x, point_y, NULL, IDF_TEXT_TRANSPARENT);
	}

	return TRUE;
}

static boolean GFX_PaintFinal(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	RGBVAL oc;
	RGBVAL tc;
	RGBVAL fc;
	RGBVAL sc;
	int nAscent;
	int nDescent;
	int text_w;
	int text_h;
	uint16 coord_x;
	uint16 coord_y;
	uint16 zoom_r;
	const AECHAR *wstr_game_end;
	AEERect frame_r;
	AECHAR wstr_score[SCORE_VALUE_MAX_LENGTH];

	oc = COL_ARGB_BGRA(COLOR_OVERLAY);
	tc = COL_ARGB_BGRA(COLOR_TEXT);
	fc = COL_ARGB_BGRA(COLOR_FINAL);
	sc = COL_ARGB_BGRA(COLOR_TILE_0);

	if (e_win || e_lose) {
		wstr_game_end = (e_win) ? wstr_game_win : wstr_game_over;

		/* XOR Screen Fill. */
		IGRAPHICS_SetColor(app->m_pIGraphics, COL_BGRA(oc, R), COL_BGRA(oc, G), COL_BGRA(oc, B), COL_BGRA(oc, A));
		IGRAPHICS_SetFillColor(app->m_pIGraphics, COL_BGRA(oc, R), COL_BGRA(oc, G), COL_BGRA(oc, B), COL_BGRA(oc, A));
		IGRAPHICS_SetFillMode(app->m_pIGraphics, TRUE);
		IGRAPHICS_SetPaintMode(app->m_pIGraphics, AEE_PAINT_XOR);
		IGRAPHICS_DrawRect(app->m_pIGraphics, &app->m_AppDevice.m_RectScreen);
		IGRAPHICS_SetPaintMode(app->m_pIGraphics, AEE_PAINT_COPY);

		IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_TEXT, fc);

		/* Text Metrics. */
		IDISPLAY_GetFontMetrics(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontX, &nAscent, &nDescent);
		text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontX, wstr_game_end);
		text_h = nAscent + nDescent;
		zoom_r = text_h / 2;

		coord_x = app->m_AppDevice.m_ScreenW / 2 - text_w / 2;
		coord_y = app->m_AppDevice.m_ScreenH / 2 - text_h / 2;

		SETAEERECT(&frame_r, coord_x - zoom_r, coord_y - zoom_r, text_w + zoom_r * 2, text_h + zoom_r * 2);

		/* Draw Text. */
		IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_LINE, fc);
		IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, oc);
		IDisplay_FrameSolidRect(app->m_App.m_pIDisplay, &frame_r);

		IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontX, wstr_game_end, -1,
			coord_x, coord_y, NULL, IDF_TEXT_TRANSPARENT);
	}

	/* Title and Score. */
	WSPRINTF(wstr_score, sizeof(AECHAR) * SCORE_VALUE_MAX_LENGTH, wstr_lbl_score, e_score);

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_TEXT, tc);

	IDISPLAY_GetFontMetrics(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, &nAscent, &nDescent);
	text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_score);
	text_h = nAscent + nDescent;
	zoom_r = text_h * app->m_AppDevice.m_ZoomFactor;
	if (app->m_AppDevice.m_ScreenW < 240) {
		zoom_r += text_h / 2; /* + 1.5 */
	}

	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, app->m_AppDevice.m_wstr_title, -1,
		app->m_AppDevice.m_OffsetW, app->m_AppDevice.m_ScreenH - zoom_r, NULL, IDF_TEXT_TRANSPARENT);

	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_score, -1,
		app->m_AppDevice.m_ScreenW - text_w - app->m_AppDevice.m_OffsetW,
		app->m_AppDevice.m_ScreenH - zoom_r, NULL, IDF_TEXT_TRANSPARENT);

	/* Soft Keys. */
	zoom_r = 2;

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_LINE, fc);

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, (app->is_softkey_menu_pushed) ? fc : sc);
	text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_menu);
	coord_x = app->m_AppDevice.m_OffsetW;
	coord_y = app->m_AppDevice.m_ScreenH - text_h - app->m_AppDevice.m_OffsetH;
	SETAEERECT(&frame_r, app->m_AppDevice.m_RectScreen.x - 1, coord_y - zoom_r,
		app->m_AppDevice.m_ScreenW / 2, text_h + zoom_r * 2);
	IDisplay_FrameSolidRect(app->m_App.m_pIDisplay, &frame_r);
	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_menu, -1, coord_x, coord_y,
		NULL, IDF_TEXT_TRANSPARENT);

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, (app->is_softkey_reset_pushed) ? fc : sc);
	text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_reset);
	coord_x = app->m_AppDevice.m_ScreenW - text_w - app->m_AppDevice.m_OffsetW;
	coord_y = app->m_AppDevice.m_ScreenH - text_h - app->m_AppDevice.m_OffsetH;
	SETAEERECT(&frame_r, app->m_AppDevice.m_ScreenW / 2 + 1, coord_y - zoom_r,
		app->m_AppDevice.m_ScreenW / 2, text_h + zoom_r * 2);
	IDisplay_FrameSolidRect(app->m_App.m_pIDisplay, &frame_r);
	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_reset, -1, coord_x, coord_y,
		NULL, IDF_TEXT_TRANSPARENT);

	return TRUE;
}
