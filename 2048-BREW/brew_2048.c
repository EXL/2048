/*
 * About:
 *   A popular "2048" puzzle game for Qualcomm BREW platform written using AEE framework.
 *
 * Author:
 *   EXL
 *
 * License:
 *   MIT
 *
 * Additional information:
 *   1. starting_brew.pdf
 *   2. https://github.com/usernameak/brew-cmake-toolchain
 */

#include <AEEAppGen.h>
#include <AEEShell.h>
#include <AEEStdLib.h>
#include <AEEGraphics.h>
#include <AEESound.h>
#include <AEEMenu.h>
#include <AEEFile.h>

#include "brew_2048.bid"
#include "brew_2048.brh"

#include "2048.h"

#define SETTINGS_FILENAME                     "brew_2048.dat"
#define GAMESAVE_FILENAME                     "brew_2048.sav"

#define WSTR_TITLE_MAX                                   (64)
#define WSTR_TEXT_MAX                                   (128)
#define WSTR_LONG_TEXT_MAX                             (1024)
#define SCORE_VALUE_MAX_LENGTH                           (16)
#define TILE_VALUE_MAX_LENGTH                             (5)
#define SHOW_NOTIFICATION_DELAY_MS                     (1200) /* 1.2 seconds. */
#define TONE_SOUND_DELAY_MS                             (500) /* 0.5 seconds. */

typedef enum { R, G, B, A } APP_COLOR_COMPONENT_T;

typedef enum {
	APP_STATE_GAME,
	APP_STATE_MENU_MAIN,
	APP_STATE_MENU_TILE,
	APP_STATE_NOTIFICATION,
	APP_STATE_HELP,
	APP_STATE_ABOUT,
	APP_STATE_MAX
} APP_STATE_T;

typedef enum {
	APP_MENU_ITEM_SAVE,
	APP_MENU_ITEM_LOAD,
	APP_MENU_ITEM_RESET,
	APP_MENU_ITEM_TILES,
	APP_MENU_ITEM_TILES_RECTANGLE,
	APP_MENU_ITEM_TILES_ROUNDED,
	APP_MENU_ITEM_HELP,
	APP_MENU_ITEM_ABOUT,
	APP_MENU_ITEM_EXIT,
	APP_MENU_ITEM_MAX
} APP_MENU_T;

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

	AEEFont m_FontX;       /* Large Size Font. */
	AEEFont m_FontXX;      /* Big Size Font. */
	AEEFont m_FontXXX;     /* Meduim/Regular Size Font. */
	AEEFont m_FontXXXX;    /* Small Size Font. */
} APP_DEVICE_T;

typedef struct {
	boolean m_RoundedRectangle;
} APP_SETTINGS_T;

typedef struct {
	JulianType date_time;
	uint16 board[BOARD_SIZE];
	uint16 win;
	uint16 lose;
	uint16 score;
} APP_SAVE_T;

typedef struct {
	AEEApplet m_App;

	APP_DEVICE_T m_AppDevice;
	APP_SETTINGS_T m_AppSettings;
	APP_SAVE_T m_AppSave;

	IGraphics *m_pIGraphics;
	IFileMgr *m_pIFileMgr;
	ISound *m_pISound;

	IMenuCtl *m_pIMenuMainCtl;
	IMenuCtl *m_pIMenuTileCtl;

	IStatic *m_pIStatic;

	boolean is_softkey_menu_pushed;
	boolean is_softkey_reset_pushed;

	APP_STATE_T m_AppState;
} APP_INSTANCE_T;

static boolean APP_InitAppData(AEEApplet *pMe);
static boolean APP_FreeAppData(AEEApplet *pMe);
static boolean APP_HandleEvent(AEEApplet *pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam);
static boolean APP_DeviceFill(AEEApplet *pMe);

static boolean APP_MenuMainInit(AEEApplet *pMe);
static boolean APP_MenuTilesInit(AEEApplet *pMe);
static boolean APP_ShowNotification(AEEApplet *pMe, const AECHAR *aTitle, const AECHAR *aText, const AECHAR *aDesc);
static boolean APP_ShowHelp(AEEApplet *pMe);
static boolean APP_ShowAbout(AEEApplet *pMe);
static boolean APP_ShowGame(AEEApplet *pMe);
static boolean APP_UpdateMenu(AEEApplet *pMe);

static boolean GFX_PaintBoard(AEEApplet *pMe);
static boolean GFX_PaintBackgroud(AEEApplet *pMe);
static boolean GFX_PaintTile(AEEApplet *pMe, uint32 value, uint8 x, uint8 y);
static boolean GFX_PaintFinal(AEEApplet *pMe);

