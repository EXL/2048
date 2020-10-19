//
//  GameController.h
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2020 EXL. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GameController : NSObject {
	id gameView;
}

+ (NSString *)saveState:(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose;
+ (NSString *)loadState:(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose;

- (void)applicationDidFinishLaunching:(NSNotification *)notification;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;

@end
