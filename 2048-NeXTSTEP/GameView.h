#import <appkit/View.h>

@interface GameView:View {
	id smallFont;
	id middleFont;
	id normalFont;
	id largeFont;
}

- initFrame:(const NXRect *)form;
- keyDown:(const NXEvent *)theEvent;
- drawSelf:(const NXRect *)rects:(int)rectCount;

- (void)drawTile:(int)value:(int)x:(int)y;
- (void)drawFinal;

- resetGame:sender;

@end