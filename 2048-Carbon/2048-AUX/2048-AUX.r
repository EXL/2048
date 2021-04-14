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

data 'ICN#' (128) {
	$"1FFF FFF8 7FFF FFFE 7000 000E E000 0007"            /* .ˇˇ¯.ˇˇ˛p...‡... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* ¿...¿...¿...¿... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* ¿...¿...¿...¿... */
	$"CE3C 18F3 D366 399B C366 399B C366 58F3"            /* Œ<.Û”f9õ√f9õ√fXÛ */
	$"C666 D8B3 CC66 FD9B CC66 199B DF3C 18F3"            /* ∆fÿ≥Ãf˝õÃf.õﬂ<.Û */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* ¿...¿...¿...¿... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* ¿...¿...¿...¿... */
	$"E000 0007 7000 000E 7FFF FFFE 1FFF FFF8"            /* ‡...p....ˇˇ˛.ˇˇ¯ */
	$"1FFF FFF8 7FFF FFFE 7FFF FFFE FFFF FFFF"            /* .ˇˇ¯.ˇˇ˛.ˇˇ˛ˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF 7FFF FFFE 7FFF FFFE 1FFF FFF8"            /* ˇˇˇˇ.ˇˇ˛.ˇˇ˛.ˇˇ¯ */
};

data 'icl8' (128) {
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ...ˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇ... */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* .ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ. */
	$"00FF FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* .ˇˇˇMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF FF00"            /* MMMMMMMMMMMMˇˇˇ. */
	$"FFFF FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇˇMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF FFFF"            /* MMMMMMMMMMMMMˇˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D DEDE DE4D 4D4D DEDE DEDE 4D4D"            /* ˇˇMMﬁﬁﬁMMMﬁﬁﬁﬁMM */
	$"4D4D 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MMMﬁﬁMMMﬁﬁﬁﬁMMˇˇ */
	$"FFFF 4DDE 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ˇˇMﬁMMﬁﬁMﬁﬁMMﬁﬁM */
	$"4D4D DEDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMﬁﬁﬁMMﬁﬁMMﬁﬁMˇˇ */
	$"FFFF 4D4D 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ˇˇMMMMﬁﬁMﬁﬁMMﬁﬁM */
	$"4D4D DEDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMﬁﬁﬁMMﬁﬁMMﬁﬁMˇˇ */
	$"FFFF 4D4D 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ˇˇMMMMﬁﬁMﬁﬁMMﬁﬁM */
	$"4DDE 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MﬁMﬁﬁMMMﬁﬁﬁﬁMMˇˇ */
	$"FFFF 4D4D 4DDE DE4D 4DDE DE4D 4DDE DE4D"            /* ˇˇMMMﬁﬁMMﬁﬁMMﬁﬁM */
	$"DEDE 4DDE DE4D 4D4D DE4D DEDE 4D4D FFFF"            /* ﬁﬁMﬁﬁMMMﬁMﬁﬁMMˇˇ */
	$"FFFF 4D4D DEDE 4D4D 4DDE DE4D 4DDE DE4D"            /* ˇˇMMﬁﬁMMMﬁﬁMMﬁﬁM */
	$"DEDE DEDE DEDE 4DDE DE4D 4DDE DE4D FFFF"            /* ﬁﬁﬁﬁﬁﬁMﬁﬁMMﬁﬁMˇˇ */
	$"FFFF 4D4D DEDE 4D4D 4DDE DE4D 4DDE DE4D"            /* ˇˇMMﬁﬁMMMﬁﬁMMﬁﬁM */
	$"4D4D 4DDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMMﬁﬁMMﬁﬁMMﬁﬁMˇˇ */
	$"FFFF 4DDE DEDE DEDE 4D4D DEDE DEDE 4D4D"            /* ˇˇMﬁﬁﬁﬁﬁMMﬁﬁﬁﬁMM */
	$"4D4D 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MMMﬁﬁMMMﬁﬁﬁﬁMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMˇˇ */
	$"FFFF FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ˇˇˇMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF FFFF"            /* MMMMMMMMMMMMMˇˇˇ */
	$"00FF FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* .ˇˇˇMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF FF00"            /* MMMMMMMMMMMMˇˇˇ. */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* .ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ. */
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ...ˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"            /* ˇˇˇˇˇˇˇˇˇˇˇˇˇ... */
};

