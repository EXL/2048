#include "2048.h"

#include <debug.h>

#include <system/application.h>
#include <system/resource.h>

#include <ogui/dialog.h>
#include <ogui/container.h>
#include <ogui/opi/addon.h>

#include "res/2048-ARIPOS_resources.h"

typedef enum _KEY_CODE {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_RESET
} KEY_CODE;

static const char *GAME2048_TASKNAME   = "2048-ARIPOS";
static const char *GAME2048_MODULENAME = "2048-ARIPOS";

static const int TILE_SIZE_600 = 7;
static const int TILE_SIZE_800 = 7;
static const int TILE_TILE_600 = 8;
static const int TILE_TILE_800 = 8;
static const int TILE_OFFSET_600 = 1;
static const int TILE_OFFSET_800 = 1;
static const int TEXT_OFFSET_600 = 9;
static const int TEXT_OFFSET_800 = 9;
static const int TILE_MARGIN_600 = 22;
static const int TILE_MARGIN_800 = 22;
static const int Y_OFFSET_600 = 1;
static const int Y_OFFSET_800 = 1;
static const int X_END_FIELD_600 = 120;
static const int X_END_FIELD_800 = 120;
static const int X_COLUMN_600 = 122;
static const int X_COLUMN_800 = 122;
static const int Y_COLUMN_OFFSET_600 = 8 + 1;
static const int Y_COLUMN_OFFSET_800 = 8 + 1;
static const int W_RECT_OVER_600 = 44;
static const int W_RECT_OVER_800 = 44;
static const int H_RECT_OVER_600 = 14;
static const int H_RECT_OVER_800 = 14;

static ResID rid_arrow_h;
static ResID rid_arrow_v;
static ResID rid_win;
static ResID rid_lose;

static int w_x;
static int w_y;
static Bool is_c_pen_800 = FALSE;
static Bool is_vertical = FALSE;

static _inline int Canvas_Offset_Coord(int coord, int tile, int margin, int offset) {
	return coord * (tile + margin) + offset;
}

static _inline void Canvas_Smart_Fill_Tile(int *ty, int *tf, int y, int value, int tile) {
    int offset = 0;

    switch (value) {
        case 2:
        case 4:
        case 8:
            offset = 2;
            break;
        case 16:
        case 32:
            offset = 3;
            break;
        case 64:
        case 128:
            offset = 4;
            break;
        case 256:
            offset = 5;
            break;
        case 512:
            offset = 6;
            break;
    }

    *ty = y + (tile - offset);
    *tf = tile - (tile - offset);
}

static _inline void Canvas_Center_Rect(int *x0, int *y0, int x, int y, int w, int h, int ww, int hh) {
    *x0 = x + (w - ww) / 2;
    *y0 = y + (h - hh) / 2;
}

static int Canvas_Draw_Tile(WidgetDC *pWDC, int value, int x, int y) {
	char num[5]; // "2048\0"
	const int ts = (is_c_pen_800) ? TILE_SIZE_600 : TILE_SIZE_800;
	const int tt = (is_c_pen_800) ? TILE_TILE_600 : TILE_TILE_800;
	const int tm = (is_c_pen_800) ? TILE_MARGIN_600 : TILE_MARGIN_800;
	const int to = (is_c_pen_800) ? TILE_OFFSET_600 : TILE_OFFSET_800;
	const int tx = (is_c_pen_800) ? TEXT_OFFSET_600 : TEXT_OFFSET_800;
	const int yo = (is_c_pen_800) ? Y_OFFSET_600 : Y_OFFSET_800;

	const int tile_x = Canvas_Offset_Coord(x, tt, tm, to);
	const int tile_y = Canvas_Offset_Coord(y, tt, 0, yo);
	const int text_x = Canvas_Offset_Coord(x, tt, tm, tx);
	const int text_y = Canvas_Offset_Coord(y, tt, 0, yo);

	WidgetDC_DrawRect(pWDC, tile_x, tile_y, ts, ts, LCD_COL_BLACK, LINE_SOLID);
	
	if (value) {
		int ty, tf;
		sprintf(num, "%d", value);

		Canvas_Smart_Fill_Tile(&ty, &tf, tile_y, value, ts);
		WidgetDC_FillRect(pWDC, tile_x, ty, ts, tf, LCD_COL_BLACK, MODE_COPY);
		WidgetDC_TextOut(pWDC, text_x, text_y, num, strlen(num), PP_FONT, MODE_COPY);
	}

	return NADA;
}

