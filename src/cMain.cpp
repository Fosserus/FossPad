#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_EXIT, cMain::OnMenuQuit)
EVT_MENU(wxID_ABOUT, cMain::OnMenuAbout)
EVT_MENU(wxID_SAVE, cMain::OnMenuSave)
EVT_MENU(wxID_OPEN, cMain::OnMenuOpen)
wxEND_EVENT_TABLE()

/*TODO:
 * Test out functionality and write down any issues; then fix them.
 * Add quick save button, and rename save to save as
 * add asterisk if text is edited
 * */


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Untitled | FossPad", wxPoint(30, 30), wxSize(800, 600)) {
	// you can add items to be in the frame here
	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	m_txt = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize,
	wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
	
	mainSizer->Add(m_txt, 1, wxEXPAND);
	this->SetSizer(mainSizer);
	m_MenuBar = new wxMenuBar();
	
	// File Menu
	m_FileMenu = new wxMenu();
	m_FileMenu->Append(wxID_OPEN, _T("&Open"));
	m_FileMenu->Append(wxID_SAVE, _T("&Save"));
	m_FileMenu->AppendSeparator();
	m_FileMenu->Append(wxID_EXIT, _T("&Quit"));
	// append all to menubar
	m_MenuBar->Append(m_FileMenu, _T("&File"));

	// Help Menu
	m_HelpMenu = new wxMenu();
	m_HelpMenu->Append(wxID_ABOUT, _T("&About"));
	// append all to menubar
	m_MenuBar->Append(m_HelpMenu, _T("&Help"));

	
	SetMenuBar(m_MenuBar);
}

cMain::~cMain() {
	Destroy();
}



void cMain::OnMenuOpen(wxCommandEvent& evt) {

	if (!m_txt->IsEmpty() && m_txt->IsModified()) {
		saveDialog = new wxMessageDialog(this, "Do you want to save first?",
			"Save", wxYES_NO | wxCANCEL);

		switch (saveDialog->ShowModal()) {
			case wxID_YES:
				saveFile();
				break;
			case wxID_NO:
				openFile();
				break;
			case wxID_CANCEL:
				return;
			default:
				return;
		} 
	}
	else {
		openFile();
	}
}
void cMain::OnMenuSave(wxCommandEvent& WXUNUSED(evt)) {

	saveFile();
}

void cMain::OnMenuQuit(wxCommandEvent& evt) {
	if (!m_txt->IsEmpty() && m_txt->IsModified()) {
		saveDialog = new wxMessageDialog(this, "Do you want to save first?",
			"Save", wxYES_NO | wxCANCEL);

		switch (saveDialog->ShowModal()) {
		case wxID_YES:
			saveFile();
			break;
		case wxID_NO:
			Destroy();
			break;
		case wxID_CANCEL:
			return;
		default:
			return; 
		}
	}
}



void cMain::OnMenuAbout(wxCommandEvent& evt) {
	abtDialog = new wxMessageDialog(this, "FossPad is a simple word processing app created by a cool dude.", 
		"About FossPad");
	if (abtDialog->ShowModal() == wxID_OK) {
		abtDialog->Destroy();
	}
}

void cMain::openFile() {
	wxString file;

	wxFileDialog openFileDialog(this, _("Open file"), "", "",
		"txt files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() != wxID_OK) {
		return;	
	}

	file = openFileDialog.GetPath();


	wxString filename = openFileDialog.GetFilename();
	this->SetTitle(filename + " | FossPad");

	m_txt->LoadFile(file);
}

void cMain::saveFile() {
	wxFileDialog saveFileDialog(this, _("Save TXT file"), "", "",
		"TXT files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_OK) {
			wxString file = saveFileDialog.GetPath();
			m_txt->SaveFile(file);
	}
	else {
		return;
	}
	
}
