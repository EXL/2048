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
int GmMenuItemQuitCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemResetCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmRawInitCb( PtWidget_t *widget ) 

;
void GmRawDrawCb( PtWidget_t *widget, PhTile_t *damage ) 

;
int GmWindowKeyEventCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemResetCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemQuitCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemBackgroundCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemTilesCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int GmMenuItemFontsCb( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#ifdef __cplusplus
}
#endif
