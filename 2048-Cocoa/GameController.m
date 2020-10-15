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

+ (NSString *)saveState:(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose {
	int i;
	NSUserDefaults *settings = [NSUserDefaults standardUserDefaults];
	NSString *strState = [NSString stringWithFormat:NSLocalizedString(@"GMStateFMT", @"State on: %@"), [[NSDate date] description]];
	[settings setObject:strState forKey:@"saveDate"];
	for (i = 0; i < boardSize; ++i)
		[settings setObject:[NSNumber numberWithInt:board[i]] forKey:[NSString stringWithFormat:@"saveBoard_%d", i]];
	[settings setObject:[NSNumber numberWithInt:score] forKey:@"saveScore"];
	[settings setObject:[NSNumber numberWithInt:win] forKey:@"saveWin"];
	[settings setObject:[NSNumber numberWithInt:lose] forKey:@"saveLose"];
	return ([settings synchronize]) ? strState : nil;
}

+ (NSString *)loadState:(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose {
	int i;
	NSNumber *value = nil;
	NSUserDefaults *settings = [NSUserDefaults standardUserDefaults];
	NSString *strState = [settings objectForKey:@"saveDate"];
	for (i = 0; i < boardSize; ++i) {
		value = [settings objectForKey:[NSString stringWithFormat:@"saveBoard_%d", i]];
		if (!value) return nil;
		board[i] = [value intValue];
	}
	value = [settings objectForKey:@"saveScore"];
	if (!value) return nil;
	*score = [value intValue];
	value = [settings objectForKey:@"saveWin"];
	if (!value) return nil;
	*win = [value intValue];
	value = [settings objectForKey:@"saveLose"];
	if (!value) return nil;
	*lose = [value intValue];
	return strState;
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
