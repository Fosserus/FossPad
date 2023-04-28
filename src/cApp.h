/*
Copyright 2023, Nathan Powell

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty, provided the copyright notice and this notice are preserved.
This file is offered as-is, without any warranty.

*/

#ifndef _CAPP_
#define _CAPP_

#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

public:
	virtual bool OnInit();

private:
	cMain* m_frame1 = nullptr;
	
};

#endif // _CAPP_

