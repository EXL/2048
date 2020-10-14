//
//  GameView.h
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2001 __CompanyName__. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface GameView : NSView {
    NSFont *smallFont;
    NSFont *middleFont;
    NSFont *normalFont;
    NSFont *largeFont;

    BOOL roundedTiles;
    BOOL showBackground;
}

- (id)initWithFrame:(NSRect)frame;
- (void)drawRect:(NSRect)rect;

- (id)keyDown:(NSEvent *)event;
//- (void)cancelOperation:(id)sender;

- (BOOL)isFlipped;

- (void)drawTile:(NSRect)bounds :(int)value :(int)x :(int)y;
- (void)drawFinal:(NSRect)bounds;

- (NSBezierPath *)roundedRect:(NSRect)rect :(int)rad;
- (NSDictionary *)textAttributes:(NSFont *)font :(NSColor *)color;
- (NSColor *)getColor:(unsigned int)color :(float)alpha;

- (id)resetGame:(id)sender;
- (id)setRoundedTiles:(id)sender;
- (id)setRectangleTiles:(id)sender;
- (id)disableBackground:(id)sender;
- (id)enableBackground:(id)sender;

- (id)save:(id)sender;
- (id)load:(id)sender;

@end
