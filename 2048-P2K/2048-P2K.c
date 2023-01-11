#include <loader.h>
#include <apps.h>
#include <uis.h>
#include <canvas.h>
#include <mem.h>
#include <utilities.h>

#include <res_def.h>
#include "app_icon.h"
#include "2048.h"
#include "2048.c"

#define TIMER_UNPUSH_MS (1)

typedef enum {
	APP_STATE_ANY,
	APP_STATE_INIT,
	APP_STATE_MAIN,
	APP_STATE_MENU,
	APP_STATE_MAX
} APP_STATE_T;

typedef enum {
	APP_TIMER_LEFT_SOFT,
	APP_TIMER_MENU,
	APP_TIMER_RIGHT_SOFT
} APP_TIMER_T;

typedef enum {
	APP_RESOURCE_ICON,
	APP_RESOURCE_MAX
} APP_RESOURCES_T;

typedef struct {
	APPLICATION_T app;

	RESOURCE_ID resources[APP_RESOURCE_MAX];
	GRAPHIC_REGION_T area;
} APP_INSTANCE_T;

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
static UINT32 HandleEventBack(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static UINT32 GetWorikingArea(GRAPHIC_REGION_T *working_area);
static UINT32 PaintAll(EVENT_STACK_T *ev_st, APPLICATION_T *app, BOOL show_score, BOOL update_soft_keys);
static UINT32 PaintBoard(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 PaintBackground(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 PaintTile(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 value, UINT8 x, UINT8 y);
static UINT32 PaintFinal(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static LIST_ENTRY_T *TestTestTest(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 start, UINT32 count);

static const char g_app_name[APP_NAME_LEN] = "2048-P2K";

static const WCHAR g_str_app_name[] = L"2048-P2K";
static const WCHAR g_str_app_soft_left[] = L"Exit";
static const WCHAR g_str_app_soft_right[] = L"Reset";
static const WCHAR g_str_app_score[] = L"Score: ";

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
//	{ EV_REQUEST_LIST_ITEMS, HandleEventMenuRequestListItems },
	{ EV_DONE, HandleEventBack },
	{ EV_DIALOG_DONE, HandleEventBack },
//	{ EV_SELECT, HandleEventSelect },
	{ STATE_HANDLERS_END, NULL }
};

static const STATE_HANDLERS_ENTRY_T g_state_table_hdls[] = {
	{ APP_STATE_ANY, NULL, NULL, g_state_any_hdls },
	{ APP_STATE_INIT, NULL, NULL, g_state_init_hdls },
	{ APP_STATE_MAIN, HandleStateEnter, HandleStateExit, g_state_main_hdls },
	{ APP_STATE_MENU, HandleStateEnter, HandleStateExit, g_state_menu_hdls }
};

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
			GetWorikingArea(&app_instance->area);
			dialog = UIS_CreateColorCanvasWithWallpaper(&port, &buffer, FALSE, TRUE);
			break;
		case APP_STATE_MENU:
			dialog = UIS_CreateStaticList(&port, 0, 3, 0, TestTestTest(ev_st, app, 1, 3), FALSE, 2, NULL, LANG_MENU);
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
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_left, 1, TRUE, TRUE, app->dialog);
			break;
		case KEY_MENU:
			UIS_CanvasDrawColorSoftkey(NULL, 0, TRUE, TRUE, app->dialog);
			break;
		case KEY_SOFT_RIGHT:
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_right, 2, TRUE, TRUE, app->dialog);
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
			status |= APP_UtilStartTimer(TIMER_UNPUSH_MS, APP_TIMER_LEFT_SOFT, app);
			break;
		case KEY_MENU:
			status |= APP_UtilStartTimer(TIMER_UNPUSH_MS, APP_TIMER_MENU, app);
			break;
		case KEY_SOFT_RIGHT:
			status |= APP_UtilStartTimer(TIMER_UNPUSH_MS, APP_TIMER_RIGHT_SOFT, app);
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
		case APP_TIMER_LEFT_SOFT:
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_left, 1, FALSE, TRUE, app->dialog);
			return ApplicationStop(ev_st, app);
			break;
		case APP_TIMER_MENU:
			UIS_CanvasDrawColorSoftkey(NULL, 0, FALSE, TRUE, app->dialog);
			APP_UtilChangeState(APP_STATE_MENU, ev_st, app);
			break;
		case APP_TIMER_RIGHT_SOFT:
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_right, 2, FALSE, TRUE, app->dialog);
			e_key(KEY_0);
			PaintAll(ev_st, app, FALSE, FALSE);
			break;
		default:
			break;
	}

	return RESULT_OK;
}

