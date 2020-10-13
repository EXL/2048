//
//  GameView.h
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2001 __CompanyName__. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface GameView : NSView {
    id smallFont;
    id middleFont;
    id normalFont;
    id largeFont;

    BOOL roundedTiles;
    BOOL showBackground;
}

- (id)initWithFrame:(NSRect)frame;
- (void)drawRect:(NSRect)rect;
- (id)keyDown:(NSEvent)event;

- (void)drawTile:(int)value :(int)x :(int)y;
- (void)drawFinal;

- (id)resetGame:sender;
- (id)setRoundedTiles:sender;
- (id)setRectangleTiles:sender;
- (id)disableBackground:sender;
- (id)enableBackground:sender;

- (id)save:sender;
- (id)load:sender;

@end
