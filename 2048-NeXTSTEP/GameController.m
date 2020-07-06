#import "GameController.h"
#import "GameView.h"

#import <appkit/appkit.h>
#import <appkit/Application.h>

@implementation GameController : Object

- appDidInit:sender {
	[self prefReadRectType];
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

- prefReadRectType {
	const char *rectType = NXGetDefaultValue([NXApp appName], "rectType");
	if (rectType != NULL && atoi(rectType))
		[gameView setRectangleTiles:self];
	return self;
}

@end
