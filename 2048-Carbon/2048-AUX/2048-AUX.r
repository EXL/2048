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
	$"1FFF FFF8 7FFF FFFE 7000 000E E000 0007"            /* .���.���p...�... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* �...�...�...�... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* �...�...�...�... */
	$"CE3C 18F3 D366 399B C366 399B C366 58F3"            /* �<.��f9��f9��fX� */
	$"C666 D8B3 CC66 FD9B CC66 199B DF3C 18F3"            /* �fس�f���f.��<.� */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* �...�...�...�... */
	$"C000 0003 C000 0003 C000 0003 C000 0003"            /* �...�...�...�... */
	$"E000 0007 7000 000E 7FFF FFFE 1FFF FFF8"            /* �...p....���.��� */
	$"1FFF FFF8 7FFF FFFE 7FFF FFFE FFFF FFFF"            /* .���.���.������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ���������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ���������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ���������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ���������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ���������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ���������������� */
	$"FFFF FFFF 7FFF FFFE 7FFF FFFE 1FFF FFF8"            /* ����.���.���.��� */
};

data 'icl8' (128) {
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ...������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"            /* �������������... */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* .��������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"            /* ���������������. */
	$"00FF FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* .���MMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF FF00"            /* MMMMMMMMMMMM���. */
	$"FFFF FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ���MMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF FFFF"            /* MMMMMMMMMMMMM��� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D DEDE DE4D 4D4D DEDE DEDE 4D4D"            /* ��MM���MMM����MM */
	$"4D4D 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MMM��MMM����MM�� */
	$"FFFF 4DDE 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ��M�MM��M��MM��M */
	$"4D4D DEDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MM���MM��MM��M�� */
	$"FFFF 4D4D 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ��MMMM��M��MM��M */
	$"4D4D DEDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MM���MM��MM��M�� */
	$"FFFF 4D4D 4D4D DEDE 4DDE DE4D 4DDE DE4D"            /* ��MMMM��M��MM��M */
	$"4DDE 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* M�M��MMM����MM�� */
	$"FFFF 4D4D 4DDE DE4D 4DDE DE4D 4DDE DE4D"            /* ��MMM��MM��MM��M */
	$"DEDE 4DDE DE4D 4D4D DE4D DEDE 4D4D FFFF"            /* ��M��MMM�M��MM�� */
	$"FFFF 4D4D DEDE 4D4D 4DDE DE4D 4DDE DE4D"            /* ��MM��MMM��MM��M */
	$"DEDE DEDE DEDE 4DDE DE4D 4DDE DE4D FFFF"            /* ������M��MM��M�� */
	$"FFFF 4D4D DEDE 4D4D 4DDE DE4D 4DDE DE4D"            /* ��MM��MMM��MM��M */
	$"4D4D 4DDE DE4D 4DDE DE4D 4DDE DE4D FFFF"            /* MMM��MM��MM��M�� */
	$"FFFF 4DDE DEDE DEDE 4D4D DEDE DEDE 4D4D"            /* ��M�����MM����MM */
	$"4D4D 4DDE DE4D 4D4D DEDE DEDE 4D4D FFFF"            /* MMM��MMM����MM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ��MMMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* MMMMMMMMMMMMMM�� */
	$"FFFF FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* ���MMMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF FFFF"            /* MMMMMMMMMMMMM��� */
	$"00FF FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D"            /* .���MMMMMMMMMMMM */
	$"4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF FF00"            /* MMMMMMMMMMMM���. */
	$"00FF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* .��������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FF00"            /* ���������������. */
	$"0000 00FF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ...������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF FF00 0000"            /* �������������... */
};

