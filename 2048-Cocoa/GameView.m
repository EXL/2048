//
//  GameView.m
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2001 __CompanyName__. All rights reserved.
//

#include "2048.h"

#import "GameView.h"

static const int TILE_SIZE   = 64;
static const int TILE_MARGIN = 16;

static inline float R(unsigned rgb) { return ((rgb >> 16) & 0xFF) / 255.0f; }
static inline float G(unsigned rgb) { return ((rgb >> 8) & 0xFF) / 255.0f; }
static inline float B(unsigned rgb) { return ((rgb >> 0) & 0xFF) / 255.0f; }

static inline int offsetCoords(int coord, int size, int offset) {
	int start = (size / 2) - (((TILE_SIZE * LINE_SIZE) + (TILE_MARGIN * (LINE_SIZE - 1))) / 2);
	return coord * (TILE_MARGIN + TILE_SIZE) + start - offset;
}

@implementation GameView

- (id)initWithFrame:(NSRect)frame {
	e_init('\e', NSLeftArrowFunctionKey, NSRightArrowFunctionKey, NSUpArrowFunctionKey, NSDownArrowFunctionKey);

    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
        // [self setFlipped:YES];
    }
    roundedTiles = YES;
    showBackground = YES;
    return self;
}

- (void)drawRect:(NSRect)rect {
    // Drawing code here.
	int x, y;
    [[NSColor colorWithCalibratedRed:R(COLOR_BOARD) green:G(COLOR_BOARD) blue:B(COLOR_BOARD) alpha:1.0f] set];
    NSRectFill([self bounds]);
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			[self drawTile:e_board[x + y * LINE_SIZE] :x :y];
	[self drawFinal];
}

- (void)drawTile:(int)value :(int)x :(int)y {
    // TODO: Not implemented.
	
}

- (void)drawFinal {
    // TODO: Not implemented.
}

- (id)keyDown:(NSEvent *)theEvent {
    // TODO: Implement keys.
	

	NSLog(@"%@ %hu", [theEvent characters], [theEvent keyCode]);

	// [self interpretKeyEvents:[NSArray arrayWithObject:theEvent]];

    [self setNeedsDisplay:YES];
    return self;
}
/*
- (void)cancelOperation:(id)sender {
	NSLog(@"ESC!");
}
*/
///

- (id)resetGame:(id)sender {
    // TODO: e_key(NS_KEY_ESC);
    [self setNeedsDisplay:YES];
    return self;
}

- (id)disableBackground:(id)sender {
    showBackground = NO;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)enableBackground:(id)sender {
    showBackground = YES;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)setRoundedTiles:(id)sender {
    roundedTiles = YES;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)setRectangleTiles:(id)sender {
    roundedTiles = NO;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)save:(id)sender {
    // TODO: Not implemented.
    return self;
}

- (id)load:(id)sender {
    // TODO: Not implemented.
    return self;
}

@end
