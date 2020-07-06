#import "GameController.h"
#import "GameView.h"

#import <foundation/NSDate.h>

#import <appkit/appkit.h>
#import <appkit/Application.h>

@implementation GameController : Object

+ (BOOL)saveState:(char *)str_state :(const int *)board :(int)boardSize :(int)score :(int)win :(int)lose {
	int i, done;
	char str_score[PRVAL_MAX_SIZE] = { '\0' }, str_win[PRVAL_MAX_SIZE] = { '\0' }, str_lose[PRVAL_MAX_SIZE] = { '\0' };
	const char *appName = [NXApp appName];
	const char *date = [[[NSDate date] description] cString];
	sprintf(str_state, "State on: %s", date);
	done = NXWriteDefault(appName, "saveDate", date);
	if (done != 1) return NO;
	for (i = 0; i < boardSize; ++i) {
		char str_value[VALUE_MAX_SIZE] = { '\0' }, prefKey[PRKEY_MAX_SIZE] = { '\0' };
		sprintf(str_value, "%d", board[i]);
		sprintf(prefKey, "saveBoard_%d", i);
		done = NXWriteDefault(appName, prefKey, str_value);
		if (done != 1) return NO;
	}
	sprintf(str_score, "%d", score);
	sprintf(str_win, "%d", win);
	sprintf(str_lose, "%d", lose);
	done = NXWriteDefault(appName, "saveScore", str_score);
	if (done != 1) return NO;
	done = NXWriteDefault(appName, "saveWin", str_win);
	if (done != 1) return NO;
	done = NXWriteDefault(appName, "saveLose", str_lose);
	if (done != 1) return NO;
	return YES;
}

+ (BOOL)loadState:(char *)str_state :(int *)board :(int)boardSize :(int *)score :(int *)win :(int *)lose {
	int i;
	const char *appName = [NXApp appName];
	const char *prefValue = NXGetDefaultValue(appName, "saveDate");
	if (!prefValue) return NO;
	sprintf(str_state, "State on: %s", prefValue);
	for (i = 0; i < boardSize; ++i) {
		char prefKey[PRKEY_MAX_SIZE] = { '\0' };
		sprintf(prefKey, "saveBoard_%d", i);
		prefValue = NXGetDefaultValue(appName, prefKey);
		if (!prefValue) return NO;
		board[i] = atoi(prefValue);
	}
	prefValue = NXGetDefaultValue(appName, "saveScore");
	if (!prefValue) return NO;
	*score = atoi(prefValue);
	prefValue = NXGetDefaultValue(appName, "saveWin");
	if (!prefValue) return NO;
	*win = atoi(prefValue);
	prefValue = NXGetDefaultValue(appName, "saveLose");
	if (!prefValue) return NO;
	*lose = atoi(prefValue);
	return YES;
}

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
	if (rectType && atoi(rectType))
		[gameView setRectangleTiles:self];
	return self;
}

@end
