#include "types.r"

resource 'WIND' (128, "2048-AUX Window") {
	{ 50, 50, 400 + 50, 340 + 50 },
	documentProc, visible, goAway, 0x0, "2048-AUX"
};

resource 'MENU' (128, "Apple Menu", preload) {
	128, textMenuProc, allEnabled, enabled, apple,
	{
		"About 2048-AUX\311", noIcon, noKey, noMark, plain;
		"-", noIcon, noKey, noMark, plain;
	}
};

resource 'MENU' (129, "Game Menu", preload) {
	129, textMenuProc, allEnabled, enabled, "Game",
	{
		"Reset", noIcon, "R", noMark, plain;
		"Tiles", noIcon, hierarchicalMenu, "\0x82", plain;
		"Color", noIcon, hierarchicalMenu, "\0x83", plain;
		"Offscreen Mode", noIcon, "F", check, plain;
		"-", noIcon, noKey, noMark, plain;
		"Quit", noIcon, "Q", noMark, plain;
	}
};

resource 'MENU' (130, "Tiles Menu", preload) {
	130, textMenuProc, allEnabled, enabled, "Tiles",
	{
		"Rounded", noIcon, noKey, check, plain;
		"Rectangle", noIcon, noKey, noMark, plain;
	}
};

resource 'MENU' (131, "Color Menu", preload) {
	131, textMenuProc, allEnabled, enabled, "Color",
	{
		"Black & White", noIcon, noKey, noMark, plain;
		"16 Colors", noIcon, noKey, check, plain;
	}
};

resource 'SIZE' (-1) {
	dontSaveScreen,
	acceptSuspendResumeEvents,
	enableOptionSwitch,
	cannotBackground,
	multiFinderAware,
	backgroundAndForeground,
	getFrontClicks,
	ignoreChildDiedEvents,
	is32BitCompatible,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	1024 * 1024,                   /* Preferred Memory Size. */
	1024 * 1024                    /* Minimum Memory Size. */
};
