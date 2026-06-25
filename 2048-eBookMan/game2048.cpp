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
#define GAMEMENU_RESET                 (112)
#define GAMEMENU_SAVE                  (113)
#define GAMEMENU_LOAD                  (114)
#define GAMEMENU_ORIENTATION           (115)
#define GAMEMENU_JINGLES               (116)
#define GAMEMENU_EXIT                  (117)
#define HELPMENU_BUTTON_ID             (120)
#define HELPMENU_WINDOW_ID             (121)
#define HELPMENU_RULES                 (122)
#define HELPMENU_ABOUT                 (123)
#define GAME_OVER                      (0)
#define GAME_DONE                      (1)

/******************* GLOBALS *************************************************/
#define STR_LEN_VALUE                  (5)
#define STR_LEN_SCORE                  (32)
#define STR_LEN_TEXT_BUFFER            (1024)

#define STR_ABOUT_1                    "The 2048 puzzle game implementation specially for eBookMan gadgets."
#define STR_ABOUT_2                    "© EXL (exl@bk.ru)"
#define STR_ABOUT_3                    "https://github.com/EXL/2048"
#define STR_ABOUT_4                    "Version: 1.0, 25-Jun-2026"

#define STR_HELP_1                     "In 2048, your goal is to slide and combine numbered tiles on a 4x4 "\
	"grid to create a tile with the value of 2048. You win by reaching 2048, and lose if the board fills up "\
	"with no available moves."
#define STR_HELP_2                     "The game is played on a 4x4 grid. At the start, two tiles randomly "\
	"appear on the grid with a value of either 2 or 4."
#define STR_HELP_3                     "You can swipe or use arrow keys to move all the tiles in one of "\
	"four directions: up, down, left, or right. All tiles slide as far as they can in that direction until "\
	"they hit the edge of the board or another tile."
#define STR_HELP_4                     "After every move, a new tile with the value of 2 (90% chance) or 4 "\
	"(10% chance) automatically spawns in an empty spot."

#define OFFSET_COORD(coord)            (coord * (Coords.tile_margin + Coords.tile_size))

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
	int win_w;
	int win_h;
	int tile_size;
	int tile_margin;
} Coordinates;

class CGameWindow : public CWindow {
	CLabel *ScoreLabel;
	Coordinates Coords;
	BOOL JinglePlayed;

 public:
	CGameWindow(U16 id, const char *title) : CWindow(id, 0, 0, 0, 0, 0, TRUE, FALSE) {
		EnableOSNotify();
		
		SetupWindow(title);
		
		ScoreLabel = new CLabel(LABEL_SCORE_ID, "Score: 00000", GUI_GetFont(9, CTRL_BOLD));
		AddChild(ScoreLabel, Coords.x_score, 2);

		JinglePlayed = FALSE;
	}
	
	void ShowScoreLabel(BOOL show) {
		if (show) {
			ScoreLabel->Show();
		} else {
			ScoreLabel->Hide();
		}
	}

	void SetupWindow(const char *title) {
		SetupCoords(&Coords, GUI_GetOrientation());
		SetWidth(Coords.win_w);
		SetHeight(Coords.win_h);
		SetTitle(title);
	}
	
	void SetupCoords(Coordinates *c, BOOL screen_orientation) {
		if (screen_orientation == LCD_PORTRAIT) {
			c->x_score = 120;
			c->win_w = 200;
			c->win_h = 240;
			c->tile_size = 42;
			c->tile_margin = 5;
		} else {
			c->x_score = 120;
			c->win_w = 240;
			c->win_h = 200;
			c->tile_size = 38;
			c->tile_margin = 4;
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
						e_key((GUI_GetOrientation() == LCD_PORTRAIT) ? K_LEFT : K_UP); Draw();
						break;
					case K_RIGHT:
						e_key((GUI_GetOrientation() == LCD_PORTRAIT) ? K_RIGHT : K_DOWN); Draw();
						break;
					case K_UP:
					case K_PAGE_UP:
					case K_TOP:
					case K_JOG_UP:
						e_key((GUI_GetOrientation() == LCD_PORTRAIT) ? K_UP : K_RIGHT); Draw();
						break;
					case K_DOWN:
					case K_PAGE_DOWN:
					case K_BOTTOM:
					case K_JOG_DOWN:
						e_key((GUI_GetOrientation() == LCD_PORTRAIT) ? K_DOWN : K_LEFT); Draw();
						break;
					case K_BACKSPACE:
						e_key(K_BACKSPACE); SetJinglePlayed(FALSE); Draw();
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
		const int center = (Coords.tile_size * 4 + Coords.tile_margin * 3) / 2;
		int lX = GetWidth() / 2 - center + OFFSET_COORD(x) - (Coords.tile_margin / 2) - 1;
		int lY = GetHeight() / 2 - center + OFFSET_COORD(y) - (Coords.tile_margin * 2) - 3;
		
		DrawRectFilled(lX + 1, lY + 1, Coords.tile_size, Coords.tile_size, COLOR_GRAY53);
		
		if (value) {
			char num[STR_LEN_VALUE];
			
			sprintf(num, "%d", value);
			
			DrawRectFilled(lX, lY, Coords.tile_size, Coords.tile_size, COLOR_WHITE);
			DrawRect(lX, lY, Coords.tile_size, Coords.tile_size, COLOR_BLACK);
			
			const int font_size = FixUpTextCoords(&lX, &lY, value);
			DrawText(num, lX, lY, GUI_GetFont(font_size, CTRL_BOLD));
		}
	}

	int FixUpTextCoords(int *x, int *y, int value) {
		if (value >= 2 && value <= 8) {
			*x = *x + (Coords.tile_size / 3) + 1;
			*y = *y + (Coords.tile_size / 3) - 1;
			return 16;
		} else if (value >= 16 && value <= 64) {
			*x = *x + (Coords.tile_size / 3) - 4;
			*y = *y + (Coords.tile_size / 3) - 1;
			return 16;
		} else if (value >= 128 && value <= 512) {
			*x = *x + (Coords.tile_size / 3) - 6;
			*y = *y + (Coords.tile_size / 3) + 2;
			return 12;
		}
		*x = *x + (Coords.tile_size / 3) - 6;
		*y = *y + (Coords.tile_size / 3) + 2;
		return 9;
	}

	void GameDrawFinal() {
		char score[STR_LEN_SCORE];
		if (GUI_GetOrientation() == LCD_PORTRAIT) {
			sprintf(score, "Score: %05d", e_score);
			ScoreLabel->SetLabel(score);
		} else {
			sprintf(score, "2048-eBookMan | Score: %05d", e_score);
			SetTitle(score);
		}

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

			if (!JinglePlayed) {
				if (SoundOn) {
					piezo_play_jingle(Jingles[(e_win) ? GAME_DONE : GAME_OVER], 0);
				}
				JinglePlayed = TRUE;
			}
		}
	}

