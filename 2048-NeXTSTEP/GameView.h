#import <appkit/View.h>

@interface GameView:View {
	id smallFont;
	id middleFont;
	id normalFont;
	id largeFont;
	BOOL firstPaint;
}

- initFrame:(const NXRect *)form;
//- init;
- free;

//- (BOOL)acceptsFirstResponder;
//- (BOOL)acceptsFirstMouse;
//- (BOOL)performKeyEquivalent:(NXEvent *)theEvent;
//- (BOOL)shouldDelayWindowOrderingForEvent:(NXEvent *)anEvent;

- drawSelf:(const NXRect *)rects :(int)rectCount;
//- drawBackground:(NXRect *)rect;
- keyDown:(NXEvent *)theEvent;
- (void)drawTile:(int)value :(int)x :(int)y;
- (void)drawFinal;

//- windowDidBecomeKey:sender;

//- close;

//- windowWillClosed:sender;

@end