#include <loader.h>
#include <apps.h>
#include <uis.h>
#include <canvas.h>
#include <res_def.h> // TODO: Delete?
#include <mem.h>

#define TIMER_UNPUSH_MS (1)

typedef enum {
	APP_STATE_ANY,
	APP_STATE_INIT,
	APP_STATE_MAIN,
	APP_STATE_MAX
} APP_STATE_T;

typedef enum {
	APP_TIMER_EXIT,
	APP_TIMER_UNPUSH
} APP_TIMER_T;

typedef struct {
	APPLICATION_T app;

	GRAPHIC_REGION_T area;
} APP_INSTANCE_T;

UINT32 Register(const char *elf_path_uri, const char *args, UINT32 ev_code);
static UINT32 ApplicationStart(EVENT_STACK_T *ev_st, REG_ID_T reg_id, void *reg_hdl);
static UINT32 ApplicationStop(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static UINT32 HandleStateEnter(EVENT_STACK_T *ev_st, APPLICATION_T *app, ENTER_STATE_TYPE_T state);
static UINT32 HandleStateExit(EVENT_STACK_T *ev_st, APPLICATION_T *app, EXIT_STATE_TYPE_T state);
static UINT32 DeleteDialog(APPLICATION_T *app);

static UINT32 HandleEventKeyPress(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventKeyRelease(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 HandleEventTimerExpired(EVENT_STACK_T *ev_st, APPLICATION_T *app);

static UINT32 PaintOnCanvas(EVENT_STACK_T *ev_st, APPLICATION_T *app);
static UINT32 GetWorikingArea(GRAPHIC_REGION_T *working_area);

static const char g_app_name[APP_NAME_LEN] = "2048-P2K";

static const WCHAR g_str_app_name[] = L"2048-P2K";
static const WCHAR g_str_app_soft_left[] = L"Exit";
static const WCHAR g_str_app_soft_right[] = L"Reset";

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

static const STATE_HANDLERS_ENTRY_T g_state_table_hdls[] = {
	{ APP_STATE_ANY, NULL, NULL, g_state_any_hdls },
	{ APP_STATE_INIT, NULL, NULL, g_state_init_hdls },
	{ APP_STATE_MAIN, HandleStateEnter, HandleStateExit, g_state_main_hdls }
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
		app_instance = (APP_INSTANCE_T *) APP_InitAppData((void *) APP_HandleEvent, sizeof(APP_INSTANCE_T),
			reg_id, 0, 1, 1, 1, 1, 0);

		status = APP_Start(ev_st, &app_instance->app, APP_STATE_MAIN,
			g_state_table_hdls, ApplicationStop, g_app_name, 0);
	}

	return status;
}

static UINT32 ApplicationStop(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;

	DeleteDialog(app);

	status = APP_Exit(ev_st, app, 0);

	LdrUnloadELF(&Lib);

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
		PaintOnCanvas(ev_st, app);
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
			status |= APP_UtilStartTimer(TIMER_UNPUSH_MS, APP_TIMER_EXIT, app);
			break;
		case KEY_MENU:
		case KEY_SOFT_RIGHT:
			status |= APP_UtilStartTimer(TIMER_UNPUSH_MS, APP_TIMER_UNPUSH, app);
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
		case APP_TIMER_UNPUSH:
			UIS_CanvasDrawColorSoftkey(NULL, 0, FALSE, TRUE, app->dialog);
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_right, 2, FALSE, TRUE, app->dialog);
			break;
		case APP_TIMER_EXIT:
			UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_left, 1, FALSE, TRUE, app->dialog);
			return ApplicationStop(ev_st, app);
			break;
		default:
			break;
	}

	return RESULT_OK;
}

static UINT32 PaintOnCanvas(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	APP_INSTANCE_T *app_instance;
	COLOR_T color;

	status = RESULT_OK;
	app_instance = (APP_INSTANCE_T *) app;

	color.red = 0xFF;
	color.green = 0x00;
	color.blue = 0x00;
	color.transparent = 0x00;

//	UIS_CanvasSetBackgroundColor(color);
//	UIS_CanvasSetForegroundColor(color);
	UIS_CanvasSetFillColor(color);

	UIS_CanvasDrawRect(app_instance->area, TRUE, app->dialog);

	UIS_CanvasDrawTitleBarWithIcon((WCHAR *) g_str_app_name, RES_GIF_FOLDER, FALSE, 1, FALSE, FALSE, app->dialog, 0, 0);

	UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_left, 1, FALSE, TRUE, app->dialog);
	UIS_CanvasDrawColorSoftkey(NULL, 0, FALSE, TRUE, app->dialog);
	UIS_CanvasDrawColorSoftkey((WCHAR *) g_str_app_soft_right, 2, FALSE, TRUE, app->dialog);

	return status;
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
