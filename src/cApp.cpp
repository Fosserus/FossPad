#include "cApp.h"
#include "../../FossPad/resource.h"

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



