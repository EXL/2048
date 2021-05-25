#include "2048.hpp"

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

unsigned BIG CGameEngine::Foreground(int value) { return (value < 16) ? COLOR_TEXT : COLOR_TEXT_LIGHT; }

unsigned BIG CGameEngine::Background(int value) {
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

void CGameEngine::SetLine(int index, int *line) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		e_board[index * LINE_SIZE + i] = line[i];
}

int CGameEngine::CompareLine(int *line_first, int *line_second) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		if (line_first[i] != line_second[i])
			return 0;
	return 1;
}

int *CGameEngine::GetLine(int index, int *reg) {
	int i;
	for (i = 0; i < LINE_SIZE; ++i)
		reg[i] = E_TILE_AT(i, index);
	return reg;
}

int *CGameEngine::MoveLine(int *line) {
	int size = 0, i;
	for (i = 0; i < LINE_SIZE; ++i)
		if (line[i])
			f_reg[size++] = line[i];
	if (!size)
		memcpy(f_reg, line, LINE_SIZE * sizeof(int));
	return f_reg;
}

void CGameEngine::ResetRegB() { memset(b_reg, 0, LINE_SIZE * sizeof(int)); }

int *CGameEngine::MergeLine(int *line) {
	int size = 0, i;
	ResetRegB();
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

void CGameEngine::ResetSpace() {
	int i;
	for (i = 0; i < BOARD_SIZE; ++i)
		f_space[i] = NULL;
}

int CGameEngine::UpdateSpace() {
	int size = 0, i;
	ResetSpace();
	for (i = 0; i < BOARD_SIZE; ++i)
		if (!e_board[i])
			f_space[size++] = &e_board[i];
	return size;
}

void CGameEngine::AddTile(int n) {
	int i;
	for (i = 0; i < n; ++i) {
		const int size = UpdateSpace();
		if (size)
			*f_space[(E_RANDOM * size / 100) % size] = (E_RANDOM < 90) ? 2 : 4;
	}
}

void CGameEngine::ResetRegs() {
	memset(b_reg, 0, LINE_SIZE * sizeof(int));
	memset(f_reg, 0, LINE_SIZE * sizeof(int));
}

void CGameEngine::Reset() {
	e_score = e_win = e_lose = 0;
	memset(e_board, 0, BOARD_SIZE * sizeof(int));
	ResetSpace();
	ResetRegs();
	AddTile(2);
}

void CGameEngine::Rotate(int a) {
	for (; a >= 90; a -= 90) {
		int rotated[BOARD_SIZE], x, y;
		for (x = 0; x < LINE_SIZE; ++x)
			for (y = 0; y < LINE_SIZE; ++y)
				rotated[x * LINE_SIZE + y] = e_board[(LINE_SIZE - y - 1) * LINE_SIZE + x];
		memcpy(e_board, rotated, BOARD_SIZE * sizeof(int));
	}
}

void CGameEngine::Left() {
	int *line, *merged, res, need_add_tile = 0, i;
	for (i = 0; i < LINE_SIZE; ++i) {
		ResetRegs();
		line = GetLine(i, b_reg);
		merged = MergeLine(MoveLine(line));
		line = GetLine(i, f_reg);
		res = CompareLine(line, merged);
		SetLine(i, merged);
		if (!need_add_tile && !res)
			need_add_tile = 1;
	}
	if (need_add_tile)
		AddTile(1);
}

int CGameEngine::CanMove() {
	int x, y;
	if (UpdateSpace())
		return 1;
	for (x = 0; x < LINE_SIZE; ++x)
		for (y = 0; y < LINE_SIZE; ++y)
			if ((x < (LINE_SIZE - 1) && E_TILE_AT(x, y) == E_TILE_AT(x + 1, y)) ||
			    (y < (LINE_SIZE - 1) && E_TILE_AT(x, y) == E_TILE_AT(x, y + 1)))
				return 1;
	return 0;
}

void CGameEngine::Right() {
	Rotate(180);
	Left();
	Rotate(180);
}

void CGameEngine::Up() {
	Rotate(270);
	Left();
	Rotate(90);
}

void CGameEngine::Down() {
	Rotate(90);
	Left();
	Rotate(270);
}

void CGameEngine::Key(int keycode) {
	if (keycode == K_ESCAPE)
		Reset();
	if (!CanMove())
		e_lose = 1;
	if (!e_win && !e_lose) {
		if (keycode == K_LEFT) Left();
		else if (keycode == K_RIGHT) Right();
		else if (keycode == K_UP) Up();
		else if (keycode == K_DOWN) Down();
	}
	if (!e_win && !CanMove())
		e_lose = 1;
}

int *CGameEngine::Win() { return &e_win; }
int *CGameEngine::Lose() { return &e_lose; }
int *CGameEngine::Score() { return &e_score; }
int *CGameEngine::Board() { return e_board; }

CGameEngine::CGameEngine(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode) {
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
	Reset();
}
