#import <objc/Object.h>

@interface GameController : Object {
	// id infoView;
	id gameView;
}

- showInfoView:sender;

- appDidInit:sender;
- windowWillClose:sender;

- prefReadRectType;

@end
