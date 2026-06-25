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
#define TILE_SIZE                      (42)
#define TILE_MARGIN                    (5)
#define OFFSET_COORD(coord)            (coord * (TILE_MARGIN + TILE_SIZE))

#define STR_LEN_VALUE                  (5)
#define STR_LEN_SCORE                  (16)

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

typedef struct tagCoordinates {
	int x_score;
} Coordinates;

class CGameWindow : public CWindow {
	CLabel *ScoreLabel;
	Coordinates Coords;

 public:
	CGameWindow(U16 id, const char *title) : CWindow(id, 0, 0, 200, 240, 0, TRUE, FALSE) {
		EnableOSNotify();
		
		SetupCoords(&Coords, FALSE);

		SetTitle(title);
		
		ScoreLabel = new CLabel(LABEL_SCORE_ID, "Score: 00000", GUI_GetFont(9, CTRL_BOLD));
		AddChild(ScoreLabel, Coords.x_score, 2);
	}
	
	void SetupCoords(Coordinates *c, BOOL landscape) {
		if (landscape) {
			c->x_score = 120;
		} else {
			c->x_score = 120;
		}
	}

	S32 MsgHandler(MSG_TYPE type, CViewable *object, S32 data) {
		switch (type) {
			case MSG_OS_NOTIFY:
				switch ((U16) data) {
					case NTFY_FOREGROUND:
					case NTFY_POWER_ON:
						MainMenuBar.Hide();
						GameWindow->Show();
						GUI_UpdateNow();
						return 1;
					case NTFY_BACKGROUND:
						Hide();
						return 1;
					default:
						break; 
				}
				break;
			case MSG_PEN_DOWN:
				HandleTouchEvent(data);
				break;
			case MSG_KEY:
				switch ((U16) data) {
					case K_LEFT:
						e_key(K_LEFT); Draw();
						break;
					case K_RIGHT:
						e_key(K_RIGHT); Draw();
						break;
					case K_UP:
					case K_PAGE_UP:
					case K_TOP:
					case K_JOG_UP:
						e_key(K_UP); Draw();
						break;
					case K_DOWN:
					case K_PAGE_DOWN:
					case K_BOTTOM:
					case K_JOG_DOWN:
						e_key(K_DOWN); Draw();
						break;
					case K_BACKSPACE:
						e_key(K_BACKSPACE); Draw();
						break;
					default:
						break; 
				}
				break;
			default:
				break;
		}
		return CWindow::MsgHandler(type, object, data);
	}
	
	void HandleTouchEvent(S32 data) {
		const U16 x = data >> 16;
		const U16 y = data & 0xFFFF;
		const U16 w4 = GetWidth() / 4;
		const U16 h4 = GetHeight() / 4;
		
		RECT u;
		u.x = w4;
		u.y = 0;
		u.width = w4 + w4 * 2;
		u.height = 0 + h4;
		
		RECT d;
		d.x = w4;
		d.y = h4 * 3;
		d.width = w4 + w4 * 2;
		d.height = h4 * 3 + h4;
		
		RECT l;
		l.x = 0;
		l.y = h4;
		l.width = 0 + w4;
		l.height = h4 + h4 * 2;
		
		RECT r;
		r.x = w4 * 3;
		r.y = h4;
		r.width = w4 * 3 + w4;
		r.height = h4 + h4 * 2;

		if (RectContainsPoint(&u, x, y)) {
			e_key(K_UP); Draw();
		} else if (RectContainsPoint(&d, x, y)) {
			e_key(K_DOWN); Draw();
		} else if (RectContainsPoint(&l, x, y)) {
			e_key(K_LEFT); Draw();
		} else if (RectContainsPoint(&r, x, y)) {
			e_key(K_RIGHT); Draw();
		}
	}
	
	inline BOOL RectContainsPoint(const RECT *rect, U16 x, U16 y) {
		return (x >= rect->x && x < rect->width && y >= rect->y && y < rect->height);
	}
	
	void Draw() {
		CWindow::Draw();
		GameDraw();
	}
	
	void GameDraw() {
		// DrawBackground
		for (int y = 0; y < LINE_SIZE; ++y) {
			for (int x = 0; x < LINE_SIZE; ++x) {
				GameDrawTile(e_board[x + y * LINE_SIZE], x, y);
			}
		}
		GameDrawFinal();
	}
	
	void GameDrawTile(int value, int x, int y) {
		const int center = (TILE_SIZE * 4 + TILE_MARGIN * 3) / 2;
		int lX = GetWidth() / 2 - center + OFFSET_COORD(x) - (TILE_MARGIN / 2) - 1;
		int lY = GetHeight() / 2 - center + OFFSET_COORD(y) - (TILE_MARGIN * 2) - 3;
		
		DrawRectFilled(lX + 1, lY + 1, TILE_SIZE, TILE_SIZE, COLOR_GRAY53);
		
		if (value) {
			char num[STR_LEN_VALUE];
			
			sprintf(num, "%d", value);
			
			DrawRectFilled(lX, lY, TILE_SIZE, TILE_SIZE, COLOR_WHITE);
			DrawRect(lX, lY, TILE_SIZE, TILE_SIZE, COLOR_BLACK);
			
			const int font_size = FixUpTextCoords(&lX, &lY, value);
			DrawText(num, lX, lY, GUI_GetFont(font_size, CTRL_BOLD));
		}
	}

	int FixUpTextCoords(int *x, int *y, int value) {
		if (value >= 2 && value <= 8) {
			*x = *x + (TILE_SIZE / 3) + 1;
			*y = *y + (TILE_SIZE / 3) - 1;
			return 16;
		} else if (value >= 16 && value <= 64) {
			*x = *x + (TILE_SIZE / 3) - 4;
			*y = *y + (TILE_SIZE / 3) - 1;
			return 16;
		} else if (value >= 128 && value <= 512) {
			*x = *x + (TILE_SIZE / 3) - 6;
			*y = *y + (TILE_SIZE / 3) + 2;
			return 12;
		}
		*x = *x + (TILE_SIZE / 3) - 6;
		*y = *y + (TILE_SIZE / 3) + 2;
		return 9;
	}

	void GameDrawFinal() {
		char score[STR_LEN_SCORE];
		sprintf(score, "Score: %05d", e_score);
		ScoreLabel->SetLabel(score);

		if (e_win || e_lose) {
			const int w = 140;
			const int h = 60;
			int x = (GetWidth() / 2) -  w / 2;
			int y = (GetHeight() / 2) -  h / 2;
			x -= 2;
			y -= 10;

			InvertRect(0, 0, GetWidth(), GetHeight());

			DrawRectFilled(x + 1, y + 1, w, h, COLOR_GRAY53);
			DrawRectFilled(x, y, w, h, COLOR_WHITE);
			DrawRect(x, y, w, h, COLOR_BLACK);

			const char *label = (e_win) ? "You Won!" : "Game Over!";
			x += (e_win) ? 18 : 6;
			y += 22;
			DrawText(label, x, y, GUI_GetFont(16, CTRL_BOLD));
		}
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
	HelpMenu->SetRow(1, HELPMENU_ABOUT, "About...");
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
			
			e_init(K_BACKSPACE, K_LEFT, K_RIGHT, K_UP, K_DOWN);
			
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
					e_key(K_BACKSPACE);
					GameWindow->Draw();
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