data 'icl4' (128) {
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"            /* ..ˇˇˇˇˇˇˇˇˇˇˇˇ. */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"            /* .ˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"            /* .ˇààààààààààààˇ */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"            /* ˇ¯ààààààààààààèˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 0008 8800 0088 8880 0888 0000 88FF"            /* ˇà..à..ààÄ.à..àˇ */
	$"FF80 8800 8008 8008 8800 0880 0880 08FF"            /* ˇÄà.Ä.Ä.à..Ä.Ä.ˇ */
	$"FF88 8800 8008 8008 8800 0880 0880 08FF"            /* ˇàà.Ä.Ä.à..Ä.Ä.ˇ */
	$"FF88 8800 8008 8008 8080 0888 0000 88FF"            /* ˇàà.Ä.Ä.ÄÄ.à..àˇ */
	$"FF88 8008 8008 8008 0080 0888 0800 88FF"            /* ˇàÄ.Ä.Ä..Ä.à..àˇ */
	$"FF88 0088 8008 8008 0000 0080 0880 08FF"            /* ˇà.àÄ.Ä....Ä.Ä.ˇ */
	$"FF88 0088 8008 8008 8880 0880 0880 08FF"            /* ˇà.àÄ.Ä.àÄ.Ä.Ä.ˇ */
	$"FF80 0000 8800 0088 8880 0888 0000 88FF"            /* ˇÄ..à..ààÄ.à..àˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ˇààààààààààààààˇ */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"            /* ˇ¯ààààààààààààèˇ */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"            /* .ˇààààààààààààˇ */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"            /* .ˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"            /* ..ˇˇˇˇˇˇˇˇˇˇˇˇ. */
};

data 'ics#' (128) {
	$"3FFC 6006 C003 8001 8C19 9839 B079 BC59"            /* ?¸`.¿.Ä.å.ò9∞yºY */
	$"B6FD B619 9C19 8001 8001 C003 6006 3FFC"            /* ∂˝∂.ú.Ä.Ä.¿.`.?¸ */
	$"3FFC 7FFE FFFF FFFF FFFF FFFF FFFF FFFF"            /* ?¸.˛ˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF 7FFE 3FFC"            /* ˇˇˇˇˇˇˇˇˇˇˇˇ.˛?¸ */
};

data 'ics4' (128) {
	$"00FF FFFF FFFF FF00 0FF8 8888 8888 8FF0"            /* .ˇˇˇˇˇˇ..¯ààààè */
	$"FF88 8888 8888 88FF F888 8888 8888 888F"            /* ˇààààààˇ¯ààààààè */
	$"F888 0088 8880 088F F880 0888 8800 088F"            /* ¯à.ààÄ.è¯Ä.àà..è */
	$"F800 8888 8000 088F F800 0088 8080 088F"            /* ¯.ààÄ..è¯..àÄÄ.è */
	$"F800 8008 0000 008F F800 8008 8880 088F"            /* ¯.Ä....è¯.Ä.àÄ.è */
	$"F880 0088 8880 088F F888 8888 8888 888F"            /* ¯Ä.ààÄ.è¯ààààààè */
	$"F888 8888 8888 888F FF88 8888 8888 88FF"            /* ¯ààààààèˇààààààˇ */
	$"0FF8 8888 8888 8FF0 00FF FFFF FFFF FF00"            /* .¯ààààè.ˇˇˇˇˇˇ. */
};