static int Canvas_Draw_Final(WidgetDC *pWDC) {
	char score[6]; // "99999\0"
	const int ef = (is_c_pen_800) ? X_END_FIELD_600 : X_END_FIELD_800;
	const int cs = (is_c_pen_800) ? X_COLUMN_600 : X_COLUMN_800;
	const int yo = (is_c_pen_800) ? Y_COLUMN_OFFSET_600 : Y_COLUMN_OFFSET_800;
	const int bo = (is_c_pen_800) ? BITMAP_OFFSET_600 : BITMAP_OFFSET_800;

	WidgetDC_DrawLine(pWDC, ef, 0, ef, w_y, LCD_COL_BLACK, LINE_SOLID);

	sprintf(score, "%d", e_score);

	WidgetDC_TextOut(pWDC, cs, 0 * yo, "Score", 5, MINIMAL_FONT, MODE_COPY);
	WidgetDC_TextOut(pWDC, cs, 1 * yo, score, strlen(score), MINIMAL_FONT, MODE_COPY);
      
    if ((rid_arrow_h != -1) && (rid_arrow_v != -1)) {  
		Lcd_Bitmap *bitmap;
		if (e_win || e_lose) {
			bitmap = (Lcd_Bitmap *) ((e_win) ? RP_Get(rid_arrow_v, NULL) : RP_Get(rid_arrow_h, NULL));
		} else {
			bitmap = (Lcd_Bitmap *) ((is_vertical) ? RP_Get(rid_arrow_v, NULL) : RP_Get(rid_arrow_h, NULL));
		}
        if (bitmap) { 
            WidgetDC_DrawBitmap(pWDC, cs, 2 * yo, bitmap, MODE_COPY);
		}
    }

	if (e_win || e_lose) {
		int x, y, o_x = (e_win) ? 3 : 2;
		const int wr = (is_c_pen_800) ? W_RECT_OVER_600 : W_RECT_OVER_800;
		const int hr = (is_c_pen_800) ? H_RECT_OVER_600 : H_RECT_OVER_800;
		const char *label = (e_win) ? "You Won!" : "You Lose!";

		WidgetDC_FillRect(pWDC, 0, 0, ef+1, w_y, LCD_COL_BLACK, MODE_XOR);

		Canvas_Center_Rect(&x, &y, 0, 0, ef+1, w_y, wr + 2, hr + 2);
		WidgetDC_FillRect(pWDC, x, y, wr + 2, hr + 2, LCD_COL_BLACK, MODE_COPY);
		Canvas_Center_Rect(&x, &y, 0, 0, ef+1, w_y, wr, hr);
		WidgetDC_FillRect(pWDC, x, y, wr, hr, LCD_COL_WHITE, MODE_COPY);

		WidgetDC_TextOut(pWDC, x + o_x, y + 2, label, strlen(label), PP_LARGEFONT, MODE_COPY);
	}

	return NADA;
}

int Canvas_Paint(OPTR pS, WidgetDC *pWDC) {
	int x, y;
	OGUI_Point size;

	size = CCALL0(Widget, pS, GetSize);
	OGUI_UnpackPoint(&w_x, &w_y, size);
	is_c_pen_800 = (w_y > 40) ? TRUE : FALSE;
	Dbg_printf("2048-ARIPOS:Paint, widget size: %dx%d, is_c_pen_800=%d\n", w_x, w_y, is_c_pen_800);

	for (y = 0; y < LINE_SIZE; ++y)
			for (x = 0; x < LINE_SIZE; ++x)
				Canvas_Draw_Tile(pWDC, e_board[x + y * LINE_SIZE], x, y);
		Canvas_Draw_Final(pWDC);

	// Call Paint method from parent Widget class.
	CCALL1(Widget, pS, Paint, pWDC);

    return NADA;  
}

