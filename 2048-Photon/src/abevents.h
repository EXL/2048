/* Event header for application - AppBuilder 2.03  */

static const ApEventLink_t AbApplLinks[] = {
	{ 3, 0, 0L, 0L, 0L, &GmWindow, NULL, NULL, 0, NULL, 0, 9, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_GmWindow[] = {
	{ 8, 1, 0L, 0L, 1L, NULL, NULL, "GmWindow", 1026, GmWindowKeyEventCb, 0, 0, 0, 0, },
	{ 8, 2, 61467L, 0L, 0L, NULL, NULL, "GmWindow", 1010, GmMenuItemResetCb, 0, 0, 0, 0, },
	{ 8, 2, 120L, 4L, 0L, NULL, NULL, "GmWindow", 1010, GmMenuItemQuitCb, 0, 0, 0, 0, },
	{ 5, 0, 0L, 0L, 0L, &GmMenuGame, NULL, "GmMenuButtonGame", 2007, NULL, 0, 1, 0, 0, },
	{ 5, 2, 103L, 4L, 0L, &GmMenuGame, NULL, "GmMenuButtonGame", 1010, NULL, 0, 1, 0, 0, },
	{ 5, 0, 0L, 0L, 0L, &GmMenuView, NULL, "GmMenuButtonView", 2007, NULL, 0, 1, 0, 0, },
	{ 5, 2, 118L, 4L, 0L, &GmMenuView, NULL, "GmMenuButtonView", 1010, NULL, 0, 1, 0, 0, },
	{ 5, 0, 0L, 0L, 0L, &GmMenuHelp, NULL, "GmMenuButtonHelp", 2007, NULL, 0, 1, 0, 0, },
	{ 5, 2, 104L, 4L, 0L, &GmMenuHelp, NULL, "GmMenuButtonHelp", 1010, NULL, 0, 1, 0, 0, },
	{ 8, 3, 0L, 0L, 0L, NULL, NULL, "GmRaw", 24003, (int(*)(PtWidget_t*,ApInfo_t*,PtCallbackInfo_t*)) GmRawInitCb, 0, 0, 0, 0, },
	{ 8, 3, 0L, 0L, 0L, NULL, NULL, "GmRaw", 24000, (int(*)(PtWidget_t*,ApInfo_t*,PtCallbackInfo_t*)) GmRawDrawCb, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_GmDialogAbout[] = {
	{ 8, 1, 0L, 0L, 2L, NULL, NULL, "GmLabelSource", 1026, GmSourceButtonEventCb, 0, 0, 0, 0, },
	{ 9, 0, 0L, 0L, 0L, NULL, NULL, "GmDialogAboutButton", 2009, NULL, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_GmMenuGame[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "GmMenuItemReset", 2009, GmMenuItemResetCb, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "GmMenuItemQuit", 2009, GmMenuItemQuitCb, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_GmMenuView[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "GmMenuItemBackground", 2009, GmMenuItemBackgroundCb, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "GmMenuItemTiles", 2009, GmMenuItemTilesCb, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "GmMenuItemFonts", 2009, GmMenuItemFontsCb, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_GmMenuHelp[] = {
	{ 4, 0, 0L, 0L, 0L, &GmDialogAbout, NULL, "GmMenuItemAbout", 2009, NULL, 0, 9, 0, 0, },
	{ 0 }
	};

const char ApOptions[] = AB_OPTIONS;
