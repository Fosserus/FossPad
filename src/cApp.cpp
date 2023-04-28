
/*
Copyright 2023, Nathan Powell

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty, provided the copyright notice and this notice are preserved.
This file is offered as-is, without any warranty.

*/

#include "cApp.h"
#include "../../FossPad/resource.h" // may vary depending on where resource.h is

wxIMPLEMENT_APP(cApp);



cApp::cApp() {

}

cApp::~cApp() {
	
}

bool cApp::OnInit() {

	wxInitAllImageHandlers();
	m_frame1 = new cMain();
	
	m_frame1->SetIcon(wxICON(aaaa));
	m_frame1->Show();
	
	return true;
}



