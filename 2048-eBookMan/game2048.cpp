#include <assert.h>
#include <stdlib.h>      // standard libraries include files 
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "sys.h"         // eBookMan include files
#include "gui.h"
#include "gui_pkg.h"

extern "C" {
#include "evnt_fun.h"
#include "lcd.h"
#include "timer.h"
#include "ereader_hostio.h"
#include "piezo.h"
}

#include "2048.h"

/******************* IDS *****************************************************/
#define GAME_WINDOW_ID                 (10)
#define LABEL_SCORE_ID                 (11)
#define MENUBAR_WINDOW_ID              (100)
#define GAMEMENU_BUTTON_ID             (110)
#define GAMEMENU_WINDOW_ID             (111)
#define GAMEMENU_JINGLES               (112)
#define GAMEMENU_SAVE                  (113)
#define GAMEMENU_LOAD                  (114)
#define GAMEMENU_RESET                 (115)
#define GAMEMENU_EXIT                  (116)
#define HELPMENU_BUTTON_ID             (120)
#define HELPMENU_WINDOW_ID             (121)
#define HELPMENU_RULES                 (122)
#define HELPMENU_ABOUT                 (123)
#define GAME_OVER                      (0)
#define GAME_DONE                      (1)

/******************* GLOBALS *************************************************/
class CGameWindow;

BOOL SoundOn = TRUE;
int Jingles[] = {-1, -1};
// standard jingles to play upon one of the above action occurrences
const char JINGLE_GAME_OVER[] = "C minor fall";
const char JINGLE_GAME_DONE[] = "Soir";

CMenuBar MainMenuBar(MENUBAR_WINDOW_ID, 23);
CMenu *GameMenu;
CMenu *HelpMenu;
CGameWindow *GameWindow;

class CGameWindow : public CWindow {
	CLabel *ScoreLabel;

 public:
	CGameWindow(U16 id, const char *title) : CWindow(id, 0, 0, 200, 240, 0, TRUE, FALSE) {
		EnableOSNotify();

		SetTitle(title);
		
		ScoreLabel = new CLabel(LABEL_SCORE_ID, "Score: 99999", GUI_GetFont(9, CTRL_BOLD));
		AddChild(ScoreLabel, 4, 2);
	}

	S32 MsgHandler(MSG_TYPE type, CViewable *object, S32 data) {
		return CWindow::MsgHandler(type, object, data);
	}
	
	void Draw() {
		DrawBackground();
		DrawTitle();
		DrawChildren();
	}
};

void Init_Menu(void) {
	GameMenu = new CMenu(GAMEMENU_WINDOW_ID);
	if (SoundOn) { 
		GameMenu->SetNumRows(8);
		GameMenu->SetRow(0, GAMEMENU_RESET, "Reset", 'r');
		GameMenu->SetSeparatorRow(1);
		GameMenu->SetRow(2, GAMEMENU_SAVE, "Save...");
		GameMenu->SetRow(3, GAMEMENU_LOAD, "Load...");
		GameMenu->SetSeparatorRow(4);
		GameMenu->SetRow(5, GAMEMENU_JINGLES, PKG_String(GUI_pkg, GUI_MENU_TOGGLE_SOUNDS), ' ');
		GameMenu->SetSeparatorRow(6);
		GameMenu->SetRow(7, GAMEMENU_EXIT, PKG_String(GUI_pkg, GUI_MENU_EXIT), ' ');
	}
	else {
		GameMenu->SetNumRows(6);
		GameMenu->SetRow(0, GAMEMENU_RESET, "Reset", 'r');
		GameMenu->SetSeparatorRow(1);
		GameMenu->SetRow(2, GAMEMENU_SAVE, "Save...");
		GameMenu->SetRow(3, GAMEMENU_LOAD, "Load...");
		GameMenu->SetSeparatorRow(4);
		GameMenu->SetRow(5, GAMEMENU_EXIT, PKG_String(GUI_pkg, GUI_MENU_EXIT), ' ');
	}
	MainMenuBar.AddButton(
		new CPushButton(
			GAMEMENU_BUTTON_ID, 0, 0, 
			PKG_String(GUI_pkg, GUI_LABEL_Game)
		), GameMenu
	);

	HelpMenu = new CMenu(HELPMENU_WINDOW_ID);
	HelpMenu->SetNumRows(2);
	HelpMenu->SetRow(0, HELPMENU_RULES, "Rules...");
	HelpMenu->SetRow(1, HELPMENU_ABOUT, PKG_String(GUI_pkg, GUI_MENU_ABOUT), ' ');
	MainMenuBar.AddButton(
		new CPushButton(
			HELPMENU_BUTTON_ID, 0, 0,
			PKG_String(GUI_pkg, GUI_LABEL_Help)
		), HelpMenu
	);
}

void Init_Jingles(void) {
	int i;
	size_t n;
	char name[100];
	int NumJingles = piezo_njingles(&n);

	for (i = 0; i < NumJingles; i++) {
		if (piezo_name_jingle(i, name, sizeof(name)) != -1) {
			if (strstr(name, JINGLE_GAME_DONE) != NULL) {
				Jingles[GAME_DONE] = i;
			} else if (strstr(name, JINGLE_GAME_OVER) != NULL) {
				Jingles[GAME_OVER] = i;
			}
		}
	}
	if (Jingles[GAME_OVER] == -1 || Jingles[GAME_DONE] == -1) {
		SoundOn = FALSE;
	}
}

S32 GUI_main(MSG_TYPE type, CViewable *object, S32 data) {
	switch (type) {
		case MSG_APP_START:
			if (OS_is_present && hostIO_am_I_the_current_task()) {
				HOSTIO_INLINE_BREAKPOINT();
			}
			
			e_init(1, 2, 3, 4, 5);
			
			Init_Jingles();
			Init_Menu(); // must init menu after jingles
			
			GameWindow = new CGameWindow(GAME_WINDOW_ID, "2048-eBookMan");
			return 1;
		case MSG_KEY:
			if (data == K_MENU) {
				MainMenuBar.Show();
			}
			return 1;
		case MSG_MENU_SELECT:
			switch ((U16) data) {
				case GAMEMENU_JINGLES:
					SoundOn = !SoundOn;
					break;
				case GAMEMENU_SAVE:
					break;
				case GAMEMENU_LOAD:
					break;
				case GAMEMENU_RESET:
					break;
				case GAMEMENU_EXIT:
					GUI_Exit();
					break;
				case HELPMENU_RULES:
					GUI_TextWindow(0, PKG_String(GUI_pkg,GUI_HELP_TITLE), PKG_String(GUI_pkg, GUI_STALAGMITE_HELP));
					break;
				case HELPMENU_ABOUT:
					char buf[256];
					sprintf(buf, PKG_String(GUI_pkg, GUI_STALAGMITE_ABOUT), "1.1", "2001");
					GUI_TextWindow(0, PKG_String(GUI_pkg, GUI_ABOUT_TITLE), buf);
					break;
				default:
					break;
			}
			
			GameWindow->Show();
			
			return 1;

		default:
			return 0;
	}
}
