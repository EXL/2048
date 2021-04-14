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
		"Some Colors", noIcon, noKey, check, plain;
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
	$"1FFF FFF8 7FFF FFFE 7000 000E E000 0007"            /* .ÿÿø.ÿÿþp...à... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* À...À...À...À... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* À...À...À...À... */
	$"CE3C 18F3 D366 399B C366 399B C366 58F3"            /* Î<.óÓf9›Ãf9›ÃfXó */
	$"C666 D8B3 CC66 FD9B CC66 199B DF3C 18F3"            /* ÆfØ³Ìfý›Ìf.›ß<.ó */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* À...À...À...À... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* À...À...À...À... */
	$"E000 0007 7000 000E 7FFF FFFE 1FFF FFF8"            /* à...p....ÿÿþ.ÿÿø */
	$"1FFF FFF8 7FFF FFFE 7FFF FFFE FFFF FFFF"            /* .ÿÿø.ÿÿþ.ÿÿþÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF 7FFF FFFE 7FFF FFFE 1FFF FFF8"            /* ÿÿÿÿ.ÿÿþ.ÿÿþ.ÿÿø */
};

data 'icl8' (128) {
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ...ÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿ... */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* .ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ. */
	$"00FF FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* .ÿÿÿMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF FF00"            /* MMMMMMMMMMMMÿÿÿ. */
	$"FFFF FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿÿMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF FFFF"            /* MMMMMMMMMMMMMÿÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D DEDE DE4D 4D4D DEDE DEDE 4D4D"            /* ÿÿMMÞÞÞMMMÞÞÞÞMM */
	$"4D4D 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MMMÞÞMMMÞÞÞÞMMÿÿ */
	$"FFFF 4DDE 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ÿÿMÞMMÞÞMÞÞMMÞÞM */
	$"4D4D DEDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMÞÞÞMMÞÞMMÞÞMÿÿ */
	$"FFFF 4D4D 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ÿÿMMMMÞÞMÞÞMMÞÞM */
	$"4D4D DEDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMÞÞÞMMÞÞMMÞÞMÿÿ */
	$"FFFF 4D4D 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ÿÿMMMMÞÞMÞÞMMÞÞM */
	$"4DDE 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MÞMÞÞMMMÞÞÞÞMMÿÿ */
	$"FFFF 4D4D 4DDE DE4D 4DDE DE4D 4DDE DE4D"            /* ÿÿMMMÞÞMMÞÞMMÞÞM */
	$"DEDE 4DDE DE4D 4D4D DE4D DEDE 4D4D FFFF"            /* ÞÞMÞÞMMMÞMÞÞMMÿÿ */
	$"FFFF 4D4D DEDE 4D4D 4DDE DE4D 4DDE DE4D"            /* ÿÿMMÞÞMMMÞÞMMÞÞM */
	$"DEDE DEDE DEDE 4DDE DE4D 4DDE DE4D FFFF"            /* ÞÞÞÞÞÞMÞÞMMÞÞMÿÿ */
	$"FFFF 4D4D DEDE 4D4D 4DDE DE4D 4DDE DE4D"            /* ÿÿMMÞÞMMMÞÞMMÞÞM */
	$"4D4D 4DDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMMÞÞMMÞÞMMÞÞMÿÿ */
	$"FFFF 4DDE DEDE DEDE 4D4D DEDE DEDE 4D4D"            /* ÿÿMÞÞÞÞÞMMÞÞÞÞMM */
	$"4D4D 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MMMÞÞMMMÞÞÞÞMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿMMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMMÿÿ */
	$"FFFF FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ÿÿÿMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF FFFF"            /* MMMMMMMMMMMMMÿÿÿ */
	$"00FF FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* .ÿÿÿMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF FF00"            /* MMMMMMMMMMMMÿÿÿ. */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* .ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ. */
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ...ÿÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"            /* ÿÿÿÿÿÿÿÿÿÿÿÿÿ... */
};

data 'icl4' (128) {
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"            /* ..ÿÿÿÿÿÿÿÿÿÿÿÿð. */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"            /* .ÿÿÿÿÿÿÿÿÿÿÿÿÿÿð */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"            /* .ÿˆˆˆˆˆˆˆˆˆˆˆˆÿð */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"            /* ÿøˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 0008 8800 0088 8880 0888 0000 88FF"            /* ÿˆ..ˆ..ˆˆ€.ˆ..ˆÿ */
	$"FF80 8800 8008 8008 8800 0880 0880 08FF"            /* ÿ€ˆ.€.€.ˆ..€.€.ÿ */
	$"FF88 8800 8008 8008 8800 0880 0880 08FF"            /* ÿˆˆ.€.€.ˆ..€.€.ÿ */
	$"FF88 8800 8008 8008 8080 0888 0000 88FF"            /* ÿˆˆ.€.€.€€.ˆ..ˆÿ */
	$"FF88 8008 8008 8008 0080 0888 0800 88FF"            /* ÿˆ€.€.€..€.ˆ..ˆÿ */
	$"FF88 0088 8008 8008 0000 0080 0880 08FF"            /* ÿˆ.ˆ€.€....€.€.ÿ */
	$"FF88 0088 8008 8008 8880 0880 0880 08FF"            /* ÿˆ.ˆ€.€.ˆ€.€.€.ÿ */
	$"FF80 0000 8800 0088 8880 0888 0000 88FF"            /* ÿ€..ˆ..ˆˆ€.ˆ..ˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ÿˆˆˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"            /* ÿøˆˆˆˆˆˆˆˆˆˆˆˆÿ */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"            /* .ÿˆˆˆˆˆˆˆˆˆˆˆˆÿð */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"            /* .ÿÿÿÿÿÿÿÿÿÿÿÿÿÿð */
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"            /* ..ÿÿÿÿÿÿÿÿÿÿÿÿð. */
};

