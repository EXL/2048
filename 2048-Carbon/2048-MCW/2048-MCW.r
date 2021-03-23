#include "Types.r"

include "2048-MCW.µ.rsrc";

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
	1024 * 1024,
	1024 * 1024
};
