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
		"Tiles", noIcon, hierarchicalMenu, "\0x82", plain; /* 130 */
		"Color", noIcon, hierarchicalMenu, "\0x83", plain; /* 131 */
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

resource 'ALRT' (128, "About 2048-AUX Dialog", purgeable) {
	{ 70, 40, 170 + 70, 360 + 40 },
	128,
	{
		OK, visible, silent,
		OK, visible, silent,
		OK, visible, silent,
		OK, visible, silent
	}
};

resource 'DITL' (128) {
	 {
/* 1 */ { 135, 290, 135 + 20, 290 + 55 },
		button {
			enabled,
			"OK"
		};
/* 2 */ { 7, 60, 7 + 20, 60 + 200 },
		staticText {
			disabled,
			"2048-AUX"
		};
/* 3 */ { 30, 60, 30 + 40, 60 + 280 },
		statictext {
			disabled,
			"Simple implementation of \"2048\" logic game for Apple A/UX operation system."
		};
/* 4 */ { 80, 60, 80 + 20, 60 + 280 },
		statictext {
			disabled,
			"Version: 1.0, 14-Apr-2021"
		};
/* 5 */ { 98, 60, 98 + 20, 60 + 280 },
		statictext {
			disabled,
			"Sources: https://github.com/EXL/2048"
		};
/* 6 */ { 116, 60, 116 + 20, 60 + 200 },
		statictext {
			disabled,
			"Copyright \251 EXL, 2021"
		};
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
