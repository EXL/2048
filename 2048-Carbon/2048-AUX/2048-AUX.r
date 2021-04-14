/*
 * Decompile resource file commands for Bourne Shell:
 *  $ /mac/bin/derez 2048-AUX.rsrc > Out.r
 *  $ /mac/bin/derez -i /mac/lib/rincludes 2048-AUX.rsrc /mac/lib/rincludes/types.r
 */

#include "types.r"

resource 'WIND' (128, "2048-AUX Window") {
	{ 50, 50, 400 + 50, 340 + 50 },
	documentProc, visible, goAway, 0x0, "2048-AUX"
};

resource 'MENU' (128, "Apple Menu", preload) {
	128, textMenuProc, 0x7FFFFFFD, enabled, apple,          /* '0b1111111111111111111111111111101' */
	{
		"About 2048-AUX\311", noIcon, noKey, noMark, plain; /* ... */
		"-", noIcon, noKey, noMark, plain;
	}
};

resource 'MENU' (129, "Game Menu", preload) {
	129, textMenuProc, 0x7FFFFFF7, enabled, "Game",         /* '0b1111111111111111111111111110111' */
	{
		"Reset", noIcon, "R", noMark, plain;
		"Tiles", noIcon, hierarchicalMenu, "\0x82", plain;  /* 130 */
		"Color", noIcon, hierarchicalMenu, "\0x83", plain;  /* 131 */
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
		"Color Device", noIcon, noKey, check, plain;
	}
};

resource 'ALRT' (128, "About 2048-AUX Dialog", purgeable) {
	{ 70, 40, 170 + 70, 360 + 40 },
	128,
	{
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1,
		OK, visible, sound1
	}
};

resource 'DITL' (128) {
	 {
/* 1 */ { 135, 290, 135 + 20, 290 + 55 },
		Button {
			enabled,
			"OK"
		};
/* 2 */ { 7, 60, 7 + 20, 60 + 200 },
		StaticText {
			disabled,
			"2048-AUX"
		};
/* 3 */ { 30, 60, 30 + 40, 60 + 280 },
		StaticText {
			disabled,
			"Simple implementation of \"2048\" logic game for Apple A/UX operation system."
		};
/* 4 */ { 80, 60, 80 + 20, 60 + 280 },
		StaticText {
			disabled,
			"Version: 1.0, 14-Apr-2021"
		};
/* 5 */ { 98, 60, 98 + 20, 60 + 280 },
		StaticText {
			disabled,
			"Sources: https://github.com/EXL/2048"
		};
/* 6 */ { 116, 60, 116 + 20, 60 + 200 },
		StaticText {
			disabled,
			"Copyright \251 EXL, 2021"                      /* (c) */
		};
	}
};

resource 'ICN#' (128) {
	{
		$"1FFF FFF8 7FFF FFFE 7000 000E E000 0007"          /* ........p....... */
		$"C000 0003 C000 0003 C000 0003 C000 0003"          /* À...À...À...À... */
		$"C000 0003 C000 0003 C000 0003 C000 0003"          /* À...À...À...À... */
		$"CE3C 18F3 D366 399B C366 399B C366 58F3"          /* Î<..Óf9›Ãf9›ÃfX. */
		$"C666 D8B3 CC66 FD9B CC66 199B DF3C 18F3"          /* ÆfØ³Ìf.›Ìf.›.<.. */
		$"C000 0003 C000 0003 C000 0003 C000 0003"          /* À...À...À...À... */
		$"C000 0003 C000 0003 C000 0003 C000 0003"          /* À...À...À...À... */
		$"E000 0007 7000 000E 7FFF FFFE 1FFF FFF8",         /* ....p........... */
		$"1FFF FFF8 7FFF FFFE 7FFF FFFE FFFF FFFF"          /* ................ */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"          /* ................ */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"          /* ................ */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"          /* ................ */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"          /* ................ */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"          /* ................ */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"          /* ................ */
		$"FFFF FFFF 7FFF FFFE 7FFF FFFE 1FFF FFF8"          /* ................ */
	}
};