static boolean GFX_PaintRedrawAll(AEEApplet *pMe);
static boolean GFX_SetCustomColors(AEEApplet *pMe);

static boolean APP_SaveSettings(AEEApplet *pMe);
static boolean APP_LoadSettings(AEEApplet *pMe);
static boolean APP_SaveAndLoadGame(AEEApplet *pMe, boolean aSave);
static boolean APP_SaveGame(AEEApplet *pMe);
static boolean APP_LoadGame(AEEApplet *pMe);

static boolean APP_PlaySoundTone(AEEApplet *pMe, AEESoundTone aSoundTone);

const AECHAR *wstr_lbl_title = L"2048-BREW";
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

static inline RGBVAL COL_BUMP(uint32 color, int32 bump) {
	uint32 A = ((color >> 24) & 0xFF) + bump;
	uint32 R = ((color >> 16) & 0xFF) + bump;
	uint32 G = ((color >>  8) & 0xFF) + bump;
	uint32 B = ((color >>  0) & 0xFF) + bump;
	return MAKE_RGBA(R, G, B, A);
}

static inline uint32 GFX_OffsetCoord(uint8 coord, uint16 tile_size, uint16 offset) {
	return (coord * (tile_size + offset) + offset);
}

AEEResult AEEClsCreateInstance(AEECLSID ClsId, IShell *pIShell, IModule *pMod, void **ppObj) {
	*ppObj = NULL;
	if (ClsId == AEECLSID_BREW_2048) {
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
	app->m_AppState = APP_STATE_GAME;

	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_GRAPHICS, (void **) &app->m_pIGraphics) != AEE_SUCCESS) {
		return FALSE;
	}
	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_MENUCTL, (void **) &app->m_pIMenuMainCtl) != AEE_SUCCESS) {
		return FALSE;
	}
	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_MENUCTL, (void **) &app->m_pIMenuTileCtl) != AEE_SUCCESS) {
		return FALSE;
	}
	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_FILEMGR, (void **) &app->m_pIFileMgr) != AEE_SUCCESS) {
		return FALSE;
	}
	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_SOUND, (void **) &app->m_pISound) != AEE_SUCCESS) {
		return FALSE;
	}
	if (ISHELL_CreateInstance(app->m_App.m_pIShell, AEECLSID_STATIC, (void **) &app->m_pIStatic) != AEE_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

static boolean APP_FreeAppData(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	IGRAPHICS_Release(app->m_pIGraphics);
	IMENUCTL_Release(app->m_pIMenuMainCtl);
	IMENUCTL_Release(app->m_pIMenuTileCtl);
	IFILEMGR_Release(app->m_pIFileMgr);
	ISOUND_Release(app->m_pISound);
	ISTATIC_Release(app->m_pIStatic);

	return TRUE;
}

static boolean APP_HandleEvent(AEEApplet *pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	switch (eCode) {
		case EVT_APP_START:
			APP_LoadSettings(pMe);
			APP_MenuMainInit(pMe);
			APP_MenuTilesInit(pMe);
			return APP_ShowGame(pMe);
		case EVT_APP_STOP:
			return TRUE;
		case EVT_DIALOG_END:
		case EVT_COPYRIGHT_END:
			switch (app->m_AppState) {
				case APP_STATE_HELP:
				case APP_STATE_ABOUT:
					app->m_AppState = APP_STATE_MENU_MAIN;
					IMENUCTL_SetActive(app->m_pIMenuMainCtl, TRUE);
					break;
				default:
					APP_ShowGame(pMe);
					break;
			}
			return TRUE;
		case EVT_COMMAND:
			switch (wParam) {
				case APP_MENU_ITEM_SAVE:
					return APP_SaveAndLoadGame(pMe, TRUE);
				case APP_MENU_ITEM_LOAD:
					return APP_SaveAndLoadGame(pMe, FALSE);
				case APP_MENU_ITEM_RESET:
					e_key(AVK_0);
					IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);
					return APP_ShowGame(pMe);
				case APP_MENU_ITEM_TILES:
					app->m_AppState = APP_STATE_MENU_TILE;
					IMENUCTL_SetSel(app->m_pIMenuTileCtl, APP_MENU_ITEM_TILES_RECTANGLE);
					IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);
					IMENUCTL_SetActive(app->m_pIMenuTileCtl, TRUE);
					return TRUE;
				case APP_MENU_ITEM_TILES_RECTANGLE:
					app->m_AppSettings.m_RoundedRectangle = FALSE;
					APP_UpdateMenu(pMe);
					APP_SaveSettings(pMe);
					IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);
					IMENUCTL_SetActive(app->m_pIMenuTileCtl, FALSE);
					return APP_ShowGame(pMe);
				case APP_MENU_ITEM_TILES_ROUNDED:
					app->m_AppSettings.m_RoundedRectangle = TRUE;
					APP_UpdateMenu(pMe);
					APP_SaveSettings(pMe);
					IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);
					IMENUCTL_SetActive(app->m_pIMenuTileCtl, FALSE);
					return APP_ShowGame(pMe);
				case APP_MENU_ITEM_HELP:
					return APP_ShowHelp(pMe);
				case APP_MENU_ITEM_ABOUT:
					return APP_ShowAbout(pMe);
				case APP_MENU_ITEM_EXIT:
					return ISHELL_CloseApplet(app->m_App.m_pIShell, FALSE);
				default:
					break;
			}
			break;
		case EVT_KEY:
			switch (app->m_AppState) {
				case APP_STATE_MENU_MAIN:
					if (wParam == AVK_CLR || wParam == AVK_SOFT2) {
						IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);
						return APP_ShowGame(pMe);
					} else {
						return IMENUCTL_HandleEvent(app->m_pIMenuMainCtl, eCode, wParam, dwParam);
					}
					break;
				case APP_STATE_MENU_TILE:
					if (wParam == AVK_CLR || wParam == AVK_SOFT2) {
						app->m_AppState = APP_STATE_MENU_MAIN;
						IMENUCTL_SetActive(app->m_pIMenuTileCtl, FALSE);
						IMENUCTL_SetActive(app->m_pIMenuMainCtl, TRUE);
						return TRUE;
					} else {
						return IMENUCTL_HandleEvent(app->m_pIMenuTileCtl, eCode, wParam, dwParam);
					}
					break;
				case APP_STATE_HELP:
					if (wParam == AVK_CLR || wParam == AVK_SELECT || wParam == AVK_SOFT2) {
						app->m_AppState = APP_STATE_MENU_MAIN;
						ISTATIC_SetActive(app->m_pIStatic, FALSE);
						IMENUCTL_SetActive(app->m_pIMenuMainCtl, TRUE);
						return TRUE;
					} else {
						return ISTATIC_HandleEvent(app->m_pIStatic, eCode, wParam, dwParam);
					}
				case APP_STATE_GAME:
					switch (wParam) {
						case AVK_0:
						case AVK_LEFT:
						case AVK_RIGHT:
						case AVK_UP:
						case AVK_DOWN:
							e_key(wParam);
							return GFX_PaintRedrawAll(pMe);
						case AVK_4:
							e_key(AVK_LEFT);
							return GFX_PaintRedrawAll(pMe);
						case AVK_6:
							e_key(AVK_RIGHT);
							return GFX_PaintRedrawAll(pMe);
						case AVK_2:
							e_key(AVK_UP);
							return GFX_PaintRedrawAll(pMe);
						case AVK_8:
							e_key(AVK_DOWN);
							return GFX_PaintRedrawAll(pMe);
						case AVK_SOFT2:
							e_key(AVK_0);
							return GFX_PaintRedrawAll(pMe);
						default:
							break;
					}
				default:
					break;
			}
			break;
		case EVT_KEY_PRESS:
			if (app->m_AppState == APP_STATE_GAME) {
				switch (wParam) {
					case AVK_SOFT1:
						app->is_softkey_menu_pushed = TRUE;
						return GFX_PaintRedrawAll(pMe);
					case AVK_SOFT2:
						app->is_softkey_reset_pushed = TRUE;
						return GFX_PaintRedrawAll(pMe);
					default:
						break;
				}
			}
			break;
		case EVT_KEY_RELEASE:
			if (app->m_AppState == APP_STATE_GAME) {
				switch (wParam) {
					case AVK_SOFT1:
						app->is_softkey_menu_pushed = FALSE;
						app->m_AppState = APP_STATE_MENU_MAIN;
						GFX_PaintRedrawAll(pMe);
						IMENUCTL_SetSel(app->m_pIMenuMainCtl, APP_MENU_ITEM_SAVE);
						IMENUCTL_SetActive(app->m_pIMenuMainCtl, TRUE);
						return TRUE;
					case AVK_SOFT2:
						app->is_softkey_reset_pushed = FALSE;
						return GFX_PaintRedrawAll(pMe);
					default:
						break;
				}
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
		case 240: /* Precalculated 240x320 values. */
			app->m_AppDevice.m_TileSize = 48;
			app->m_AppDevice.m_OffsetX = 6;
			app->m_AppDevice.m_OffsetY = 6;
			app->m_AppDevice.m_OffsetW = 10;
			app->m_AppDevice.m_OffsetH = 6;
			app->m_AppDevice.m_Radius = 14;
			app->m_AppDevice.m_GapX = 0;
			app->m_AppDevice.m_GapY = 0;
			app->m_AppDevice.m_FontX = AEE_FONT_LARGE;
			app->m_AppDevice.m_FontXX = AEE_FONT_LARGE;
			app->m_AppDevice.m_FontXXX = AEE_FONT_BOLD;
			app->m_AppDevice.m_FontXXXX = AEE_FONT_NORMAL;
			break;
		case 176: /* Precalculated 176x220 values. */
			app->m_AppDevice.m_TileSize = 34;
			app->m_AppDevice.m_OffsetX = 4;
			app->m_AppDevice.m_OffsetY = 4;
			app->m_AppDevice.m_OffsetW = 10;
			app->m_AppDevice.m_OffsetH = 4;
			app->m_AppDevice.m_Radius = 10;
			app->m_AppDevice.m_GapX = 0;
			app->m_AppDevice.m_GapY = 0;
			app->m_AppDevice.m_FontX = AEE_FONT_LARGE;
			app->m_AppDevice.m_FontXX = AEE_FONT_BOLD;
			app->m_AppDevice.m_FontXXX = AEE_FONT_BOLD;
			app->m_AppDevice.m_FontXXXX = AEE_FONT_NORMAL;
			break;
	}

	return TRUE;
}

