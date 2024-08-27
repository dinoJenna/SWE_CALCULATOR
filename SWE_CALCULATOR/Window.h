#pragma once
#include "wx/wx.h"

class Window : public wxFrame
{
private:
	//text display
	wxTextCtrl* display;
	//updated interface for calculator
	void CreateUI();
	//event handler
	void OnButtonClicked(wxCommandEvent& evt);

	//event table
	wxDECLARE_EVENT_TABLE();

public:
	//ctor
	Window();
};

