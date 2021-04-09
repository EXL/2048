/*
 *  Contains some resources and permit this Carbon application to launch on OS X.
 *
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <Carbon.r>
#include <Dialogs.r>
#include <Icons.r>

/*---------------------------- dlgx ¥ Carbon on OS X about dialog information -------------------*/

resource 'dlgx' (128) {
	versionZero {
//		kDialogFlagsHandleMovableModal +
//		kDialogFlagsUseControlHierarchy
		kDialogFlagsUseThemeControls +
		kDialogFlagsUseThemeBackground
	}
};

/*---------------------------- icns ¥ Carbon on OS X icon information ---------------------------*/

// read 'icns' (-16455) "2048-Carbon.icns";

read 'icns' (128) "2048-Carbon.icns";

/*---------------------------- carb ¥ Carbon on OS X launch information -------------------------*/

type 'carb' {

};

resource 'carb' (0) {

};
