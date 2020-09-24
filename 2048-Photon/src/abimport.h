/* Import (extern) header for application - AppBuilder 2.03  */

#include "abdefine.h"

extern ApWindowLink_t GmWindow;
extern ApWidget_t AbWidgets[ 5 ];

extern ApMenuLink_t GmMenuGame;
extern ApMenuLink_t GmMenuView;
extern ApMenuLink_t GmMenuHelp;

#ifdef __cplusplus
extern "C" {
#endif
int GmMenuItemQuitCallback( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemResetCallback( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemResetCallback( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemQuitCallback( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmRawInit( PtWidget_t *widget ) 

;
void GmRawDraw( PtWidget_t *widget, PhTile_t *damage ) 

;
int GmWindowKeysCallback( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#ifdef __cplusplus
}
#endif
