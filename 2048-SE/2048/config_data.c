#include "..\\include\cfg_items.h"
#include "config_data.h"

#pragma diag_suppress = Pe177
CFGVAR CFG_HDR cfghdr1 = {CFG_CBOX, "Tile Style", 0, 2};
CFGVAR int tile_style = 0;
CFGVAR CFG_CBOX_ITEM cfgRadioBtn1[2] = {"Rectangle", "Rounded"};