	void SetJinglePlayed(BOOL val) {
		JinglePlayed = val;
	}
};

void Init_Menu(void) {
	GameMenu = new CMenu(GAMEMENU_WINDOW_ID);
	if (SoundOn) { 
		GameMenu->SetNumRows(9);
		GameMenu->SetRow(0, GAMEMENU_RESET, "Reset", 'r');
		GameMenu->SetSeparatorRow(1);
		GameMenu->SetRow(2, GAMEMENU_SAVE, "Save...");
		GameMenu->SetRow(3, GAMEMENU_LOAD, "Load...");
		GameMenu->SetSeparatorRow(4);
		GameMenu->SetRow(5, GAMEMENU_ORIENTATION, 
			(GUI_GetOrientation() == LCD_PORTRAIT) ? "Landscape Mode" : "Portrait mode");
		GameMenu->SetRow(6, GAMEMENU_JINGLES, (SoundOn) ? "Jingles off" : "Jingles on");
		GameMenu->SetSeparatorRow(7);
		GameMenu->SetRow(8, GAMEMENU_EXIT, PKG_String(GUI_pkg, GUI_MENU_EXIT), ' ');
	}
	else {
		GameMenu->SetNumRows(8);
		GameMenu->SetRow(0, GAMEMENU_RESET, "Reset", 'r');
		GameMenu->SetSeparatorRow(1);
		GameMenu->SetRow(2, GAMEMENU_SAVE, "Save...");
		GameMenu->SetRow(3, GAMEMENU_LOAD, "Load...");
		GameMenu->SetSeparatorRow(4);
		GameMenu->SetRow(5, GAMEMENU_ORIENTATION, 
			(GUI_GetOrientation() == LCD_PORTRAIT) ? "Landscape Mode" : "Portrait mode");
		GameMenu->SetSeparatorRow(6);
		GameMenu->SetRow(7, GAMEMENU_EXIT, PKG_String(GUI_pkg, GUI_MENU_EXIT), ' ');
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
				case GAMEMENU_RESET:
					e_key(K_BACKSPACE);
					GameWindow->SetJinglePlayed(FALSE);
					GameWindow->Draw();
					break;
				case GAMEMENU_SAVE:
					GUI_TextWindow(0, "Save 2048 State", "Not yet implemented");
					break;
				case GAMEMENU_LOAD:
					GUI_TextWindow(0, "Load 2048 State", "Not yet implemented");
					break;
				case GAMEMENU_ORIENTATION:
					GUI_SetOrientation(!GUI_GetOrientation());
					GameWindow->SetupWindow("2048-eBookMan");
					GameWindow->Draw();
					GameWindow->ShowScoreLabel(GUI_GetOrientation() == LCD_PORTRAIT);
					GameMenu->SetRow(5, GAMEMENU_ORIENTATION, 
						(GUI_GetOrientation() == LCD_PORTRAIT) ? "Landscape Mode" : "Portrait mode");
					break;
				case GAMEMENU_JINGLES:
					SoundOn = !SoundOn;
					GameMenu->SetRow(6, GAMEMENU_JINGLES, (SoundOn) ? "Jingles Off" : "Jingles On");
					break;
				case GAMEMENU_EXIT:
					GUI_Exit();
					break;
				case HELPMENU_RULES:
					char help_str[STR_LEN_TEXT_BUFFER];
					sprintf(help_str, "%s\n\n%s\n\n%s\n\n%s", STR_HELP_1, STR_HELP_2, STR_HELP_3, STR_HELP_4);
					GUI_TextWindow(0, "Rules of 2048 Game", help_str);
					break;
				case HELPMENU_ABOUT:
					char about_str[STR_LEN_TEXT_BUFFER];
					sprintf(about_str, "%s\n\n%s\n%s\n\n%s", 
						STR_ABOUT_1, STR_ABOUT_2, STR_ABOUT_3, STR_ABOUT_4);
					GUI_TextWindow(0, "About 2048-eBookMan", about_str);
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
