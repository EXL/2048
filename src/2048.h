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

extern int e_win();
extern int e_lose();
extern int e_score();

extern int *e_board();

extern void e_key_event(int key);

extern unsigned e_foreground(int value);
extern unsigned e_background(int value);

#ifdef __cplusplus
}
#endif

#endif // H_2048
