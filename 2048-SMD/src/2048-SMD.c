#include "2048.h"

#include <genesis.h>

#include "gfx.h"
#include "sfx.h"

#define GM_FIELD_OFFSET_SCALE   5
#define GM_TILE_MARGIN          5
#define GM_TILE_SIZE            40
#define GM_WIDTH_AUX            320
#define GM_HEIGHT_AUX           10
#define GM_SCORE_SIZE           6
#define GM_SCORE_STR_SIZE       (7 + GM_SCORE_SIZE)
#define SFX_TURN                64

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

static void drawBoard(void) {
	int i;
	for (i = 0; i < BOARD_SIZE; ++i)
		SPR_setFrame(tile[i], convertValueToIndex(e_board[i]));
}

static void drawText(void) {
	char strValue[GM_SCORE_SIZE];
	char strScore[GM_SCORE_STR_SIZE];
	intToStr(e_score, strValue, GM_SCORE_SIZE - 1);
	strcpy(strScore, "Score: ");
	strcat(strScore, strValue);
	/* X and Y coordinates in tiles, 40x28. */
	VDP_drawText("2048-SMD: https://github.com/EXL/2048/", 1, 1);
	VDP_drawText("Start/A/B to Restart!", 1, 26);
	VDP_drawText(strScore, 27, 26);
}

static void drawFinal(void) {
	if (e_win) {
		VDP_drawImage(BG_A, &GM_YouWon_Normal, 2, 6);
		VDP_drawImage(BG_A, &GM_YouWon_Mirrored, 33, 6);
	} else if (e_lose) {
		VDP_drawImage(BG_A, &GM_GameOver_Normal, 2, 4);
		VDP_drawImage(BG_A, &GM_GameOver_Mirrored, 33, 4);
	}
}

static void joyEvent(u16 joy, u16 changed, u16 state) {
	if (joy == JOY_1 || joy == JOY_2) {
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
			SYS_reset();
			/* e_key(BUTTON_START); */
		if (!e_win && !e_lose && state)
			XGM_startPlayPCM(SFX_TURN, 1, SOUND_PCM_CH2);
	}
}

static void initSprites(void) {
	int y, x;
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x) {
			const int xOffset = offsetCoords(x) + GM_WIDTH_AUX / GM_FIELD_OFFSET_SCALE;
			const int yOffset = offsetCoords(y) + GM_HEIGHT_AUX;
			/* PAL0: '0..15' colors, '0' for background color, '15' for text color. */
			tile[x + y * LINE_SIZE] = SPR_addSprite(&GM_Tiles, xOffset, yOffset, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
		}
}

int main(bool hardReset) {
	e_init(BUTTON_START, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN);

	JOY_init();
	JOY_setEventHandler(joyEvent);

	XGM_setPCM(SFX_TURN, GM_Turn, sizeof(GM_Turn));

	VDP_setScreenWidth320();
	SPR_init();
	initSprites();
	PAL_fadeIn(0, (4 * 16) - 1, GM_Tiles.palette->data, 10, FALSE); /* from '0' to '63' color indexes. */

	while(TRUE) {
		drawBoard();
		drawText();
		drawFinal();
		SPR_update();
		SYS_doVBlankProcess();
	}

	return 0;
}