data 'ics#' (128) {
	$"3FFC 6006 C003 8001 8C19 9839 B079 BC59"            /* ?ü`.À.€.Œ.˜9°y¼Y */
	$"B6FD B619 9C19 8001 8001 C003 6006 3FFC"            /* ¶ý¶.œ.€.€.À.`.?ü */
	$"3FFC 7FFE FFFF FFFF FFFF FFFF FFFF FFFF"            /* ?ü.þÿÿÿÿÿÿÿÿÿÿÿÿ */
	$"FFFF FFFF FFFF FFFF FFFF FFFF 7FFE 3FFC"            /* ÿÿÿÿÿÿÿÿÿÿÿÿ.þ?ü */
};

data 'ics4' (128) {
	$"00FF FFFF FFFF FF00 0FF8 8888 8888 8FF0"            /* .ÿÿÿÿÿÿ..øˆˆˆˆð */
	$"FF88 8888 8888 88FF F888 8888 8888 888F"            /* ÿˆˆˆˆˆˆÿøˆˆˆˆˆˆ */
	$"F888 0088 8880 088F F880 0888 8800 088F"            /* øˆ.ˆˆ€.ø€.ˆˆ.. */
	$"F800 8888 8000 088F F800 0088 8080 088F"            /* ø.ˆˆ€..ø..ˆ€€. */
	$"F800 8008 0000 008F F800 8008 8880 088F"            /* ø.€....ø.€.ˆ€. */
	$"F880 0088 8880 088F F888 8888 8888 888F"            /* ø€.ˆˆ€.øˆˆˆˆˆˆ */
	$"F888 8888 8888 888F FF88 8888 8888 88FF"            /* øˆˆˆˆˆˆÿˆˆˆˆˆˆÿ */
	$"0FF8 8888 8888 8FF0 00FF FFFF FFFF FF00"            /* .øˆˆˆˆð.ÿÿÿÿÿÿ. */
};

data 'ics8' (128) {
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"            /* ..ÿÿÿÿÿÿÿÿÿÿÿÿ.. */
	$"00FF FF4D 4D4D 4D4D 4D4D 4D4D 4DFF FF00"            /* .ÿÿMMMMMMMMMMÿÿ. */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* ÿÿMMMMMMMMMMMMÿÿ */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* ÿMMMMMMMMMMMMMMÿ */
	$"FF4D 4D4D DEDE 4D4D 4D4D 4DDE DE4D 4DFF"            /* ÿMMMÞÞMMMMMÞÞMMÿ */
	$"FF4D 4DDE DE4D 4D4D 4D4D DEDE DE4D 4DFF"            /* ÿMMÞÞMMMMMÞÞÞMMÿ */
	$"FF4D DEDE 4D4D 4D4D 4DDE DEDE DE4D 4DFF"            /* ÿMÞÞMMMMMÞÞÞÞMMÿ */
	$"FF4D DEDE DEDE 4D4D 4DDE 4DDE DE4D 4DFF"            /* ÿMÞÞÞÞMMMÞMÞÞMMÿ */
	$"FF4D DEDE 4DDE DE4D DEDE DEDE DEDE 4DFF"            /* ÿMÞÞMÞÞMÞÞÞÞÞÞMÿ */
	$"FF4D DEDE 4DDE DE4D 4D4D 4DDE DE4D 4DFF"            /* ÿMÞÞMÞÞMMMMÞÞMMÿ */
	$"FF4D 4DDE DEDE 4D4D 4D4D 4DDE DE4D 4DFF"            /* ÿMMÞÞÞMMMMMÞÞMMÿ */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* ÿMMMMMMMMMMMMMMÿ */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* ÿMMMMMMMMMMMMMMÿ */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* ÿÿMMMMMMMMMMMMÿÿ */
	$"00FF FF4D 4D4D 4D4D 4D4D 4D4D 4DFF FF00"            /* .ÿÿMMMMMMMMMMÿÿ. */
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"            /* ..ÿÿÿÿÿÿÿÿÿÿÿÿ.. */
};

data 'FREF' (128) {
	$"4150 504C 0000 00"                                  /* APPL... */
};

data 'MCW ' (0, "Owner resource") {
	$"0032 3034 382D 4155 5820 5369 676E 6174"            /* .2048-AUX Signat */
	$"7572 65"                                            /* ure */
};

data 'BNDL' (128) {
	$"4155 5820 0000 0001 4652 4546 0000 0000"            /* AUX ....FREF.... */
	$"0080 4943 4E23 0000 0000 0080"                      /* .€ICN#.....€ */
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
