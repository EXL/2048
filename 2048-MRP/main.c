#include "header/bridge.h"
#include "2048.h"
#include <string.h>

int32 mrc_init(void);
int32 mrc_pause(void);
int32 mrc_resume(void);
int32 mrc_exitApp(void);
int32 mrc_event(int32 code, int32 p0, int32 p1);

#define VALUE_MAX_SIZE 5 // "2048\0"
#define SCORE_MAX_SIZE 16 // "Score: 999999..."

#define FIELD_MARGIN (screen_width/20)
#define FIELD_SIZE (screen_width - FIELD_MARGIN*2)
#define TILE_MARGIN (screen_width/80)
#define TILE_SIZE (FIELD_SIZE/LINE_SIZE - TILE_MARGIN*2)

#define ABS(n) (((n) < 0) ? (-(n)) : (n))

#define GET_R(color) ((color & 0xFF0000) >> 16)
#define GET_G(color) ((color & 0xFF00) >> 8)
#define GET_B(color) (color & 0xFF)
#define GET_COMPONENTS(color) GET_R(color), GET_G(color), GET_B(color)

uint16 screen_width, screen_height;
int mouse_begin_x, mouse_begin_y;
inFuncs_st *inf;
mr_table_st *mrt;

long time(void *unused) {
    return (long) mrt->mr_getTime();
}

void error(char *str) {
    inf->mrc_clearScreen(0, 0, 0);
    inf->mrc_drawText(str, 0, 0, 255, 0, 0, 0, 1);
    inf->mrc_refreshScreen(0, 0, screen_width, screen_height);
    while (1);
}

outFuncs_st *_start(inFuncs_st *in) {
    outFuncs_st *ret = in->mrc_malloc(sizeof(outFuncs_st));
    ret->mrc_init = mrc_init;
    ret->mrc_event = mrc_event;
    ret->mrc_exitApp = mrc_exitApp;
    ret->mrc_pause = mrc_pause;
    ret->mrc_resume = mrc_resume;

	screen_width = (uint16)(*in->mr_table->mr_screen_w);
	screen_height = (uint16)(*in->mr_table->mr_screen_h);

    inf = in;
    mrt = in->mr_table;
    return ret;
}

int string_width(char *str) {
	// MRP doesn't have a way to get the actual on-screen width of string,
	// but here's a (hopefully) reasonable enough approximation.
	// On the vmrp emulator, each character is 8 px wide
	// On the myPhone 8870, it's not a monospace font but it seems to be close to 7px per char on average
	// So approximate at 7.5 px width per character
	return strlen(str)*15/2;
}

int string_height() {
	// No way to get the actual font height, but again, close enough approximation
	return 17;
}

void draw_tile(int value, int x, int y) {
	const int bg = e_background(value);
	const int fg = e_foreground(value);
	int color = (e_win || e_lose) ? bg - COLOR_FADE : bg;
    mrt->DrawRect(x, y, TILE_SIZE, TILE_SIZE, GET_COMPONENTS(color));  // TODO: round rectangle like on MRE version

	if (!value) return;

	char num_str[VALUE_MAX_SIZE];
	mrt->sprintf(num_str, "%d", value);

	const int text_x = x + TILE_SIZE/2 - string_width(num_str)/2;
	const int text_y = y + TILE_SIZE/2 - string_height()/2;

	color = (e_win || e_lose) ? fg - COLOR_FADE : fg;
    inf->mrc_drawText(num_str, text_x, text_y, GET_COMPONENTS(color), 0, 1);
}

void draw_final() {
	int text_x, text_y;

	if (e_win || e_lose) {
        char* text = e_win ? "You won!" : "Game over!";
		text_x = screen_width/2 - string_width(text)/2;
		text_y = screen_height/2 - string_height()/2;

        inf->mrc_drawText(text, text_x, text_y, GET_COMPONENTS(COLOR_FINAL), 0, 1);
	}

	text_y = screen_height - string_height() - 4;
	int color = (e_win || e_lose) ? COLOR_TEXT - COLOR_FADE : COLOR_TEXT;
    inf->mrc_drawText("Restart", 4, text_y, GET_COMPONENTS(color), 0, 1);

	text_x = screen_width - string_width("Exit") - 4;
    inf->mrc_drawText("Exit", text_x, text_y, GET_COMPONENTS(color), 0, 1);

	char score_str[SCORE_MAX_SIZE];
	mrt->sprintf(score_str, "Score: %d", e_score);

	text_x = screen_width/2 - string_width(score_str)/2;
    inf->mrc_drawText(score_str, text_x, 4, GET_COMPONENTS(color), 0, 1);
}

