/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <Carbon.h>

const SInt16 kAlertID = 128;

class SimpleAlert
{
public:
	SimpleAlert();
	void Run();

private:
	void Initialize();
};

SimpleAlert::SimpleAlert()
{
	Initialize();
}

void SimpleAlert::Initialize()
{
	InitCursor();
}

void SimpleAlert::Run()
{
	NoteAlert(kAlertID, NULL);
}

void main(void)
{
	SimpleAlert theApplication;

	theApplication.Run();
}
