/* Define header for application - AppBuilder 2.03  */

/* 'GmWindow' Window link */
extern const int ABN_GmWindow;
#define ABW_GmWindow                         AbGetABW( ABN_GmWindow )
extern const int ABN_GmRaw;
#define ABW_GmRaw                            AbGetABW( ABN_GmRaw )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

#define AB_OPTIONS "s:x:y:h:w:S:"