static boolean APP_MenuMainInit(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	CtlAddItem menu_item;

	IMENUCTL_SetRect(app->m_pIMenuMainCtl, &app->m_AppDevice.m_RectScreen);
	IMENUCTL_SetTitle(app->m_pIMenuMainCtl, BREW_2048_RES_FILE, IDS_MENU_TITLE_MAIN, NULL);
	IMENUCTL_SetProperties(app->m_pIMenuMainCtl, MP_UNDERLINE_TITLE | MP_WRAPSCROLL);

	menu_item.pText = NULL;
	menu_item.pImage = NULL;
	menu_item.pszResText = BREW_2048_RES_FILE;
	menu_item.pszResImage = BREW_2048_RES_FILE;
	menu_item.wFont = AEE_FONT_NORMAL;
	menu_item.dwData = 0;

	menu_item.wText = IDS_MENU_ITEM_SAVE;
	menu_item.wImage = IDI_ICON_SAVE;
	menu_item.wItemID = APP_MENU_ITEM_SAVE;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_LOAD;
	menu_item.wImage = IDI_ICON_LOAD;
	menu_item.wItemID = APP_MENU_ITEM_LOAD;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_RESET;
	menu_item.wImage = IDI_ICON_RESET;
	menu_item.wItemID = APP_MENU_ITEM_RESET;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_TILES;
	menu_item.wImage = IDI_ICON_TILE;
	menu_item.wItemID = APP_MENU_ITEM_TILES;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_HELP;
	menu_item.wImage = IDI_ICON_HELP;
	menu_item.wItemID = APP_MENU_ITEM_HELP;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_ABOUT;
	menu_item.wImage = IDI_ICON_ABOUT;
	menu_item.wItemID = APP_MENU_ITEM_ABOUT;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_EXIT;
	menu_item.wImage = IDI_ICON_EXIT;
	menu_item.wItemID = APP_MENU_ITEM_EXIT;
	IMENUCTL_AddItemEx(app->m_pIMenuMainCtl, &menu_item);

	IMENUCTL_EnableCommand(app->m_pIMenuMainCtl, TRUE);

	return TRUE;
}

