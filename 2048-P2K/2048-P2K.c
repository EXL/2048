#include <loader.h>
#include <apps.h>
#include <uis.h>
#include <canvas.h>
#include <res_def.h>

typedef enum {
	APP_STATE_ANY,
	APP_STATE_INIT,
	APP_STATE_MAIN,
	APP_STATE_MAX
} APP_STATE_T;

typedef struct {
	APPLICATION_T app;
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

static const char g_app_name[APP_NAME_LEN] = "2048-P2K";

static const WCHAR g_str_app_name[] = L"2048-P2K";

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
	SU_PORT_T port;
	DRAWING_BUFFER_T buffer;
	UIS_DIALOG_T dialog;
	APP_STATE_T app_state;

	if (state != ENTER_STATE_ENTER) {
		return RESULT_OK;
	}

	DeleteDialog(app);

	port = app->port;
	app_state = app->state;

	switch (app_state) {
		case APP_STATE_MAIN:
			buffer.w = 128;
			buffer.h = 160;
			buffer.buf = NULL;
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
	UINT32 result;
	EVENT_T *event;

	result = RESULT_OK;
	event = AFW_GetEv(ev_st);

	APP_ConsumeEv(ev_st, app);

	switch (event->data.key_pressed) {
		case KEY_SOFT_LEFT:
//			UIS_CanvasDrawColorSoftkey(L"Exit", 1, TRUE, FALSE, app->dialog);
			return ApplicationStop(ev_st, app);
			break;
		case KEY_SOFT_RIGHT:
//			UIS_CanvasDrawColorSoftkey(L"Reset", 2, TRUE, FALSE, app->dialog);
			break;
		default:
			break;
	}

//	PaintOnCanvas(ev_st, app);

	return result;
}

static UINT32 HandleEventKeyRelease(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	return RESULT_OK;
}

static UINT32 HandleEventTimerExpired(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	return RESULT_OK;
}

static UINT32 PaintOnCanvas(EVENT_STACK_T *ev_st, APPLICATION_T *app) {
	UINT32 status;
	COLOR_T color;
	GRAPHIC_REGION_T rect;

	status = RESULT_OK;

	color.red = 0xFF;
	color.green = 0xFF;
	color.blue = 0xFF;
	color.transparent = 0xFF;

	UIS_CanvasSetFillColor(color);

	rect.ulc.x = 0;
	rect.ulc.y = 0;
	rect.lrc.x = 0 + 128;
	rect.lrc.y = 0 + 140;

	UIS_CanvasFillRect(rect, app->dialog);

	UIS_CanvasDrawTitleBarWithIcon((WCHAR *) g_str_app_name, RES_GIF_FOLDER, FALSE, 1, FALSE, FALSE, app->dialog, 0, 0);

	UIS_CanvasDrawColorSoftkey(NULL, 0, FALSE, FALSE, app->dialog);
	UIS_CanvasDrawColorSoftkey(L"Exit", 1, FALSE, FALSE, app->dialog);
	UIS_CanvasDrawColorSoftkey(L"Reset", 2, FALSE, FALSE, app->dialog);

	return status;
}
