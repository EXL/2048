#include "2048.h"

int w_line_size = LINE_SIZE;
int w_board_size = BOARD_SIZE;
int *w_board = e_board;

unsigned int w_color_board = COLOR_BOARD;
unsigned int w_color_final = COLOR_FINAL;
unsigned int w_color_text = COLOR_TEXT;
unsigned int w_color_overlay = COLOR_OVERLAY;

extern double w_R(unsigned rgb) { return ((rgb >> 16) & 0xFF) / 255.0; }
extern double w_G(unsigned rgb) { return ((rgb >> 8) & 0xFF) / 255.0; }
extern double w_B(unsigned rgb) { return ((rgb >> 0) & 0xFF) / 255.0; }