static boolean APP_MenuTilesInit(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	CtlAddItem menu_item;

	IMENUCTL_SetRect(app->m_pIMenuTileCtl, &app->m_AppDevice.m_RectScreen);
	IMENUCTL_SetTitle(app->m_pIMenuTileCtl, BREW_2048_RES_FILE, IDS_MENU_TITLE_TILE, NULL);
	IMENUCTL_SetProperties(app->m_pIMenuTileCtl, MP_UNDERLINE_TITLE | MP_WRAPSCROLL);

	menu_item.pText = NULL;
	menu_item.pImage = NULL;
	menu_item.pszResText = BREW_2048_RES_FILE;
	menu_item.pszResImage = BREW_2048_RES_FILE;
	menu_item.wFont = AEE_FONT_NORMAL;
	menu_item.dwData = 0;

	menu_item.wText = IDS_MENU_ITEM_RECTANGLE;
	menu_item.wImage = (app->m_AppSettings.m_RoundedRectangle) ? IDI_ICON_CHECKBOX_FALSE : IDI_ICON_CHECKBOX_TRUE;
	menu_item.wItemID = APP_MENU_ITEM_TILES_RECTANGLE;
	IMENUCTL_AddItemEx(app->m_pIMenuTileCtl, &menu_item);

	menu_item.wText = IDS_MENU_ITEM_ROUNDED;
	menu_item.wImage = (app->m_AppSettings.m_RoundedRectangle) ? IDI_ICON_CHECKBOX_TRUE : IDI_ICON_CHECKBOX_FALSE;
	menu_item.wItemID = APP_MENU_ITEM_TILES_ROUNDED;
	IMENUCTL_AddItemEx(app->m_pIMenuTileCtl, &menu_item);

	IMENUCTL_EnableCommand(app->m_pIMenuTileCtl, TRUE);

	return TRUE;
}