data 'icl4' (128) {
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"            /* ..�������������. */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"            /* .��������������� */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"            /* .��������������� */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 0008 8800 0088 8880 0888 0000 88FF"            /* ��..�..���.�..�� */
	$"FF80 8800 8008 8008 8800 0880 0880 08FF"            /* ���.�.�.�..�.�.� */
	$"FF88 8800 8008 8008 8800 0880 0880 08FF"            /* ���.�.�.�..�.�.� */
	$"FF88 8800 8008 8008 8080 0888 0000 88FF"            /* ���.�.�.��.�..�� */
	$"FF88 8008 8008 8008 0080 0888 0800 88FF"            /* ���.�.�..�.�..�� */
	$"FF88 0088 8008 8008 0000 0080 0880 08FF"            /* ��.��.�....�.�.� */
	$"FF88 0088 8008 8008 8880 0880 0880 08FF"            /* ��.��.�.��.�.�.� */
	$"FF80 0000 8800 0088 8880 0888 0000 88FF"            /* ��..�..���.�..�� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FF88 8888 8888 8888 8888 8888 8888 88FF"            /* ���������������� */
	$"FFF8 8888 8888 8888 8888 8888 8888 8FFF"            /* ���������������� */
	$"0FFF 8888 8888 8888 8888 8888 8888 FFF0"            /* .��������������� */
	$"0FFF FFFF FFFF FFFF FFFF FFFF FFFF FFF0"            /* .��������������� */
	$"000F FFFF FFFF FFFF FFFF FFFF FFFF F000"            /* ..�������������. */
};

data 'ics#' (128) {
	$"3FFC 6006 C003 8001 8C19 9839 B079 BC59"            /* ?�`.�.�.�.�9�y�Y */
	$"B6FD B619 9C19 8001 8001 C003 6006 3FFC"            /* ���.�.�.�.�.`.?� */
	$"3FFC 7FFE FFFF FFFF FFFF FFFF FFFF FFFF"            /* ?�.������������� */
	$"FFFF FFFF FFFF FFFF FFFF FFFF 7FFE 3FFC"            /* ������������.�?� */
};

data 'ics4' (128) {
	$"00FF FFFF FFFF FF00 0FF8 8888 8888 8FF0"            /* .������..������� */
	$"FF88 8888 8888 88FF F888 8888 8888 888F"            /* ���������������� */
	$"F888 0088 8880 088F F880 0888 8800 088F"            /* ��.���.���.��..� */
	$"F800 8888 8000 088F F800 0088 8080 088F"            /* �.���..��..���.� */
	$"F800 8008 0000 008F F800 8008 8880 088F"            /* �.�....��.�.��.� */
	$"F880 0088 8880 088F F888 8888 8888 888F"            /* ��.���.��������� */
	$"F888 8888 8888 888F FF88 8888 8888 88FF"            /* ���������������� */
	$"0FF8 8888 8888 8FF0 00FF FFFF FFFF FF00"            /* .�������.������. */
};

data 'ics8' (128) {
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"            /* ..������������.. */
	$"00FF FF4D 4D4D 4D4D 4D4D 4D4D 4DFF FF00"            /* .��MMMMMMMMMM��. */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* ��MMMMMMMMMMMM�� */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* �MMMMMMMMMMMMMM� */
	$"FF4D 4D4D DEDE 4D4D 4D4D 4DDE DE4D 4DFF"            /* �MMM��MMMMM��MM� */
	$"FF4D 4DDE DE4D 4D4D 4D4D DEDE DE4D 4DFF"            /* �MM��MMMMM���MM� */
	$"FF4D DEDE 4D4D 4D4D 4DDE DEDE DE4D 4DFF"            /* �M��MMMMM����MM� */
	$"FF4D DEDE DEDE 4D4D 4DDE 4DDE DE4D 4DFF"            /* �M����MMM�M��MM� */
	$"FF4D DEDE 4DDE DE4D DEDE DEDE DEDE 4DFF"            /* �M��M��M������M� */
	$"FF4D DEDE 4DDE DE4D 4D4D 4DDE DE4D 4DFF"            /* �M��M��MMMM��MM� */
	$"FF4D 4DDE DEDE 4D4D 4D4D 4DDE DE4D 4DFF"            /* �MM���MMMMM��MM� */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* �MMMMMMMMMMMMMM� */
	$"FF4D 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D 4DFF"            /* �MMMMMMMMMMMMMM� */
	$"FFFF 4D4D 4D4D 4D4D 4D4D 4D4D 4D4D FFFF"            /* ��MMMMMMMMMMMM�� */
	$"00FF FF4D 4D4D 4D4D 4D4D 4D4D 4DFF FF00"            /* .��MMMMMMMMMM��. */
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF 0000"            /* ..������������.. */
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
	$"0080 4943 4E23 0000 0000 0080"                      /* .�ICN#.....� */
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
