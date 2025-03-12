#include "2048.h"

#include <debug.h>

#include <system/application.h>
#include <system/resource.h>

#include <ogui/dialog.h>
#include <ogui/container.h>
#include <ogui/opi/addon.h>

#include "res/Game2048_resources.h"

#define  STR_LEN_VALUE            (5)
#define  STR_LEN_SCORE            (6)
#define  STR_LEN_LABEL           (10)

#if defined(_MSC_VER)
#define INLINE _inline
#else
#define INLINE inline
#endif

#define TS                        ((is_c_pen_800) ?     13 :      7) /* TILE_SIZE       */
#define TT                        ((is_c_pen_800) ?     14 :      8) /* TILE_TILE       */
#define TO                        ((is_c_pen_800) ?      1 :      1) /* TILE_OFFSET     */
#define TX                        ((is_c_pen_800) ?      2 :      9) /* TEXT_OFFSET     */
#define TM                        ((is_c_pen_800) ?      0 :     22) /* TILE_MARGIN     */
#define YO                        ((is_c_pen_800) ?      1 :      1) /* Y_OFFSET        */
#define EF                        ((is_c_pen_800) ?     58 :    120) /* X_END_FIELD     */
#define YC                        ((is_c_pen_800) ? TS + 1 : TT + 1) /* Y_COLUMN_OFFSET */
#define WR                        ((is_c_pen_800) ?     44 :     44) /* W_RECT_OVER     */
#define HR                        ((is_c_pen_800) ?     14 :     14) /* H_RECT_OVER     */

typedef enum _KEY_CODE {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_RESET
} KEY_CODE;

static const char *GAME2048_TASKNAME   = "Game2048";
static const char *GAME2048_MODULENAME = "Game2048";

static ResID rid_arrow_h;
static ResID rid_arrow_v;
static ResID rid_win;
static ResID rid_lose;

static int w_x, w_y;
static Bool is_c_pen_800 = FALSE;
static Bool is_vertical = FALSE;

static INLINE int Canvas_Offset_Coord(int coord, int tile, int margin, int offset) {
	return coord * (tile + margin) + offset;
}

static INLINE void Canvas_Smart_Fill_Tile(int *ty, int *tf, int y, int value, int tile) {
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
		case 512:
			offset = 5;
			break;
		case 1024:
		case 2048:
			offset = 6;
			break;
	}

	*ty = y + (tile - offset);
	*tf = tile - (tile - offset);
}

static INLINE void Canvas_Center_Rect(int *x0, int *y0, int x, int y, int w, int h, int ww, int hh) {
	*x0 = x + (w - ww) / 2;
	*y0 = y + (h - hh) / 2;
}

static INLINE void Canvas_FixUp_Text_Offsets(int *x, int *y, FontGUID *font, int value) {
	if (!is_c_pen_800) {
		*x = 0;
		*y = 0;
		*font = PP_FONT;
	} else {
		switch (value) {
			case 2:
			case 4:
			case 8:
				*x = 3;
				*y = 2;
				*font = PP_LARGEFONT;
				break;
			case 16:
				*x = 2;
				*y = 2;
				*font = DEFAULT_FONT;
				break;
			case 32:
			case 64:
				*x = 1;
				*y = 3;
				*font = PP_FONT;
				break;
			case 128:
			case 256:
			case 512:
			case 1024:
			case 2048:
				*x = 0;
				*y = 4;
				*font = MINIMAL_FONT;
				break;
		}
	}
}

static int Canvas_Draw_Tile(WidgetDC *pWDC, int value, int x, int y) {
	char num[STR_LEN_VALUE]; // "2048\0"
#if defined(_UNICODE)
	wchar wnum[STR_LEN_VALUE];
#endif
	const int tile_x = Canvas_Offset_Coord(x, TT, TM, TO);
	const int tile_y = Canvas_Offset_Coord(y, TT,  0, YO);
	const int text_x = Canvas_Offset_Coord(x, TT, TM, TX);
	const int text_y = Canvas_Offset_Coord(y, TT,  0, YO);

	WidgetDC_DrawRect(pWDC, tile_x, tile_y, TS, TS, LCD_COL_BLACK, LINE_SOLID);
	
	if (value) {
		int ty, tf;
		int x_o, y_o;
		FontGUID font;

		sprintf(num, "%d", value);
#if defined(_UNICODE)
		ISOToUniCode(wnum, strlen(num), num);
#endif

		if (!is_c_pen_800) {
			Canvas_Smart_Fill_Tile(&ty, &tf, tile_y, value, TS);
			WidgetDC_FillRect(pWDC, tile_x, ty, TS, tf, LCD_COL_BLACK, MODE_COPY);
		}

		Canvas_FixUp_Text_Offsets(&x_o, &y_o, &font, value);
#if defined(_UNICODE)
		WidgetDC_TextOut(pWDC, text_x + x_o, text_y + y_o, wnum, wstrlen(wnum),
			font, (is_c_pen_800 && (value < 512)) ? MODE_XOR : MODE_COPY);
#else
		WidgetDC_TextOut(pWDC, text_x + x_o, text_y + y_o, num, strlen(num),
			font, (is_c_pen_800 && (value < 512)) ? MODE_XOR : MODE_COPY);
#endif
	}

	return NADA;
}

