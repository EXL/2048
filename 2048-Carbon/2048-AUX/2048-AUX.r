#include "types.r"

resource 'WIND' (128, "2048-AUX") {
	{ 50, 50, 400 + 50, 340 + 50 },
	documentProc, visible, nogoaway, 0x0, "2048-AUX"
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
	32 * 1024,                   /* Preferred Memory Size. */
	32 * 1024                    /* Minimum Memory Size. */
};