int Canvas_SelectPressed(OPTR pS) {
	Dbg_printf("2048-ARIPOS:SelectPressed\n");
	is_vertical = !is_vertical;
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Canvas_StepUp(OPTR pS) {
	Dbg_printf("2048-ARIPOS:StepUp\n");
	e_key((is_vertical) ? KEY_UP : KEY_LEFT);
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Canvas_StepDown(OPTR pS) {
	Dbg_printf("2048-ARIPOS:StepDown\n");
	e_key((is_vertical) ? KEY_DOWN : KEY_RIGHT);
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Canvas_ScanPressed(OPTR pS) {
	Dbg_printf("2048-ARIPOS:ScanPressed\n");
	e_key(KEY_RESET);
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

void Game2048_Stop(void) {
	Task_StopChildren((char *) GAME2048_TASKNAME);
}

int Game2048_Close(OPTR pDialog, int BtnNbr) {
	OPI_DisposeObject(pDialog);
	Game2048_Stop();
	return NADA;
}

int Game2048_Start(OPTR pFromObj) {
	OPTR pDlg;

	e_init(KEY_RESET, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);

	rid_arrow_h = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_ARROW_HORZONTAL, 0);
	rid_arrow_v = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_ARROW_VERTICAL, 0);

	pDlg = FullScreenColumnDialog(OGUI_GetMainView(), NULL, OPI_METHOD_HOOK(CloseDialog, Game2048_Close));
	if (pDlg) {
		int flags;

		flags = MCALL0(pDlg, GetWidgetFlags);
		flags = flags | WF_Static;
//		flags = flags | WF_Static | WF_DrawBorder;
		MCALL1(pDlg, SetWidgetFlags, flags);

		OPI_SET_METHOD(pDlg, OPI_METHOD_HOOK(Paint, Canvas_Paint));
		OPI_SET_METHOD(pDlg, OPI_METHOD_HOOK(SelectPressed, Canvas_SelectPressed));
		OPI_SET_METHOD(pDlg, OPI_METHOD_HOOK(StepUp, Canvas_StepUp));
		OPI_SET_METHOD(pDlg, OPI_METHOD_HOOK(StepDown, Canvas_StepDown));
		OPI_SET_METHOD(pDlg, OPI_METHOD_HOOK(ScanPressed, Canvas_ScanPressed));

		// ICONTODO
		MCALL1(pDlg, SetTaskName, "2048-ARIPOS");

		MCALL0(pDlg, Mark);

	}
	return NADA;
}

void Game2048_Suspend(void) {
	Task_SuspendChildren((char *) GAME2048_TASKNAME);
}

void Game2048_Unsuspend(void) {
	Game2048_Start(NULL);
}

void Game2048_CleanUp(void) {
	Task_Exit((char *) GAME2048_TASKNAME);
}

int Game2048_Installer(void) {
	return Application_Install(
		(char *) GAME2048_TASKNAME,
		(char *) GAME2048_MODULENAME,
		"Game2048_evthandler"
	);
}

int Game2048_Uninstaller(void) {
	return Application_Uninstall(
		(char *) GAME2048_TASKNAME
	);
}

void Game2048_evthandler(int a, void *ptr, void *userdata) {
	switch (a) {
		case TASKEVT_START:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_START\n");
			Game2048_Start(NULL);
			break;
		case TASKEVT_STOP:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_STOP\n");
			Game2048_Stop();
			break;
		case TASKEVT_SUSPEND:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_SUSPENED\n");
			Game2048_Suspend();
			break;
		case TASKEVT_UNSUSPEND:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_UNSUSPENED\n");
			Game2048_Unsuspend();
			break;
		case TASKEVT_CHLD:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_CHLD\n");
			// Do nothing, wait for all childs to exit
			break;
		case TASKEVT_NOCHLD:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_NOCHLD\n");
			// Cleanup and exit
			Game2048_CleanUp();
			break;
		default:
			Dbg_printf("2048-ARIPOS:Got unknown:%d\n",a);
	}
}
