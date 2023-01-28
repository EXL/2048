/*
 * About:
 *   A popular "2048" puzzle game for Motorola P2K as native ELF-application written using AFW and UIS frameworks.
 *
 * Author:
 *   EXL
 *
 * License:
 *   MIT
 *
 * Application type:
 *   GUI
 *
 * Additional information:
 *   1. https://forum.motofan.ru/index.php?showforum=184
 *   2. https://wiki.motofan.ru/ElfPack
 *   3. https://wiki.motofan.ru/ElfPack2
 */

#include <loader.h>
#include <apps.h>
#include <uis.h>
#include <canvas.h>
#include <mem.h>
#include <utilities.h>
#include <dl.h>
#include <filesystem.h>
#include <time_date.h>
#include <mme.h>
#include <dl_keypad.h>

#include "2048.h"

#include "p2k_app_icon_15x15_gif.h"
#include "p2k_app_icon_41x41_gif.h"

#define TIMER_FAST_TRIGGER_MS             (1)
#define TIMER_POPUP_DELAY_MS            (100)
#define SCORE_TITLE_MAX_LENGTH           (16)
#define SCORE_VALUE_MAX_LENGTH            (6)
#define TILE_VALUE_MAX_LENGTH             (5)

typedef enum {
	APP_STATE_ANY,
	APP_STATE_INIT,
	APP_STATE_MAIN,
	APP_STATE_MENU,
	APP_STATE_POPUP,
	APP_STATE_SELECT,
	APP_STATE_VIEW,
	APP_STATE_MAX
} APP_STATE_T;

typedef enum {
	APP_TIMER_EXIT,
	APP_TIMER_EXIT_FAST,
	APP_TIMER_MENU,
	APP_TIMER_RESET,
	APP_TIMER_SAVE
} APP_TIMER_T;

typedef enum {
	APP_SOFT_KEY_MENU,
	APP_SOFT_KEY_LEFT,
	APP_SOFT_KEY_RIGHT
} APP_SOFT_KEY_T;

typedef enum {
	APP_RESOURCE_NAME,
	APP_RESOURCE_ICON,
	APP_RESOURCE_ICON_BIG,
	APP_RESOURCE_MENU_BACKGROUND,
	APP_RESOURCE_MENU_TILES,
	APP_RESOURCE_MAX
} APP_RESOURCES_T;

typedef enum {
	APP_MENU_ITEM_FIRST,
	APP_MENU_ITEM_SAVE = APP_MENU_ITEM_FIRST,
	APP_MENU_ITEM_LOAD,
	APP_MENU_ITEM_RESET,
	APP_MENU_ITEM_BACKGROUND,
	APP_MENU_ITEM_TILES,
	APP_MENU_ITEM_HELP,
	APP_MENU_ITEM_ABOUT,
	APP_MENU_ITEM_EXIT,
	APP_MENU_ITEM_MAX
} APP_MENU_ITEM_T;

typedef enum {
	APP_LIST_MENU,
	APP_LIST_BACKGROUND,
	APP_LIST_TILES
} APP_LIST_T;

typedef enum {
	APP_POPUP_SAVE_OK,
	APP_POPUP_SAVE_FAIL,
	APP_POPUP_LOAD_OK,
	APP_POPUP_LOAD_FAIL,
	APP_POPUP_RESETED,
	APP_POPUP_BACKGROUND_CHANGED,
	APP_POPUP_TILES_CHANGED
} APP_POPUP_T;

typedef enum {
	APP_BACKGROUND_SHOW,
	APP_BACKGROUND_HIDE,
	APP_BACKGROUND_MAX
} APP_BACKGROUND_T;

typedef enum {
	APP_TILES_ROUNDED,
	APP_TILES_RECTANGLE,
	APP_TILES_MAX
} APP_TILES_T;

typedef enum {
	APP_SELECT_BACKGROUND,
	APP_SELECT_TILES
} APP_SELECT_T;

typedef enum {
	APP_VIEW_HELP,
	APP_VIEW_ABOUT
} APP_VIEW_T;

typedef struct {
	APP_BACKGROUND_T background;
	APP_TILES_T tiles;
} APP_OPTIONS_T;

typedef struct {
	UINT16 tile_size;
	UINT16 offset_x;
	UINT16 offset_y;
	UINT16 offset_width;
	UINT16 offset_height;
	UINT16 rounded_rad;
	UINT16 pencil_width;
	UINT16 font_large;
	UINT16 font_normal;
	UINT16 font_small;
	UINT16 font_ultra_small;
	UINT16 font_final;
	UINT16 gap;
	UINT16 gap_y_huge;
} APP_MEASURED_T;

typedef enum {
	APP_DISPLAY_128x160 = 160,
	APP_DISPLAY_176x220 = 220,
	APP_DISPLAY_240x320 = 320
} APP_DISPLAY_T;

typedef struct {
	CLK_DATE_T date;
	CLK_TIME_T time;
	UINT16 board[BOARD_SIZE];
	UINT16 win;
	UINT16 lose;
	UINT16 score;
} SAVE_T;

typedef struct {
	APPLICATION_T app;

	RESOURCE_ID resources[APP_RESOURCE_MAX];
	GRAPHIC_REGION_T area;
	APP_OPTIONS_T options;
	APP_MEASURED_T measured;
	APP_POPUP_T popup;
	APP_SELECT_T select;
	APP_VIEW_T view;
	APP_MENU_ITEM_T menu_current_item_index;
	SAVE_T save;
	BOOL flag_from_select;
} APP_INSTANCE_T;

static __inline UINT32 OffsetCoord(UINT8 coord, UINT16 tile_size, UINT16 offset);
static __inline void SetRgbColor(COLOR_T *color, UINT32 rgb);
static __inline void CenterRect(GRAPHIC_REGION_T *r_i, GRAPHIC_REGION_T *r_o);

#if defined(EP1)
UINT32 Register(const char *elf_path_uri, const char *args, UINT32 ev_code); /* ElfPack 1.x entry point. */
#elif defined(EP2)
ldrElf *_start(WCHAR *uri, WCHAR *arguments);                                /* ElfPack 2.x entry point. */
#elif defined(EPMCORE)
UINT32 ELF_Entry(ldrElf *elf, WCHAR *arguments);                             /* ElfPack M*CORE entry point. */
#endif