void draw() {
	int color = (e_win || e_lose) ? COLOR_BOARD - COLOR_FADE : COLOR_BOARD;
    inf->mrc_clearScreen(GET_COMPONENTS(color));

	for (int y = 0; y < LINE_SIZE; y++) {
		for (int x = 0; x < LINE_SIZE; x++) {
			draw_tile(
				e_board[x + y * LINE_SIZE],
				FIELD_MARGIN + TILE_MARGIN/2 + x*(TILE_SIZE + TILE_MARGIN*2),
				screen_height/2 - FIELD_SIZE/2 + y*(TILE_SIZE + TILE_MARGIN*2)
			);
		}
	}
	draw_final();
    inf->mrc_refreshScreen(0, 0, screen_width, screen_height);
}

void load_game() {
	// TODO
	// int32 file = mrt->mr_open("2048/2048.sav", 1);
	// mrt->mr_read(file, &e_win, sizeof(int32));
	// mrt->mr_read(file, &e_lose, sizeof(int32));
	// mrt->mr_read(file, &e_score, sizeof(int32));
	// mrt->mr_read(file, &e_board, sizeof(int32)*BOARD_SIZE);
	// mrt->mr_close(file);
}

void save_game() {
	// TODO: does not work
	// int32 file = mrt->mr_open("2048/2048.sav", 1);
	// mrt->mr_write(file, &e_win, sizeof(int32));
	// mrt->mr_write(file, &e_lose, sizeof(int32));
	// mrt->mr_write(file, &e_score, sizeof(int32));
	// mrt->mr_write(file, &e_board, sizeof(int32)*BOARD_SIZE);
	// mrt->mr_close(file);
}

int32 mrc_init(void) {
	mrt->mr_mkDir("2048");

	e_init(MR_KEY_SOFTLEFT, MR_KEY_LEFT, MR_KEY_RIGHT, MR_KEY_UP, MR_KEY_DOWN);
	load_game();
    draw();
    
    int32 timer = inf->mrc_timerCreate();
    inf->mrc_timerStart(timer, 50, 0, draw, 1);
}

int32 mrc_pause(void) {
    return 0;
}

int32 mrc_resume(void) {
    draw();
}

int32 mrc_exitApp(void) {
    return 0;
}

int32 mrc_event(int32 code, int32 p0, int32 p1) {
    switch (code) {
        case MR_MOUSE_DOWN: {
			mouse_begin_x = p0;
			mouse_begin_y = p1;
            break;
        }
        case MR_MOUSE_UP: {
			int right = p0 - mouse_begin_x;
			int down = p1 - mouse_begin_y;
			int left = -right;
			int up = -down;

			int total_offset = ABS(right) + ABS(down);

			if (total_offset < screen_width/16) {
				// Not swiped long enough, treat it as a tap
				// Check if user tapped on the Restart or Exit softkeys
				if (p1 < screen_height*7/8) break;  // Tapped too high up, ignore

				if (p0 < screen_width/4) {
					e_key(MR_KEY_SOFTLEFT);
				}
				else if (p0 > screen_width*3/4) {
					save_game();
					inf->mrc_exit();
					return 0;
				}
			} else {
				// Determine which direction was swiped
				if (right > up && right > down && right > left) {
					e_key(MR_KEY_RIGHT);
				}
				else if (left > up && left > down && left > right) {
					e_key(MR_KEY_LEFT);
				}
				else if (up > down && up > left && up > right) {
					e_key(MR_KEY_UP);
				}
				else {
					e_key(MR_KEY_DOWN);
				}
			}
            break;
        }
        case MR_KEY_RELEASE: {
            if (p0 == MR_KEY_SOFTRIGHT) {
                save_game();
                inf->mrc_exit();
                return 0;
            } else {
                e_key(p0);
            }
            break;
        }
    }
    draw();
    return 0;
}
