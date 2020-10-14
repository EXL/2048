//
//  GameController.m
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2020 EXL. All rights reserved.
//

#import "GameController.h"
#import "GameView.h"

@implementation GameController

+ (BOOL)saveState:(char *)str_state :(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose {
	// TODO: Not yet implemented.
	return YES;
}

+ (BOOL)loadState:(char *)str_state :(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose {
	// TODO: Not yet implemented.
	return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
	// TODO: [[gameView window] setMiniwindowIcon:"icon48.tiff"];
	[[gameView window] makeKeyAndOrderFront:self];
	[[gameView window] makeFirstResponder:gameView];
	[gameView updateMenus];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
	return YES;
}

@end
