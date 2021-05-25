#ifndef HPP_2048
#define HPP_2048

#if defined(macintosh) /* Classic Mac OS platform. */
#define BIG long
#else
#define BIG
#endif

#define LINE_SIZE                           4
#define BOARD_SIZE                          LINE_SIZE * LINE_SIZE
#define END_GAME_TARGET                     2048

#define COLOR_BOARD                         0xFFBBADA0
#define COLOR_FINAL                         0xFF800000
#define COLOR_TEXT                          0xFF776E65
#define COLOR_TEXT_LIGHT                    0xFFF9F6F2
#define COLOR_OVERLAY                       0xFF888888
#define COLOR_FADE                          0xFF222222
#define COLOR_TILE_0                        0xFFCDC1B4
#define COLOR_TILE_2                        0xFFEEE4DA
#define COLOR_TILE_4                        0xFFEDE0C8
#define COLOR_TILE_8                        0xFFF2B179
#define COLOR_TILE_16                       0xFFF59563
#define COLOR_TILE_32                       0xFFF67C5F
#define COLOR_TILE_64                       0xFFF65E3B
#define COLOR_TILE_128                      0xFFEDCF72
#define COLOR_TILE_256                      0xFFEDCC61
#define COLOR_TILE_512                      0xFFEDC850
#define COLOR_TILE_1024                     0xFFEDC53F
#define COLOR_TILE_2048                     0xFFEDC22E

class CGameEngine {
	int e_win;
	int e_lose;
	int e_score;
	int e_board[BOARD_SIZE];

	int *f_space[BOARD_SIZE];
	int b_reg[LINE_SIZE];
	int f_reg[LINE_SIZE];

	int K_ESCAPE;
	int K_LEFT;
	int K_RIGHT;
	int K_UP;
	int K_DOWN;

	int *GetLine(int index, int *reg);
	void SetLine(int index, int *line);
	int *MoveLine(int *line);
	int *MergeLine(int *line);
	int CompareLine(int *line_first, int *line_second);

	int CanMove();
	void Reset();
	void ResetRegB();
	void ResetRegs();
	void ResetSpace();
	int UpdateSpace();
	void AddTile(int n);
	void Rotate(int a);
	void Left();
	void Right();
	void Up();
	void Down();

public:
	CGameEngine(int esc_keycode, int left_keycode, int right_keycode, int up_keycode, int down_keycode);

	void Key(int keycode);

	unsigned BIG Foreground(int value);
	unsigned BIG Background(int value);

	int *Board();
	int *Score();
	int *Win();
	int *Lose();
};
#endif // HPP_2048