static UINT32 ApplicationStart(EVENT_STACK_T *ev_st, REG_ID_T reg_id, void *reg_hdl);
static UINT32 ApplicationStop(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static UINT32 InitResourses(RESOURCE_ID *resources);
static UINT32 FreeResourses(RESOURCE_ID *resources);

static UINT32 HandleStateEnter(EVENT_STACK_T *ev_st, APPLICATION_T *app, ENTER_STATE_TYPE_T state);
static UINT32 HandleStateExit(EVENT_STACK_T *ev_st, APPLICATION_T *app, EXIT_STATE_TYPE_T state);
static UINT32 DeleteDialog(APPLICATION_T *app);

static UINT32 HandleEventKeyPress(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventKeyRelease(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventTimerExpired(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventSelect(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventBack(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static UINT32 HandleEventSelectDone(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventSelectBack(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static void SetPathsToFiles(void);
static UINT32 SetWorikingArea(GRAPHIC_REGION_T *working_area);
static UINT32 SetMeasuredValues(APP_MEASURED_T *measured_values, DRAWING_BUFFER_T *buffer);
static UINT32 DrawSoftKeys(EVENT_STACK_T *ev_st, APPLICATION_T *app, APP_SOFT_KEY_T softkey, BOOL pushed);

static UINT32 PaintAll(EVENT_STACK_T *ev_st, APPLICATION_T *app, BOOL show_score, BOOL update_soft_keys);
static UINT32 PaintBoard(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 PaintBackground(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 PaintTile(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 value, UINT8 x, UINT8 y);
static UINT32 PaintFinal(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static LIST_ENTRY_T *CreateList(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 start, UINT32 count, APP_LIST_T list);
static const WCHAR *GetBackgroundOptionString(APP_BACKGROUND_T background);
static const WCHAR *GetTilesOptionString(APP_TILES_T tiles);

static UINT32 ReadFile(void *data_struct, UINT32 size, const WCHAR *file_path);
static UINT32 SaveFile(void *data_struct, UINT32 size, const WCHAR *file_path);
static UINT32 LoadGame(APPLICATION_T *app);
static UINT32 SaveGame(APPLICATION_T *app);

static const char g_app_name[APP_NAME_LEN] = "2048-UIS";

static const WCHAR g_str_app_name[] = L"2048-P2K-UIS";
static const WCHAR g_str_app_soft_left[] = L"Exit";
static const WCHAR g_str_app_soft_right[] = L"Reset";
static const WCHAR g_str_app_score[] = L"Score: ";
static const WCHAR g_str_menu_save[] = L"Save Game";
static const WCHAR g_str_menu_load[] = L"Load Game";
static const WCHAR g_str_menu_reset[] = L"Reset Game";
static const WCHAR g_str_menu_background[] = L"Background:";
static const WCHAR g_str_menu_tiles[] = L"Tiles:";
static const WCHAR g_str_menu_help[] = L"Help...";
static const WCHAR g_str_menu_about[] = L"About...";
static const WCHAR g_str_menu_exit[] = L"Exit";
static const WCHAR g_str_changed[] = L"Changed:";
static const WCHAR g_str_reseted[] = L"The game has been reset!";
static const WCHAR g_str_game_won[] = L"You Won!";
static const WCHAR g_str_game_over[] = L"Game Over!";
static const WCHAR g_str_view_help[] = L"Help";
static const WCHAR g_str_select_background[] = L"Background";
static const WCHAR g_str_select_backgroud_show[] = L"Show";
static const WCHAR g_str_select_backgroud_hide[] = L"Hide";
static const WCHAR g_str_select_tiles[] = L"Tiles";
static const WCHAR g_str_select_tiles_rounded[] = L"Rounded";
static const WCHAR g_str_select_tiles_rectangle[] = L"Rectangle";
static const WCHAR g_str_save_ok[] = L"Game Saved!";
static const WCHAR g_str_save_fail[] = L"Save Error!";
static const WCHAR g_str_save_fail_desc[] = L"Cannot create file.";
static const WCHAR g_str_load_ok[] = L"Game Loaded!";
static const WCHAR g_str_load_fail[] = L"Load Error!";
static const WCHAR g_str_load_fail_desc[] = L"Cannot find file.";
static const WCHAR g_str_state_on[] = L"State on:";
static const WCHAR g_str_help_content_p1[] = L"A popular puzzle game for Motorola P2K as native ELF-application "
	L"written using AFW and UIS frameworks. Collect \"2048\" by moving tiles! Use \"0\" button to reset game. "
	L"Use \"Rectangle\" tiles if the game is slow.";
static const WCHAR g_str_about_content_p1[] = L"Version: 1.0";
static const WCHAR g_str_about_content_p2[] = L"Thanks: K. Bulenkov.";
static const WCHAR g_str_about_content_p3[] = L"\x00A9 EXL, 15-Jan-2023.";
static const WCHAR g_str_about_content_p4[] = L"https://github.com/EXL/2048/tree/master/2048-P2K";

static const COLOR_T g_color_board   = { 0xBB, 0xAD, 0xA0, 0xFF }; /* COLOR_BOARD   */
static const COLOR_T g_color_overlay = { 0x88, 0x88, 0x88, 0xFF }; /* COLOR_OVERLAY */
static const COLOR_T g_color_text    = { 0x77, 0x6E, 0x65, 0xFF }; /* COLOR_TEXT    */
static const COLOR_T g_color_final   = { 0x88, 0x00, 0x00, 0xFF }; /* COLOR_FINAL   */

static WCHAR g_config_file_path[FS_MAX_URI_NAME_LENGTH];
static WCHAR g_save_file_path[FS_MAX_URI_NAME_LENGTH];

#if defined(EP2)
static ldrElf g_app_elf;
#elif defined(EPMCORE)
static ldrElf *g_app_elf = NULL;
#endif

static EVENT_HANDLER_ENTRY_T g_state_any_hdls[] = {
	{ EV_REVOKE_TOKEN, APP_HandleUITokenRevoked },
	{ EV_TIMER_EXPIRED, HandleEventTimerExpired },
	{ STATE_HANDLERS_END, NULL }
};

static EVENT_HANDLER_ENTRY_T g_state_init_hdls[] = {
	{ EV_GRANT_TOKEN, APP_HandleUITokenGranted },
	{ STATE_HANDLERS_END, NULL }
};

static EVENT_HANDLER_ENTRY_T g_state_main_hdls[] = {
	{ EV_DONE, ApplicationStop },
	{ EV_DIALOG_DONE, ApplicationStop },
	{ EV_INK_KEY_PRESS, HandleEventKeyPress },
	{ EV_INK_KEY_RELEASE, HandleEventKeyRelease },
	{ STATE_HANDLERS_END, NULL }
};

static EVENT_HANDLER_ENTRY_T g_state_menu_hdls[] = {
	{ EV_DONE, HandleEventBack },
	{ EV_DIALOG_DONE, HandleEventBack },
	{ EV_SELECT, HandleEventSelect },
	{ STATE_HANDLERS_END, NULL }
};

static EVENT_HANDLER_ENTRY_T g_state_popup_hdls[] = {
	{ EV_DONE, HandleEventBack },
	{ EV_DIALOG_DONE, HandleEventBack },
	{ STATE_HANDLERS_END, NULL }
};

static EVENT_HANDLER_ENTRY_T g_state_select_hdls[] = {
	{ EV_DONE, HandleEventSelectDone },
	{ EV_DIALOG_DONE, HandleEventSelectBack },
	{ EV_CANCEL, HandleEventSelectBack },
	{ STATE_HANDLERS_END, NULL }
};

static const STATE_HANDLERS_ENTRY_T g_state_table_hdls[] = {
	{ APP_STATE_ANY, NULL, NULL, g_state_any_hdls },
	{ APP_STATE_INIT, NULL, NULL, g_state_init_hdls },
	{ APP_STATE_MAIN, HandleStateEnter, NULL, g_state_main_hdls },
	{ APP_STATE_MENU, HandleStateEnter, HandleStateExit, g_state_menu_hdls },
	{ APP_STATE_POPUP, HandleStateEnter, HandleStateExit, g_state_popup_hdls },
	{ APP_STATE_SELECT, HandleStateEnter, HandleStateExit, g_state_select_hdls },
	{ APP_STATE_VIEW, HandleStateEnter, HandleStateExit, g_state_popup_hdls } /* Same as popups. */
};

static __inline UINT32 OffsetCoord(UINT8 coord, UINT16 tile_size, UINT16 offset) {
	return (coord * (tile_size + offset) + offset);
}

static __inline void SetRgbColor(COLOR_T *color, UINT32 rgb) {
	color->red         = (rgb & 0x00FF0000) >> 16;
	color->green       = (rgb & 0x0000FF00) >>  8;
	color->blue        = (rgb & 0x000000FF) >>  0;
	color->transparent = (rgb & 0xFF000000) >> 24;
}

static __inline void CenterRect(GRAPHIC_REGION_T *r_i, GRAPHIC_REGION_T *r_o) {
	r_i->ulc.x = r_o->ulc.x + (r_o->lrc.x - r_o->ulc.x - r_i->lrc.x) / 2;
	r_i->ulc.y = r_o->ulc.y + (r_o->lrc.y - r_o->ulc.y - r_i->lrc.y) / 2;
	r_i->lrc.x = r_i->ulc.x + r_i->lrc.x;
	r_i->lrc.y = r_i->ulc.y + r_i->lrc.y;
}

#if defined(EP1)
UINT32 Register(const char *elf_path_uri, const char *args, UINT32 ev_code) {
	UINT32 status;
	UINT32 ev_code_base;

	ev_code_base = ev_code;

	status = APP_Register(&ev_code_base, 1, g_state_table_hdls, APP_STATE_MAX, (void *) ApplicationStart);

	u_atou(elf_path_uri, g_config_file_path);
	u_atou(elf_path_uri, g_save_file_path);
	SetPathsToFiles();

	LdrStartApp(ev_code_base);

	return status;
}
#elif defined(EP2)
ldrElf *_start(WCHAR *uri, WCHAR *arguments) {
	UINT32 status;
	UINT32 ev_code_base;
	UINT32 reserve;

	if (ldrIsLoaded(g_app_name)) {
		cprint("2048-UIS: Error! Application has already been loaded!\n");
		return NULL;
	}

	status = RESULT_OK;
	ev_code_base = ldrRequestEventBase();
	reserve = ev_code_base + 1;
	reserve = ldrInitEventHandlersTbl(g_state_any_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_init_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_main_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_menu_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_popup_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_select_hdls, reserve);

	status |= APP_Register(&ev_code_base, 1, g_state_table_hdls, APP_STATE_MAX, (void *) ApplicationStart);

	u_strcpy(g_config_file_path, uri);
	u_strcpy(g_save_file_path, uri);
	SetPathsToFiles();

	status |= ldrSendEvent(ev_code_base);
	g_app_elf.name = (char *) g_app_name;

	return (status == RESULT_OK) ? &g_app_elf : NULL;
}
#elif defined(EPMCORE)
UINT32 ELF_Entry(ldrElf *elf, WCHAR *arguments) {
	UINT32 status;
	UINT32 reserve;
	WCHAR *ptr;

	status = RESULT_OK;
	g_app_elf = elf;
	g_app_elf->name = (char *) g_app_name;

	if (ldrIsLoaded(g_app_elf->name)) {
		PFprintf("%s: Application already loaded.\n", g_app_elf->name);
		return RESULT_FAIL;
	}

	reserve = g_app_elf->evbase + 1;
	reserve = ldrInitEventHandlersTbl(g_state_any_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_init_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_main_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_menu_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_popup_hdls, reserve);
	reserve = ldrInitEventHandlersTbl(g_state_select_hdls, reserve);

	status |= APP_Register(&g_app_elf->evbase, 1, g_state_table_hdls, APP_STATE_MAX, (void *) ApplicationStart);
	if (status == RESULT_OK) {
		PFprintf("%s: Application has been registered successfully.\n", g_app_elf->name);

		ptr = NULL;
		u_strcpy(g_config_file_path, L"file:/");
		ptr = g_config_file_path + u_strlen(g_config_file_path);
		DL_FsGetURIFromID(&g_app_elf->id, ptr);
		u_strcpy(g_save_file_path, L"file:/");
		ptr = g_save_file_path + u_strlen(g_save_file_path);
		DL_FsGetURIFromID(&g_app_elf->id, ptr);
		SetPathsToFiles();

		status |= ldrSendEvent(g_app_elf->evbase);
	} else {
		PFprintf("%s: Cannot register application.\n", g_app_elf->name);
	}

	return status;
}
#endif

static UINT32 ApplicationStart(EVENT_STACK_T *ev_st, REG_ID_T reg_id, void *reg_hdl) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;

	status = RESULT_FAIL;

	if (AFW_InquireRoutingStackByRegId(reg_id) != RESULT_OK) {
		e_init(KEY_0, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);

		app_instance = (APP_INSTANCE_T *) APP_InitAppData((void *) APP_HandleEvent, sizeof(APP_INSTANCE_T),
			reg_id, 0, 1, 1, 1, 1, 0);

		InitResourses(app_instance->resources);
		app_instance->options.background = APP_BACKGROUND_SHOW;
		app_instance->options.tiles = APP_TILES_ROUNDED;
		app_instance->menu_current_item_index = APP_MENU_ITEM_FIRST;
		app_instance->select = APP_SELECT_BACKGROUND;
		app_instance->popup = APP_POPUP_RESETED;
		app_instance->view = APP_VIEW_HELP;
		app_instance->flag_from_select = FALSE;

		if (DL_FsFFileExist(g_config_file_path)) {
			ReadFile(&app_instance->options, sizeof(APP_OPTIONS_T), g_config_file_path);
		} else {
			SaveFile(&app_instance->options, sizeof(APP_OPTIONS_T), g_config_file_path);
		}

		status = APP_Start(ev_st, &app_instance->app, APP_STATE_MAIN,
			g_state_table_hdls, ApplicationStop, g_app_name, 0);

#if defined(EP2)
		g_app_elf.app = (APPLICATION_T *) app_instance;
#elif defined(EPMCORE)
		g_app_elf->app = &app_instance->app;
#endif
	}

	return status;
}

static UINT32 ApplicationStop(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	DeleteDialog(app);

	FreeResourses(app_instance->resources);

	status |= APP_Exit(ev_st, app, 0);

#if defined(EP1)
	LdrUnloadELF(&Lib);
#elif defined(EP2)
	ldrUnloadElf();
#elif defined(EPMCORE)
	ldrUnloadElf(g_app_elf);
#endif

	return status;
}

static UINT32 InitResourses(RESOURCE_ID *resources) {
	UINT32 status;

	status = RESULT_OK;

	status |= DRM_CreateResource(&resources[APP_RESOURCE_NAME], RES_TYPE_STRING,
		(void *) g_str_app_name, (u_strlen(g_str_app_name) + 1) * sizeof(WCHAR));
	status |= DRM_CreateResource(&resources[APP_RESOURCE_MENU_BACKGROUND], RES_TYPE_STRING,
		(void *) g_str_select_background, (u_strlen(g_str_select_background) + 1) * sizeof(WCHAR));
	status |= DRM_CreateResource(&resources[APP_RESOURCE_MENU_TILES], RES_TYPE_STRING,
		(void *) g_str_select_tiles, (u_strlen(g_str_select_tiles) + 1) * sizeof(WCHAR));

	status |= DRM_CreateResource(&resources[APP_RESOURCE_ICON], RES_TYPE_GRAPHICS,
		(void *) p2k_app_icon_15x15_gif, sizeof(p2k_app_icon_15x15_gif));
	status |= DRM_CreateResource(&resources[APP_RESOURCE_ICON_BIG], RES_TYPE_GRAPHICS,
		(void *) p2k_app_icon_41x41_gif, sizeof(p2k_app_icon_41x41_gif));

	return status;
}

static UINT32 FreeResourses(RESOURCE_ID *resources) {
	UINT32 status;
	UINT32 i;

	status = RESULT_OK;

	for (i = 0; i < APP_RESOURCE_MAX; ++i) {
		if (resources[i]) {
			status |= DRM_ClearResource(resources[i]);
		}
	}

	return status;
}

static UINT32 HandleStateEnter(EVENT_STACK_T *ev_st, APPLICATION_T *app, ENTER_STATE_TYPE_T state) {
	APP_INSTANCE_T *app_instance;
	SU_PORT_T port;
	CONTENT_T content;
	UIS_DIALOG_T dialog;
	APP_STATE_T app_state;
	UINT8 notice_type;
	DRAWING_BUFFER_T buffer;
	GRAPHIC_POINT_T point;
	LIST_ENTRY_T *list;

	if (state != ENTER_STATE_ENTER) {
		if (app->state != APP_STATE_MAIN) {
			return RESULT_OK;
		}
	}

	app_instance = (APP_INSTANCE_T *) app;

	DeleteDialog(app);

	port = app->port;
	app_state = app->state;
	dialog = DialogType_None;

	memclr(&content, sizeof(CONTENT_T));

	switch (app_state) {
		case APP_STATE_MAIN:
#if defined(EPMCORE)
			UIS_CanvasGetDisplaySize(&point);
#else
			point = UIS_CanvasGetDisplaySize();
#endif
			buffer.w = point.x + 1;
			buffer.h = point.y + 1;
			buffer.buf = NULL;
			SetWorikingArea(&app_instance->area);
			SetMeasuredValues(&app_instance->measured, &buffer);
			dialog = UIS_CreateColorCanvasWithWallpaper(&port, &buffer, FALSE, TRUE);
			break;
		case APP_STATE_MENU:
			list = CreateList(ev_st, app, 1, APP_MENU_ITEM_MAX, APP_LIST_MENU);
			if (list != NULL) {
				dialog = UIS_CreateStaticList(&port, 0, APP_MENU_ITEM_MAX, 0, list, FALSE, 2, NULL,
					app_instance->resources[APP_RESOURCE_NAME]);
				suFreeMem(list);

				/* Insert cursor to proper position. */
				if (app_instance->flag_from_select) {
					if (app_instance->menu_current_item_index != APP_MENU_ITEM_FIRST) {
						APP_UtilAddEvChangeListPosition(ev_st, app, app_instance->menu_current_item_index + 1,
							NULL, NULL, NULL);
						UIS_HandleEvent(dialog, ev_st);
					}
					app_instance->flag_from_select = FALSE;
				}
			}
			break;
		case APP_STATE_POPUP:
			notice_type = NOTICE_TYPE_OK;
			switch (app_instance->popup) {
				default:
				case APP_POPUP_SAVE_OK:
					UIS_MakeContentFromString("MCq0NMCq1NMCd2 t3", &content, g_str_save_ok,
						g_str_state_on, app_instance->save.date, app_instance->save.time);
					break;
				case APP_POPUP_SAVE_FAIL:
					notice_type = NOTICE_TYPE_FAIL;
					UIS_MakeContentFromString("MCq0NMCq1", &content, g_str_save_fail, g_str_save_fail_desc);
					break;
				case APP_POPUP_LOAD_OK:
					UIS_MakeContentFromString("MCq0NMCq1NMCd2 t3", &content, g_str_load_ok,
						g_str_state_on, app_instance->save.date, app_instance->save.time);
					break;
				case APP_POPUP_LOAD_FAIL:
					notice_type = NOTICE_TYPE_FAIL;
					UIS_MakeContentFromString("MCq0NMCq1", &content, g_str_load_fail, g_str_load_fail_desc);
					break;
				case APP_POPUP_RESETED:
					UIS_MakeContentFromString("MCq0", &content, g_str_reseted);
					break;
				case APP_POPUP_BACKGROUND_CHANGED:
					UIS_MakeContentFromString("MCq0NMCq1NMCq2", &content, g_str_changed,
						g_str_select_background, GetBackgroundOptionString(app_instance->options.background));
					break;
				case APP_POPUP_TILES_CHANGED:
					UIS_MakeContentFromString("MCq0NMCq1NMCq2", &content, g_str_changed,
						g_str_select_tiles, GetTilesOptionString(app_instance->options.tiles));
					break;
			}
			dialog = UIS_CreateTransientNotice(&port, &content, notice_type);
			break;
		case APP_STATE_SELECT:
			switch (app_instance->select) {
				default:
				case APP_SELECT_BACKGROUND:
					list = CreateList(ev_st, app, 1, APP_BACKGROUND_MAX, APP_LIST_BACKGROUND);
					if (list != NULL) {
						dialog = UIS_CreateStaticSelectionEditor(&port, 0, APP_BACKGROUND_MAX, list,
							app_instance->options.background + 1, NULL,
							app_instance->resources[APP_RESOURCE_MENU_BACKGROUND]);
						suFreeMem(list);
					}
					break;
				case APP_SELECT_TILES:
					list = CreateList(ev_st, app, 1, APP_TILES_MAX, APP_LIST_TILES);
					if (list != NULL) {
						dialog = UIS_CreateStaticSelectionEditor(&port, 0, APP_TILES_MAX, list,
							app_instance->options.tiles + 1, NULL, app_instance->resources[APP_RESOURCE_MENU_TILES]);
						suFreeMem(list);
					}
					break;
			}
			break;
		case APP_STATE_VIEW:
			switch (app_instance->view) {
				default:
				case APP_VIEW_HELP:
					UIS_MakeContentFromString("q0Nq1", &content, g_str_view_help, g_str_help_content_p1);
					break;
				case APP_VIEW_ABOUT:
					UIS_MakeContentFromString("q0NMCp1NMCq2NMCq3NMCq4NMCq5", &content, g_str_app_name,
						app_instance->resources[APP_RESOURCE_ICON_BIG], g_str_about_content_p1,
						g_str_about_content_p2, g_str_about_content_p3, g_str_about_content_p4);
					break;
			}
			dialog = UIS_CreateViewer(&port, &content, NULL);
			break;
		default:
			break;
	}

	if (dialog == DialogType_None) {
		return RESULT_FAIL;
	}

	app->dialog = dialog;

	switch (app_state) {
	case APP_STATE_MAIN:
		PaintAll(ev_st, app, (e_score > 0), TRUE);
		break;
	default:
		break;
	}

	return RESULT_OK;
}

static UINT32 HandleStateExit(EVENT_STACK_T *ev_st, APPLICATION_T *app, EXIT_STATE_TYPE_T state) {
	if (state == EXIT_STATE_EXIT) {
		DeleteDialog(app);
		return RESULT_OK;
	}
	return RESULT_FAIL;
}

static UINT32 DeleteDialog(APPLICATION_T *app) {
	if (app->dialog != DialogType_None) {
		UIS_Delete(app->dialog);
		app->dialog = DialogType_None;
		return RESULT_OK;
	}

	return RESULT_FAIL;
}

static UINT32 HandleEventKeyPress(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	EVENT_T *event;

	status = RESULT_OK;
	event = AFW_GetEv(ev_st);

	APP_ConsumeEv(ev_st, app);

	switch (event->data.key_pressed) {
		case KEY_SOFT_LEFT:
			DrawSoftKeys(ev_st, app, APP_SOFT_KEY_LEFT, TRUE);
			break;
		case KEY_MENU:
			DrawSoftKeys(ev_st, app, APP_SOFT_KEY_MENU, TRUE);
			break;
		case KEY_SOFT_RIGHT:
			DrawSoftKeys(ev_st, app, APP_SOFT_KEY_RIGHT, TRUE);
			break;
		case KEY_4:
		case KEY_LEFT:
			e_key(KEY_LEFT);
			PaintAll(ev_st, app, TRUE, FALSE);
			break;
		case KEY_6:
		case KEY_RIGHT:
			e_key(KEY_RIGHT);
			PaintAll(ev_st, app, TRUE, FALSE);
			break;
		case KEY_2:
		case KEY_UP:
			e_key(KEY_UP);
			PaintAll(ev_st, app, TRUE, FALSE);
			break;
		case KEY_8:
		case KEY_DOWN:
			e_key(KEY_DOWN);
			PaintAll(ev_st, app, TRUE, FALSE);
			break;
		case KEY_0:
			e_key(KEY_0);
			PaintAll(ev_st, app, FALSE, FALSE);
			break;
		default:
			break;
	}

	return status;
}

static UINT32 HandleEventKeyRelease(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	EVENT_T *event;

	status = RESULT_OK;
	event = AFW_GetEv(ev_st);

	APP_ConsumeEv(ev_st, app);

	switch (event->data.key_pressed) {
		case KEY_RED:
		case KEY_SOFT_LEFT:
			status |= APP_UtilStartTimer(TIMER_FAST_TRIGGER_MS, APP_TIMER_EXIT, app);
			break;
		case KEY_MENU:
			status |= APP_UtilStartTimer(TIMER_FAST_TRIGGER_MS, APP_TIMER_MENU, app);
			break;
		case KEY_SOFT_RIGHT:
			status |= APP_UtilStartTimer(TIMER_FAST_TRIGGER_MS, APP_TIMER_RESET, app);
			break;
		default:
			break;
	}

	return status;
}

static UINT32 HandleEventTimerExpired(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	EVENT_T *event;
	APP_TIMER_T timer_id;

	event = AFW_GetEv(ev_st);
	timer_id = ((DL_TIMER_DATA_T *) event->attachment)->ID;

	switch (timer_id) {
		case APP_TIMER_EXIT:
			DrawSoftKeys(ev_st, app, APP_SOFT_KEY_LEFT, FALSE);
			/* No break here. */
		case APP_TIMER_EXIT_FAST:
			/* Play an exit sound using quiet speaker. */
			DL_AudPlayTone(0x00,  0xFF);
			return ApplicationStop(ev_st, app);
			break;
		case APP_TIMER_MENU:
			DrawSoftKeys(ev_st, app, APP_SOFT_KEY_MENU, FALSE);
			APP_UtilChangeState(APP_STATE_MENU, ev_st, app);
			break;
		case APP_TIMER_RESET:
			DrawSoftKeys(ev_st, app, APP_SOFT_KEY_RIGHT, FALSE);
			e_key(KEY_0);
			PaintAll(ev_st, app, FALSE, FALSE);
			break;
		case APP_TIMER_SAVE:
#ifdef USE_MME
			/* Play a normal camera shutter sound using loud speaker. */
			/* NOTE: Function `MME_GC_playback_open_audio_play_forget()` may not be available on most libraries. */
			MME_GC_playback_open_audio_play_forget(L"/a/mobile/system/shutter5.amr");
#endif
			break;
		default:
			break;
	}

	return RESULT_OK;
}

static UINT32 HandleEventSelect(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	EVENT_T *event;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;
	event = AFW_GetEv(ev_st);

	app_instance->menu_current_item_index = event->data.index - 1;

	switch (app_instance->menu_current_item_index) {
		case APP_MENU_ITEM_SAVE:
			if (SaveGame(app) == RESULT_OK) {
				app_instance->popup = APP_POPUP_SAVE_OK;
				APP_UtilStartTimer(TIMER_POPUP_DELAY_MS, APP_TIMER_SAVE, app);
			} else {
				app_instance->popup = APP_POPUP_SAVE_FAIL;
			}
			status |= APP_UtilChangeState(APP_STATE_POPUP, ev_st, app);
			break;
		case APP_MENU_ITEM_LOAD:
			if (LoadGame(app) == RESULT_OK) {
				app_instance->popup = APP_POPUP_LOAD_OK;
			} else {
				app_instance->popup = APP_POPUP_LOAD_FAIL;
			}
			status |= APP_UtilChangeState(APP_STATE_POPUP, ev_st, app);
			break;
		case APP_MENU_ITEM_RESET:
			e_key(KEY_0);
			app_instance->popup = APP_POPUP_RESETED;
			status |= APP_UtilChangeState(APP_STATE_POPUP, ev_st, app);
			break;
		case APP_MENU_ITEM_BACKGROUND:
			app_instance->select = APP_SELECT_BACKGROUND;
			status |= APP_UtilChangeState(APP_STATE_SELECT, ev_st, app);
			break;
		case APP_MENU_ITEM_TILES:
			app_instance->select = APP_SELECT_TILES;
			status |= APP_UtilChangeState(APP_STATE_SELECT, ev_st, app);
			break;
		case APP_MENU_ITEM_HELP:
			app_instance->view = APP_VIEW_HELP;
			status |= APP_UtilChangeState(APP_STATE_VIEW, ev_st, app);
			break;
		case APP_MENU_ITEM_ABOUT:
			app_instance->view = APP_VIEW_ABOUT;
			status |= APP_UtilChangeState(APP_STATE_VIEW, ev_st, app);
			break;
		case APP_MENU_ITEM_EXIT:
			status |= APP_UtilStartTimer(TIMER_FAST_TRIGGER_MS, APP_TIMER_EXIT_FAST, app);
			break;
		default:
			break;
	}

	return status;
}

static UINT32 HandleEventBack(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;

	status = RESULT_OK;

	status |= APP_UtilChangeState(APP_STATE_MAIN, ev_st, app);

	return status;
}

static UINT32 HandleEventSelectDone(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	EVENT_T *event;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;
	event = AFW_GetEv(ev_st);

	switch (app_instance->select) {
		default:
		case APP_SELECT_BACKGROUND:
			app_instance->popup = APP_POPUP_BACKGROUND_CHANGED;
			app_instance->options.background = event->data.index - 1;
			break;
		case APP_SELECT_TILES:
			app_instance->popup = APP_POPUP_TILES_CHANGED;
			app_instance->options.tiles = event->data.index - 1;
			break;
	}

	status |= SaveFile(&app_instance->options, sizeof(APP_OPTIONS_T), g_config_file_path);
	status |= APP_UtilChangeState(APP_STATE_POPUP, ev_st, app);

	return status;
}

static UINT32 HandleEventSelectBack(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	app_instance->flag_from_select = TRUE;

	status |= APP_UtilChangeState(APP_STATE_MENU, ev_st, app);

	return status;
}

static void SetPathsToFiles(void) {
	g_config_file_path[u_strlen(g_config_file_path) - 3] = '\0';
	g_save_file_path[u_strlen(g_save_file_path) - 3] = '\0';
	u_strcat(g_config_file_path, L"cfg");
	u_strcat(g_save_file_path, L"sav");
}

static UINT32 SetWorikingArea(GRAPHIC_REGION_T *working_area) {
	UINT32 status;
	GRAPHIC_REGION_T rect;
	UINT8 count_lines;
	UINT8 chars_on_line;
	UINT8 height_title_bar_end;
	UINT8 height_soft_keys_start;

	status = RESULT_OK;

	UIS_CanvasGetWorkingArea(&rect, &count_lines, &chars_on_line, TITLE_BAR_AREA, TRUE, 1);
	height_title_bar_end = rect.lrc.y + 1;

	UIS_CanvasGetWorkingArea(&rect, &count_lines, &chars_on_line, SOFTKEY_AREA, TRUE, 1);
	height_soft_keys_start = rect.ulc.y - 1;

	rect.ulc.y = height_title_bar_end;
	/* rect.lrc.x -= 1; */
	rect.lrc.y = height_soft_keys_start;
	/* rect.lrc.y += 1; */

	memcpy(working_area, &rect, sizeof(GRAPHIC_REGION_T));

	return status;
}

static UINT32 SetMeasuredValues(APP_MEASURED_T *measured_values, DRAWING_BUFFER_T *buffer) {
	UINT32 status;

	status = RESULT_OK;

	switch (buffer->h) {
		default:
		case APP_DISPLAY_128x160:
			measured_values->tile_size = 22;
			measured_values->offset_x = 8;
			measured_values->offset_y = 4;
			measured_values->offset_width = 0;
			measured_values->offset_height = 1;
			measured_values->rounded_rad = 3;
			measured_values->pencil_width = 1;
			measured_values->font_large = 0x0A;        /* Bold WAP-browser font. */
			measured_values->font_normal = 0x01;       /* General font. */
			measured_values->font_small = 0x06;        /* Software keys font. */
			measured_values->font_ultra_small = 0x09;  /* Very narrow numbers font. */
			measured_values->font_final = 0x0A;        /* Bold WAP-browser font. */
			measured_values->gap = 1;
			measured_values->gap_y_huge = 2;
			break;
		case APP_DISPLAY_176x220:
		case APP_DISPLAY_240x320: /* FIXME: Unknown values for 240x320 screen, set them similar to 176x220. */
			measured_values->tile_size = 34;
			measured_values->offset_x = 4;
			measured_values->offset_y = 4;
			measured_values->offset_width = 10;
			measured_values->offset_height = 2;
			measured_values->rounded_rad = 4;
			measured_values->pencil_width = 2;
			measured_values->font_large = 0x05;        /* Big numbers at set of number font. */
			measured_values->font_normal = 0x05;       /* Big numbers at set of number font. */
			measured_values->font_small = 0x04;        /* Small numbers at set of number font. */
			measured_values->font_ultra_small = 0x01;  /* General font. */
			measured_values->font_final = 0x0A;        /* Bold WAP-browser font. */
			measured_values->gap = 1;
			measured_values->gap_y_huge = 0;
			break;
	}

	return status;
}

static UINT32 DrawSoftKeys(EVENT_STACK_T *ev_st, APPLICATION_T *app, APP_SOFT_KEY_T softkey, BOOL pushed) {
	UINT32 status;

	status = RESULT_OK;

	switch (softkey) {
		case APP_SOFT_KEY_MENU:
			UIS_CanvasDrawColorSoftkey(NULL, 0, pushed, TRUE, app->dialog);
			break;
		case APP_SOFT_KEY_LEFT:
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_left, 1, pushed, TRUE, app->dialog);
			break;
		case APP_SOFT_KEY_RIGHT:
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_right, 2, pushed, TRUE, app->dialog);
			break;
		default:
			break;
	}

	return status;
}

static UINT32 PaintAll(EVENT_STACK_T *ev_st, APPLICATION_T *app, BOOL show_score, BOOL update_soft_keys) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	WCHAR score_title[SCORE_TITLE_MAX_LENGTH] = { 0 };
	WCHAR score_value[SCORE_VALUE_MAX_LENGTH] = { 0 };

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	if (show_score) {
		u_ltou(e_score, score_value);
		u_strcat(score_title, g_str_app_score);
		u_strcat(score_title, score_value);
		UIS_CanvasDrawTitleBarWithIcon(score_title, app_instance->resources[APP_RESOURCE_ICON],
			FALSE, 1, FALSE, FALSE, app->dialog, 0, 0);
	} else {
		UIS_CanvasDrawTitleBarWithIcon((WCHAR *) g_str_app_name, app_instance->resources[APP_RESOURCE_ICON],
			FALSE, 1, FALSE, FALSE, app->dialog, 0, 0);
	}

	status |= PaintBoard(ev_st, app);

	if (update_soft_keys) {
		DrawSoftKeys(ev_st, app, APP_SOFT_KEY_LEFT, FALSE);
		DrawSoftKeys(ev_st, app, APP_SOFT_KEY_MENU, FALSE);
		DrawSoftKeys(ev_st, app, APP_SOFT_KEY_RIGHT, FALSE);
	}

	return status;
}

static UINT32 PaintBoard(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	UINT8 x;
	UINT8 y;

	status = RESULT_OK;

	status |= PaintBackground(ev_st, app);
	for (y = 0; y < LINE_SIZE; ++y) {
		for (x = 0; x < LINE_SIZE; ++x) {
			status |= PaintTile(ev_st, app, e_board[x + y * LINE_SIZE], x, y);
		}
	}
	status |= PaintFinal(ev_st, app);

	return status;
}

static UINT32 PaintBackground(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	switch (app_instance->options.background) {
		default:
		case APP_BACKGROUND_SHOW:
			UIS_CanvasFillRect(app_instance->area, app->dialog);
			break;
		case APP_BACKGROUND_HIDE:
			UIS_CanvasSetBackgroundColor(g_color_board);
			UIS_CanvasSetForegroundColor(g_color_board);
			UIS_CanvasDrawRect(app_instance->area, TRUE, app->dialog);
			break;
	}

	UIS_CanvasSetLineWidth(app_instance->measured.pencil_width);

	return status;
}

static UINT32 PaintTile(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 value, UINT8 x, UINT8 y) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	UINT32 coord_x;
	UINT32 coord_y;
	GRAPHIC_REGION_T rect;
	COLOR_T color;
	UINT32 font_id;
	UINT16 tile_size;
	UINT16 radius;
	UINT16 offset_w;
	UINT16 offset_h;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;
	tile_size = app_instance->measured.tile_size;
	offset_w = app_instance->measured.offset_width;
	offset_h = app_instance->measured.offset_height;

	coord_x = OffsetCoord(x, tile_size, app_instance->measured.offset_x) + offset_w;
	coord_y = OffsetCoord(y, tile_size, app_instance->measured.offset_y) + app_instance->area.ulc.y + offset_h;

	rect.ulc.x = coord_x;
	rect.ulc.y = coord_y;
	rect.lrc.x = coord_x + app_instance->measured.tile_size;
	rect.lrc.y = coord_y + app_instance->measured.tile_size;

	SetRgbColor(&color, e_background(value));
	UIS_CanvasSetBackgroundColor(color);
	UIS_CanvasSetForegroundColor(g_color_text);

	switch (app_instance->options.tiles) {
		default:
		case APP_TILES_ROUNDED:
			radius = app_instance->measured.rounded_rad;
			UIS_CanvasDrawRoundRect(rect, radius, radius, TRUE, app->dialog);
			break;
		case APP_TILES_RECTANGLE:
			UIS_CanvasDrawRect(rect, TRUE, app->dialog);
			break;
	}

	if (value) {
		WCHAR tile_value[TILE_VALUE_MAX_LENGTH] = { 0 };
		GRAPHIC_POINT_T point;
		GRAPHIC_METRIC_T string_measure;

		if (value < 64) {
			SetRgbColor(&color, e_foreground(value));
			UIS_CanvasSetForegroundColor(color);
		}

		u_ltou(value, tile_value);

		if (value < 10) {
			font_id = app_instance->measured.font_large;
		} else if (value < 100) {
			font_id = app_instance->measured.font_normal;
		} else if (value < 1000) {
			font_id = app_instance->measured.font_small;
		} else {
			font_id = app_instance->measured.font_ultra_small;
		}

		UIS_CanvasSetFont(font_id, app->dialog);
#if defined(EPMCORE)
		FONT_ATTRIB_T font_attrib;
		UIS_CanvasGetAttributesFromFontID(&font_attrib, font_id);
		GET_STRING_SIZE(tile_value, &string_measure, font_attrib);
#else
		UIS_CanvasGetStringSize(tile_value, &string_measure, font_id);
#endif

		point.x = (coord_x + (tile_size - string_measure.width) / 2) + app_instance->measured.gap;
		point.y = (coord_y + (tile_size - string_measure.height) / 2) + app_instance->measured.gap;

		if (value > 1000) {
			point.y -= app_instance->measured.gap_y_huge;
		}

		UIS_CanvasDrawColorText(tile_value, 0, u_strlen(tile_value), point, 0, app->dialog);
	}

	return status;
}

static UINT32 PaintFinal(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;

	status = RESULT_OK;

	if (e_win || e_lose) {
		APP_INSTANCE_T *app_instance;
		WCHAR *string_final;
		GRAPHIC_METRIC_T string_measure;
		GRAPHIC_REGION_T rect;
		GRAPHIC_POINT_T point;

		app_instance = (APP_INSTANCE_T *) app;
		if (e_win) {
			string_final = (WCHAR *) g_str_game_won;
		} else {
			string_final = (WCHAR *) g_str_game_over;
		}

#if defined(EPMCORE)
		FONT_ATTRIB_T font_attrib;
		UIS_CanvasGetAttributesFromFontID(&font_attrib, app_instance->measured.font_final);
		GET_STRING_SIZE(string_final, &string_measure, font_attrib);
#else
		UIS_CanvasGetStringSize(string_final, &string_measure, app_instance->measured.font_final);
#endif

		rect.lrc.x = string_measure.width;
		rect.lrc.y = string_measure.height;
		CenterRect(&rect, &app_instance->area);
		point.x = rect.ulc.x;
		point.y = rect.ulc.y;

		rect.lrc.x = string_measure.width + string_measure.width / 3;
		rect.lrc.y = string_measure.height + string_measure.height / 2;
		CenterRect(&rect, &app_instance->area);

		UIS_CanvasSetBackgroundColor(g_color_overlay);
		UIS_CanvasSetForegroundColor(g_color_final);
		UIS_CanvasDrawRect(rect, TRUE, app->dialog);
		UIS_CanvasSetFont(app_instance->measured.font_final, app->dialog);
		UIS_CanvasDrawColorText(string_final, 0, u_strlen(string_final), point, 0, app->dialog);
	}

	return status;
}

static LIST_ENTRY_T *CreateList(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 start, UINT32 count, APP_LIST_T list) {
	UINT32 status;
	INT32 result;
	APP_INSTANCE_T *app_instance;
	UINT32 i;
	LIST_ENTRY_T *list_elements;

	status = RESULT_OK;
	result = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	if (count == 0) {
		return NULL;
	}
	list_elements = (LIST_ENTRY_T *) suAllocMem(sizeof(LIST_ENTRY_T) * count, &result);
	if (result != RESULT_OK) {
		return NULL;
	}

	for (i = 0; i < count; ++i) {
		memclr(&list_elements[i], sizeof(LIST_ENTRY_T));
		list_elements[i].editable = FALSE;
		list_elements[i].content.static_entry.formatting = TRUE;
	}

	switch (list) {
		default:
		case APP_LIST_MENU:
			status |= UIS_MakeContentFromString("Mq0",
				&list_elements[APP_MENU_ITEM_SAVE].content.static_entry.text,
				g_str_menu_save);
			status |= UIS_MakeContentFromString("Mq0",
				&list_elements[APP_MENU_ITEM_LOAD].content.static_entry.text,
				g_str_menu_load);
			status |= UIS_MakeContentFromString("Mq0",
				&list_elements[APP_MENU_ITEM_RESET].content.static_entry.text,
				g_str_menu_reset);
			status |= UIS_MakeContentFromString("Mq0Sq1",
				&list_elements[APP_MENU_ITEM_BACKGROUND].content.static_entry.text,
				g_str_menu_background, GetBackgroundOptionString(app_instance->options.background));
			status |= UIS_MakeContentFromString("Mq0Sq1",
				&list_elements[APP_MENU_ITEM_TILES].content.static_entry.text,
				g_str_menu_tiles, GetTilesOptionString(app_instance->options.tiles));
			status |= UIS_MakeContentFromString("Mq0",
				&list_elements[APP_MENU_ITEM_HELP].content.static_entry.text,
				g_str_menu_help);
			status |= UIS_MakeContentFromString("Mq0",
				&list_elements[APP_MENU_ITEM_ABOUT].content.static_entry.text,
				g_str_menu_about);
			status |= UIS_MakeContentFromString("Mq0",
				&list_elements[APP_MENU_ITEM_EXIT].content.static_entry.text,
				g_str_menu_exit);
			break;
		case APP_LIST_BACKGROUND:
			status |= UIS_MakeContentFromString("q0",
				&list_elements[APP_BACKGROUND_SHOW].content.static_entry.text,
				g_str_select_backgroud_show);
			status |= UIS_MakeContentFromString("q0",
				&list_elements[APP_BACKGROUND_HIDE].content.static_entry.text,
				g_str_select_backgroud_hide);
			break;
		case APP_LIST_TILES:
			status |= UIS_MakeContentFromString("q0",
				&list_elements[APP_TILES_ROUNDED].content.static_entry.text,
				g_str_select_tiles_rounded);
			status |= UIS_MakeContentFromString("q0",
				&list_elements[APP_TILES_RECTANGLE].content.static_entry.text,
				g_str_select_tiles_rectangle);
			break;
	}

	if (status != RESULT_OK) {
		suFreeMem(list_elements);
		return NULL;
	}

	return list_elements;
}

static const WCHAR *GetBackgroundOptionString(APP_BACKGROUND_T background) {
	switch (background) {
		default:
		case APP_BACKGROUND_SHOW:
			return g_str_select_backgroud_show;
		case APP_BACKGROUND_HIDE:
			return g_str_select_backgroud_hide;
	}
}

static const WCHAR *GetTilesOptionString(APP_TILES_T tiles) {
	switch (tiles) {
		default:
		case APP_TILES_ROUNDED:
			return g_str_select_tiles_rounded;
		case APP_TILES_RECTANGLE:
			return g_str_select_tiles_rectangle;
	}
}

static UINT32 ReadFile(void *data_struct, UINT32 size, const WCHAR *file_path) {
	UINT32 readen;
	FILE_HANDLE_T file_handle;

	readen = 0;
	file_handle = DL_FsOpenFile((WCHAR *) file_path, FILE_READ_MODE, 0);

	DL_FsReadFile(data_struct, size, 1, file_handle, &readen);
	DL_FsCloseFile(file_handle);

	return (readen == 0);
}

static UINT32 SaveFile(void *data_struct, UINT32 size, const WCHAR *file_path) {
	UINT32 written;
	FILE_HANDLE_T file_handle;

	written = 0;
	file_handle = DL_FsOpenFile((WCHAR *) file_path, FILE_WRITE_MODE, 0);

	DL_FsWriteFile(data_struct, size, 1, file_handle, &written);
	DL_FsCloseFile(file_handle);

	return (written == 0);
}

static UINT32 LoadGame(APPLICATION_T *app) {
	UINT32 i;
	APP_INSTANCE_T *app_instance;

	app_instance = (APP_INSTANCE_T *) app;

	if (ReadFile(&app_instance->save, sizeof(SAVE_T), g_save_file_path) == RESULT_OK) {
		e_win = app_instance->save.win;
		e_lose = app_instance->save.lose;
		e_score = app_instance->save.score;
		for (i = 0; i < BOARD_SIZE; ++i) {
			e_board[i] = app_instance->save.board[i];
		}
		return RESULT_OK;
	}

	return RESULT_FAIL;
}

static UINT32 SaveGame(APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	UINT32 i;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	status |= (DL_ClkGetDate(&app_instance->save.date) == FALSE);
	status |= (DL_ClkGetTime(&app_instance->save.time) == FALSE);

	app_instance->save.win = e_win;
	app_instance->save.lose = e_lose;
	app_instance->save.score = e_score;
	for (i = 0; i < BOARD_SIZE; ++i) {
		app_instance->save.board[i] = e_board[i];
	}

	status |= SaveFile(&app_instance->save, sizeof(SAVE_T), g_save_file_path);

	return status;
}
