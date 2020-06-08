#ifndef H_2048
#define H_2048

#ifdef __cplusplus
extern "C" {
#endif

#define HORIZONTAL         4
#define VERTICAL           4
#define BOARD_SIZE         HORIZONTAL * VERTICAL
#define END_GAME_TARGET    2048

extern void e_init(int escape, int left, int right, int up, int down);
extern void e_reset();
//extern void left();
//extern void right();
//extern void up();
//extern void down();

extern unsigned e_foreground(int value);
extern unsigned e_background(int value);

extern int *e_board();
extern int e_win();
extern int e_lose();
extern int e_score();
extern void e_key_event(int key);
//extern void set_win(int res);
//extern void set_lose(int res);

#ifdef __cplusplus
}
#endif

#endif // H_2048
