#ifndef H_2048
#define H_2048

#ifdef __cplusplus
extern "C" {
#endif

#define LINE_SIZE                           4
#define BOARD_SIZE                          LINE_SIZE * LINE_SIZE
#define END_GAME_TARGET                     2048

#define COLOR_BOARD                         0xFFBBADA0
#define COLOR_FINAL                         0xFF800000
#define COLOR_TEXT                          0xFF776E65
#define COLOR_OVERLAY                       0xFF888888
#define COLOR_FADE                          0xFF222222

extern int e_win;
extern int e_lose;
extern int e_score;
extern int e_board[BOARD_SIZE];

extern void e_init(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);
extern void e_key(int keycode);

extern unsigned e_foreground(int value);
extern unsigned e_background(int value);

#ifdef __cplusplus
}
#endif

#endif // H_2048
