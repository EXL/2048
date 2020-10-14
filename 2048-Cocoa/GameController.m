//
//  GameController.m
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2001 __CompanyName__. All rights reserved.
//

#import "GameController.h"
#import "GameView.h"

@implementation GameController

+ (BOOL)saveState:(char *)str_state :(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose {
    // TODO: Not implemented.
    return YES;
}

+ (BOOL)loadState:(char *)str_state :(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose {
    // TODO: Not implemented.
    return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
	fprintf(stderr, "addDidInit\n");
	// [self prefReads];
        // TODO: Not implemented.
	//[[gameView window] setMiniwindowIcon:"icon48.tiff"];
	[[gameView window] makeKeyAndOrderFront:self];
	[[gameView window] makeFirstResponder:gameView];
	[gameView updateMenus];
	//return self;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
	return YES;
}

/*
- (void)windowWillClose:(NSNotification *)aNotification {
	fprintf(stderr, "windowWillClose\n");
	[NSApp terminate:self];
        //return self;
}
*/

//- (void)prefReads {
//
//	[gameView setNeedsDisplay:YES];
//}

@end