resource 'icl8' (128) {
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"              /* ................ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"              /* ................ */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"              /* ................ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"              /* ................ */
	$"00FF FFFF 9595 9595 9595 9595 9595 9595"              /* ....•••••••••••• */
	$"9595 9595 9595 9595 9595 9595 FFFF FF00"              /* ••••••••••••.... */
	$"FFFF FF95 9595 9595 9595 9595 9595 9595"              /* ...••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 95FF FFFF"              /* •••••••••••••... */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 DDDD DD95 9595 DDDD DDDD 9595"              /* ..••...•••....•• */
	$"9595 95DD DD95 9595 DDDD DDDD 9595 FFFF"              /* •••..•••....••.. */
	$"FFFF 95DD 9595 DDDD 95DD DD95 95DD DD95"              /* ..•.••..•..••..• */
	$"9595 DDDD DD95 95DD DD95 95DD DD95 FFFF"              /* ••...••..••..•.. */
	$"FFFF 9595 9595 DDDD 95DD DD95 95DD DD95"              /* ..••••..•..••..• */
	$"9595 DDDD DD95 95DD DD95 95DD DD95 FFFF"              /* ••...••..••..•.. */
	$"FFFF 9595 9595 DDDD 95DD DD95 95DD DD95"              /* ..••••..•..••..• */
	$"95DD 95DD DD95 9595 DDDD DDDD 9595 FFFF"              /* •.•..•••....••.. */
	$"FFFF 9595 95DD DD95 95DD DD95 95DD DD95"              /* ..•••..••..••..• */
	$"DDDD 95DD DD95 9595 DD95 DDDD 9595 FFFF"              /* ..•..•••.•..••.. */
	$"FFFF 9595 DDDD 9595 95DD DD95 95DD DD95"              /* ..••..•••..••..• */
	$"DDDD DDDD DDDD 95DD DD95 95DD DD95 FFFF"              /* ......•..••..•.. */
	$"FFFF 9595 DDDD 9595 95DD DD95 95DD DD95"              /* ..••..•••..••..• */
	$"9595 95DD DD95 95DD DD95 95DD DD95 FFFF"              /* •••..••..••..•.. */
	$"FFFF 95DD DDDD DDDD 9595 DDDD DDDD 9595"              /* ..•.....••....•• */
	$"9595 95DD DD95 9595 DDDD DDDD 9595 FFFF"              /* •••..•••....••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF 9595 9595 9595 9595 9595 9595 9595"              /* ..•••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 9595 FFFF"              /* ••••••••••••••.. */
	$"FFFF FF95 9595 9595 9595 9595 9595 9595"              /* ...••••••••••••• */
	$"9595 9595 9595 9595 9595 9595 95FF FFFF"              /* •••••••••••••... */
	$"00FF FFFF 9595 9595 9595 9595 9595 9595"              /* ....•••••••••••• */
	$"9595 9595 9595 9595 9595 9595 FFFF FF00"              /* ••••••••••••.... */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"              /* ................ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"              /* ................ */
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"              /* ................ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"              /* ................ */
};

resource 'icl4' (128) {
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"              /* ................ */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"              /* ................ */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"              /* ..ˆˆˆˆˆˆˆˆˆˆˆˆ.. */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"              /* ..ˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 AAA8 88AA AA88 888A A888 AAAA 88FF"              /* .ˆª¨ˆªªˆˆŠ¨ˆªªˆ. */
	$"FF8E 88AA 8AA8 8AA8 88AA A88A A88A A8FF"              /* .ŽˆªŠ¨Š¨ˆª¨Š¨Š¨. */
	$"FF88 88AA 8AA8 8AA8 88AA A88A A88A A8FF"              /* .ˆˆªŠ¨Š¨ˆª¨Š¨Š¨. */
	$"FF88 88AA 8AA8 8AA8 8A8A A888 AAAA 88FF"              /* .ˆˆªŠ¨Š¨ŠŠ¨ˆªªˆ. */
	$"FF88 8AA8 8AA8 8AA8 AA8A A888 A8AA 88FF"              /* .ˆŠ¨Š¨Š¨ªŠ¨ˆ¨ªˆ. */
	$"FF88 AA88 8AA8 8AA8 AAAA AA8A A88A A8FF"              /* .ˆªˆŠ¨Š¨ªªªŠ¨Š¨. */
	$"FF88 AA88 8AA8 8AA8 888A A88A A88A A8FF"              /* .ˆªˆŠ¨Š¨ˆŠ¨Š¨Š¨. */
	$"FF8A AAAA 88AA AA88 888A A888 AAAA 88FF"              /* .ŠªªˆªªˆˆŠ¨ˆªªˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"              /* .ˆˆˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"              /* ..ˆˆˆˆˆˆˆˆˆˆˆˆ. */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"              /* ..ˆˆˆˆˆˆˆˆˆˆˆˆ.. */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"              /* ................ */
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"              /* ................ */
};

