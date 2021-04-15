/*
 * Decompile resource file commands for MPW Shell:
 *  DeRez 2048-MCW.rsrc > Out.r
 *  DeRez -i "{RIncludes}" 2048-MCW.rsrc Types.r > OutTypes.r
 */

#include "Types.r"

include "2048-MCW.rsrc";

resource 'SIZE' (-1) {
	reserved,
	acceptSuspendResumeEvents,
	reserved,
	canBackground,
	doesActivateOnFGSwitch,
	reserved,
	reserved,
	reserved,
	is32BitCompatible,
	isHighLevelEventAware,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	1024 * 1024,                                            /* Preferred Memory Size. */
	1024 * 1024                                             /* Minimum Memory Size. */
};
