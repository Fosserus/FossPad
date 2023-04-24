#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_EXIT, cMain::OnMenuQuit)
EVT_MENU(wxID_ABOUT, cMain::OnMenuAbout)
EVT_MENU(wxID_SAVEAS, cMain::OnMenuSaveAs)
EVT_MENU(wxID_SAVE, cMain::OnMenuSaveFile)
EVT_MENU(wxID_OPEN, cMain::OnMenuOpen)
EVT_TEXT(wxID_ANY, cMain::OnTextEdited)
wxEND_EVENT_TABLE()

/*TODO:
 * Work on adding font control?
 * Debug a little
 * */

	bool hasAppended = false;
	wxString m_currentFilePath;
	wxString m_fileName;


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
	m_FileMenu->Append(wxID_SAVEAS, _T("&Save As"));
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

	// managing shortcuts
	wxAcceleratorEntry entries[4];
	entries[0].Set(wxACCEL_CTRL, (int)'O', wxID_OPEN);
	entries[1].Set(wxACCEL_CTRL, (int)'S', wxID_SAVE);
	wxAcceleratorTable accel(2, entries);
	this->SetAcceleratorTable(accel);


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
				saveFileAs();
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
void cMain::OnMenuSaveAs(wxCommandEvent& WXUNUSED(evt)) {

	saveFileAs();
}

void cMain::OnMenuQuit(wxCommandEvent& evt) {
	if (!m_txt->IsEmpty() && m_txt->IsModified()) {
		saveDialog = new wxMessageDialog(this, "Do you want to save first?",
			"Save", wxYES_NO | wxCANCEL);

		switch (saveDialog->ShowModal()) {
		case wxID_YES:
			saveFileAs();
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
	else {
		Destroy();
	}
}



void cMain::OnMenuAbout(wxCommandEvent& evt) {
	abtDialog = new wxMessageDialog(this, "FossPad is a simple word processing app created by a cool dude.", 
		"About FossPad");
	if (abtDialog->ShowModal() == wxID_OK) {
		abtDialog->Destroy();
	}
}

void cMain::OnTextEdited(wxCommandEvent& evt) {
	if (!hasAppended && m_txt->IsModified()) {
		this->SetTitle(this->GetTitle() + "*");
		hasAppended = true;
	}
	

}

void cMain::openFile() {

	wxFileDialog openFileDialog(this, _("Open file"), "", "",
		"txt files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() != wxID_OK) {
		return;	
	}

	m_currentFilePath = openFileDialog.GetPath();


	m_fileName = openFileDialog.GetFilename();
	this->SetTitle(m_fileName + " | FossPad");

	m_txt->LoadFile(m_currentFilePath);
	hasAppended = false;
}

void cMain::saveFile() {
	if (m_currentFilePath.empty()) {
		saveFileAs();
	}
	else {
		this->SetTitle(m_fileName + " | FossPad");
		m_txt->SaveFile(m_currentFilePath);
		hasAppended = false;
	}

}

void cMain::saveFileAs() {
	wxFileDialog saveFileDialog(this, _("Save TXT file"), "", "",
		"TXT files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_OK) {
			m_currentFilePath = saveFileDialog.GetPath();
			m_fileName = saveFileDialog.GetFilename();
			this->SetTitle(m_fileName + " | FossPad");
			m_txt->SaveFile(m_currentFilePath);
			hasAppended = false;
	}
	else {
		return;
	}
	
}

void cMain::OnMenuSaveFile(wxCommandEvent& evt) {
	
	saveFile();
}

