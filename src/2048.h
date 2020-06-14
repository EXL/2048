#ifndef H_2048
#define H_2048

#ifdef __cplusplus
extern "C" {
#endif

#define HORIZONTAL                          4
#define VERTICAL                            4
#define BOARD_SIZE                          HORIZONTAL * VERTICAL
#define END_GAME_TARGET                     2048

#define COLOR_BOARD                         0xFFBBADA0
#define COLOR_FINAL                         0xFF800000
#define COLOR_TEXT                          0xFF776E65
#define COLOR_OVERLAY                       0xFF888888
#define COLOR_FADE                          0xFF222222

extern int *e_init_board(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);

extern int e_win();
extern int e_lose();
extern int e_score();
extern void e_set(int e_score, int e_win, int e_lose);

extern void e_key_event(int key);

extern unsigned e_foreground(int value);
extern unsigned e_background(int value);

#ifdef __cplusplus
}
#endif

#endif // H_2048
