//
//  GameView.m
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2001 __CompanyName__. All rights reserved.
//

#include "2048.h"

#import "GameView.h"

#define ww bounds.size.width
#define hh bounds.size.height

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
		smallFont = [NSFont boldSystemFontOfSize:18.0f];
		middleFont = [NSFont boldSystemFontOfSize:22.0f];
		normalFont = [NSFont systemFontOfSize:18.0f];
		largeFont = [NSFont boldSystemFontOfSize:28.0f];
		
		roundedTiles = YES;
		showBackground = YES;
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
	int x, y;
	NSRect bounds = [self bounds];
	[(showBackground) ? [self getColor:COLOR_BOARD :1.0f] : [NSColor clearColor] set];
	NSRectFillUsingOperation(bounds, NSCompositeSourceOver);
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			[self drawTile:bounds :e_board[x + y * LINE_SIZE] :x :y];
	[self drawFinal:bounds];
}

- (void)drawTile:(NSRect)bounds :(int)value :(int)x :(int)y {
	const int xOffset = offsetCoords(x, ww, 0), yOffset = offsetCoords(y, hh, TILE_MARGIN * 2);
	const NSRect tile = NSMakeRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE);
	[[self getColor:e_background(value) :1.0f] set];
	if (roundedTiles)
		[[self roundedRect:tile :8.0f] fill];
	else
		NSRectFill(tile);
	if (value) {
		NSFont *currentFont = (value < 100) ? largeFont : (value < 1000) ? middleFont : smallFont;
		NSSize strSize;
		NSString *strValue = [NSString stringWithFormat:@"%d", value];
		NSDictionary *attrs = [self textAttributes:currentFont :[self getColor:e_foreground(value) :1.0f]];
		strSize = [strValue sizeWithAttributes:attrs];
		[strValue drawAtPoint:NSMakePoint(xOffset + (TILE_SIZE - strSize.width) / 2, yOffset + (TILE_SIZE - strSize.height) / 2) withAttributes:attrs];
	}
}

- (void)drawFinal:(NSRect)bounds {
	NSString *strScore = [NSString stringWithFormat:NSLocalizedString(@"GMScoreFMT", @"Score: %d"), e_score];
	NSString *strEscape = @"ESC to Restart!";
	NSDictionary *attrs = [self textAttributes:normalFont :[self getColor:COLOR_TEXT :1.0f]];
	NSSize strSize;
	if (e_win || e_lose) {
		NSString *strCenter = (e_win) ? NSLocalizedString(@"GMYouWon", @"You Won!") : NSLocalizedString(@"GMGameOver", @"Game Over!");
		NSDictionary *attrs = [self textAttributes:largeFont :[self getColor:COLOR_FINAL :1.0f]];
		[[self getColor:COLOR_OVERLAY :0.5f] set];
		NSRectFillUsingOperation(bounds, NSCompositeSourceOver);
		strSize = [strCenter sizeWithAttributes:attrs];
		[strCenter drawAtPoint:NSMakePoint(ww / 2 - strSize.width / 2, hh / 2 - strSize.height / 2) withAttributes:attrs];
	}
	strSize = [strScore sizeWithAttributes:attrs];
	[strEscape drawAtPoint:NSMakePoint(TILE_MARGIN, hh - strSize.height - 10) withAttributes:attrs];
	[strScore drawAtPoint:NSMakePoint(ww - strSize.width - TILE_MARGIN, hh - strSize.height - 10) withAttributes:attrs];
}

- (NSBezierPath *)roundedRect:(NSRect)rect :(int)rad {
	const int left = rect.origin.x, right = rect.origin.x + rect.size.width, top = rect.origin.y, bottom = rect.origin.y + rect.size.height;
	const float offset = rad * (1 - 0.551915024494f);
	NSBezierPath *path = [NSBezierPath bezierPath];
	[path moveToPoint:NSMakePoint(left + rad, top)];
	[path lineToPoint:NSMakePoint(right - rad, top)];
	[path curveToPoint:NSMakePoint(right, top + rad) controlPoint1:NSMakePoint(right - offset, top) controlPoint2:NSMakePoint(right, top + offset)];
	[path lineToPoint:NSMakePoint(right, bottom - rad)];
	[path curveToPoint:NSMakePoint(right - rad, bottom) controlPoint1:NSMakePoint(right, bottom - offset) controlPoint2:NSMakePoint(right - offset, bottom)];
	[path lineToPoint:NSMakePoint(left + rad, bottom)];
	[path curveToPoint:NSMakePoint(left, bottom - rad) controlPoint1:NSMakePoint(left + offset, bottom) controlPoint2:NSMakePoint(left, bottom - offset)];
	[path lineToPoint:NSMakePoint(left, top + rad)];
	[path curveToPoint:NSMakePoint(left + rad, top) controlPoint1:NSMakePoint(left, top + offset) controlPoint2:NSMakePoint(left + offset, top)];
	[path closePath];
	return path;
}

- (NSDictionary *)textAttributes:(NSFont *)font :(NSColor *)color {
	return [NSDictionary dictionaryWithObjectsAndKeys:font, NSFontAttributeName, color, NSForegroundColorAttributeName, nil];
}

- (NSColor *)getColor:(unsigned int)color :(float)alpha {
	return [NSColor colorWithCalibratedRed:R(color) green:G(color) blue:B(color) alpha:alpha];
}

- (id)keyDown:(NSEvent *)theEvent {
	int i;
	NSString *characters = [theEvent charactersIgnoringModifiers];
	for (i = 0; i < [characters length]; ++i) {
		const unichar key = [characters characterAtIndex:i];
		switch (key) {
			case 'r': e_key('\e'); break;
			case 'w': e_key(NSUpArrowFunctionKey); break;
			case 'a': e_key(NSLeftArrowFunctionKey); break;
			case 's': e_key(NSDownArrowFunctionKey); break;
			case 'd': e_key(NSRightArrowFunctionKey); break;
			default: e_key(key); break;
		}
	}
	// NSLog(@"%@ %hu", [theEvent characters], [theEvent keyCode]);
    [self setNeedsDisplay:YES];
    return self;
}

- (BOOL)isFlipped {
	return YES;
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
