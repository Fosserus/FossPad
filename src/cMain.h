#pragma once
#include "wx/wx.h"
#include <streambuf>
#include <wx/stc/stc.h>
#include <wx/file.h>
#include <wx/textfile.h>


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	
public:
	wxTextCtrl* m_txt = nullptr;
	wxMenuBar* m_MenuBar;
	wxBoxSizer* mainSizer;
	wxMenu* m_FileMenu;
	wxMenu* m_HelpMenu;
	wxMessageDialog* abtDialog;
	wxMessageDialog* saveDialog;

	
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& WXUNUSED(evt));
	void OnMenuQuit(wxCommandEvent& evt);
	void OnMenuAbout(wxCommandEvent& evt);
	void openFile();
	void saveFile();

	wxDECLARE_EVENT_TABLE();
};


