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
    [[NSColor colorWithCalibratedRed:R(COLOR_BOARD) green:G(COLOR_BOARD) blue:B(COLOR_BOARD) alpha:1.0f] set];
    NSRectFill([self bounds]);
}

- (void)drawTile:(int)value :(int)x :(int)y {
    // TODO: Not implemented.
}

- (void)drawFinal {
    // TODO: Not implemented.
}

- (id)keyDown:(NSEvent)event {
    // TODO: Implement keys.
	fprintf(stderr, "KEY\n");
	[[NSColor redColor] set];
    NSRectFill([self bounds]);
    [self setNeedsDisplay:YES];
    return self;
}

///

- (id)resetGame:sender {
    // TODO: e_key(NS_KEY_ESC);
    [self setNeedsDisplay:YES];
    return self;
}

- (id)disableBackground:sender {
    showBackground = NO;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)enableBackground:sender {
    showBackground = YES;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)setRoundedTiles:sender {
    roundedTiles = YES;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)setRectangleTiles:sender {
    roundedTiles = NO;
    // TODO: Write defaults.
    [self setNeedsDisplay:YES];
    return self;
}

- (id)save:sender {
    // TODO: Not implemented.
    return self;
}

- (id)load:sender {
    // TODO: Not implemented.
    return self;
}

@end
