#import <appkit/View.h>

@interface GameView : View {
	id menuCellTiles;
	id menuCellBackground;

	BOOL roundedTiles;
	BOOL showBackground;
}

- initFrame:(const NXRect *)frameRect;
- keyDown:(const NXEvent *)theEvent;
- drawSelf:(const NXRect *)rects :(int)rectCount;

- (void)drawTile:(int)value :(int)x :(int)y;
- (void)drawFinal;

- resetGame:sender;
- setTiles:sender;
- setBackground:sender;

- save:sender;
- load:sender;

- (void)updateMenus;

@end
