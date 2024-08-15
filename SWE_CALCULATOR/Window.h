#pragma once
#include "wx/wx.h"
#include <vector>

class Window : public wxFrame
{
private:
	//buttons
	wxButton* numButtons[10];
	wxButton* binButtons[5];
	wxButton* unaryButtons[3];
	wxButton* eqlButton = nullptr;
	wxButton* clrButton = nullptr;
	wxButton* delButton = nullptr;
	wxButton* decButton = nullptr;
	wxButton* negButton = nullptr;
	wxTextCtrl* display = nullptr;

public:
	//ctor
	Window();
	//event handler
	void OnButtonClicked(wxCommandEvent& evt);
	//calculates result
	double Calculate(const wxString& expression);
	
	//event table
	wxDECLARE_EVENT_TABLE();
};

