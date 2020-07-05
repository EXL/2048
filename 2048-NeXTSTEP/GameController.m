#import "GameController.h"

#import <appkit/Application.h>
#import <appkit/View.h>

@implementation GameController : Object

- appDidInit:sender {
	[[gameView window] makeKeyAndOrderFront:self];
	[[gameView window] makeFirstResponder:gameView];
	return self;
}

- windowWillClose:sender {
	return [NXApp terminate:self];
}

- showInfoView:sender {
	// TODO: show info
	return self;
}

@end