static boolean APP_ShowNotification(AEEApplet *pMe, const AECHAR *aTitle, const AECHAR *aText, const AECHAR *aDesc) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	AEERect rNot;
	int nAscent;
	int nDescent;
	int text_h;

	app->m_AppState = APP_STATE_NOTIFICATION;
	IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);

	GFX_PaintRedrawAll(pMe);
	GFX_SetCustomColors(pMe);

	IDISPLAY_GetFontMetrics(app->m_App.m_pIDisplay, AEE_FONT_BOLD, &nAscent, &nDescent);
	text_h = nAscent + nDescent;
	SETAEERECT(&rNot,
		app->m_AppDevice.m_OffsetX,
		(app->m_AppDevice.m_RectScreen.dy / 2) - text_h * 2,
		app->m_AppDevice.m_RectScreen.dx - (app->m_AppDevice.m_OffsetX * 2),
		text_h * 4
	);

	IDISPLAY_DrawRect(app->m_App.m_pIDisplay, &rNot,
		COL_ARGB_BGRA(COLOR_TEXT), COL_ARGB_BGRA(COLOR_BOARD), IDF_RECT_FRAME | IDF_RECT_FILL);

	rNot.x  += 1;
	rNot.dx -= 1 * 2;
	rNot.y  += 2;
	rNot.dy -= 2 * 2;

	IDISPLAY_DrawText(app->m_App.m_pIDisplay, AEE_FONT_BOLD, aTitle, -1, 0, 0, &rNot,
		IDF_ALIGN_CENTER | IDF_ALIGN_TOP);
	IDISPLAY_DrawText(app->m_App.m_pIDisplay, AEE_FONT_NORMAL, aText, -1, 0, 0, &rNot,
		IDF_ALIGN_CENTER | IDF_ALIGN_MIDDLE);
	if (aDesc) {
		IDISPLAY_DrawText(app->m_App.m_pIDisplay, AEE_FONT_NORMAL, aDesc, -1, 0, 0, &rNot,
			IDF_ALIGN_CENTER | IDF_ALIGN_BOTTOM);
	}

	IDISPLAY_Update(app->m_App.m_pIDisplay);
	ISHELL_SetTimer(app->m_App.m_pIShell, SHOW_NOTIFICATION_DELAY_MS, (PFNNOTIFY) APP_ShowGame, (void *) pMe);

	return TRUE;
}

static boolean APP_ShowHelp(AEEApplet *pMe) {
	const uint32 text_size = sizeof(AECHAR) * WSTR_LONG_TEXT_MAX; /* 2048 bytes, 1024 characters. */
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	AECHAR title[WSTR_TITLE_MAX];
	AECHAR *text;
	boolean load_ok;

	app->m_AppState = APP_STATE_HELP;
	IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);

	GFX_SetCustomColors(pMe);
	IDISPLAY_ClearScreen(app->m_App.m_pIDisplay);

	text = (AECHAR *) MALLOC(text_size);
	load_ok = ISHELL_LoadResString(app->m_App.m_pIShell, BREW_2048_RES_FILE, IDS_HELP_TITLE, title, WSTR_TITLE_MAX);
	load_ok = ISHELL_LoadResString(app->m_App.m_pIShell, BREW_2048_RES_FILE, IDS_HELP_TEXT, text, text_size);

	if (!text || !load_ok) {
		if (text) {
			FREE(text);
		}
		return FALSE;
	}

	ISTATIC_SetProperties(app->m_pIStatic, ST_TEXTALLOC | ST_UNDERLINE);
	ISTATIC_SetText(app->m_pIStatic, title, text, AEE_FONT_BOLD, AEE_FONT_NORMAL);
	ISTATIC_SetActive(app->m_pIStatic, TRUE);
	ISTATIC_Redraw(app->m_pIStatic);

	return TRUE;
}

