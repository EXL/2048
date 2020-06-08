#ifndef H_2048
#define H_2048

#ifdef __cplusplus
extern "C" {
#endif

#define HORIZONTAL         4
#define VERTICAL           4
#define BOARD_SIZE         HORIZONTAL * VERTICAL
#define END_GAME_TARGET    2048

extern int *e_init_board(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);

extern int e_win();
extern int e_lose();
extern int e_score();

extern void e_key_event(int key);

extern unsigned e_foreground(int value);
extern unsigned e_background(int value);

#ifdef __cplusplus
}
#endif

#endif // H_2048
