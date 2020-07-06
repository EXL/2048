#import <appkit/View.h>

@interface GameView : View {
	id smallFont;
	id middleFont;
	id normalFont;
	id largeFont;

	BOOL roundedTiles;
}

- initFrame:(const NXRect *)frameRect;
- keyDown:(const NXEvent *)theEvent;
- drawSelf:(const NXRect *)rects :(int)rectCount;

- (void)drawTile:(int)value :(int)x :(int)y;
- (void)drawFinal;

- resetGame:sender;
- setRoundedTiles:sender;
- setRectangleTiles:sender;

- save:sender;
- load:sender;

@end
