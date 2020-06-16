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

extern void e_init(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);
extern void e_key(int keycode);

extern int e_win;
extern int e_lose;
extern int e_score;
extern int e_board[BOARD_SIZE];

static inline unsigned e_foreground(int value) { return (value < 16) ? COLOR_TEXT : 0xFFF9F6F2; }
static inline unsigned e_background(int value) {
	switch (value) {
		case    2: return 0xFFEEE4DA;
		case    4: return 0xFFEDE0C8;
		case    8: return 0xFFF2B179;
		case   16: return 0xFFF59563;
		case   32: return 0xFFF67C5F;
		case   64: return 0xFFF65E3B;
		case  128: return 0xFFEDCF72;
		case  256: return 0xFFEDCC61;
		case  512: return 0xFFEDC850;
		case 1024: return 0xFFEDC53F;
		case 2048: return 0xFFEDC22E;
	}
	return 0xFFCDC1B4;
}

#ifdef __cplusplus
}
#endif

#endif // H_2048