static boolean APP_ShowAbout(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	app->m_AppState = APP_STATE_ABOUT;
	IMENUCTL_SetActive(app->m_pIMenuMainCtl, FALSE);

	GFX_SetCustomColors(pMe);
	IDISPLAY_ClearScreen(app->m_App.m_pIDisplay);

	ISHELL_ShowCopyright(app->m_App.m_pIShell);

	return TRUE;
}

static boolean APP_ShowGame(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	app->m_AppState = APP_STATE_GAME;

	GFX_SetCustomColors(pMe);
	GFX_PaintRedrawAll(pMe);

	return TRUE;
}

static boolean APP_UpdateMenu(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	CtlAddItem menu_item;

	menu_item.pText = NULL;
	menu_item.pImage = NULL;
	menu_item.pszResText = BREW_2048_RES_FILE;
	menu_item.pszResImage = BREW_2048_RES_FILE;
	menu_item.wFont = AEE_FONT_NORMAL;
	menu_item.dwData = 0;

	menu_item.wImage = (app->m_AppSettings.m_RoundedRectangle) ? IDI_ICON_CHECKBOX_FALSE : IDI_ICON_CHECKBOX_TRUE;
	IMENUCTL_SetItem(app->m_pIMenuTileCtl, APP_MENU_ITEM_TILES_RECTANGLE, MSIF_IMAGE, &menu_item);

	menu_item.wImage = (app->m_AppSettings.m_RoundedRectangle) ? IDI_ICON_CHECKBOX_TRUE : IDI_ICON_CHECKBOX_FALSE;
	IMENUCTL_SetItem(app->m_pIMenuTileCtl, APP_MENU_ITEM_TILES_ROUNDED, MSIF_IMAGE, &menu_item);

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
	const AECHAR *score_string;

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
	text_h = nAscent + nDescent;

	zoom_r = 1;
	text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_score);

	if (e_score > 0) {
		score_string = &wstr_score[0];
	} else {
		score_string = wstr_lbl_title;
	}

	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, score_string, -1,
	app->m_AppDevice.m_ScreenW - text_w - app->m_AppDevice.m_OffsetW,
	app->m_AppDevice.m_ScreenH - text_h * 2 - zoom_r,
	NULL, IDF_TEXT_TRANSPARENT);

	/* Soft Keys. */
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_LINE, fc);

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, (app->is_softkey_menu_pushed) ? fc : sc);
	text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_menu);
	coord_x = app->m_AppDevice.m_OffsetW;
	coord_y = app->m_AppDevice.m_ScreenH - text_h - app->m_AppDevice.m_OffsetH;
	SETAEERECT(&frame_r, app->m_AppDevice.m_RectScreen.x - 1, coord_y - zoom_r,
		app->m_AppDevice.m_ScreenW / 2, text_h + zoom_r);
	IDisplay_FrameSolidRect(app->m_App.m_pIDisplay, &frame_r);
	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_menu, -1, coord_x, coord_y,
		NULL, IDF_TEXT_TRANSPARENT);

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, (app->is_softkey_reset_pushed) ? fc : sc);
	text_w = IDISPLAY_MeasureText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_reset);
	coord_x = app->m_AppDevice.m_ScreenW - text_w - app->m_AppDevice.m_OffsetW;
	coord_y = app->m_AppDevice.m_ScreenH - text_h - app->m_AppDevice.m_OffsetH;
	SETAEERECT(&frame_r, app->m_AppDevice.m_ScreenW / 2 + 1, coord_y - zoom_r,
		app->m_AppDevice.m_ScreenW / 2, text_h + zoom_r);
	IDisplay_FrameSolidRect(app->m_App.m_pIDisplay, &frame_r);
	IDISPLAY_DrawText(app->m_App.m_pIDisplay, app->m_AppDevice.m_FontXXXX, wstr_soft_reset, -1, coord_x, coord_y,
		NULL, IDF_TEXT_TRANSPARENT);

	return TRUE;
}

