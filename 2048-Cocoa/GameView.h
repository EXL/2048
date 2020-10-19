//
//  GameView.h
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2020 EXL. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GameView : NSView {
	id menuItemTiles;
	id menuItemBackground;

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

- (BOOL)isFlipped;

- (void)drawTile:(NSRect)bounds :(int)value :(int)x :(int)y;
- (void)drawFinal:(NSRect)bounds;

- (NSBezierPath *)roundedRect:(NSRect)rect :(int)rad;
- (NSDictionary *)textAttributes:(NSFont *)font :(NSColor *)color;
- (NSColor *)getColor:(unsigned int)color :(float)alpha;

- (id)menuReset:(id)sender;
- (id)menuTiles:(id)sender;
- (id)menuBackground:(id)sender;
- (id)menuSave:(id)sender;
- (id)menuLoad:(id)sender;

- (void)setRoundedTiles:(BOOL)value;
- (void)setShowBackground:(BOOL)value;

- (void)updateMenus;
- (void)showAlertSheet:(NSString *)title :(NSString *)information;

@end
