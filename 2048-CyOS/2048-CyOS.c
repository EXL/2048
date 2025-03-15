#include "2048.h"

#include <cybiko.h>
#include <cywin.h>

#define STR_LEN_VALUE            (5)
#define STR_LEN_SCORE            (6)
#define STR_LEN_LABEL           (10)

#define TILE_MARGIN              (3)
#define TILE_SIZE               (22)
#define X_END_FIELD             ((TILE_MARGIN * 4) + (TILE_SIZE * 4))

struct module_t g_main_module;

static bool g_quit = FALSE;
static bool g_focus = FALSE;
static bool g_reg_esc = FALSE;
static bool g_req_score = FALSE;
static bool g_req_draw = FALSE;

static void draw_tile(int value, int x, int y) {
	int x_o;
	int y_o;
	struct rect_t tile;

	x_o = (x * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN);
	y_o = (y * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN) - 2;

	tile.x = x_o + 1;
	tile.y = y_o + 1;
	tile.w = TILE_SIZE;
	tile.h = TILE_SIZE;

	DisplayGraphics_set_color(g_main_module.m_gfx, CLR_DKGRAY);
	DisplayGraphics_fill_rect_Ex(g_main_module.m_gfx, &tile);

	if (value) {
		int w;
		int x_f;
		int y_f;
		struct Font *font;
		char num[STR_LEN_VALUE]; // "2048\0"

		tile.x = x_o;
		tile.y = y_o;

		sprintf(num, "%d", value);

		DisplayGraphics_set_color(g_main_module.m_gfx, CLR_WHITE);
		DisplayGraphics_fill_rect_Ex(g_main_module.m_gfx, &tile);
		DisplayGraphics_set_color(g_main_module.m_gfx, CLR_BLACK);
		DisplayGraphics_draw_rect_Ex(g_main_module.m_gfx, &tile);
		/* EXL, 14-Mar-2025: This works buggy on small rect sizes? Also slow. */
//		draw_roundrect(g_main_module.m_gfx, &tile, RR_ROUND, NULL);

		font = (value < 100) ? cool_bold_font : (value < 1000) ? mini_bold_font : mini_normal_font;
		DisplayGraphics_set_font(g_main_module.m_gfx, font);

		x_f = (value < 1000) ? 1 : 0;
		y_f = (value < 100) ? 0 : 1;
		w = DisplayGraphics_string_width(g_main_module.m_gfx, num);
		DisplayGraphics_draw_text(
			g_main_module.m_gfx, num,
			(x_o + ((TILE_SIZE - w) / 2)) + x_f, (y_o + (TILE_SIZE / 4)) + y_f
		);
	}
}

static void draw_final(void) {
	char score[STR_LEN_SCORE]; // "99999\0"
	const char *score_label = "Score:";
	const char *reset_label_1 = "Press <DEL>";
	const char *reset_label_2 = "to Reset!";

	sprintf(score, "%d", e_score);

	DisplayGraphics_set_color(g_main_module.m_gfx, CLR_BLACK);
	DisplayGraphics_set_font(g_main_module.m_gfx, cool_bold_font);
	DisplayGraphics_draw_text(g_main_module.m_gfx, score_label, X_END_FIELD + TILE_MARGIN, 2);
	DisplayGraphics_draw_text(g_main_module.m_gfx, score, X_END_FIELD + TILE_MARGIN, 18);

	DisplayGraphics_set_color(g_main_module.m_gfx, CLR_DKGRAY);
	DisplayGraphics_set_font(g_main_module.m_gfx, mini_normal_font);
	DisplayGraphics_draw_text(g_main_module.m_gfx, reset_label_1, X_END_FIELD + TILE_MARGIN, SCREEN_HEIGHT - 24);
	DisplayGraphics_draw_text(g_main_module.m_gfx, reset_label_2, X_END_FIELD + TILE_MARGIN + 6, SCREEN_HEIGHT - 12);

	if (e_win || e_lose) {
		int o_x = (e_win) ? 0 : 1;
		const char *game_over_label = (e_win) ? "You Won!" : "You Lose!";
		DisplayGraphics_set_draw_mode(g_main_module.m_gfx, DM_XOR);
		DisplayGraphics_set_color(g_main_module.m_gfx, CLR_BLACK);
		DisplayGraphics_fill_rect(g_main_module.m_gfx, 2, 0, X_END_FIELD, SCREEN_HEIGHT - 1);

		DisplayGraphics_set_font(g_main_module.m_gfx, cool_bold_font);
		DisplayGraphics_draw_text(g_main_module.m_gfx, game_over_label, X_END_FIELD + TILE_MARGIN - o_x, 46);
	}
}

static void draw(void) {
	int x;
	int y;

	DisplayGraphics_set_draw_mode(g_main_module.m_gfx, DM_PUT);
	DisplayGraphics_fill_screen(g_main_module.m_gfx, CLR_WHITE);

	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			draw_tile(e_board[x + y * LINE_SIZE], x, y);
	draw_final();

	DisplayGraphics_show(g_main_module.m_gfx);
}

long main(int argc, char *argv[], bool start) {
	init_module(&g_main_module);

	e_init(KEY_DEL, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);

	// Hi-Sco

	// Music bkg title?

	AppGeneric_clear_screen();

	while (!g_quit) {
		struct Message *p_msg;
		struct KeyParam *p_key_param;

		p_msg = cWinApp_get_message(g_main_module.m_process, 0, 1, MSG_USER);

		g_reg_esc = g_req_score = g_req_draw = FALSE;

		switch (p_msg->msgid) {
			case MSG_SHUTUP:
			case MSG_QUIT:
				g_quit = TRUE;
				g_focus = FALSE;
				break;
			case MSG_GOTFOCUS:
				g_focus = TRUE;
				g_req_draw = TRUE;
				break;
			case MSG_LOSTFOCUS:
				g_focus = FALSE;
				// TODO: Stop music?
				break;
			case MSG_KEYDOWN:
				p_key_param = Message_get_key_param(p_msg);
				switch (p_key_param->scancode) {
					case KEY_DEL:
					case KEY_LEFT:
					case KEY_RIGHT:
					case KEY_UP:
					case KEY_DOWN:
						e_key(p_key_param->scancode);
						g_req_draw = TRUE;
						break;
					case KEY_R:
						e_key(KEY_DEL);
						g_req_draw = TRUE;
						break;
					case KEY_ESC:
						/* Drop key auto-repeat. */
						if(!(p_key_param->mask & KEYMASK_AUTOREPEAT)) {
							g_reg_esc = TRUE;
						}
						break;
					default:
						/* Process other keys like "Help", etc. */
						cWinApp_defproc(g_main_module.m_process, p_msg);
						break;
				}
				break;
			default:
				cWinApp_defproc(g_main_module.m_process, p_msg);
				break;
		}

		Message_delete(p_msg);

		if (g_reg_esc) {
			// Show menu there.
			g_quit = TRUE;
		}

		if (g_focus && g_req_draw) {
			draw();
		}

		if (g_focus && g_req_score) {
			// Score
		}
	}

	return 0L;
}
