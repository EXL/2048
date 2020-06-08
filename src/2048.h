#ifndef H_2048
#define H_2048

#define HORIZONTAL         4
#define VERTICAL           4
#define BOARD_SIZE         HORIZONTAL * VERTICAL
#define END_GAME_TARGET    2048

extern void reset();
extern void left();
extern void right();
extern void up();
extern void down();
extern unsigned foreground(int value);
extern unsigned background(int value);
extern int *board_p();

#endif // H_2048
