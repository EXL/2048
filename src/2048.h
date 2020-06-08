#ifndef H_2048
#define H_2048

const int HORIZONTAL = 4, VERTICAL = 4;
const int BOARD_SIZE = HORIZONTAL * VERTICAL;
const int END_GAME_TARGET = 2048;

extern void reset();
extern void left();
extern void right();
extern void up();
extern void down();
extern unsigned foreground(int value);
extern unsigned background(int value);
extern int *board_p();

#endif // H_2048
