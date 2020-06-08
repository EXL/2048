#include "2048.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>

#define forl int i = 0; for (; i < HORIZONTAL; ++i)
#define forb int i = 0; for (; i < BOARD_SIZE; ++i)

int board[BOARD_SIZE];
int *space[BOARD_SIZE];
int b_reg[HORIZONTAL], f_reg[HORIZONTAL];

int win, lose, score;
int K_ESCAPE, K_LEFT, K_RIGHT, K_UP, K_DOWN;

static inline double math_random() { return rand() / (double) RAND_MAX; }
static inline double degrees_to_radians(int degrees) { return ((degrees) * M_PI / 180.0); }
static inline int tile_at(int x, int y) { return board[x + y * 4]; }

extern int *e_board() { return board; }
extern int e_win() { return win; }
extern int e_lose() { return lose; }
extern int e_score() { return score; }

extern unsigned e_foreground(int value) { return (value < 16) ? 0x00776E65 : 0x00F9F6F2; }
extern unsigned e_background(int value) {
	switch (value) {
		case    2: return 0x00EEE4DA;
		case    4: return 0x00EDE0C8;
		case    8: return 0x00F2B179;
		case   16: return 0x00F59563;
		case   32: return 0x00F67C5F;
		case   64: return 0x00F65E3B;
		case  128: return 0x00EDCF72;
		case  256: return 0x00EDCC61;
		case  512: return 0x00EDC850;
		case 1024: return 0x00EDC53F;
		case 2048: return 0x00EDC22E;
	}
	return 0x00CDC1B4;
}

extern void e_init(int escape, int left, int right, int up, int down) {
	K_ESCAPE = escape;
	K_LEFT = left;
	K_RIGHT = right;
	K_UP = up;
	K_DOWN = down;
	srand(time(NULL));
}

static void set_line(int index, int *line) {
	forl
		board[index * 4 + i] = line[i];
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
	for (; i < HORIZONTAL && line[i]; ++i) {
		int value = line[i];
		if (i < 3 && line[i] == line[i + 1]) {
			value *= 2;
			score += value;
			if (value == END_GAME_TARGET)
				win = 1;
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
		if (!board[i])
			space[size++] = &board[i];
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

extern void e_reset() {
	score = win = lose = 0;
	forb
		board[i] = 0;
	reset_space();
	reset_regs();
	add_tile();
	add_tile();
}

static void rotate(int angle) {
	int new_board[BOARD_SIZE];
	int offset_x = 3, offset_y = 3, x = 0;
	if (angle == 90)
		offset_y = 0;
	else if (angle == 270)
		offset_x = 0;
	const double rad = degrees_to_radians(angle);
	const int cs = (int) cos(rad), sn = (int) sin(rad);
	for (; x < HORIZONTAL; ++x) {
		int y = 0;
		for (; y < VERTICAL; ++y) {
			int new_x = (x * cs) - (y * sn) + offset_x, new_y = (x * sn) + (y * cs) + offset_y;
			new_board[new_x + new_y * 4] = tile_at(x, y);
		}
	}
	forb
		board[i] = new_board[i];
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

static int can_move() {
	if (update_space())
		return 1;
	int x = 0;
	for (; x < HORIZONTAL; ++x) {
		int y = 0;
		for (; y < VERTICAL; ++y)
			if ((x < 3 && tile_at(x, y) == tile_at(x + 1, y)) || (y < 3 && tile_at(x, y) == tile_at(x, y + 1)))
				return 1;
	}
	return 0;
}

extern void e_key_event(int key) {
	if (key == K_ESCAPE)
		e_reset();
	if (!can_move())
		lose = 1;
	if (!win && !lose) {
		if (key == K_LEFT) left();
		else if (key == K_RIGHT) right();
		else if (key == K_UP) up();
		else if (key == K_DOWN) down();
	}
	if (!win && !can_move())
		lose = 1;
}
