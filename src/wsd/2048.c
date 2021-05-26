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
#define E_TILE_AT(x, y)  (engine->e_board[(x) + ((y) * LINE_SIZE)])

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

static void set_line(Engine *engine, int index, int *line) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		engine->e_board[index * LINE_SIZE + i] = line[i];
}

static int compare(int *line_first, int *line_second) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		if (line_first[i] != line_second[i])
			return 0;
	return 1;
}

static int *get_line(Engine *engine, int index, int *reg) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		reg[i] = E_TILE_AT(i, index);
	return reg;
}

static int *move_line(Engine *engine, int *line) {
	int size = 0, i;
	for (i = 0; i < LINE_SIZE; ++i)
		if (line[i])
			engine->f_reg[size++] = line[i];
	if (!size)
		memcpy(engine->f_reg, line, LINE_SIZE * sizeof(int));
	return engine->f_reg;
}

static void reset_b_reg(Engine *engine) { memset(engine->b_reg, 0, LINE_SIZE * sizeof(int)); }

static int *merge_line(Engine *engine, int *line) {
	int size = 0, i;
	reset_b_reg(engine);
	for (i = 0; i < LINE_SIZE && line[i]; ++i) {
		int value = line[i];
		if (i < (LINE_SIZE - 1) && line[i] == line[i + 1]) {
			value *= 2;
			engine->e_score += value;
			if (value == END_GAME_TARGET)
				engine->e_win = 1;
			++i;
		}
		engine->b_reg[size++] = value;
	}
	if (!size)
		memcpy(engine->b_reg, line, LINE_SIZE * sizeof(int));
	return engine->b_reg;
}

static void reset_space(Engine *engine) {
	int i;
	for (i = 0; i < BOARD_SIZE; ++i)
		engine->f_space[i] = NULL;
}

static int update_space(Engine *engine) {
	int size = 0, i;
	reset_space(engine);
	for (i = 0; i < BOARD_SIZE; ++i)
		if (!engine->e_board[i])
			engine->f_space[size++] = &(engine->e_board[i]);
	return size;
}

static void add_tile(Engine *engine, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		const int size = update_space(engine);
		if (size)
			*(engine->f_space[(E_RANDOM * size / 100) % size]) = (E_RANDOM < 90) ? 2 : 4;
	}
}

static void reset_regs(Engine *engine) {
	memset(engine->b_reg, 0, LINE_SIZE * sizeof(int));
	memset(engine->f_reg, 0, LINE_SIZE * sizeof(int));
}

static void reset(Engine *engine) {
	engine->e_score = engine->e_win = engine->e_lose = 0;
	memset(engine->e_board, 0, BOARD_SIZE * sizeof(int));
	reset_space(engine);
	reset_regs(engine);
	add_tile(engine, 2);
}

static void rotate(Engine *engine, int a) {
	for (; a >= 90; a -= 90) {
		int rotated[BOARD_SIZE], x, y;
		for (x = 0; x < LINE_SIZE; ++x)
			for (y = 0; y < LINE_SIZE; ++y)
				rotated[x * LINE_SIZE + y] = engine->e_board[(LINE_SIZE - y - 1) * LINE_SIZE + x];
		memcpy(engine->e_board, rotated, BOARD_SIZE * sizeof(int));
	}
}

static void left(Engine *engine) {
	int *line, *merged, res, need_add_tile = 0, i;
	for (i = 0; i < LINE_SIZE; ++i) {
		reset_regs(engine);
		line = get_line(engine, i, engine->b_reg);
		merged = merge_line(engine, move_line(engine, line));
		line = get_line(engine, i, engine->f_reg);
		res = compare(line, merged);
		set_line(engine, i, merged);
		if (!need_add_tile && !res)
			need_add_tile = 1;
	}
	if (need_add_tile)
		add_tile(engine, 1);
}

static int can_move(Engine *engine) {
	int x, y;
	if (update_space(engine))
		return 1;
	for (x = 0; x < LINE_SIZE; ++x)
		for (y = 0; y < LINE_SIZE; ++y)
			if ((x < (LINE_SIZE - 1) && E_TILE_AT(x, y) == E_TILE_AT(x + 1, y)) ||
			    (y < (LINE_SIZE - 1) && E_TILE_AT(x, y) == E_TILE_AT(x, y + 1)))
				return 1;
	return 0;
}

static void right(Engine *engine) {
	rotate(engine, 180);
	left(engine);
	rotate(engine, 180);
}

static void up(Engine *engine) {
	rotate(engine, 270);
	left(engine);
	rotate(engine, 90);
}

static void down(Engine *engine) {
	rotate(engine, 90);
	left(engine);
	rotate(engine, 270);
}

extern void e_key(Engine *engine, int keycode) {
	if (keycode == engine->K_ESCAPE)
		reset(engine);
	if (!can_move(engine))
		engine->e_lose = 1;
	if (!engine->e_win && !engine->e_lose) {
		if (keycode == engine->K_LEFT) left(engine);
		else if (keycode == engine->K_RIGHT) right(engine);
		else if (keycode == engine->K_UP) up(engine);
		else if (keycode == engine->K_DOWN) down(engine);
	}
	if (!engine->e_win && !can_move(engine))
		engine->e_lose = 1;
}

extern void e_init(Engine *engine) {
#if !defined(mc68000) || defined(NeXT) /* GCC on Sega Mega Drive and Sega Genesis platform. */
#if !defined(THINK_C) /* Symantec THINK C IDE on Classic Mac OS platform. */
	srand((unsigned int) time(NULL));
#endif
#endif
	reset(engine);
}
