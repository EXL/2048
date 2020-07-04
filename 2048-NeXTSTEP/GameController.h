#import <objc/Object.h>

@interface GameController:Object {
	// id infoView;
	id gameView;
}

- appDidInit:sender;
- windowWillClose:sender;

- showInfoView:sender;

@end