static boolean GFX_PaintRedrawAll(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;

	GFX_PaintBoard(pMe);

	IDISPLAY_Update(app->m_App.m_pIDisplay);

	return TRUE;
}

static boolean GFX_SetCustomColors(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	AEEMenuColors menu_colors;

	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_WIN, COL_ARGB_BGRA(COLOR_BOARD));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_TEXT, COL_ARGB_BGRA(COLOR_TEXT));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_BACKGROUND, COL_ARGB_BGRA(COLOR_BOARD));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_USER_LINE, COL_ARGB_BGRA(COLOR_BOARD));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_FRAME_HI, COL_BUMP(COLOR_TEXT, 0x60));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_FRAME_LO, COL_BUMP(COLOR_TEXT, -0x60));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_LT_SHADOW, COL_BUMP(COLOR_TEXT, 0x70));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_DK_SHADOW, COL_BUMP(COLOR_TEXT, -0x40));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_SCROLLBAR, COL_ARGB_BGRA(COLOR_TEXT));
	IDISPLAY_SetColor(app->m_App.m_pIDisplay, CLR_SYS_SCROLLBAR_FILL, COL_ARGB_BGRA(COLOR_FINAL));

	menu_colors.wMask = 0xFFFF;
	menu_colors.cBack = COL_ARGB_BGRA(COLOR_BOARD);
	menu_colors.cText = COL_ARGB_BGRA(COLOR_TEXT);
	menu_colors.cSelBack = COL_ARGB_BGRA(COLOR_FINAL);
	menu_colors.cSelText = COL_BUMP(COLOR_TEXT, 0x70);
	menu_colors.cFrame = COL_ARGB_BGRA(COLOR_TEXT);
	menu_colors.cScrollbar = COL_ARGB_BGRA(COLOR_TEXT);
	menu_colors.cScrollbarFill = COL_ARGB_BGRA(COLOR_FINAL);
	menu_colors.cTitle = COL_ARGB_BGRA(COLOR_BOARD);
	menu_colors.cTitleText = COL_ARGB_BGRA(COLOR_TEXT);

	IMENUCTL_SetColors(app->m_pIMenuMainCtl, &menu_colors);
	IMENUCTL_SetColors(app->m_pIMenuTileCtl, &menu_colors);

	return TRUE;
}

