#import <objc/Object.h>

@interface GameController:Object {
	id infoView;
	id gameView;
}

//- doInit;
- init;
- appDidInit:sender;
- windowWillClose:sender;
- showInfoView:sender;
- resetGame:sender;

@end