resource 'ics#' (128) {
	{
		$"3FFC 6006 C003 8001 8C19 9839 B079 BC59"          /* ?.`.À.€.Œ.˜9°y¼Y */
		$"B6FD B619 9C19 8001 8001 C003 6006 3FFC",         /* ¶.¶.œ.€.€.À.`.?. */
		$"3FFC 7FFE FFFF FFFF FFFF FFFF FFFF FFFF"          /* ?............... */
		$"FFFF FFFF FFFF FFFF FFFF FFFF 7FFE 3FFC"          /* ..............?. */
	}
};

resource 'ics4' (128) {
	$"00FF FFFF FFFF FF00 0FF8 8888 8888 8FF0"              /* ..........ˆˆˆˆ. */
	$"FF88 8888 8888 88FF F888 8888 8888 888F"              /* .ˆˆˆˆˆˆ..ˆˆˆˆˆˆ */
	$"F888 AA88 888A A88F F88A A888 88AA A88F"              /* .ˆªˆˆŠ¨.Š¨ˆˆª¨ */
	$"F8AA 8888 8AAA A88F F8AA AA88 8A8A A88F"              /* .ªˆˆŠª¨.ªªˆŠŠ¨ */
	$"F8AA 8AA8 AAAA AA8F F8AA 8AA8 888A A88F"              /* .ªŠ¨ªªª.ªŠ¨ˆŠ¨ */
	$"F88A AA88 888A A88F F888 8888 8888 888F"              /* .ŠªˆˆŠ¨.ˆˆˆˆˆˆ */
	$"F888 8888 8888 888F FF88 8888 8888 88FF"              /* .ˆˆˆˆˆˆ.ˆˆˆˆˆˆ. */
	$"0FF8 8888 8888 8FF0 00FF FFFF FFFF FF00"              /* ..ˆˆˆˆ......... */
};

resource 'ics8' (128) {
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"              /* ................ */
	$"00FF FF95 9595 9595 9595 9595 95FF FF00"              /* ...••••••••••... */
	$"FFFF 9595 9595 9595 9595 9595 9595 FFFF"              /* ..••••••••••••.. */
	$"FF95 9595 9595 9595 9595 9595 9595 95FF"              /* .••••••••••••••. */
	$"FF95 9595 DDDD 9595 9595 95DD DD95 95FF"              /* .•••..•••••..••. */
	$"FF95 95DD DD95 9595 9595 DDDD DD95 95FF"              /* .••..•••••...••. */
	$"FF95 DDDD 9595 9595 95DD DDDD DD95 95FF"              /* .•..•••••....••. */
	$"FF95 DDDD DDDD 9595 95DD 95DD DD95 95FF"              /* .•....•••.•..••. */
	$"FF95 DDDD 95DD DD95 DDDD DDDD DDDD 95FF"              /* .•..•..•......•. */
	$"FF95 DDDD 95DD DD95 9595 95DD DD95 95FF"              /* .•..•..••••..••. */
	$"FF95 95DD DDDD 9595 9595 95DD DD95 95FF"              /* .••...•••••..••. */
	$"FF95 9595 9595 9595 9595 9595 9595 95FF"              /* .••••••••••••••. */
	$"FF95 9595 9595 9595 9595 9595 9595 95FF"              /* .••••••••••••••. */
	$"FFFF 9595 9595 9595 9595 9595 9595 FFFF"              /* ..••••••••••••.. */
	$"00FF FF95 9595 9595 9595 9595 95FF FF00"              /* ...••••••••••... */
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"              /* ................ */
};

resource 'FREF' (128) {
	'APPL', 0, ""
};

resource 'BNDL' (128) {
	'AUX ', 0,
	{
		'FREF', { 0, 128 },
		'ICN#', { 0, 128 }
	}
};

data 'AUX ' (0, "Owner resource") {
	$"1300 3230 3438 2D41 5558 2053 6967 6E61"              /* ..2048-AUX Signa */
	$"7475 7265"                                            /* ture */
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
	1024 * 1024,                                            /* Preferred Memory Size. */
	1024 * 1024                                             /* Minimum Memory Size. */
};
