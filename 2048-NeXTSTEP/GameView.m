#include "2048.h"
#include "KeyCodes.h"
#include "PostScriptWraps.h"

#import "GameView.h"

#import <appkit/appkit.h>

#include <stdio.h>

#define ww bounds.size.width
#define hh bounds.size.height

#define VALUE_MAX_SIZE 5  // "2048\0"
#define SCORE_MAX_SIZE 16 // "Score: 999999"

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static inline float R(unsigned rgb) { return ((rgb >> 16) & 0xFF) / 255.0f; }
static inline float G(unsigned rgb) { return ((rgb >> 8) & 0xFF) / 255.0f; }
static inline float B(unsigned rgb) { return ((rgb >> 0) & 0xFF) / 255.0f; }

static inline int offsetCoords(int coord, int size, int offset) {
	int start = (size / 2) - (((TILE_SIZE * LINE_SIZE) + (TILE_MARGIN * (LINE_SIZE - 1))) / 2);
	return coord * (TILE_MARGIN + TILE_SIZE) + start - offset;
}

@implementation GameView : View

- (void)drawTile:(int)value :(int)x :(int)y {
	const int xOffset = offsetCoords(x, ww, 0), yOffset = offsetCoords(y, hh, TILE_MARGIN * 2);
	const unsigned bkg = e_background(value), frg = e_foreground(value);
	NXRect tile = { {xOffset, yOffset}, {TILE_SIZE, TILE_SIZE} };
	if (roundedTiles)
		PSWdrawRectRounded(R(bkg), G(bkg), B(bkg),
			tile.origin.x, tile.origin.x + tile.size.width, tile.origin.y, tile.origin.y + tile.size.height, 8.0f);
	else {
		NXSetColor(NXConvertRGBToColor(R(bkg), G(bkg), B(bkg)));
		NXRectFill(&tile);
	}
	if (value) {
		id currentFont = (value < 100) ? largeFont : (value < 1000) ? middleFont : smallFont;
		int w, h = (int) [currentFont pointSize];
		char str_value[VALUE_MAX_SIZE];
		sprintf(str_value, "%d", value);
		[currentFont set];
		w = [currentFont getWidthOf:str_value];
		PSWdrawText(R(frg), G(frg), B(frg),
			xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 4, str_value);
	}
}

- (void)drawFinal {
	int w;
	char str_score[SCORE_MAX_SIZE];
	if (e_win || e_lose) {
		const char *center = (e_win) ? "You won!" : "Game Over!";
		PSWfade(R(COLOR_OVERLAY), G(COLOR_OVERLAY), B(COLOR_OVERLAY), 0.5f, ww, hh);
		[largeFont set];
		w = [largeFont getWidthOf:center];
		PSWdrawText(R(COLOR_FINAL), G(COLOR_FINAL), B(COLOR_FINAL), ww / 2 - w / 2, hh / 2, center);
	}
	sprintf(str_score, "Score: %d", e_score);
	[normalFont set];
	w = [normalFont getWidthOf:str_score];
	PSWdrawText(R(COLOR_TEXT), G(COLOR_TEXT), B(COLOR_TEXT), TILE_MARGIN, hh - 10, "ESC to Restart!");
	PSWdrawText(R(COLOR_TEXT), G(COLOR_TEXT), B(COLOR_TEXT), ww - w - TILE_MARGIN, hh - 10, str_score);
}

- drawSelf:(const NXRect *)rects :(int)rectCount {
	int x, y;
	NXSetColor(NXConvertRGBToColor(R(COLOR_BOARD), G(COLOR_BOARD), B(COLOR_BOARD)));
	NXRectFill(&bounds);
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			[self drawTile:e_board[x + y * LINE_SIZE] :x :y];
	[self drawFinal];
	return self;
}

- keyDown:(const NXEvent *)theEvent {
	short charCode = theEvent->data.key.charCode;
	switch (charCode) {
		case NX_KEY_R: e_key(NX_KEY_ESC); break;
		case NX_KEY_W: e_key(NX_KEY_UP); break;
		case NX_KEY_A: e_key(NX_KEY_LEFT); break;
		case NX_KEY_S: e_key(NX_KEY_DOWN); break;
		case NX_KEY_D: e_key(NX_KEY_RIGHT); break;
		default: e_key(charCode); break;
	}
	[self update];
	return self;
}

- resetGame:sender {
	e_key(NX_KEY_ESC);
	[self update];
	return self;
}

- setRoundedTiles:sender {
	roundedTiles = YES;
	[self update];
	return self;
}

- setRectangleTiles:sender {
	roundedTiles = NO;
	[self update];
	return self;
}

- initFrame:(const NXRect *)frameRect {
	[super initFrame:frameRect];

	e_init(NX_KEY_ESC, NX_KEY_LEFT, NX_KEY_RIGHT, NX_KEY_UP, NX_KEY_DOWN);

	[self allocateGState];
	[self setClipping:NO];
	[self setFlipped:YES];

	smallFont = [Font boldSystemFontOfSize:14.0f matrix:NX_FLIPPEDMATRIX];
	middleFont = [Font boldSystemFontOfSize:18.0f matrix:NX_FLIPPEDMATRIX];
	normalFont = [Font systemFontOfSize:18.0f matrix:NX_FLIPPEDMATRIX];
	largeFont = [Font boldSystemFontOfSize:24.0f matrix:NX_FLIPPEDMATRIX];

	roundedTiles = YES;

	return self;
}

@end
