
/* 2048.c */

/* GmMenuItemsCbs.c */
int GmMenuItemQuitCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int GmMenuItemResetCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int GmMenuItemBackgroundCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int GmMenuItemTilesCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );
int GmMenuItemFontsCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* GmRawDrawCb.c */
void GmRawDrawCb ( PtWidget_t *widget , PhTile_t *damage );

/* GmRawInitCb.c */
void GmFontsSetAntialias ( int antialias );
int GmRawInitCb ( PtWidget_t *widget );

/* GmSourceButtonEventCb.c */
int GmSourceButtonEventCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* GmWindowKeyEventCb.c */
int GmWindowKeyEventCb ( PtWidget_t *widget , ApInfo_t *apinfo , PtCallbackInfo_t *cbinfo );

/* abmain.c */
