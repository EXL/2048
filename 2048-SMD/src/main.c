#include "2048.h"

#include <genesis.h>

#include "gfx.h"

#define GM_FIELD_OFFSET_SCALE   5
#define GM_TILE_MARGIN          5
#define GM_TILE_SIZE            40
#define GM_WIDTH_AUX            320
#define GM_HEIGHT_AUX           5
#define GM_SCORE_SIZE           6
#define GM_SCORE_STR_SIZE       (7 + GM_SCORE_SIZE)

static Sprite *tile[BOARD_SIZE];

static inline int offsetCoords(int coord) { return coord * (GM_TILE_MARGIN + GM_TILE_SIZE) + GM_TILE_MARGIN * 2; }

static inline int convertValueToIndex(int value) {
	/* return log2(value); */
	switch (value) {
	default:   return  0;
	case 2:    return  1;
	case 4:    return  2;
	case 8:    return  3;
	case 16:   return  4;
	case 32:   return  5;
	case 64:   return  6;
	case 128:  return  7;
	case 256:  return  8;
	case 512:  return  9;
	case 1024: return 10;
	case 2048: return 11;
	}
}

static void drawBoard() {
	int i;
	for (i = 0; i < BOARD_SIZE; ++i)
		SPR_setFrame(tile[i], convertValueToIndex(e_board[i]));
}

static void drawText() {
	char strValue[GM_SCORE_SIZE];
	char strScore[GM_SCORE_STR_SIZE];

	intToStr(e_score, strValue, GM_SCORE_SIZE - 1);
	strcpy(strScore, "Score: ");
	strcat(strScore, strValue);

	/* X and Y coordinates in tiles, 40x28. */
	VDP_drawText("2048-SMD: https://github.com/EXL/2048", 2, 0);
	VDP_drawText("Start/A/B to Restart!", 2, 25);
	VDP_drawText(strScore, 25, 25);
}

static void joyEvent(u16 joy, u16 changed, u16 state) {
	const u16 value = changed & state;

	if (value & BUTTON_LEFT)
		e_key(BUTTON_LEFT);
	else if (value & BUTTON_RIGHT)
		e_key(BUTTON_RIGHT);
	else if (value & BUTTON_UP)
		e_key(BUTTON_UP);
	else if (value & BUTTON_DOWN)
		e_key(BUTTON_DOWN);
	else if (value & BUTTON_START || value & BUTTON_A || value & BUTTON_B)
		e_key(BUTTON_START);
}

static void initSprite(int x, int y) {
	const int xOffset = offsetCoords(x) + GM_WIDTH_AUX / GM_FIELD_OFFSET_SCALE;
	const int yOffset = offsetCoords(y) + GM_HEIGHT_AUX;
	tile[x + y * LINE_SIZE] = SPR_addSprite(&GM_Tiles, xOffset, yOffset, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
}

static void displayDebugTextBoard() {
	int y, x;
	char tile[5];

	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x) {
			intToStr(e_board[x + y * LINE_SIZE], tile, 5);
			VDP_drawText(tile, x * 6, y * 4);
		}
}

int main(bool hardReset) {
	int y = 0, x = 0;
	u16 palette[64];

	e_init(BUTTON_START, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN);

	//    updateBoard();

	JOY_init();
	JOY_setEventHandler(joyEvent);

	VDP_setScreenWidth320();

	SPR_init();

	VDP_setPaletteColors(0, (u16*) palette_black, 64);

	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			initSprite(x, y);

	// tile = SPR_addSprite(&GM_Tiles, 100, 100, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));

	memcpy(&palette[0], GM_Palette.data, 64 * 2);
	PAL_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);

	while(TRUE) {
		//        handleInput();

		drawBoard();
		drawText();
//		SPR_setFrame(tile[5], 4);
		SPR_update();

		SYS_doVBlankProcess();
	}

	return 0;
}
