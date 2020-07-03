#import <appkit/appkit.h>

#import <stdio.h>

#import "2048.h"
#import "GameView.h"
#import "SortWraps.h"
#import "Keycodes.h"

#define VALUE_MAX_SIZE 5   // "2048\0"
#define VALUE_MAX_SCORE 16 // "Score: 999999"

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static inline float R(unsigned rgb) { return ((rgb >> 16) & 0xFF) / 255.0f; }
static inline float G(unsigned rgb) { return ((rgb >> 8) & 0xFF) / 255.0f; }
static inline float B(unsigned rgb) { return ((rgb >> 0) & 0xFF) / 255.0f; }

static inline int offsetCoords(int coord, int size, int offset) {
	int start = (size / 2) - (((TILE_SIZE * LINE_SIZE) + (TILE_MARGIN * (LINE_SIZE - 1))) / 2);
	return coord * (TILE_MARGIN + TILE_SIZE) + start - offset;
}

@implementation GameView:View

- initFrame:(const NXRect *)form {
	[super initFrame:form];

	[self allocateGState];
	[self setClipping:NO];
	[self setFlipped:YES];
	//[super init];
	//[self lockFocus];

	//smallFont = [Font newFont:"Helvetica Bold" size:14 style:3 matrix:NX_FLIPPEDMATRIX];
	//middleFont = [Font newFont:"Helvetica" size:18 matrix:NX_FLIPPEDMATRIX];
	//normalFont = [Font newFont:"Helvetica" size:18 matrix:NX_FLIPPEDMATRIX];
	//largeFont = [Font newFont:"Helvetica" size:24 matrix:NX_FLIPPEDMATRIX];	

	smallFont = [Font boldSystemFontOfSize:14.0f matrix:NX_FLIPPEDMATRIX];	
	middleFont = [Font boldSystemFontOfSize:18.0f matrix:NX_FLIPPEDMATRIX];	
	normalFont = [Font systemFontOfSize:18.0f matrix:NX_FLIPPEDMATRIX];	
	largeFont = [Font boldSystemFontOfSize:24.0f matrix:NX_FLIPPEDMATRIX];	
	//[self drawBorders:NO];

	// TODO: Set Background.
	//[self setBackgroundColor:NX_COLORWHITE];

	// Display??
	// [self display];

	e_init(NX_KEY_ESC, NX_KEY_LEFT, NX_KEY_RIGHT, NX_KEY_UP, NX_KEY_DOWN);

	//[self lockFocus];

    //[[self window] makeKeyAndOrderFront:self];
    //[[self window] makeFirstResponder:self];
    //[self display];

	firstPaint = YES;

	return self;
}

- free {
	return [super free];
}
/*
- (BOOL)acceptsFirstResponder {
	return YES;
}

- (BOOL)acceptsFirstMouse {
	return YES;
}

- (BOOL)performKeyEquivalent:(NXEvent *)theEvent {
	//return YES;
	return [super performKeyEquivalent:theEvent];
}

- (BOOL)shouldDelayWindowOrderingForEvent:(NXEvent *)anEvent {
	return YES;
}

- windowDidBecomeKey:sender {
	fprintf(stderr, "WTF\n");
	return self;
}

- drawBackground:(NXRect *)rect {
	NXEraseRect(&bounds);
	return self;
}
*/
- (void)drawTile:(int)value:(int)x:(int) y {
	const int xOffset = offsetCoords(x, bounds.size.width, 0), yOffset = offsetCoords(y, bounds.size.height, TILE_MARGIN * 2);
	NXRect tileRect = { {xOffset, yOffset}, {TILE_SIZE, TILE_SIZE} };
	NXSetColor(NXConvertRGBToColor(R(e_background(value)), G(e_background(value)), B(e_background(value))));
	NXRectFill(&tileRect);
	if (value) {
		int w, h = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
		id currentFont = (value < 100) ? largeFont : (value < 1000) ? middleFont : smallFont;
		char str_value[VALUE_MAX_SIZE];
		sprintf(str_value, "%d", value);
		[currentFont set];
		w = [currentFont getWidthOf:str_value];
		//PSsetrgbcolor();
		PSWdrawName(R(e_foreground(value)), G(e_foreground(value)), B(e_foreground(value)), xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 4, str_value);
	}

/*

	char str_value[VALUE_MAX_SIZE];
	NXRect bRect = { {xOffset, yOffset}, {TILE_SIZE, TILE_SIZE} };
	//bounds.size.height
	sprintf(str_value, "%d", value);
	//NXDrawGroove(&bRect, NULL);
	//PSshow(str_value);
	//PSWdrawStrings("1","2","3","4", yOffset);
	[smallFont set];
	PSWdrawName(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, str_value); 
*/
}

- (void)drawFinal {
	int w;
	char str_score[VALUE_MAX_SCORE];
	if (e_win || e_lose) {
		const char *center = (e_win) ? "You won!" : "Game Over!";
		PSWfade(R(COLOR_OVERLAY), G(COLOR_OVERLAY), B(COLOR_OVERLAY), 0.5f, bounds.size.width, bounds.size.height);
		[largeFont set];
		w = [largeFont getWidthOf:center];
		PSWdrawName(R(COLOR_FINAL), G(COLOR_FINAL), B(COLOR_FINAL), bounds.size.width / 2 - w / 2, bounds.size.height / 2, center);	
	}
	sprintf(str_score, "Score: %d", e_score);
	[normalFont set];
	w = [normalFont getWidthOf:str_score];
	PSWdrawName(R(COLOR_TEXT), G(COLOR_TEXT), B(COLOR_TEXT), TILE_MARGIN, bounds.size.height - 10, "ESC to Restart!");
	PSWdrawName(R(COLOR_TEXT), G(COLOR_TEXT), B(COLOR_TEXT), bounds.size.width - w - TILE_MARGIN, bounds.size.height - 10, str_score);
}

- keyDown:(NXEvent *)theEvent {
	int charCode = theEvent->data.key.charCode;
	fprintf(stderr, "Key: %d\n", theEvent->data.key.charCode);
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

- drawSelf:(const NXRect *)rects :(int)rectCount {
	int x, y;
	//[window makeKeyAndOrderFront:window];
	if (firstPaint) {
    		//[[self window] makeKeyAndOrderFront:self];
    		//[[self window] makeFirstResponder:self];
		firstPaint = NO;
	}
    //[self display];
	//[self lockFocus];
	//NXRect bRect = { {0.0, 0.0}, {20.0, 20.0} };
	//[self lockFocus];
	NXSetColor(NXConvertRGBToColor(R(COLOR_BOARD), G(COLOR_BOARD), B(COLOR_BOARD)));
	NXRectFill(&bounds);
	// NXDrawButton(&bRect, NULL);		
	//[self drawBackground:rects];
	
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			[self drawTile:e_board[x + y * LINE_SIZE] :x :y];
	[self drawFinal];
	//[self unlockFocus];
	return self;
}

- resetGame:sender {
	fprintf(stderr, "WTHF?\n");
	e_key(NX_KEY_ESC);
	[self update];
	[self display];
	[[self window] reenableDisplay];
	[[self window] display];
	return self;
}

/*
- windowWillClosed:sender {
	fprintf(stderr, "CLOSE\n");
	return self;
}
*/

@end