#include <Types.h>
#include <Locator.h>
#include <Memory.h>
#include <Misctool.h>
#include <QuickDraw.h>
#include <Event.h>
#include <Window.h>
#include <Control.h>
#include <Menu.h>
#include <Lineedit.h>
#include <Dialog.h>

#include "Src.2048.h"
#include "Src.2048.c"

#include <stdio.h> /* TODO: Delete this!!! */

#define ABOUT_ITEM 257
#define NEW_ITEM 258
#define QUIT_ITEM 259
#define UNTIT_ITEM 260

#define MODE mode640
#define MaxX 640
#define dpAttr attrLocked+attrFixed+attrBank

char *menu1 = "\>L@\\XN1\r\L  A Window Program  \\N257\r\.";
char *menu2 = "\>L  File    \\N2\r\L  New \\N258V\r\L  Quit  \\N259*Qq\r\.";
char *menu3 = "\>L Windows  \\N3\r\L  Untitled  \\N260\r\.";

int myID;
Handle zp;
int ToolTable[] = {
	7,
	4, 0x0100, /* QiuckDraw */
	6, 0x0100, /* Event */
	14, 0x0100, /* Window */
	15, 0x0100, /* Control */
	16, 0x0100, /* Menu */
	20, 0x0100, /* Line Edit */
	21, 0x0100  /* Dialog */
};

StartTools() {
	TLStartUp();
	myID = MMStartUp();
	MTStartUp();
	LoadTools(ToolTable);
	ToolInit();
}

ToolInit() {
	zp = NewHandle(0x700L, myID, dpAttr, 0L);
	QDStartUp((int) *zp, MODE, 160, myID);
	EMStartUp((int) (*zp + 0x300), 20, 0, MaxX, 0, 200, myID);
	WindStartUp(myID);
	RefreshDesktop(NULL);
	CtlStartUp(myID, (int)  (*zp + 0x400));
	MenuStartUp(myID, (int) (*zp + 0x500));
	LEStartUp(myID, (int) (*zp + 0x600));
	DialogStartUp(myID);
	ShowCursor();
}

ShutDown() {
	GrafOff();
	DialogShutDown();
	LEShutDown();
	MenuShutDown();
	CtlShutDown();
	WindShutDown();
	EMShutDown();
	QDShutDown();
	MTShutDown();
	DisposeHandle(zp);
	MMShutDown(myID);
	TLShutDown();
}

BuildMenu() {
	InsertMenu(NewMenu(menu3), 0);
	InsertMenu(NewMenu(menu2), 0);
	InsertMenu(NewMenu(menu1), 0);
	FixMenuBar();
	DrawMenuBar();
}

LocInfo picOLocInfo = {
	mode640,
	NULL,
	160,
	0, 0, 200, 640
};

Rect screenRect = { 0, 0, 200, 640 };
GrafPort picOPort;

#define IMAGE_ATTR (attrLocked + attrFixed + attrNoCross + attrNoSpec + attrPage)

PicOSetup() {
	GrafPortPtr thePortPtr;
	picOLocInfo.ptrToPixImage = *(NewHandle(0x8000L, myID, IMAGE_ATTR, NULL));
	thePortPtr = GetPort();
	OpenPort(&picOPort);
	SetPort(&picOPort);
	SetPortLoc(&picOLocInfo);
	ClipRect(&screenRect);
	EraseRect(&screenRect);
	SetPort(thePortPtr);
}

#define FRAME fQContent + fMove + fZoom + fGrow + fBScroll + fRScroll + fClose + fTitle

ParamList template = {
	sizeof(ParamList),
	FRAME,
	"\p2048",
	0L,
	26, 0, 188, 616,
	NULL,
	0, 0,
	200, 640,
	200, 640,
	2, 2,
	20, 32,
	0,
	0,
	NULL,
	NULL,
	NULL,
	26, 0, 188, 616,
	(GrafPortPtr) -1L,
	NULL
};

pascal void DrawContent() {
	PPToPort(&picOLocInfo, &(picOLocInfo.boundsRect), 0, 0, modeCopy);
}

GrafPortPtr winOPtr;

MakeWindow() {
	template.wContDefProc = DrawContent;
	winOPtr = NewWindow(&template);
	PicOSetup();
}

ItemTemplate item1 = { 1, { 8, 129, 22, 179 }, buttonItem, "\pStart\r", 0, 0, NULL };
ItemTemplate item2 = { 2, { 8, 8, 22, 58 }, buttonItem, "\pQuit\r", 0, 0, NULL };
ItemTemplate item3 = { 3, { 8, 67, 22, 117 }, buttonItem, "\pHelp\r", 0, 0, NULL };

DialogTemplate dtemp = { { 84, 63, 114, 252 }, 1, 0L, &item1, &item2, &item3, NULL };

Boolean done = false;

DoDialog() {
	GrafPortPtr dlgPtr;
	Word hit;
	dlgPtr = GetNewModalDialog(&dtemp);
	while ((hit = ModalDialog(NULL)) == 3);
	done = (hit == 2);
	CloseDialog(dlgPtr);
}

main() {
	e_init(0, 1, 2, 3, 4);
	StartTools();
	BuildMenu();
	MakeWindow();
	EventLoop();
	DisposeHandle(FindHandle(picOLocInfo.ptrToPixImage));
	ShutDown();
}

WmTaskRec myEvent;

EventLoop() {
	myEvent.wmTaskMask = 0x0FFF;
	while (!done)
		switch (TaskMaster(everyEvent, &myEvent)) {
			case wInMenuBar:
				DoMenus();
				break;
			case wInGoAway:
				HideWindow(winOPtr);
				break;
			case wInContent:
				Sketch();
				break;
		}
}

DoMenus() {
	Word *data = (Word *) &myEvent.wmTaskData;
	switch (*data) {
		case ABOUT_ITEM:
			DoDialog();
			e_key(0);
			break;
		case QUIT_ITEM:
			done = true;
			break;
		case NEW_ITEM:
			ErasePicO();
			HideWindow(winOPtr);
			CloseWindow(winOPtr);
			winOPtr = NewWindow(&template);
		case UNTIT_ITEM:
			SelectWindow(winOPtr);
			ShowWindow(winOPtr);
			break;
	}
	HiliteMenu(false, *(data + 1));
}

ErasePicO() {
	GrafPortPtr oldPortPtr;
	oldPortPtr = GetPort();
	SetPort(&picOPort);
	ClipRect(&screenRect);
	EraseRect(&screenRect);
	SetPort(oldPortPtr);
}

Sketch() {
	int i;
	Point mouseLoc;
	GrafPortPtr thePortPtr = (GrafPortPtr) myEvent.wmTaskData;
	Rect theRect;

        	mouseLoc = myEvent.wmWhere;

	StartDrawing(thePortPtr);
	GetPortRect(&theRect);
	GlobalToLocal(&mouseLoc);

	MoveTo(mouseLoc);
	SetPort(&picOPort);
	ClipRect(&theRect);
	MoveTo(mouseLoc);
	SetPort(thePortPtr);

	for (i = 0; i < BOARD_SIZE; ++i)
		printf("%d ", e_board[i]);
	printf("\n");

	while (StillDown(0)) {
		GetMouse(&mouseLoc);

		LineTo(mouseLoc);
		SetPort(&picOPort);
		LineTo(mouseLoc);
		SetPort(thePortPtr);
	}
	SetOrigin(0, 0);
}
