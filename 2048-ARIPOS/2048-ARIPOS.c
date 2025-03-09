#include <debug.h>

#include <system/application.h>
#include <system/resource.h>

#include <ogui/dialog.h>
#include <ogui/container.h>
#include <ogui/opi/addon.h>

#include "res/2048-ARIPOS_resources.h"

int Game2048_Start(OPTR pFromObj);

static const char *GAME2048_TASKNAME   = "2048-ARIPOS";
static const char *GAME2048_MODULENAME = "2048-ARIPOS";

static ResID rid_arrow_h;
static ResID rid_arrow_v;

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

void Game2048_Stop(void) {
	Task_StopChildren((char *) GAME2048_TASKNAME);
}

void Game2048_Suspend(void) {
	Task_SuspendChildren((char *) GAME2048_TASKNAME);
}

void Game2048_Unsuspend(void) {
	Game2048_Start(NULL);
}

int Game2048_Close(OPTR pDialog, int BtnNbr) {
	OPI_DisposeObject(pDialog);
	Game2048_Stop();
	return NADA;
}

int Canvas_Paint(OPTR pS, WidgetDC *pWDC) {
	Lcd_Bitmap *hCir;
	int i, j;
	Dbg_printf("2048-ARIPOS:Paint\n");
  
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j) {
			WidgetDC_DrawRect(pWDC, (i*(8+22))+ ((i == 0) ? 1 : 1), j*8+1, 7, 7, LCD_COL_BLACK, MODE_COPY);
			WidgetDC_TextOut(pWDC, (i*(8+22))+ ((i == 0) ? 9 : 9), j*8+1, "2048", 4, PP_FONT, MODE_COPY);  
		}

	WidgetDC_DrawLine(pWDC, 120, 0, 120, 32, LCD_COL_BLACK, LINE_SOLID); 

	WidgetDC_TextOut(pWDC, 122, 0*8+1, "Score", 5, MINIMAL_FONT, MODE_COPY);
	WidgetDC_TextOut(pWDC, 122, 1*8+1, "20480", 5, MINIMAL_FONT, MODE_COPY);

      
    if ((rid_arrow_h != -1) && (rid_arrow_v != -1)) {  
        hCir = (Lcd_Bitmap *) RP_Get(rid_arrow_h, NULL);
        if (hCir) {  
            WidgetDC_DrawBitmap(pWDC, 122, 2*8-1, hCir, MODE_COPY);
		}
    }

	WidgetDC_FillRect(pWDC, 0, 0, 121, 33, LCD_COL_BLACK, MODE_XOR); 
  

    CCALL1(Widget, pS, Paint, pWDC);
	
    return NADA;  
}

int Canvas_SelectPressed(OPTR pS) {
	Dbg_printf("2048-ARIPOS:SelectPressed\n");
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Canvas_StepUp(OPTR pS) {
	Dbg_printf("2048-ARIPOS:StepUp\n");
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Canvas_StepDown(OPTR pS) {
	Dbg_printf("2048-ARIPOS:StepDown\n");
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Canvas_ScanPressed(OPTR pS) {
	Dbg_printf("2048-ARIPOS:ScanPressed\n");
	CCALL0(Widget, pS, MarkRenderDirty);
	return NADA;  
}

int Game2048_Start(OPTR pFromObj) {
	OPTR pDlg;

	rid_arrow_h = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_ARROW_HORZONTAL, 0);
	rid_arrow_v = Res_MakeID((char *) GAME2048_MODULENAME, RES_TYPE_BITMAP, RES_GAME2048_BMP_ARROW_VERTICAL, 0);

	pDlg = FullScreenColumnDialog(OGUI_GetMainView(), NULL, OPI_METHOD_HOOK(CloseDialog, Game2048_Close));
	if (pDlg) {
		int flags = MCALL0(pDlg, GetWidgetFlags);
		flags = flags | /*WF_DrawBorder |*/ WF_Static;
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

void Game2048_CleanUp(void) {
	Task_Exit((char *) GAME2048_TASKNAME);
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