data 'ics8' (128) {
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"            /* ..ˇˇˇˇˇˇˇˇˇˇˇˇ.. */
	$"00FF FF4D 4D4D 4D4D 4D4D 4D4D 4DFF FF00"            /* .ˇˇMMMMMMMMMMˇˇ. */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* ˇˇMMMMMMMMMMMMˇˇ */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* ˇMMMMMMMMMMMMMMˇ */
	$"FF4D 4D4D DEDE 4D4D 4D4D 4DDE DE4D 4DFF"            /* ˇMMMﬁﬁMMMMMﬁﬁMMˇ */
	$"FF4D 4DDE DE4D 4D4D 4D4D DEDE DE4D 4DFF"            /* ˇMMﬁﬁMMMMMﬁﬁﬁMMˇ */
	$"FF4D DEDE 4D4D 4D4D 4DDE DEDE DE4D 4DFF"            /* ˇMﬁﬁMMMMMﬁﬁﬁﬁMMˇ */
	$"FF4D DEDE DEDE 4D4D 4DDE 4DDE DE4D 4DFF"            /* ˇMﬁﬁﬁﬁMMMﬁMﬁﬁMMˇ */
	$"FF4D DEDE 4DDE DE4D DEDE DEDE DEDE 4DFF"            /* ˇMﬁﬁMﬁﬁMﬁﬁﬁﬁﬁﬁMˇ */
	$"FF4D DEDE 4DDE DE4D 4D4D 4DDE DE4D 4DFF"            /* ˇMﬁﬁMﬁﬁMMMMﬁﬁMMˇ */
	$"FF4D 4DDE DEDE 4D4D 4D4D 4DDE DE4D 4DFF"            /* ˇMMﬁﬁﬁMMMMMﬁﬁMMˇ */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* ˇMMMMMMMMMMMMMMˇ */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* ˇMMMMMMMMMMMMMMˇ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* ˇˇMMMMMMMMMMMMˇˇ */
	$"00FF FF4D 4D4D 4D4D 4D4D 4D4D 4DFF FF00"            /* .ˇˇMMMMMMMMMMˇˇ. */
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"            /* ..ˇˇˇˇˇˇˇˇˇˇˇˇ.. */
};

data 'PICT' (128, "About Bar") {
	$"00A4 0000 0000 0004 00C8 0011 02FF 0C00"            /* .§.......»...ˇ.. */
	$"FFFF FFFF 0000 0000 0000 0000 00C8 0000"            /* ˇˇˇˇ.........».. */
	$"0004 0000 0000 0000 0001 000A 0000 0000"            /* ................ */
	$"0258 0320 0098 801A 0000 0000 0004 00C8"            /* .X. .òÄ........» */
	$"0000 0000 0000 0000 0048 0000 0048 0000"            /* .........H...H.. */
	$"0000 0001 0001 0001 0000 0000 3ECB CFD4"            /* ............>Àœ‘ */
	$"0000 0000 0000 0D6F 0000 0001 0000 FFFF"            /* ......¬o......ˇˇ */
	$"FFFF FFFF 0001 0000 0000 0000 0000 0000"            /* ˇˇˇˇ............ */
	$"0004 00C8 0000 0000 0004 00C8 0000 04E8"            /* ...».......»...Ë */
	$"FF00 0004 E8FF 0000 04E8 FF00 0004 E8FF"            /* ˇ...Ëˇ...Ëˇ...Ëˇ */
	$"0000 00FF"                                          /* ...ˇ */
};

data 'FREF' (128) {
	$"4150 504C 0000 00"                                  /* APPL... */
};

data 'AUX ' (0, "Owner resource") {
	$"0032 3034 382D 4155 5820 5369 676E 6174"            /* .2048-AUX Signat */
	$"7572 65"                                            /* ure */
};

data 'BNDL' (128) {
	$"4155 5820 0000 0001 4652 4546 0000 0000"            /* AUX ....FREF.... */
	$"0080 4943 4E23 0000 0000 0080"                      /* .ÄICN#.....Ä */
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
