#import "GameController.h"

#import <appkit/Application.h>
#import <objc/NXStringTable.h>
#import <appkit/Panel.h>
#import <appkit/Text.h>
#import <appkit/Button.h>
#import <appkit/publicWraps.h>

#import <stdio.h>

@implementation GameController:Object


- init {
	fprintf(stderr, "Init\n");
	[super init];
	return self;
}

- appDidInit:sender {
	fprintf(stderr, "DidInit\n");
    	[[gameView window] makeKeyAndOrderFront:self];
	[[gameView window] makeFirstResponder:gameView];
	return self;
}
- windowWillClose:sender {
	fprintf(stderr, "WillClose\n");
	return [NXApp terminate:self];
}
- showInfoView:sender {
	return self;
}
- resetGame:sender {
	return self;
}

@end