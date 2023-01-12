#include <loader.h>
#include <apps.h>
#include <uis.h>
#include <canvas.h>
#include <mem.h>
#include <utilities.h>

/* TODO BLOCK!!!! */
#include <res_def.h>
#include "app_icon.h"
#include "2048.h"
#include "2048.c"
/* TODO BLOCK!!!! */

#define TIMER_FAST_TRIGGER_MS             (1)
#define SCORE_TITLE_MAX_LENGTH           (16)
#define SCORE_VALUE_MAX_LENGTH            (6)
#define TILE_VALUE_MAX_LENGTH             (5)

typedef enum {
	APP_STATE_ANY,
	APP_STATE_INIT,
	APP_STATE_MAIN,
	APP_STATE_MENU,
	APP_STATE_MAX
} APP_STATE_T;

typedef enum {
	APP_TIMER_EXIT,
	APP_TIMER_MENU,
	APP_TIMER_RESET
} APP_TIMER_T;

typedef enum {
	APP_SOFT_KEY_MENU,
	APP_SOFT_KEY_LEFT,
	APP_SOFT_KEY_RIGHT
} APP_SOFT_KEY_T;

typedef enum {
	APP_RESOURCE_NAME,
	APP_RESOURCE_ICON,
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

typedef struct {
	BOOL show_background;
	BOOL rounded_tiles;
} APP_OPTIONS_T;

typedef struct {
	UINT16 tile_size;
	UINT16 offset_x;
	UINT16 offset_y;
	UINT16 rounded_rad;
	UINT16 font_large;
	UINT16 font_normal;
	UINT16 font_small;
	UINT16 font_ultra_small;
	UINT16 gap;
	UINT16 gap_y_huge;
} APP_MEASURED_T;

typedef enum {
	APP_DISPLAY_128x160 = 160,
	APP_DISPLAY_176x220 = 220,
	APP_DISPLAY_240x320 = 320
} APP_DISPLAY_T;

typedef struct {
	APPLICATION_T app;

	RESOURCE_ID resources[APP_RESOURCE_MAX];
	GRAPHIC_REGION_T area;
	APP_OPTIONS_T options;
	APP_MEASURED_T measured;
} APP_INSTANCE_T;

static __inline UINT32 OffsetCoord(UINT8 coord, UINT16 tile_size, UINT16 offset);
static __inline void SetRgbColor(COLOR_T *color, UINT32 rgb);

UINT32 Register(const char *elf_path_uri, const char *args, UINT32 ev_code);
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

static UINT32 SetWorikingArea(GRAPHIC_REGION_T *working_area);
static UINT32 SetMeasuredValues(APP_MEASURED_T *measured_values, DRAWING_BUFFER_T *buffer);
static UINT32 DrawSoftKeys(EVENT_STACK_T *ev_st, APPLICATION_T *app, APP_SOFT_KEY_T softkey, BOOL pushed);

static UINT32 PaintAll(EVENT_STACK_T *ev_st, APPLICATION_T *app, BOOL show_score, BOOL update_soft_keys);
static UINT32 PaintBoard(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 PaintBackground(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 PaintTile(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 value, UINT8 x, UINT8 y);
static UINT32 PaintFinal(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static LIST_ENTRY_T *CreateMainMenuList(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 start, UINT32 count);

static const char g_app_name[APP_NAME_LEN] = "2048-UIS";

static const WCHAR g_str_app_name[] = L"2048-P2K-UIS";
static const WCHAR g_str_app_soft_left[] = L"Exit";
static const WCHAR g_str_app_soft_right[] = L"Reset";
static const WCHAR g_str_app_score[] = L"Score: ";
static const WCHAR g_str_menu_save[] = L"Save Game";
static const WCHAR g_str_menu_load[] = L"Load Game";
static const WCHAR g_str_menu_reset[] = L"Reset Game";
static const WCHAR g_str_menu_background[] = L"Background";
static const WCHAR g_str_menu_tiles[] = L"Tiles";
static const WCHAR g_str_menu_help[] = L"Help...";
static const WCHAR g_str_menu_about[] = L"About...";
static const WCHAR g_str_menu_exit[] = L"Exit";

static const COLOR_T g_color_board = { 0xBB, 0xAD, 0xA0, 0xFF }; /* COLOR_BOARD */
static const COLOR_T g_color_text  = { 0x77, 0x6E, 0x65, 0xFF }; /* COLOR_TEXT  */

static const EVENT_HANDLER_ENTRY_T g_state_any_hdls[] = {
	{ EV_REVOKE_TOKEN, APP_HandleUITokenRevoked },
	{ EV_TIMER_EXPIRED, HandleEventTimerExpired },
	{ STATE_HANDLERS_END, NULL }
};

static const EVENT_HANDLER_ENTRY_T g_state_init_hdls[] = {
	{ EV_GRANT_TOKEN, APP_HandleUITokenGranted },
	{ STATE_HANDLERS_END, NULL }
};

static const EVENT_HANDLER_ENTRY_T g_state_main_hdls[] = {
	{ EV_DONE, ApplicationStop },
	{ EV_DIALOG_DONE, ApplicationStop },
	{ EV_INK_KEY_PRESS, HandleEventKeyPress },
	{ EV_INK_KEY_RELEASE, HandleEventKeyRelease },
	{ STATE_HANDLERS_END, NULL }
};

static const EVENT_HANDLER_ENTRY_T g_state_menu_hdls[] = {
	{ EV_DONE, HandleEventBack },
	{ EV_DIALOG_DONE, HandleEventBack },
	{ EV_SELECT, HandleEventSelect },
	{ STATE_HANDLERS_END, NULL }
};

static const STATE_HANDLERS_ENTRY_T g_state_table_hdls[] = {
	{ APP_STATE_ANY, NULL, NULL, g_state_any_hdls },
	{ APP_STATE_INIT, NULL, NULL, g_state_init_hdls },
	{ APP_STATE_MAIN, HandleStateEnter, HandleStateExit, g_state_main_hdls },
	{ APP_STATE_MENU, HandleStateEnter, HandleStateExit, g_state_menu_hdls }
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

UINT32 Register(const char *elf_path_uri, const char *args, UINT32 ev_code) {
	UINT32 status;
	UINT32 ev_code_base;

	ev_code_base = ev_code;

	status = APP_Register(&ev_code_base, 1, g_state_table_hdls, APP_STATE_MAX, (void *) ApplicationStart);

	LdrStartApp(ev_code_base);

	return status;
}

static UINT32 ApplicationStart(EVENT_STACK_T *ev_st, REG_ID_T reg_id, void *reg_hdl) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;

	status = RESULT_FAIL;

	if (AFW_InquireRoutingStackByRegId(reg_id) != RESULT_OK) {
		e_init(KEY_0, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);

		app_instance = (APP_INSTANCE_T *) APP_InitAppData((void *) APP_HandleEvent, sizeof(APP_INSTANCE_T),
			reg_id, 0, 1, 1, 1, 1, 0);

		InitResourses(app_instance->resources);
		app_instance->options.rounded_tiles = TRUE;
		app_instance->options.show_background = TRUE;

		status = APP_Start(ev_st, &app_instance->app, APP_STATE_MAIN,
			g_state_table_hdls, ApplicationStop, g_app_name, 0);
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

	LdrUnloadELF(&Lib);

	return status;
}

static UINT32 InitResourses(RESOURCE_ID *resources) {
	UINT32 status;

	status = RESULT_OK;

	status |= DRM_CreateResource(&resources[APP_RESOURCE_NAME], RES_TYPE_STRING,
		(void *) g_str_app_name, (u_strlen(g_str_app_name) + 1) * sizeof(WCHAR));
	status |= DRM_CreateResource(&resources[APP_RESOURCE_ICON], RES_TYPE_GRAPHICS,
		(void *) g_app_icon, sizeof(g_app_icon));

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
	DRAWING_BUFFER_T buffer;
	UIS_DIALOG_T dialog;
	APP_STATE_T app_state;
	GRAPHIC_POINT_T point;
	LIST_ENTRY_T *list;

	if (state != ENTER_STATE_ENTER) {
		return RESULT_OK;
	}

	app_instance = (APP_INSTANCE_T *) app;

	DeleteDialog(app);

	port = app->port;
	app_state = app->state;

	switch (app_state) {
		case APP_STATE_MAIN:
			point = UIS_CanvasGetDisplaySize();
			buffer.w = point.x + 1;
			buffer.h = point.y + 1;
			buffer.buf = NULL;
			SetWorikingArea(&app_instance->area);
			SetMeasuredValues(&app_instance->measured, &buffer);
			dialog = UIS_CreateColorCanvasWithWallpaper(&port, &buffer, FALSE, TRUE);
			break;
		case APP_STATE_MENU:
			list = CreateMainMenuList(ev_st, app, 1, APP_MENU_ITEM_MAX);
			if (list != NULL) {
				dialog = UIS_CreateStaticList(&port, 0, APP_MENU_ITEM_MAX, 0, list, FALSE, 2, NULL,
					app_instance->resources[APP_RESOURCE_NAME]);
				suFreeMem(list);
			}
			break;
		default:
			dialog = DialogType_None;
			break;
	}

	if (dialog == DialogType_None) {
		return RESULT_FAIL;
	}

	app->dialog = dialog;

	switch (app_state) {
	case APP_STATE_MAIN:
		PaintAll(ev_st, app, FALSE, TRUE);
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
		default:
			break;
	}

	return RESULT_OK;
}

static UINT32 HandleEventSelect(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	EVENT_T *event;

	status = RESULT_OK;
	event = AFW_GetEv(ev_st);

	UtilLogStringData("Selected item index: %d", event->data.index - 1);

	return status;
}

static UINT32 HandleEventBack(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;

	status = RESULT_OK;

	status |= APP_UtilChangeState(APP_STATE_MAIN, ev_st, app);

	return status;
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
			measured_values->rounded_rad = 4;
			measured_values->font_large = 0x0A;
			measured_values->font_normal = 0x01;
			measured_values->font_small = 0x06;
			measured_values->font_ultra_small = 0x09;
			measured_values->gap = 1;
			measured_values->gap_y_huge = 2;
			break;
		case APP_DISPLAY_176x220:
		case APP_DISPLAY_240x320: /* FIXME: Unknown values for 240x320 screen, set them similar to 176x220. */
			measured_values->tile_size = 22;
			measured_values->offset_x = 8;
			measured_values->offset_y = 4;
			measured_values->rounded_rad = 4;
			measured_values->font_large = 0x0A;
			measured_values->font_normal = 0x01;
			measured_values->font_small = 0x06;
			measured_values->font_ultra_small = 0x09;
			measured_values->gap = 1;
			measured_values->gap_y_huge = 2;
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
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			status |= PaintTile(ev_st, app, e_board[x + y * LINE_SIZE], x, y);
	status |= PaintFinal(ev_st, app);

	return status;
}

static UINT32 PaintBackground(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	if (app_instance->options.show_background) {
		UIS_CanvasFillRect(app_instance->area, app->dialog);
	} else {
		UIS_CanvasSetBackgroundColor(g_color_board);
		UIS_CanvasSetForegroundColor(g_color_board);
		UIS_CanvasDrawRect(app_instance->area, TRUE, app->dialog);
	}

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

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;
	tile_size = app_instance->measured.tile_size;

	coord_x = OffsetCoord(x, tile_size, app_instance->measured.offset_x);
	coord_y = OffsetCoord(y, tile_size, app_instance->measured.offset_y) + app_instance->area.ulc.y + 1;

	rect.ulc.x = coord_x;
	rect.ulc.y = coord_y;
	rect.lrc.x = coord_x + app_instance->measured.tile_size;
	rect.lrc.y = coord_y + app_instance->measured.tile_size;

	SetRgbColor(&color, e_background(value));
	UIS_CanvasSetBackgroundColor(color);
	UIS_CanvasSetForegroundColor(g_color_text);

	if (app_instance->options.rounded_tiles) {
		radius = app_instance->measured.rounded_rad;
		UIS_CanvasDrawRoundRect(rect, radius, radius, TRUE, app->dialog);
	} else {
		UIS_CanvasDrawRect(rect, TRUE, app->dialog);
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
		UIS_CanvasGetStringSize(tile_value, &string_measure, font_id);

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

	return status;
}

static LIST_ENTRY_T *CreateMainMenuList(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 start, UINT32 count) {
	UINT32 status;
	INT32 result;
	UINT32 i;
	LIST_ENTRY_T *list;

	status = RESULT_OK;
	result = RESULT_OK;

	if (count == 0) {
		return NULL;
	}
	list = (LIST_ENTRY_T *) suAllocMem(sizeof(LIST_ENTRY_T) * APP_MENU_ITEM_MAX, &result);
	if (result != RESULT_OK) {
		return NULL;
	}

	for (i = 0; i < APP_MENU_ITEM_MAX; ++i) {
		memclr(&list[i], sizeof(LIST_ENTRY_T));
		list[i].editable = FALSE;
		list[i].content.static_entry.formatting = TRUE;
	}

	status |= UIS_MakeContentFromString("Mq0",
		&list[APP_MENU_ITEM_SAVE].content.static_entry.text,
		g_str_menu_save);
	status |= UIS_MakeContentFromString("Mq0",
		&list[APP_MENU_ITEM_LOAD].content.static_entry.text,
		g_str_menu_load);
	status |= UIS_MakeContentFromString("Mq0",
		&list[APP_MENU_ITEM_RESET].content.static_entry.text,
		g_str_menu_reset);
	status |= UIS_MakeContentFromString("Mq0Sq1",
		&list[APP_MENU_ITEM_BACKGROUND].content.static_entry.text,
		g_str_menu_background, L"TODO");
	status |= UIS_MakeContentFromString("Mq0Sq1",
		&list[APP_MENU_ITEM_TILES].content.static_entry.text,
		g_str_menu_tiles, L"TODO");
	status |= UIS_MakeContentFromString("Mq0",
		&list[APP_MENU_ITEM_HELP].content.static_entry.text,
		g_str_menu_help);
	status |= UIS_MakeContentFromString("Mq0",
		&list[APP_MENU_ITEM_ABOUT].content.static_entry.text,
		g_str_menu_about);
	status |= UIS_MakeContentFromString("Mq0",
		&list[APP_MENU_ITEM_EXIT].content.static_entry.text,
		g_str_menu_exit);

	if (status != RESULT_OK) {
		suFreeMem(list);
		return NULL;
	}

	return list;
}
