#import <objc/Object.h>

#define VALUE_MAX_SIZE 5   // "2048\0"
#define PRKEY_MAX_SIZE 16  // "saveBoard_16"
#define PRVAL_MAX_SIZE 7   // "1000000"
#define SCORE_MAX_SIZE 16  // "Score: 999999"
#define STATE_MAX_SIZE 128 // "State on: <date>"

@interface GameController : Object {
	id gameInfo;
	id gameView;
}

+ (BOOL)saveState:(char *)str_state :(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose;
+ (BOOL)loadState:(char *)str_state :(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose;

- showGameInfo:sender;

- appDidInit:sender;
- windowWillClose:sender;

@end
