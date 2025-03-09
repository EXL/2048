/////////////////////////////////////////////////////////////
//
//  $Archive:: /Iris/modules/helloworld/helloworld.c       $
// $Revision:: 13                                          $
//   $Author:: Olam                                        $
//     $Date:: 2/17/00 12:07p                              $
// Revision history
//
//
// Copyright (C) C Technologies AB, 1999 All rights reserved
//
// Description: Simple "HelloWorld" application
//

#include <debug.h>

#include <mem/malloc.h>

#include <system/application.h>
#include <system/stdresourcetypes.h>

#include <ogui/dialog.h>
#include <ogui/container.h>
#include <ogui/resourcetextfield.h>
#include <ogui/button.h>
#include <ogui/ogui.h>

#include "res/2048-ARIPOS_resources.h"

static const char *GAME2048_TASKNAME   = "2048-ARIPOS";
static const char *GAME2048_MODULENAME = "2048-ARIPOS";

int Game2048_Installer(void) {
	Dbg_printf("Game2048:Installer\n");
	return Application_Install(
		(char *) GAME2048_TASKNAME,
		(char *) GAME2048_MODULENAME,
		"Game2048_evthandler"
	);
}

int Game2048_Uninstaller(void) {
	Dbg_printf("Game2048:Uninstaller\n");
	return Application_Uninstall(
		(char *) GAME2048_TASKNAME
	);
}

void Game2048_Stop(void) {
	// Stop any tasks that have been started by the '2048-ARIPOS'-
	// applicaion.
	Task_StopChildren((char *) GAME2048_TASKNAME);
}

void Game2048_Suspend(void) {
	Task_SuspendChildren((char *) GAME2048_TASKNAME);
}

void Game2048_Unsuspend(void) {
	Game2048_Start(NULL);
}

// The Game2048_Close function is called when the main dialog is
// closed. (For instance, when the user presses the "Done" button.)
int Game2048_Close(OPTR pDialog, int BtnNbr) {
	// Dispose the main dialog object and stop the application
	OPI_DisposeObject(pDialog);
	Game2048_Stop();
	return NADA;
}

// The Game2048_Start function creates a fullscreen dialog,
// containing a ResourceTextField displaying the "2048-ARIPOS"
// resource string in the current language, along with a "Done" button.
int Game2048_Start(OPTR pFromObj) {
	OPTR pDlg, pTxt, pDoneBtn;
	ResID strrid;
	
	// Create the main dialog. We'll use a method hook to call a 
	// function when someone tries to close the dialog.
	pDlg = FullScreenColumnDialog(OGUI_GetMainView(), NULL, OPI_METHOD_HOOK(CloseDialog, Game2048_Close));
	if (pDlg) {
		// Create the resource ID to the "Hello World" text resource
		// in the current language
		strrid = Res_MakeID((char *)GAME2048_MODULENAME, RES_TYPE_STRING, RES_HELLOWORLD_STR_HELLO_WORLD, 0);
		
		// Create a resourcetextfield displaying the string that is
		// identified by strrid
		pTxt = ResourceTextField(pDlg, strrid, NULL);

		// Create a Done button. By not using any specific
		// ButtonPush hook, we'll get default behaviour.  
		// (i.e. the CloseDialog hook named Game2048_Close
		// will be called)
		pDoneBtn = DoneButton(pDlg, OPI_NullHook());
		
		// If created successfully, set focus to the Done button
		if (pDoneBtn) {
			MCALL0(pDoneBtn, Mark);
		}
	}
	return NADA;
}

void Game2048_CleanUp(void) {
	Task_Exit((char *) GAME2048_TASKNAME);
}

// The eventhandler is the interface between the System module
// and our "Game2048" task. The System module will send
// messages to this eventhandler as the user tries to start or
// stop this task.
void Game2048_evthandler(int a, void *ptr, void *userdata) {
	switch (a) {
		case TASKEVT_START:
			Dbg_printf("Game2048:Got TASKEVT_START\n");
			Game2048_Start(NULL);
			break;
		case TASKEVT_STOP:
			Dbg_printf("Game2048:Got TASKEVT_STOP\n");
			Game2048_Stop();
			break;
		case TASKEVT_SUSPEND:
			Dbg_printf("Game2048:Got TASKEVT_SUSPENED\n");
			Game2048_Suspend();
			break;
		case TASKEVT_UNSUSPEND:
			Dbg_printf("Game2048:Got TASKEVT_UNSUSPENED\n");
			Game2048_Unsuspend();
			break;
		case TASKEVT_CHLD:
			Dbg_printf("Game2048:Got TASKEVT_CHLD\n");
			// Do nothing, wait for all childs to exit
			break;
		case TASKEVT_NOCHLD:
			Dbg_printf("Game2048:Got TASKEVT_NOCHLD\n");
			// Cleanup and exit
			Game2048_CleanUp();
			break;
		default:
			Dbg_printf("Game2048:Got unknown:%d\n",a);
	}
}
