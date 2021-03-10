#include "2048.h"

#if defined(mc68000) && !defined(NeXT) /* GCC on Sega Mega Drive and Sega Genesis platform. */
	#include <genesis.h>
	#define rand random
#else
	#include <time.h>
	#include <stdlib.h>
#endif
#include <string.h>

#if defined(THINK_C) /* Symantec THINK C IDE on Classic Mac OS platform. */
#define rand Random
#endif

#define E_RANDOM         ((unsigned int) rand() % 100 + 1)
#define E_TILE_AT(x, y)  (e_board[(x) + ((y) * LINE_SIZE)])

int e_board[BOARD_SIZE];
int e_win, e_lose, e_score;

static int *f_space[BOARD_SIZE];
static int b_reg[LINE_SIZE], f_reg[LINE_SIZE];
static int K_ESCAPE, K_LEFT, K_RIGHT, K_UP, K_DOWN;

extern unsigned BIG e_foreground(int value) { return (value < 16) ? COLOR_TEXT : COLOR_TEXT_LIGHT; }

extern unsigned BIG e_background(int value) {
	switch (value) {
		case    2: return    COLOR_TILE_2;
		case    4: return    COLOR_TILE_4;
		case    8: return    COLOR_TILE_8;
		case   16: return   COLOR_TILE_16;
		case   32: return   COLOR_TILE_32;
		case   64: return   COLOR_TILE_64;
		case  128: return  COLOR_TILE_128;
		case  256: return  COLOR_TILE_256;
		case  512: return  COLOR_TILE_512;
		case 1024: return COLOR_TILE_1024;
		case 2048: return COLOR_TILE_2048;
	}
	return COLOR_TILE_0;
}

static void set_line(int index, int *line) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		e_board[index * LINE_SIZE + i] = line[i];
}

static int compare(int *line_first, int *line_second) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		if (line_first[i] != line_second[i])
			return 0;
	return 1;
}

static int *get_line(int index, int *reg) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		reg[i] = E_TILE_AT(i, index);
	return reg;
}

static int *move_line(int *line) {
	int size = 0, i;
	for (i = 0; i < LINE_SIZE; ++i)
		if (line[i])
			f_reg[size++] = line[i];
	if (!size)
		memcpy(f_reg, line, LINE_SIZE * sizeof(int));
	return f_reg;
}

static void reset_b_reg() { memset(b_reg, 0, LINE_SIZE * sizeof(int)); }

static int *merge_line(int *line) {
	int size = 0, i;
	reset_b_reg();
	for (i = 0; i < LINE_SIZE && line[i]; ++i) {
		int value = line[i];
		if (i < (LINE_SIZE - 1) && line[i] == line[i + 1]) {
			value *= 2;
			e_score += value;
			if (value == END_GAME_TARGET)
				e_win = 1;
			++i;
		}
		b_reg[size++] = value;
	}
	if (!size)
		memcpy(b_reg, line, LINE_SIZE * sizeof(int));
	return b_reg;
}

static void reset_space() {
	int i;
	for (i = 0; i < BOARD_SIZE; ++i)
		f_space[i] = NULL;
}

static int update_space() {
	int size = 0, i;
	reset_space();
	for (i = 0; i < BOARD_SIZE; ++i)
		if (!e_board[i])
			f_space[size++] = &e_board[i];
	return size;
}

static void add_tile(int n) {
	int i;
	for (i = 0; i < n; ++i) {
		const int size = update_space();
		if (size)
			*f_space[(E_RANDOM * size / 100) % size] = (E_RANDOM < 90) ? 2 : 4;
	}
}

static void reset_regs() {
	memset(b_reg, 0, LINE_SIZE * sizeof(int));
	memset(f_reg, 0, LINE_SIZE * sizeof(int));
}

static void reset() {
	e_score = e_win = e_lose = 0;
	memset(e_board, 0, BOARD_SIZE * sizeof(int));
	reset_space();
	reset_regs();
	add_tile(2);
}

static void rotate(int a) {
	for (; a >= 90; a -= 90) {
		int rotated[BOARD_SIZE], x, y;
		for (x = 0; x < LINE_SIZE; ++x)
			for (y = 0; y < LINE_SIZE; ++y)
				rotated[x * LINE_SIZE + y] = e_board[(LINE_SIZE - y - 1) * LINE_SIZE + x];
		memcpy(e_board, rotated, BOARD_SIZE * sizeof(int));
	}
}

static void left() {
	int *line, *merged, res, need_add_tile = 0, i;
	for (i = 0; i < LINE_SIZE; ++i) {
		reset_regs();
		line = get_line(i, b_reg);
		merged = merge_line(move_line(line));
		line = get_line(i, f_reg);
		res = compare(line, merged);
		set_line(i, merged);
		if (!need_add_tile && !res)
			need_add_tile = 1;
	}
	if (need_add_tile)
		add_tile(1);
}

static int can_move() {
	int x, y;
	if (update_space())
		return 1;
	for (x = 0; x < LINE_SIZE; ++x)
		for (y = 0; y < LINE_SIZE; ++y)
			if ((x < (LINE_SIZE - 1) && E_TILE_AT(x, y) == E_TILE_AT(x + 1, y)) ||
			    (y < (LINE_SIZE - 1) && E_TILE_AT(x, y) == E_TILE_AT(x, y + 1)))
				return 1;
	return 0;
}

static void right() {
	rotate(180);
	left();
	rotate(180);
}

static void up() {
	rotate(270);
	left();
	rotate(90);
}

static void down() {
	rotate(90);
	left();
	rotate(270);
}

extern void e_key(int keycode) {
	if (keycode == K_ESCAPE)
		reset();
	if (!can_move())
		e_lose = 1;
	if (!e_win && !e_lose) {
		if (keycode == K_LEFT) left();
		else if (keycode == K_RIGHT) right();
		else if (keycode == K_UP) up();
		else if (keycode == K_DOWN) down();
	}
	if (!e_win && !can_move())
		e_lose = 1;
}

extern void e_init(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode) {
#if !defined(mc68000) || defined(NeXT) /* GCC on Sega Mega Drive and Sega Genesis platform. */
#if !defined(THINK_C) /* Symantec THINK C IDE on Classic Mac OS platform. */
	srand((unsigned int) time(NULL));
#endif
#endif
	K_ESCAPE = esc_keycode;
	K_LEFT = left_keycode;
	K_RIGHT = right_keycode;
	K_UP = up_keycode;
	K_DOWN = down_keycode;
	reset();
}