static int Canvas_Draw_Final(WidgetDC *pWDC) {
	char score[STR_LEN_SCORE]; // "99999\0"
	const char *score_label = "Score";
#if defined(_UNICODE)
	wchar wscore[STR_LEN_SCORE];
	wchar wscore_label[STR_LEN_SCORE];
#endif

	WidgetDC_DrawLine(pWDC, EF, 0, EF, w_y, LCD_COL_BLACK, LINE_SOLID);

	sprintf(score, "%d", e_score);
#if defined(_UNICODE)
	ISOToUniCode(wscore, strlen(score), score);
	ISOToUniCode(wscore_label, strlen(score_label), (char *) score_label);

	WidgetDC_TextOut(pWDC, EF + 2, 0 * YC, wscore_label, wstrlen(wscore_label),
		(is_c_pen_800) ? PP_LARGEFONT : MINIMAL_FONT, MODE_COPY);
	WidgetDC_TextOut(pWDC, EF + 2, 1 * YC, wscore, wstrlen(wscore),
		(is_c_pen_800) ? PP_LARGEFONT : MINIMAL_FONT, MODE_COPY);
#else
	WidgetDC_TextOut(pWDC, EF + 2, 0 * YC, score_label, strlen(score_label),
		(is_c_pen_800) ? PP_LARGEFONT : MINIMAL_FONT, MODE_COPY);
	WidgetDC_TextOut(pWDC, EF + 2, 1 * YC, score, strlen(score),
		(is_c_pen_800) ? PP_LARGEFONT : MINIMAL_FONT, MODE_COPY);
#endif

	if ((rid_arrow_h != -1) && (rid_arrow_v != -1)) {
		Lcd_Bitmap *bitmap;
		if (e_win || e_lose) {
			bitmap = (Lcd_Bitmap *) ((e_win) ? RP_Get(rid_win, NULL) : RP_Get(rid_lose, NULL));
		} else {
			bitmap = (Lcd_Bitmap *) ((is_vertical) ? RP_Get(rid_arrow_v, NULL) : RP_Get(rid_arrow_h, NULL));
		}
		if (bitmap) {
			WidgetDC_DrawBitmap(pWDC, EF + 2, 2 * YC, bitmap, MODE_COPY);
		}
	}

	if (e_win || e_lose) {
		int x, y, o_x = (e_win) ? 3 : 2;
		const char *label = (e_win) ? "You Won!" : "You Lose!";
#if defined(_UNICODE)
		wchar wlabel[STR_LEN_LABEL];
		ISOToUniCode(wlabel, strlen(label), (char *) label);
#endif

		WidgetDC_FillRect(pWDC, 0, 0, EF + 1, w_y, LCD_COL_BLACK, MODE_XOR);

		Canvas_Center_Rect(&x, &y, 0, 0, EF + 1, w_y, WR + 2, HR + 2);
		WidgetDC_FillRect(pWDC, x, y, WR + 2, HR + 2, LCD_COL_BLACK, MODE_COPY);
		Canvas_Center_Rect(&x, &y, 0, 0, EF + 1, w_y, WR, HR);
		WidgetDC_FillRect(pWDC, x, y, WR, HR, LCD_COL_WHITE, MODE_COPY);
#if defined(_UNICODE)
		WidgetDC_TextOut(pWDC, x + o_x, y + 2, wlabel, wstrlen(wlabel), PP_LARGEFONT, MODE_COPY);
#else
		WidgetDC_TextOut(pWDC, x + o_x, y + 2, (char *) label, strlen(label), PP_LARGEFONT, MODE_COPY);
#endif
	}

	return NADA;
}

int Canvas_Paint(OPTR pS, WidgetDC *pWDC) {
	int x, y;
	OGUI_Point size;

	// Determine Widget size and check if app running on C-Pen 800.
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
	is_vertical = FALSE;
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

#if 0
	e_board[ 0] =  128;
	e_board[ 1] =   64;
	e_board[ 4] =  256;
	e_board[ 5] =   32;
	e_board[ 8] =  512;
	e_board[ 9] =   16;
	e_board[12] = 1024;
	e_board[13] =    8;
#endif

	rid_arrow_h = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_ARROW_HORZONTAL, 0);
	rid_arrow_v = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_ARROW_VERTICAL, 0);
	rid_win = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_WIN, 0);
	rid_lose = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_LOSE, 0);

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

		// Set application icon (relevant only for C-Pen 800).
		MCALL1(pDlg, SetTaskName, "2048-ARIPOS");

		// Activate dialog Widget and set focus to it.
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
	return Application_Install((char *) GAME2048_TASKNAME, (char *) GAME2048_MODULENAME, "Game2048_evthandler");
}

int Game2048_Uninstaller(void) {
	return Application_Uninstall((char *) GAME2048_TASKNAME);
}

void Game2048_evthandler(int event, void *ptr, void *userdata) {
	switch (event) {
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
			// Do nothing, wait for all childs to exit.
			break;
		case TASKEVT_NOCHLD:
			Dbg_printf("2048-ARIPOS:Got TASKEVT_NOCHLD\n");
			// Cleanup and exit.
			Game2048_CleanUp();
			break;
		default:
			Dbg_printf("2048-ARIPOS:Got unknown:0x%08X %d\n", event, event);
	}
}
