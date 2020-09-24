/* Link header for application - AppBuilder 2.03  */

extern ApContext_t AbContext;

ApWindowLink_t GmWindow = {
	"GmWindow.wgtw",
	&AbContext,
	AbLinks_GmWindow, 0, 11
	};

ApDialogLink_t GmDialogAbout = {
	"GmDialogAbout.wgtd",
	&AbContext,
	NULL, 5, 0
	};

static ApItem_t ApItems_GmMenuGame[ 4 ] = {
	{ 1, 1, 0,"ESC", 0, "GmMenuItemReset", "Reset", NULL },
	{ 1, 16, 0, NULL, 4, "", "", NULL },
	{ 1, 1, 4,"X", 0, "GmMenuItemQuit", "Quit", NULL },
	{ 0, 0, NULL, NULL, 0, NULL, NULL, NULL } };

ApMenuLink_t GmMenuGame = {
	"GmMenuGame",
	"",
	NULL,
	NULL,
	2,
	ApItems_GmMenuGame,
	& AbContext,
	AbLinks_GmMenuGame,
	6, 2, 3
	};

static ApItem_t ApItems_GmMenuView[ 4 ] = {
	{ 1, 4, 0, NULL, 0, "GmMenuItemBackground", "Background", NULL },
	{ 1, 4, 0, NULL, 0, "GmMenuItemTiles", "Round Tiles", NULL },
	{ 1, 4, 0, NULL, 0, "GmMenuItemFonts", "Smooth Fonts", NULL },
	{ 0, 0, NULL, NULL, 0, NULL, NULL, NULL } };

ApMenuLink_t GmMenuView = {
	"GmMenuView",
	"",
	NULL,
	NULL,
	2,
	ApItems_GmMenuView,
	& AbContext,
	AbLinks_GmMenuView,
	10, 3, 3
	};

static ApItem_t ApItems_GmMenuHelp[ 2 ] = {
	{ 1, 1, 0, NULL, 0, "GmMenuItemAbout", "About 2048-Photon...", NULL },
	{ 0, 0, NULL, NULL, 0, NULL, NULL, NULL } };

ApMenuLink_t GmMenuHelp = {
	"GmMenuHelp",
	"",
	NULL,
	NULL,
	2,
	ApItems_GmMenuHelp,
	& AbContext,
	AbLinks_GmMenuHelp,
	14, 1, 1
	};

