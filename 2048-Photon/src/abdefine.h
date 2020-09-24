/* Define header for application - AppBuilder 2.03  */

/* 'GmWindow' Window link */
extern const int ABN_GmWindow;
#define ABW_GmWindow                         AbGetABW( ABN_GmWindow )
extern const int ABN_GmMenuButtonGame;
#define ABW_GmMenuButtonGame                 AbGetABW( ABN_GmMenuButtonGame )
extern const int ABN_GmMenuButtonView;
#define ABW_GmMenuButtonView                 AbGetABW( ABN_GmMenuButtonView )
extern const int ABN_GmMenuButtonHelp;
#define ABW_GmMenuButtonHelp                 AbGetABW( ABN_GmMenuButtonHelp )
extern const int ABN_GmRaw;
#define ABW_GmRaw                            AbGetABW( ABN_GmRaw )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

/* 'GmMenuGame' Menu link */
extern const int ABN_GmMenuGame;
extern const int ABN_GmMenuItemReset;
extern const int ABN_GmMenuItemQuit;

/* 'GmMenuView' Menu link */
extern const int ABN_GmMenuView;
extern const int ABN_GmMenuItemBackground;
extern const int ABN_GmMenuItemTiles;
extern const int ABN_GmMenuItemFonts;

/* 'GmMenuHelp' Menu link */
extern const int ABN_GmMenuHelp;
extern const int ABN_GmMenuItemAbout;

#define AB_OPTIONS "s:x:y:h:w:S:"