static boolean APP_SaveSettings(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	IFile *pIFile;
	uint32 bytes;

	pIFile = NULL;

	bytes = IFILEMGR_GetFreeSpace(app->m_pIFileMgr, NULL);
	if (bytes > sizeof(app->m_AppSettings)) {
		if (IFILEMGR_Test(app->m_pIFileMgr, SETTINGS_FILENAME) == AEE_SUCCESS) {
			pIFile = IFILEMGR_OpenFile(app->m_pIFileMgr, SETTINGS_FILENAME, _OFM_READWRITE);
		} else {
			pIFile = IFILEMGR_OpenFile(app->m_pIFileMgr, SETTINGS_FILENAME, _OFM_CREATE);
		}
		if (pIFile) {
			bytes = IFILE_Write(pIFile, (PACKED const void *) &app->m_AppSettings, sizeof(app->m_AppSettings));
			IFILE_Release(pIFile);
			if (bytes == sizeof(app->m_AppSettings)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

static boolean APP_LoadSettings(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	IFile *pIFile;
	uint32 bytes;

	pIFile = NULL;

	if (IFILEMGR_Test(app->m_pIFileMgr, SETTINGS_FILENAME) == AEE_SUCCESS) {
		pIFile = IFILEMGR_OpenFile(app->m_pIFileMgr, SETTINGS_FILENAME, _OFM_READ);
		if (pIFile) {
			bytes = IFILE_Read(pIFile, (PACKED void *) &app->m_AppSettings, sizeof(app->m_AppSettings));
			IFILE_Release(pIFile);
			if (bytes == sizeof(app->m_AppSettings)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

static boolean APP_SaveAndLoadGame(AEEApplet *pMe, boolean aSave) {
	const uint32 s = sizeof(AECHAR);
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	AECHAR title[WSTR_TITLE_MAX];
	AECHAR text[WSTR_TEXT_MAX];
	AECHAR time_date[WSTR_TEXT_MAX];
	boolean result;
	uint16 res_ok_title;
	uint16 res_err_title;
	uint16 res_err_text;
	AEESoundTone tone;

	if (aSave) {
		result = APP_SaveGame(pMe);
		res_ok_title = IDS_SAVE_TITLE;
		res_err_title = IDS_SAVE_ERROR_TITLE;
		res_err_text = IDS_SAVE_ERROR_TEXT;
		tone = AEE_TONE_WARN;
	} else {
		result = APP_LoadGame(pMe);
		res_ok_title = IDS_LOAD_TITLE;
		res_err_title = IDS_LOAD_ERROR_TITLE;
		res_err_text = IDS_LOAD_ERROR_TEXT;
		tone = AEE_TONE_CTRL;
	}

	if (result) {
		ISHELL_LoadResString(app->m_App.m_pIShell, BREW_2048_RES_FILE, res_ok_title, title, s * WSTR_TITLE_MAX);
		ISHELL_LoadResString(app->m_App.m_pIShell, BREW_2048_RES_FILE, IDS_STATE, text, s * WSTR_TEXT_MAX);
		WSPRINTF(time_date, s * WSTR_TEXT_MAX, L"%02d:%02d:%02d %02d/%02d/%04d",
			 app->m_AppSave.date_time.wHour, app->m_AppSave.date_time.wMinute, app->m_AppSave.date_time.wSecond,
			 app->m_AppSave.date_time.wMonth, app->m_AppSave.date_time.wDay, app->m_AppSave.date_time.wYear);
		APP_PlaySoundTone(pMe, tone);
		return APP_ShowNotification(pMe, title, text, time_date);
	} else {
		ISHELL_LoadResString(app->m_App.m_pIShell, BREW_2048_RES_FILE, res_err_title, title, s * WSTR_TITLE_MAX);
		ISHELL_LoadResString(app->m_App.m_pIShell, BREW_2048_RES_FILE, res_err_text, text, s * WSTR_TEXT_MAX);
		return APP_ShowNotification(pMe, title, text, NULL);
	}

	return TRUE;
}

static boolean APP_SaveGame(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	IFile *pIFile;
	uint32 bytes;

	pIFile = NULL;

	bytes = IFILEMGR_GetFreeSpace(app->m_pIFileMgr, NULL);
	if (bytes > sizeof(app->m_AppSettings)) {
		if (IFILEMGR_Test(app->m_pIFileMgr, GAMESAVE_FILENAME) == AEE_SUCCESS) {
			pIFile = IFILEMGR_OpenFile(app->m_pIFileMgr, GAMESAVE_FILENAME, _OFM_READWRITE);
		} else {
			pIFile = IFILEMGR_OpenFile(app->m_pIFileMgr, GAMESAVE_FILENAME, _OFM_CREATE);
		}
		if (pIFile) {
			uint16 i;
			GETJULIANDATE(0, &app->m_AppSave.date_time);
			app->m_AppSave.win = e_win;
			app->m_AppSave.lose = e_lose;
			app->m_AppSave.score = e_score;
			for (i = 0; i < BOARD_SIZE; ++i) {
				app->m_AppSave.board[i] = e_board[i];
			}

			bytes = IFILE_Write(pIFile, (PACKED const void *) &app->m_AppSave, sizeof(app->m_AppSave));
			IFILE_Release(pIFile);
			if (bytes == sizeof(app->m_AppSave)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

static boolean APP_LoadGame(AEEApplet *pMe) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	IFile *pIFile;
	uint32 bytes;

	pIFile = NULL;

	if (IFILEMGR_Test(app->m_pIFileMgr, GAMESAVE_FILENAME) == AEE_SUCCESS) {
		pIFile = IFILEMGR_OpenFile(app->m_pIFileMgr, GAMESAVE_FILENAME, _OFM_READ);
		if (pIFile) {
			bytes = IFILE_Read(pIFile, (PACKED void *) &app->m_AppSave, sizeof(app->m_AppSave));
			IFILE_Release(pIFile);
			if (bytes == sizeof(app->m_AppSave)) {
				uint16 i;
				e_win = app->m_AppSave.win;
				e_lose = app->m_AppSave.lose;
				e_score = app->m_AppSave.score;
				for (i = 0; i < BOARD_SIZE; ++i) {
					e_board[i] = app->m_AppSave.board[i];
				}
				return TRUE;
			}
		}
	}

	return FALSE;
}

static boolean APP_PlaySoundTone(AEEApplet *pMe, AEESoundTone aSoundTone) {
	APP_INSTANCE_T *app = (APP_INSTANCE_T *) pMe;
	AEESoundToneData tone;

	tone.eTone = aSoundTone;
	tone.wDuration = TONE_SOUND_DELAY_MS;

	ISOUND_PlayTone(app->m_pISound, tone);

	return TRUE;
}
