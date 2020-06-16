#include "2048.h"

#include <time.h>
#include <stdlib.h>

#define forl int i = 0; for (; i < LINE_SIZE; ++i)
#define forb int i = 0; for (; i < BOARD_SIZE; ++i)

int e_board[BOARD_SIZE];
int e_win, e_lose, e_score;

static int *space[BOARD_SIZE];
static int b_reg[LINE_SIZE], f_reg[LINE_SIZE];
static int K_ESCAPE, K_LEFT, K_RIGHT, K_UP, K_DOWN;

static inline double math_random() { return rand() / (double) RAND_MAX; }
static inline int tile_at(int x, int y) { return e_board[x + y * LINE_SIZE]; }

static void set_line(int index, int *line) {
	forl
		e_board[index * LINE_SIZE + i] = line[i];
}

static int compare(int *line_first, int *line_second) {
	forl
		if (line_first[i] != line_second[i])
			return 0;
	return 1;
}

static int *get_line(int index, int *reg) {
	forl
		reg[i] = tile_at(i, index);
	return reg;
}

static void copy_line(int *dest, int *src) {
	forl
		dest[i] = src[i];
}

static int *move_line(int *line) {
	int size = 0;
	forl
		if (line[i])
			f_reg[size++] = line[i];
	if (!size)
		copy_line(f_reg, line);
	return f_reg;
}

static void reset_b_reg() {
	forl
		b_reg[i] = 0;
}

static int *merge_line(int *line) {
	reset_b_reg();
	int i = 0, size = 0;
	for (; i < LINE_SIZE && line[i]; ++i) {
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
		copy_line(b_reg, line);
	return b_reg;
}

static void reset_space() {
	forb
		space[i] = NULL;
}

static int update_space() {
	reset_space();
	int size = 0;
	forb
		if (!e_board[i])
			space[size++] = &e_board[i];
	return size;
}

static void add_tile() {
	const int size = update_space();
	if (size)
		*space[(int)(math_random() * size) % size] = (math_random() < 0.9) ? 2 : 4;
}

static void reset_regs() {
	forl
		b_reg[i] = f_reg[i] = 0;
}

static void reset() {
	e_score = e_win = e_lose = 0;
	forb
		e_board[i] = 0;
	reset_space();
	reset_regs();
	add_tile();
	add_tile();
}

static void rotate_90() {
	int rotated[BOARD_SIZE], x = 0, y;
	for (; x < LINE_SIZE; ++x)
		for (y = 0; y < LINE_SIZE; ++y)
			rotated[x * LINE_SIZE + y] = e_board[(LINE_SIZE - y - 1) * LINE_SIZE + x];
	forb
		e_board[i] = rotated[i];
}

static void left() {
	int need_add_tile = 0;
	forl {
		reset_regs();
		int *line = get_line(i, b_reg), *merged = merge_line(move_line(line));
		line = get_line(i, f_reg);
		int res = compare(line, merged);
		set_line(i, merged);
		if (!need_add_tile && !res)
			need_add_tile = 1;
	}
	if (need_add_tile)
		add_tile();
}

static int can_move() {
	if (update_space())
		return 1;
	int x = 0;
	for (; x < LINE_SIZE; ++x) {
		int y = 0;
		for (; y < LINE_SIZE; ++y)
			if ((x < (LINE_SIZE - 1) && tile_at(x, y) == tile_at(x + 1, y)) ||
			    (y < (LINE_SIZE - 1) && tile_at(x, y) == tile_at(x, y + 1)))
				return 1;
	}
	return 0;
}

static void right() {
	rotate_90(); rotate_90();              // 180
	left();
	rotate_90(); rotate_90();              // 180
}

static void up() {
	rotate_90(); rotate_90(); rotate_90(); // 270
	left();
	rotate_90();                           // 90
}

static void down() {
	rotate_90();                           // 90
	left();
	rotate_90(); rotate_90(); rotate_90(); // 270
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
	srand(time(NULL));
	K_ESCAPE = esc_keycode;
	K_LEFT = left_keycode;
	K_RIGHT = right_keycode;
	K_UP = up_keycode;
	K_DOWN = down_keycode;
	reset();
}
