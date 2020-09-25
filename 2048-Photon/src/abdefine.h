/* Define header for application - AppBuilder 2.03  */

#include "abvars.h"

/* 'GmWindow' Window link */
#define ABW_GmWindow                         AbGetABW( ABN_GmWindow )
#define ABW_GmMenuButtonGame                 AbGetABW( ABN_GmMenuButtonGame )
#define ABW_GmMenuButtonView                 AbGetABW( ABN_GmMenuButtonView )
#define ABW_GmMenuButtonHelp                 AbGetABW( ABN_GmMenuButtonHelp )
#define ABW_GmRaw                            AbGetABW( ABN_GmRaw )

/* 'GmDialogAbout' Dialog link */
#define ABW_GmDialogAbout                    AbGetABW( ABN_GmDialogAbout )
#define ABW_GmLabelSource                    AbGetABW( ABN_GmLabelSource )
#define ABW_GmDialogAboutButton              AbGetABW( ABN_GmDialogAboutButton )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

/* 'GmMenuGame' Menu link */

/* 'GmMenuView' Menu link */

/* 'GmMenuHelp' Menu link */

#define AB_OPTIONS "s:x:y:h:w:S:"