static UINT32 GetWorikingArea(GRAPHIC_REGION_T *working_area) {
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

static UINT32 PaintAll(EVENT_STACK_T *ev_st, APPLICATION_T *app, BOOL show_score, BOOL update_soft_keys) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	WCHAR score_title[32] = { 0 };
	WCHAR score_string[10] = { 0 };

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	if (show_score) {
		u_ltou(e_score, score_string);
		u_strcat(score_title, g_str_app_score);
		u_strcat(score_title, score_string);
		UIS_CanvasDrawTitleBarWithIcon(score_title, app_instance->resources[APP_RESOURCE_ICON],
			FALSE, 1, FALSE, FALSE, app->dialog, 0, 0);
	} else {
		UIS_CanvasDrawTitleBarWithIcon((WCHAR *) g_str_app_name, app_instance->resources[APP_RESOURCE_ICON],
			FALSE, 1, FALSE, FALSE, app->dialog, 0, 0);
	}

	status |= PaintBoard(ev_st, app);

	if (update_soft_keys) {
		UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_left, 1, FALSE, TRUE, app->dialog);
		UIS_CanvasDrawColorSoftkey(NULL, 0, FALSE, TRUE, app->dialog);
		UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_right, 2, FALSE, TRUE, app->dialog);
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
	COLOR_T color;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	if (0) {
		UIS_CanvasFillRect(app_instance->area, app->dialog);
	} else {
		color.red = (COLOR_BOARD & 0x00FF0000) >> 16;
		color.green = (COLOR_BOARD & 0x0000FF00) >> 8;
		color.blue = (COLOR_BOARD & 0x000000FF) >> 0;
		color.transparent = (COLOR_BOARD & 0xFF000000) >> 24;

		UIS_CanvasSetBackgroundColor(color);
		UIS_CanvasSetForegroundColor(color);

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
	UINT32 tile_color;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	coord_x = x * (22 + 8) + 8;
	coord_y = (y * (22 + 4) + 4) + app_instance->area.ulc.y + 1;

	rect.ulc.x = coord_x;
	rect.ulc.y = coord_y;
	rect.lrc.x = coord_x + 22;
	rect.lrc.y = coord_y + 22;

	tile_color = e_background(value);
	color.red = (tile_color & 0x00FF0000) >> 16;
	color.green = (tile_color & 0x0000FF00) >> 8;
	color.blue = (tile_color & 0x000000FF) >> 0;
	color.transparent = (tile_color & 0xFF000000) >> 24;
	UIS_CanvasSetBackgroundColor(color);

	tile_color = e_foreground(value);
	color.red = (tile_color & 0x00FF0000) >> 16;
	color.green = (tile_color & 0x0000FF00) >> 8;
	color.blue = (tile_color & 0x000000FF) >> 0;
	color.transparent = (tile_color & 0xFF000000) >> 24;
	UIS_CanvasSetForegroundColor(color);

	UIS_CanvasDrawRoundRect(rect, 4, 4, TRUE, app->dialog);

	if (value) {
		WCHAR str_value[5] = { 0 };
		GRAPHIC_POINT_T point;

		u_ltou(value, str_value);
		if (value < 10) {
			UIS_CanvasSetFont(0x0A, app->dialog);
			point.x = coord_x + 8;
			point.y = coord_y + 3;
		} else if (value < 100) {
			UIS_CanvasSetFont(0x01, app->dialog);
			if (value < 32) {
				point.x = coord_x + 6;
			} else {
				point.x = coord_x + 5;
			}
			point.y = coord_y + 3;
		} else if (value < 1000) {
			UIS_CanvasSetFont(0x06, app->dialog);
			if (value < 256) {
				point.x = coord_x + 2;
			} else {
				point.x = coord_x + 3;
			}
			point.y = coord_y + 4;
		} else {
			UIS_CanvasSetFont(0x09, app->dialog);
			point.x = coord_x + 4;
			point.y = coord_y + 2;
		}
		UIS_CanvasDrawColorText(str_value, 0, u_strlen(str_value), point, 0, app->dialog);
	}

	return status;
}

static UINT32 PaintFinal(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;

	status = RESULT_OK;

	return status;
}

static UINT32 HandleEventBack(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	EVENT_T *event;

	status = RESULT_OK;
	event = AFW_GetEv(ev_st);

	APP_ConsumeEv(ev_st, app);

	status |= APP_UtilChangeState(APP_STATE_MAIN, ev_st, app);

	return status;
}

static LIST_ENTRY_T *TestTestTest(EVENT_STACK_T *ev_st, APPLICATION_T *app, UINT32 start, UINT32 count) {
	UINT32 status;
	INT32 result;
	UINT32 i;
	LIST_ENTRY_T *list;

	status = RESULT_OK;
	result = RESULT_OK;

	if (count == 0) {
//		return RESULT_FAIL;
	}
	list = (LIST_ENTRY_T *) suAllocMem(sizeof(LIST_ENTRY_T) * 3, &result);
	if (result != RESULT_OK) {
//		return RESULT_FAIL;
	}

	for (i = 0; i < 3; ++i) {
		memclr(&list[i], sizeof(LIST_ENTRY_T));
		list[i].editable = FALSE;
		list[i].content.static_entry.formatting = TRUE;
	}

	status |= UIS_MakeContentFromString("q0",
		&list[0].content.static_entry.text,
		L"1");
	status |= UIS_MakeContentFromString("q0",
		&list[1].content.static_entry.text,
		L"2");
	status |= UIS_MakeContentFromString("q0",
		&list[2].content.static_entry.text,
		L"3");

	status |= APP_UtilAddEvUISListData(ev_st, app, 0, start, 3, FBF_LEAVE,
		sizeof(LIST_ENTRY_T) * 3, list);
	if (status != RESULT_FAIL) {
		UIS_HandleEvent(app->dialog, ev_st);
	}

//	suFreeMem(list);

	return list;
}
