//
//  GameController.h
//  2048-Cocoa
//
//  Created by happymac on Mon Oct 12 2020.
//  Copyright (c) 2001 __CompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GameController : NSObject {
    id gameView;
}

+ (BOOL)saveState:(char *)str_state :(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose;
+ (BOOL)loadState:(char *)str_state :(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose;

//-ÊappDidInit:sender;
- (id)windowWillClose:sender;

- (id)prefReads;

@end
